#include "presentation.h"

#include "imgui.h"

#include <cstring>
#include <string>

namespace {

// safe strncpy that always nul-terminates
void copyStringIntoFixedBuffer(char* destinationBuffer,
                               std::size_t destinationBufferSize,
                               const std::string& sourceString) {
    if (destinationBufferSize == 0) {
        return;
    }
    const std::size_t copyableCharacterCount =
        std::min(sourceString.size(), destinationBufferSize - 1);
    std::memcpy(destinationBuffer, sourceString.data(), copyableCharacterCount);
    destinationBuffer[copyableCharacterCount] = '\0';
}