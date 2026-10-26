#include "key_processor.h"

#include "case_map.h"
#include <ctime>

namespace lotus {

    namespace {

        constexpr char32_t transformTurkish(char32_t base, char32_t w_key) {
            (void)w_key;
            switch (base) {
                case U'c': return U'ç';
                case U'C': return U'Ç';
                case U's': return U'ş';
                case U'S': return U'Ş';
                case U'g': return U'ğ';
                case U'G': return U'Ğ';
                case U'u': return U'ü';
                case U'U': return U'Ü';
                case U'o': return U'ö';
                case U'O': return U'Ö';
                case U'i': return U'ı';
                case U'I': return U'İ';
                default: return 0;
            }
        }

        constexpr char32_t turkishBaseOf(char32_t ch) {
            switch (ch) {
                case U'ç': return U'c';
                case U'Ç': return U'C';
                case U'ş': return U's';
                case U'Ş': return U'S';
                case U'ğ': return U'g';
                case U'Ğ': return U'G';
                case U'ü': return U'u';
                case U'Ü': return U'U';
                case U'ö': return U'o';
                case U'Ö': return U'O';
                case U'ı': return U'i';
                case U'İ': return U'I';
                default: return 0;
            }
        }

    } // namespace

    KeyProcessor::KeyProcessor() = default;

    KeyProcessor::KeyProcessor(InputMethod, bool) {}

    void KeyProcessor::setOptions(const Options& options) {
        options_ = options;
    }

    Options& KeyProcessor::options() {
        return options_;
    }

    const Options& KeyProcessor::options() const {
        return options_;
    }

    void KeyProcessor::setMacroEnabled(bool enabled) {
        options_.macroEnabled = enabled;
    }

    void KeyProcessor::setShouldRestoreKeyStrokes(bool restore) {
        shouldRestoreKeyStrokes_ = restore;
    }

    bool KeyProcessor::shouldRestoreKeyStrokes() const {
        return shouldRestoreKeyStrokes_;
    }

    void KeyProcessor::setMacroTable(std::shared_ptr<const MacroTable> table) {
        macroTable_ = std::move(table);
    }

    void KeyProcessor::setDictionary(std::shared_ptr<const Dictionary> dictionary) {
        dictionary_ = std::move(dictionary);
    }

    bool KeyProcessor::isValidState(KeyStates states) {
        return !states.intersects(kInvalidStates);
    }

    bool KeyProcessor::canProcessKey(uint32_t keyVal) const {
        if (keyVal == kFcitxBackSpace || keyVal == kFcitxSpace || keyVal == kFcitxReturn || keyVal == kFcitxKP_Enter || keyVal == kFcitxTab) {
            return true;
        }
        if (keyVal >= 32 && keyVal < 127) {
            return true;
        }
        if (turkishBaseOf(static_cast<char32_t>(keyVal)) != 0) {
            return true;
        }
        return false;
    }

    bool KeyProcessor::isCompositionEmpty() const {
        return nodes_.empty();
    }

    std::string KeyProcessor::formatTime(const std::string& layout) {
        std::time_t now = std::time(nullptr);
        std::tm     tmNow{};
#if defined(_WIN32)
        localtime_s(&tmNow, &now);
#else
        localtime_r(&now, &tmNow);
#endif
        char buf[128];
        if (layout == "15") {
            std::snprintf(buf, sizeof(buf), "%02d", tmNow.tm_hour);
            return buf;
        }
        std::strftime(buf, sizeof(buf), layout.c_str(), &tmNow);
        return buf;
    }

    const std::u32string& KeyProcessor::preedit() const {
        return preedit_;
    }

    std::u32string KeyProcessor::takeCommit() {
        std::u32string out = std::move(commit_);
        commit_.clear();
        return out;
    }

    void KeyProcessor::commitPreedit() {
        commit_ = preedit_;
        reset();
    }

    void KeyProcessor::reset() {
        nodes_.clear();
        preedit_.clear();
    }

    void KeyProcessor::rebuildPreedit() {
        preedit_.clear();
        preedit_.reserve(nodes_.size());
        for (const auto& node : nodes_) {
            preedit_.push_back(node.displayChar);
        }
    }

    bool KeyProcessor::isWordBreak(char32_t ch) const {
        if (ch == U' ' || ch == U'\t' || ch == U'\n' || ch == U'\r')
            return true;
        if (ch >= 33 && ch <= 47)
            return true; // ! " # $ % & ' ( ) * + , - . /
        if (ch >= 58 && ch <= 64)
            return true; // : ; < = > ? @
        if (ch >= 91 && ch <= 96)
            return true; // [ \ ] ^ _ `
        if (ch >= 123 && ch <= 126)
            return true; // { | } ~
        return false;
    }

