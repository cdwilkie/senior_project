/*Tokenizer supports functionality to
* extract tokens from wstring lines.
* Stores each found word in Token struct
* along with an associated tokenID
*/
#include "../include/Tokenizer.h"
#include <sstream>


/*
*tokenize() extracts the tokens/words from 
* the provided wstring. Returns vector of Tokens
*/
std::vector<Tokenizer::Token> Tokenizer::tokenize(
        const std::wstring& stringInput) {
    std::vector<Tokenizer::Token> tokens;       //Holds tokenized data
    std::wistringstream wiss(stringInput);      //Opens wstring stream to parse string
    std::wstring tokenWord;                     //Holds wstring data for token

    while (wiss >> std::ws >> tokenWord) {      //While data in stream, skip whitespace, extract
        Tokenizer::Token token;                 //Token to store token data
        token.word = tokenWord;                 //Assign attribute with extracted chars
        token.tokenID = 0;                      //Default tokenID zero
        tokens.push_back(token);                //Add new token to vector
    }//end while data in stream
    return tokens;                              //Return vector of tokens
}//end tokenize()

/*tokenizeChunk() helper function to tokenize a chunk
* of the passed vector of lines (wstrings).
*/
void Tokenizer::tokenizeChunk(const std::vector<std::wstring>& lines,
        std::vector<std::vector<Tokenizer::Token>>& tokens, size_t start, size_t end){
    for (size_t i = start; i < end; ++i) {      //Iterate through lines in chunk
        tokens[i] = Tokenizer::tokenize(lines[i]);//Store tokenized line in vector
    }//end for every line in chunk
}//end tokenizeChunk

/*tokenizeLines supports multithreading
* to tokenize a vector of lines and store
* results in vector of Tokens.
*/
void Tokenizer::tokenizeLines(std::vector<std::wstring>& lines,
        std::vector<std::vector<Tokenizer::Token>>& tokens, size_t numThreads){
    tokens.resize(lines.size());                //Ensure tokens vector size.

    const size_t chunkSize = (lines.size() + numThreads - 1) / numThreads;//Chunk
    std::vector<std::thread> threads(numThreads);//Create vector of threads

    for (size_t i = 0; i < numThreads; ++i) {   //Iterate through threads
        const int start = i * chunkSize;        //Caculate start index
        const int end = std::min(start + chunkSize, lines.size());//Calc end
        threads[i] = std::thread(tokenizeChunk, std::cref(lines),
            std::ref(tokens), start, end);      //Assign task
    }//end for every thread assign

    for (int i = 0; i < threads.size(); ++i) {  //Iterate through threads
        threads[i].join();                      //Join thread
    }//end for every thread join
}//end tokenizeLines()
