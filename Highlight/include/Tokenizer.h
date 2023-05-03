/*Tokenizer supports functionality to
* tokenize strings utilizing multiple threads.
* Token struct holds a wstring (unicode) word
* and an associated tokenID for matching.
*/
#pragma once

#include <string>
#include <vector>
#include <thread>

class Tokenizer {
public:
    /*Token encapulates information about word
    * being tokenized, containing the word and
    * a tokenID for matching
    */
    struct Token {
        std::wstring word;                      //Holds unicode string
        int tokenID;                            //Used for matching
    };

    /*tokenize() extracts the words (series of char
    * seperated by whitespace) from string input
    * and stores in vector. Returns vector
    */
    static std::vector<Token> tokenize (const std::wstring& stringInput);

    /*tokenizeChunk extracts words from a
    * chunk of the passed vector and populates
    * a second vector with the extracted
    * words/tokens.
    */
    static void tokenizeChunk(const std::vector<std::wstring>& lines,
        std::vector<std::vector<Token>>& tokens, size_t start, size_t end);

    /*tokenizeLines() supports multithreading
    * functionality to extract tokens from
    * a vector of lines(strings) and populate a
    * second vector (tokens) with that information
    */
    static void tokenizeLines(std::vector<std::wstring>& lines,
        std::vector<std::vector<Token>>& tokens, size_t numThreads);

};