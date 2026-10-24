#ifndef _LOTUS_GENERATED_CHARSET_DATA_H_
#define _LOTUS_GENERATED_CHARSET_DATA_H_

#include <cstddef>
#include <cstdint>

namespace lotus::data {
    /** @brief Output charsets: only Unicode is used. */
    enum class Charset : std::uint8_t {
        Unicode = 0,
    };

    /** @brief Number of Charset values. */
    inline constexpr std::size_t kCharsetCount = 1U;
} // namespace lotus::data

#endif // _LOTUS_GENERATED_CHARSET_DATA_H_