    std::u32string KeyProcessor::expandMacro(std::u32string_view trigger, std::u32string_view replacement) const {
        if (!options_.autoCapitalizeMacro) {
            return std::u32string(replacement);
        }

        bool allUpper = true;
        for (char32_t ch : trigger) {
            if (case_map::isLower(ch))
                allUpper = false;
        }

        if (allUpper && !trigger.empty()) {
            return case_map::toUpper(replacement);
        }
        return std::u32string(replacement);
    }

    void KeyProcessor::rebuildFromText(std::u32string_view text) {
        reset();
        for (char32_t ch : text) {
            char32_t base = turkishBaseOf(ch);
            if (base != 0) {
                nodes_.push_back(KeyNode{.displayChar = ch, .rawBaseChar = base, .isTransformed = true});
            } else {
                nodes_.push_back(KeyNode{.displayChar = ch, .rawBaseChar = ch, .isTransformed = false});
            }
        }
        rebuildPreedit();
    }

    bool KeyProcessor::processKey(uint32_t keyVal, KeyStates states) {
        if (!isValidState(states)) {
            commitPreedit();
            return false;
        }

        if (keyVal == kFcitxBackSpace) {
            if (nodes_.empty()) {
                return false;
            }
            nodes_.pop_back();
            rebuildPreedit();
            return true;
        }

        if (keyVal == kFcitxReturn || keyVal == kFcitxKP_Enter) {
            if (nodes_.empty()) {
                return false;
            }
            commitPreedit();
            return true;
        }

        if (keyVal == kFcitxSpace) {
            if (nodes_.empty()) {
                return false;
            }
            if (options_.macroEnabled && macroTable_ != nullptr) {
                if (const auto macroVal = macroTable_->get(preedit_)) {
                    commit_ = expandMacro(preedit_, *macroVal);
                    commit_.push_back(U' ');
                    reset();
                    return true;
                }
            }
            commit_ = preedit_;
            commit_.push_back(U' ');
            reset();
            return true;
        }

        if (keyVal == kFcitxTab) {
            if (options_.macroEnabled && macroTable_ != nullptr && !nodes_.empty()) {
                if (const auto macroVal = macroTable_->get(preedit_)) {
                    commit_ = expandMacro(preedit_, *macroVal);
                    reset();
                    return true;
                }
            }
            if (!nodes_.empty()) {
                commitPreedit();
                return false;
            }
            return false;
        }

        if (keyVal < 32) {
            if (!nodes_.empty()) {
                commitPreedit();
            }
            return false;
        }

        char32_t keyChar = static_cast<char32_t>(keyVal);

        if (states.has(KeyState::Lock)) {
            if (keyChar >= U'a' && keyChar <= U'z') {
                keyChar = keyChar - U'a' + U'A';
            }
        }

        if (isWordBreak(keyChar)) {
            if (!nodes_.empty()) {
                if (options_.macroEnabled && macroTable_ != nullptr) {
                    if (const auto macroVal = macroTable_->get(preedit_)) {
                        commit_ = expandMacro(preedit_, *macroVal);
                        commit_.push_back(keyChar);
                        reset();
                        return true;
                    }
                }
                commit_ = preedit_;
                commit_.push_back(keyChar);
                reset();
                return true;
            }
            return false;
        }

        // Turkish Telex: 'w' or 'W' as modifier
        if (keyChar == U'w' || keyChar == U'W') {
            if (!nodes_.empty()) {
                KeyNode& last = nodes_.back();
                if (last.isTransformed) {
                    // Revert transformation: e.g. ç -> cw, Ç -> Cw / CW
                    last.displayChar   = last.rawBaseChar;
                    last.isTransformed = false;
                    nodes_.push_back(KeyNode{.displayChar = keyChar, .rawBaseChar = keyChar, .isTransformed = false});
                    rebuildPreedit();
                    return true;
                } else {
                    char32_t transformed = transformTurkish(last.displayChar, keyChar);
                    if (transformed != 0) {
                        last.rawBaseChar   = last.displayChar;
                        last.displayChar   = transformed;
                        last.isTransformed = true;
                        rebuildPreedit();
                        return true;
                    } else {
                        nodes_.push_back(KeyNode{.displayChar = keyChar, .rawBaseChar = keyChar, .isTransformed = false});
                        rebuildPreedit();
                        return true;
                    }
                }
            } else {
                nodes_.push_back(KeyNode{.displayChar = keyChar, .rawBaseChar = keyChar, .isTransformed = false});
                rebuildPreedit();
                return true;
            }
        }

        // Regular character
        nodes_.push_back(KeyNode{.displayChar = keyChar, .rawBaseChar = keyChar, .isTransformed = false});
        rebuildPreedit();
        return true;
    }

} // namespace lotus
