#include "../include/Tokenizer.h"
#include <sstream>


std::vector<std::wstring> Tokenizer::tokenize (const std::wstring& stringInput) {
    std::vector<std::wstring> tokens;
    std::wistringstream wiss(stringInput);
    std::wstring token;

    while (wiss >> std::ws >> token) {
        tokens.push_back(token);
    }
    return tokens;
}