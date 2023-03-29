#pragma once

#include <string>
#include <vector>

class Tokenizer {
public:
    static std::vector<std::wstring> tokenize (const std::wstring& stringInput, const wchar_t delimiter);


};