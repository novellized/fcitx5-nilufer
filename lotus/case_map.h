#ifndef _LOTUS_CASE_MAP_H_
#define _LOTUS_CASE_MAP_H_

#include <string>
#include <string_view>

namespace lotus::case_map {

    /**
     * @brief Lowercases a code point with Turkish support.
     * @param codePoint Input code point.
     * @return Lowercase code point.
     */
    char32_t toLower(char32_t codePoint);

    /**
     * @brief Uppercases a code point with Turkish support.
     * @param codePoint Input code point.
     * @return Uppercase code point.
     */
    char32_t toUpper(char32_t codePoint);

    /**
     * @brief Reports whether a code point is an uppercase letter.
     * @param codePoint Input code point.
     * @return True when the code point is uppercase.
     */
    bool isUpper(char32_t codePoint);

    /**
     * @brief Reports whether a code point is a lowercase letter.
     * @param codePoint Input code point.
     * @return True when the code point is lowercase.
     */
    bool isLower(char32_t codePoint);

    /**
     * @brief Reports whether a code point is an alphabetic letter.
     * @param codePoint Input code point.
     * @return True when the code point is a letter.
     */
    bool isLetter(char32_t codePoint);

    /**
     * @brief Lowercases every code point of a text.
     * @param text Input code points.
     * @return Lowercased code points.
     */
    std::u32string toLower(std::u32string_view text);

    /**
     * @brief Uppercases every code point of a text.
     * @param text Input code points.
     * @return Uppercased code points.
     */
    std::u32string toUpper(std::u32string_view text);

} // namespace lotus::case_map

#endif // _LOTUS_CASE_MAP_H_
