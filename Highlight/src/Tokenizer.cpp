#include "../include/Tokenizer.h"
#include <sstream>

std::vector<std::wstring> Tokenizer::tokenize (const std::wstring& stringInput, const wchar_t delimiter = L' ') {
    std::vector<std::wstring> tokens;
    std::wistringstream wiss(stringInput);
    std::wstring token;

    while (std::getline(wiss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}