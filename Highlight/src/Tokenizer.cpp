#include "../include/Tokenizer.h"
#include <sstream>


std::vector<Tokenizer::Token> Tokenizer::tokenize (const std::wstring& stringInput) {
    std::vector<Tokenizer::Token> tokens;
    std::wistringstream wiss(stringInput);
    std::wstring tokenWord;

    while (wiss >> std::ws >> tokenWord) {
        Tokenizer::Token token;
        token.word = tokenWord;
        //fix this
        token.tokenID = 0;
        tokens.push_back(token);
    }
    return tokens;
}