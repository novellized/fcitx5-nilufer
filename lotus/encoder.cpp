#include "encoder.h"
#include "utf8.h"

namespace lotus {

    std::string encode(Charset /*charset*/, std::u32string_view text) {
        return utf8::encode(text);
    }

} // namespace lotus
