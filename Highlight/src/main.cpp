#include <algorithm>
#include <execution>
#include <iostream>
#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"
#include "../include/ThreadPool.h"


#include "../include/UnitTest.h"



int main (int argc, char** argv) {

    auto startTime2 = UnitTest::start();

    std::vector<std::wstring> lines;            //Holds file contents, one line per index
    
    if (argc <= 1) {                            //If no arguments given
        std::string inFile = UserInput::getFilename();//Prompt user for filename
       
        lines = FileHandler::readLines(inFile); //Open file and read lines

    }//end if no argument
    else {     
        auto startTime0 = UnitTest::start();                                 //Else argument given 
        lines = FileHandler::readLines(argv[1]);//Use argument as filename, open, readlines
        auto stopTIme0 = UnitTest::stop();
        UnitTest::duration(startTime0, stopTIme0);
    }//end if argument
    


    //Test tokenizer


    std::vector<std::vector<Tokenizer::Token>> fileTokens;//2-D Holds tokens from each line

/*
    //Method 1. Parallelism for_each()

    auto startTime = UnitTest::start();  //Test TIme Start

    std::for_each(std::execution::par, lines.begin(), lines.end(), [&fileTokens](const std::wstring& line) {
            std::vector<Tokenizer::Token> tokens = Tokenizer::tokenize(line);
            fileTokens.push_back(tokens);
    });

    auto stopTime = UnitTest::stop();   //Test Time End
    UnitTest::duration(startTime, stopTime); //Display Results


    lines.clear(); //Empty the lines vector
    lines.shrink_to_fit(); //Release memory from lines vector
//*************************************************************************
*/
//Method 2
/*
std::vector<std::future<std::vector<Tokenizer::Token>>> futures;
ThreadPool pool = ThreadPool(4);



auto startTime = UnitTest::start();

for (const auto& line : lines) {
    futures.emplace_back(pool.enqueueTokenize(line));
}

for (auto& future : futures) {
    std::vector<Tokenizer::Token> lineTokens = future.get();
    fileTokens.emplace_back(lineTokens);
}
auto stopTime = UnitTest::stop();
UnitTest::duration(startTime, stopTime);

    lines.clear(); //Empty the lines vector
    lines.shrink_to_fit(); //Release memory from lines vector

*/


//Method 3
auto startTime = UnitTest::start();
size_t numThreads = 8;
Tokenizer::tokenizeLines(lines, fileTokens, numThreads);
auto stopTime = UnitTest::stop();
UnitTest::duration(startTime, stopTime);

    lines.clear(); //Empty the lines vector
    lines.shrink_to_fit(); //Release memory from lines vector

    /*
    std::string outFile = UserInput::getFilename();//Prompt for outfile location
    FileHandler::writeLines(outFile, lines);    //Write lines to outfile
    */


auto stopTIme2 = UnitTest::stop();
    UnitTest::duration(startTime2, stopTIme2);

    return 0;
}