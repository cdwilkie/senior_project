#include "tokenGen.h"
#include <vector>

   
FILE *in_fp, *fopen();


int main (int argc, char** argv) {
    
    std::vector<Token> storedTokens;            //Will store each token
    std::string keyword;                        //User defined search keyword

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


        getChar();                              //Get first character of file
        do {
            lex();                              //Call lexical analyzer to generate token
            
            struct Token token;                 //Token datatype stores token info
            token.tokenType = nextToken;        //Store type of token
            token.word = lexeme;                //Store the token word
            storedTokens.push_back(token);      //Add the token to vector

        } while (nextToken != EOF);             //Continue until end of file
    
        
        std::cout << "Scanning Tokens for Keyword: " << std::endl;

        for (int i = 0; i < storedTokens.size(); ++i ) { //Iterate through tokens
            if (storedTokens[i].tokenType == 11 &&       //If token word == keyword
                    strcmp(storedTokens[i].word.c_str(), keyword.c_str()) == 0) {
                storedTokens[i].tokenType = KEYWORD;    //Update token type
            }//end if token == keyword
            std::cout << storedTokens[i].tokenType << " "
                << storedTokens[i].word << std::endl;
        }//end for check for keyword
        
        for (int i =0; i < storedTokens.size(); ++i) {
            std::cout << storedTokens[i].word << " ";
        }
        std::cout << std::endl;
        
    }







    return 0;
}
