#include "tokenGen.h"
#include <vector>

   
FILE *in_fp, *fopen();


int main (int argc, char** argv) {
    
    std::vector<Token> storedTokens;

    if (argc > 1 && (in_fp = fopen(argv[1], "r")) == NULL) {

        std::cout << "Error opening " << argv[1] << std::endl;
    }

    else {
        std::cout << argv[1] << " opened successfully!" << std::endl;
        getChar();
        do {
            lex();                              //Call lexical analyzer to generate token
            
            struct Token token;
            token.tokenType = nextToken;
            token.word = lexeme;
            storedTokens.push_back(token);

        } while (nextToken != EOF);             //Continue until end of file
    
        for (int i = 0; i < storedTokens.size(); ++i ) {
            std::cout << storedTokens[i].tokenType << " "
                << storedTokens[i].word << std::endl;
        }
    }







    return 0;
}
