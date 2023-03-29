#pragma once

#include <string>
#include <vector>

class Tokenizer {
public:
    struct Token {
        std::wstring word;
        int tokenID;
    };
    static std::vector<Token> tokenize (const std::wstring& stringInput);


};