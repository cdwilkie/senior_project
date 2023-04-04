#include "../include/Tokenizer.h"
#include <sstream>



std::vector<Tokenizer::Token> Tokenizer::tokenize (const std::wstring& stringInput) {
    std::vector<Tokenizer::Token> tokens;
    std::wistringstream wiss(stringInput);
    std::wstring tokenWord;

    while (wiss >> std::ws >> tokenWord) {
        Tokenizer::Token token;
        token.word = tokenWord;
        //fix this below \/
        token.tokenID = 0;
        tokens.push_back(token);
    }
    return tokens;
}


void Tokenizer::tokenizeChunk(const std::vector<std::wstring>& lines, std::vector<std::vector<Tokenizer::Token>>& tokens, size_t start, size_t end){
    for (size_t i = start; i < end; ++i) {
        tokens[i] = Tokenizer::tokenize(lines[i]);
    }
}

void Tokenizer::tokenizeLines(std::vector<std::wstring>& lines, std::vector<std::vector<Tokenizer::Token>>& tokens, size_t numThreads){
    tokens.resize(lines.size());

    const size_t chunkSize = (lines.size() + numThreads - 1) / numThreads;
    std::vector<std::thread> threads(numThreads);

    for (size_t i = 0; i < numThreads; ++i) {
        const int start = i * chunkSize;
        const int end = std::min(start + chunkSize, lines.size());
        threads[i] = std::thread(tokenizeChunk, std::cref(lines), std::ref(tokens), start, end);
    }

    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }


}
