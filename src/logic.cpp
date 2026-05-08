#include "logic.h"

#include <algorithm>
#include <cctype>
#include <string>

namespace {

// lowercase ascii copy, used for case-insensitive compares and search
std::string toLowerCopy(const std::string& original) {
    std::string lowered(original.size(), '\0');
    for (std::size_t characterIndex = 0; characterIndex < original.size(); ++characterIndex) {
        lowered[characterIndex] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(original[characterIndex])));
    }
    return lowered;
}
// order contacts by (lastName, firstName), case-insensitive
bool isContactLessByName(const Contact& leftContact, const Contact& rightContact) {
    const std::string leftLast  = toLowerCopy(leftContact.lastName);
    const std::string rightLast = toLowerCopy(rightContact.lastName);
    if (leftLast != rightLast) {
        return leftLast < rightLast;
    }
    return toLowerCopy(leftContact.firstName) < toLowerCopy(rightContact.firstName);
}