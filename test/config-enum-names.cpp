// SPDX-FileCopyrightText: 2026 Nguyen Hoang Ky <nhktmdzhg@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// The engine stores the output charset and the input method as enums; the strings live in the
// configuration (FCITX_CONFIG_ENUM_NAME in lotus-config.h). This test pins that the strings users
// already have in lotus.conf keep resolving to the same enum values, that the configuration writes
// those strings back, and that the names are not translated.
#include "lotus-config.h"

#include <fcitx-config/iniparser.h>

#include <array>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

namespace {

    int  failures = 0;

    void check(const char* name, bool condition) {
        if (!condition) {
            std::printf("FAIL %s\n", name);
            ++failures;
        }
    }

    /** @brief Reads a whole file as text. */
    std::string readText(const std::filesystem::path& path) {
        std::ifstream file(path);
        return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    }

    /**
     * @brief Saves the typed configuration and reads it back, like fcitx5 does around a restart.
     *
     * The file work lives here so the exception-escape check keeps `runConfigEnumNames` free of
     * throwing calls, and it uses a temporary file: the user configuration is never touched.
     * @param config Configuration to write.
     * @param savedText Output content of the written file.
     * @return Configuration read back from the file.
     */
    fcitx::lotusConfig roundTrip(const fcitx::lotusConfig& config, std::string& savedText) {
        const auto path = std::filesystem::temp_directory_path() / "lotus-config-enum-names.conf";
        check("config saves", fcitx::safeSaveAsIni(config, path.string()));
        savedText = readText(path);
        fcitx::lotusConfig reloaded;
        fcitx::readAsIni(reloaded, path.string());
        std::filesystem::remove(path);
        return reloaded;
    }

} // namespace

int runConfigEnumNames() {
    fcitx::RawConfig   raw;
    fcitx::lotusConfig config;
    raw.setValueByPath("OutputCharset", "Unicode");
    raw.setValueByPath("InputMethod", "Turkish Telex");
    config.load(raw, true);

    check("OutputCharset resolves", config.outputCharset.value() == fcitx::Charset::Unicode);
    check("InputMethod resolves", config.inputMethod.value() == fcitx::InputMethodId::TurkishTelex);

    std::string        savedText;
    fcitx::lotusConfig reloaded = roundTrip(config, savedText);
    check("file keeps the charset name", savedText.find("Unicode") != std::string::npos);
    check("file keeps the input method name", savedText.find("Turkish Telex") != std::string::npos);
    check("reloaded OutputCharset value", *reloaded.outputCharset == fcitx::Charset::Unicode);
    check("reloaded InputMethod value", *reloaded.inputMethod == fcitx::InputMethodId::TurkishTelex);

    check("charset names", fcitx::CharsetToString(fcitx::Charset::Unicode) == "Unicode");
    check("input method names",
          fcitx::InputMethodIdToString(fcitx::InputMethodId::TurkishTelex) == "Turkish Telex" && fcitx::InputMethodIdToString(fcitx::InputMethodId::Custom) == "Custom");

    constexpr std::array<std::string_view, lotus::kCharsetCount> kExpectedCharsets = {
        "Unicode",
    };
    constexpr std::array<std::string_view, lotus::kInputMethodCount> kExpectedInputMethods = {
        "Turkish Telex",
        "Custom",
    };
    for (std::size_t i = 0; i < kExpectedCharsets.size(); ++i) {
        check("charset config name", fcitx::CharsetToString(static_cast<fcitx::Charset>(i)) == kExpectedCharsets.at(i));
    }
    for (std::size_t i = 0; i < kExpectedInputMethods.size(); ++i) {
        check("input method config name", fcitx::InputMethodIdToString(static_cast<fcitx::InputMethodId>(i)) == kExpectedInputMethods.at(i));
    }

    fcitx::RawConfig description;
    config.inputMethod.dumpDescription(description);
    const std::string* launchSubConfig = description.valueByPath("LaunchSubConfig");
    check("custom keymap keeps its sub-config", launchSubConfig != nullptr && *launchSubConfig == "True");
    const std::string* lastName = description.valueByPath("Enum/1");
    check("input method list has Custom last", lastName != nullptr && *lastName == "Custom");
    check("enum names are not translated", description.valueByPath("EnumI18n/0") == nullptr);

    if (failures != 0) {
        std::printf("%d failure(s)\n", failures);
        return 1;
    }
    std::printf("config enum names: all checks passed\n");
    return 0;
}

int main() {
    try {
        return runConfigEnumNames();
    } catch (const std::exception& error) {
        std::printf("FAIL unexpected exception: %s\n", error.what());
        return 1;
    }
}
