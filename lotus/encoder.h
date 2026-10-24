#ifndef _LOTUS_ENCODER_H_
#define _LOTUS_ENCODER_H_

#include "data/charset_data.h"

#include <string>
#include <string_view>

namespace lotus {

    using data::Charset;
    using data::kCharsetCount;

    /**
     * @brief Encodes engine text in Unicode (UTF-8).
     * @param charset Output charset (Unicode).
     * @param text Engine text in UTF-32.
     * @return Encoded UTF-8 string.
     */
    std::string encode(Charset charset, std::u32string_view text);

} // namespace lotus

#endif // _LOTUS_ENCODER_H_
