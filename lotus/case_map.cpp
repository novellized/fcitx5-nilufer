#include "case_map.h"

namespace lotus::case_map {

    char32_t toLower(char32_t codePoint) {
        if (codePoint >= U'A' && codePoint <= U'Z') {
            if (codePoint == U'I') {
                return U'ı'; // Turkish dotless I -> ı
            }
            return codePoint - U'A' + U'a';
        }
        switch (codePoint) {
            case U'Ç': return U'ç';
            case U'Ş': return U'ş';
            case U'Ğ': return U'ğ';
            case U'Ü': return U'ü';
            case U'Ö': return U'ö';
            case U'İ': return U'i'; // Turkish capital I with dot -> i
            default:   return codePoint;
        }
    }

    char32_t toUpper(char32_t codePoint) {
        if (codePoint >= U'a' && codePoint <= U'z') {
            if (codePoint == U'i') {
                return U'İ'; // Turkish dotted i -> İ
            }
            return codePoint - U'a' + U'A';
        }
        switch (codePoint) {
            case U'ç': return U'Ç';
            case U'ş': return U'Ş';
            case U'ğ': return U'Ğ';
            case U'ü': return U'Ü';
            case U'ö': return U'Ö';
            case U'ı': return U'I'; // Turkish dotless ı -> I
            default:   return codePoint;
        }
    }

    bool isUpper(char32_t codePoint) {
        if (codePoint >= U'A' && codePoint <= U'Z') return true;
        switch (codePoint) {
            case U'Ç':
            case U'Ş':
            case U'Ğ':
            case U'Ü':
            case U'Ö':
            case U'İ':
                return true;
            default:
                return false;
        }
    }

    bool isLower(char32_t codePoint) {
        if (codePoint >= U'a' && codePoint <= U'z') return true;
        switch (codePoint) {
            case U'ç':
            case U'ş':
            case U'ğ':
            case U'ü':
            case U'ö':
            case U'ı':
                return true;
            default:
                return false;
        }
    }

    bool isLetter(char32_t codePoint) {
        return isUpper(codePoint) || isLower(codePoint);
    }

    std::u32string toLower(std::u32string_view text) {
        std::u32string result;
        result.reserve(text.size());
        for (char32_t ch : text) {
            result.push_back(toLower(ch));
        }
        return result;
    }

    std::u32string toUpper(std::u32string_view text) {
        std::u32string result;
        result.reserve(text.size());
        for (char32_t ch : text) {
            result.push_back(toUpper(ch));
        }
        return result;
    }

} // namespace lotus::case_map
