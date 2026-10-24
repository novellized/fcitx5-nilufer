#ifndef _LOTUS_GENERATED_INPUT_METHOD_DATA_H_
#define _LOTUS_GENERATED_INPUT_METHOD_DATA_H_

#include <cstddef>
#include <cstdint>

namespace lotus::data {
    /** @brief Input methods for Nilüfer (Turkish Telex). */
    enum class InputMethodId : std::uint8_t {
        TurkishTelex = 0,
        Telex        = 0, ///< Alias for test compatibility
        Custom       = 1,
    };

    /** @brief Number of InputMethodId values. */
    inline constexpr std::size_t kInputMethodCount = 2U;
} // namespace lotus::data

#endif // _LOTUS_GENERATED_INPUT_METHOD_DATA_H_
