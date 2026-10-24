#ifndef _LOTUS_INPUT_METHOD_H_
#define _LOTUS_INPUT_METHOD_H_

#include "data/input_method_data.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace lotus {

    using data::InputMethodId;
    using data::kInputMethodCount;

    struct InputMethod {
        std::vector<char32_t> keys;
    };

    InputMethod parseInputMethod(const std::unordered_map<std::string, std::string>& definition);
    const InputMethod& cachedInputMethod(InputMethodId id);

} // namespace lotus

#endif // _LOTUS_INPUT_METHOD_H_
