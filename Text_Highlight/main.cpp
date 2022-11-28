#include "tokenGen.h"
#include <vector>

   
FILE *in_fp, *fopen();


int main (int argc, char** argv) {
    
    std::vector<Token> storedTokens;
    std::string keyword;

    if (argc < 2) {
        std::cout << "Expected filename argument" << std::endl;
    }

    else if (argc > 1 && (in_fp = fopen(argv[1], "r")) == NULL) {

        std::cout << "Error opening " << argv[1] << std::endl;
    }

    else {
        std::cout << argv[1] << " opened successfully!" << std::endl;

        std::cout << "\nPlease enter the search argument" << std::endl;
        std::cin >> keyword;


        getChar();
        do {
            lex();                              //Call lexical analyzer to generate token
            
            struct Token token;
            token.tokenType = nextToken;
            token.word = lexeme;
            storedTokens.push_back(token);

        } while (nextToken != EOF);             //Continue until end of file
    
        
        std::cout << "Scanning Tokens for Keyword: " << std::endl;

        for (int i = 0; i < storedTokens.size(); ++i ) {
            if (storedTokens[i].tokenType == 11 &&
                    strcmp(storedTokens[i].word.c_str(), keyword.c_str()) == 0) {
                storedTokens[i].tokenType = KEYWORD;
            }
            std::cout << storedTokens[i].tokenType << " "
                << storedTokens[i].word << std::endl;
        }
        
        for (int i =0; i < storedTokens.size(); ++i) {
            std::cout << storedTokens[i].word << " ";
        }
        std::cout << std::endl;
        
    }







    return 0;
}
