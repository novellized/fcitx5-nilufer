#include "input_method.h"

namespace lotus {

    InputMethod parseInputMethod(const std::unordered_map<std::string, std::string>&) {
        InputMethod im;
        im.keys = {U'w', U'W'};
        return im;
    }

    const InputMethod& cachedInputMethod(InputMethodId) {
        static const InputMethod im{ .keys = {U'w', U'W'} };
        return im;
    }

} // namespace lotus
