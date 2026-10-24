#ifndef _LOTUS_KEY_PROCESSOR_H_
#define _LOTUS_KEY_PROCESSOR_H_

#include "dictionary.h"
#include "encoder.h"
#include "input_method.h"
#include "macro_table.h"
#include "types.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace lotus {

    inline constexpr uint32_t kFcitxBackSpace = 0xFF08U;
    inline constexpr uint32_t kFcitxSpace     = 0x020U;
    inline constexpr uint32_t kFcitxTab       = 0xFF09U;
    inline constexpr uint32_t kFcitxReturn    = 0xFF0DU;
    inline constexpr uint32_t kFcitxKP_Enter  = 0xFF8DU;

    struct Options {
        bool    autoNonVnRestore    = false;
        bool    ddFreeStyle         = false;
        bool    macroEnabled        = false;
        bool    autoCapitalizeMacro = false;
        bool    spellCheckWithDicts = false;
        bool    modernStyle         = false;
        bool    freeMarking         = false;
        Charset outputCharset       = Charset::Unicode;
        std::optional<W2uMode>              w2u              = std::nullopt;
        std::optional<BracketTransformMode> bracketTransform = std::nullopt;
        std::string                         timeFormat       = "%H:%M";
        std::string                         dateFormat       = "%d/%m/%Y";
    };

    struct KeyNode {
        char32_t displayChar = 0;
        char32_t rawBaseChar = 0;
        bool isTransformed = false;
    };

    /**
     * @brief Turkish Telex input processor for Nilüfer.
     */
    class KeyProcessor {
      public:
        KeyProcessor();
        explicit KeyProcessor(InputMethod inputMethod, bool spellCheckWithDictsDefault = false);

        void setOptions(const Options& options);
        [[nodiscard]] Options& options();
        [[nodiscard]] const Options& options() const;

        void setMacroEnabled(bool enabled);
        void setShouldRestoreKeyStrokes(bool restore);
        [[nodiscard]] bool shouldRestoreKeyStrokes() const;

        void setMacroTable(std::shared_ptr<const MacroTable> table);
        void setDictionary(std::shared_ptr<const Dictionary> dictionary);

        bool processKey(uint32_t keyVal, KeyStates states);
        [[nodiscard]] bool canProcessKey(uint32_t keyVal) const;
        [[nodiscard]] static bool isValidState(KeyStates states);

        [[nodiscard]] const std::u32string& preedit() const;
        std::u32string takeCommit();
        void commitPreedit();
        void reset();
        void rebuildFromText(std::u32string_view text);

        [[nodiscard]] bool isCompositionEmpty() const;
        static std::string formatTime(const std::string& layout);

      private:
        void rebuildPreedit();
        bool isWordBreak(char32_t ch) const;
        std::u32string expandMacro(std::u32string_view trigger, std::u32string_view replacement) const;

        Options options_{};
        bool shouldRestoreKeyStrokes_ = false;
        std::shared_ptr<const MacroTable> macroTable_ = nullptr;
        std::shared_ptr<const Dictionary> dictionary_ = nullptr;

        std::vector<KeyNode> nodes_;
        std::u32string preedit_;
        std::u32string commit_;
    };

} // namespace lotus

#endif // _LOTUS_KEY_PROCESSOR_H_
