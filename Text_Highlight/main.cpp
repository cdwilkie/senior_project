#include "tokenGen.h"
#include <vector>

   
FILE *in_fp, *fopen();

std::ostream& boldOn(std::ostream& os) {
    return os << "\e[1m";
}//end boldOn

std::ostream& boldOff(std::ostream& os) {
    return os << "\e[0m";
}

int main (int argc, char** argv) {
    
    std::vector<Token> storedTokens;            //Will store each token
    std::string keyword;                        //User defined search keyword
    std::string outfile;                        //User defined outfile name
    
/************ Reading filename from Command Line and Scanning ***********/

    if (argc < 2) {                             //If missing command-line args
        std::cout << "Expected filename argument" << std::endl;
    }//end if < 2

    else if (argc > 1 &&                        //If file is null
            (in_fp = fopen(argv[1], "r")) == NULL) { 

        std::cout << "Error opening " << argv[1] << std::endl;
    }//end else if file null

    else {                                      //Else file opened in read mode
        std::cout << argv[1] << " opened successfully!" << std::endl;
        std::cout << "\nPlease enter the search argument" << std::endl;
        std::cin >> keyword;                    //Store user defined keyword

/************** Generate tokens for each word in file *******************/

        getChar();                              //Get first character of file
        do {
            lex();                              //Call lexical analyzer to generate token
            
            struct Token token;                 //Token datatype stores token info
            token.tokenType = nextToken;        //Store type of token
            token.word = lexeme;                //Store the token word
            storedTokens.push_back(token);      //Add the token to vector

        } while (nextToken != EOF);             //Continue until end of file
    
/************* Iterate through TOKENS to find KEYWORD *******************/

        std::cout << "Scanning Tokens for Keyword: " << std::endl;

        for (int i = 0; i < storedTokens.size(); ++i ) { //Iterate through tokens
            if (storedTokens[i].tokenType == 11 &&       //If token word == keyword
                    strcmp(storedTokens[i].word.c_str(), keyword.c_str()) == 0) {
                storedTokens[i].tokenType = KEYWORD;    //Update token type
            }//end if token == keyword
        }//end for check for keyword

/************ Collect outfile name and write contents to file ***********/

        std::cout << "Enter a filename for output" << std::endl;
        std::cin >> outfile;                    //Collect user outfile name
        std::ofstream outs(outfile);            //Outfile stream
        for (int i =0; i < storedTokens.size(); ++i) {
            if (i % 10 == 0) {
                outs << "\n";
                std::cout << "\n";
            }
            if (storedTokens[i].tokenType == 15) {
                outs << "***" << storedTokens[i].word << "***" << " "; //Output to console in bold
                std::cout << boldOn << storedTokens[i].word << boldOff << " ";//Write to outfile with markers
            }//end if keyword token
            else {
                outs << storedTokens[i].word << " ";//Output to console
                std::cout << storedTokens[i].word << " ";//Write to outfile
            }//end else no match
        }//end for iterate through tokens for output
        std::cout << std::endl;                 //Clear buffer.
        
    }//end else file can be read







    return 0;
}//end main()
