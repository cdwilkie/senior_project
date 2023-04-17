#pragma once

#include <string>
#include <vector>
#include <thread>

class Tokenizer {
public:

    struct Token {
        std::wstring word;
        int tokenID;
    };

    static std::vector<Token> tokenize (const std::wstring& stringInput);

    static void tokenizeChunk(const std::vector<std::wstring>& lines,
        std::vector<std::vector<Token>>& tokens, size_t start, size_t end);

    static void tokenizeLines(std::vector<std::wstring>& lines,
        std::vector<std::vector<Token>>& tokens, size_t numThreads);

};