#ifndef _LOTUS_TYPES_H_
#define _LOTUS_TYPES_H_

#include <cstdint>

namespace lotus {

    /** @brief Typing modes (bit flags). */
    enum class Mode : uint8_t {
        TurkishMode     = 1U << 0U,
        VietnameseMode  = 1U << 0U, // Kept as alias for src compatibility
        EnglishMode     = 1U << 1U,
        ToneLess        = 1U << 2U,
        MarkLess        = 1U << 3U,
        LowerCase       = 1U << 4U,
        FullText        = 1U << 5U,
        PunctuationMode = 1U << 6U,
        InReverseOrder  = 1U << 7U,
    };

    template <typename Flag>
    struct FlagSet {
        uint32_t bits = 0U;

        constexpr FlagSet() = default;
        constexpr FlagSet(Flag flag) : bits(static_cast<uint32_t>(flag)) {}
        explicit constexpr FlagSet(uint32_t mask) : bits(mask) {}

        [[nodiscard]] constexpr bool has(Flag flag) const {
            return (bits & static_cast<uint32_t>(flag)) != 0U;
        }

        constexpr FlagSet& add(Flag flag) {
            bits |= static_cast<uint32_t>(flag);
            return *this;
        }

        constexpr FlagSet& remove(Flag flag) {
            bits &= ~static_cast<uint32_t>(flag);
            return *this;
        }

        [[nodiscard]] constexpr bool intersects(FlagSet other) const {
            return (bits & other.bits) != 0U;
        }
    };

    using ModeSet = FlagSet<Mode>;

    template <typename Flag>
    constexpr FlagSet<Flag> operator|(Flag first, Flag second) {
        return FlagSet<Flag>{static_cast<uint32_t>(first) | static_cast<uint32_t>(second)};
    }

    template <typename Flag>
    constexpr FlagSet<Flag> operator|(FlagSet<Flag> set, Flag flag) {
        return FlagSet<Flag>{set.bits | static_cast<uint32_t>(flag)};
    }

    template <typename Flag>
    constexpr FlagSet<Flag> operator|(FlagSet<Flag> first, FlagSet<Flag> second) {
        return FlagSet<Flag>{first.bits | second.bits};
    }

    enum class EngineFlag : uint8_t {
        ModernTonePlacement     = 1U << 0U,
        FreeToneMarking         = 1U << 1U,
        W2uEnabled              = 1U << 2U,
        BracketTransformEnabled = 1U << 3U,
    };

    using EngineFlags = FlagSet<EngineFlag>;

    enum class W2uMode : uint8_t {
        Disabled   = 0,
        NonStart   = 1,
        Everywhere = 2,
    };

    enum class BracketTransformMode : uint8_t {
        Disabled   = 0,
        NonStart   = 1,
        Everywhere = 2,
    };

    enum class KeyState : uint32_t {
        Shift   = 1U << 0U,  ///< Shift (fcitx5 KeyState::Shift).
        Lock    = 1U << 1U,  ///< Caps Lock (fcitx5 KeyState::CapsLock).
        Ctrl    = 1U << 2U,  ///< Control (fcitx5 KeyState::Ctrl).
        Mod1    = 1U << 3U,  ///< Alt (fcitx5 KeyState::Alt / Mod1).
        Ignored = 1U << 25U, ///< fcitx5 KeyState::IgnoredMask, the Go forward mask.
        Super   = 1U << 26U, ///< Gtk virtual Super (fcitx5 KeyState::Super2).
        Hyper   = 1U << 27U, ///< Gtk virtual Hyper (fcitx5 KeyState::Hyper2).
        Meta    = 1U << 28U, ///< Meta (fcitx5 KeyState::Meta).
    };

    using KeyStates = FlagSet<KeyState>;

    inline constexpr KeyStates kInvalidStates = KeyState::Ctrl | KeyState::Mod1 | KeyState::Ignored | KeyState::Super | KeyState::Hyper | KeyState::Meta;

    constexpr KeyStates        keyStatesFromBits(uint32_t bits) {
        return KeyStates{bits};
    }

    constexpr ModeSet toMask(Mode mode) {
        return ModeSet{static_cast<uint32_t>(mode)};
    }

} // namespace lotus

#endif // _LOTUS_TYPES_H_
