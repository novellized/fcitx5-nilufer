#include "input_method.h"

namespace lotus {

    InputMethod parseInputMethod(const std::unordered_map<std::string, std::string>& /*definition*/) {
        InputMethod im;
        im.keys = {U'w', U'W'};
        return im;
    }

    const InputMethod& cachedInputMethod(InputMethodId /*id*/) {
        static const InputMethod im{.keys = {U'w', U'W'}};
        return im;
    }

} // namespace lotus
