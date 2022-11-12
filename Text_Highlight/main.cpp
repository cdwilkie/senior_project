#include "tokenGen.h"

FILE *in_fp, *fopen();   


int main (int argc, char** argv) {

    if (argc > 1 && (in_fp = fopen(argv[1], "r")) == NULL) {

        std::cout << "Error opening " << argv[1] << std::endl;
    }

    else {
        std::cout << argv[1] << " opened successfully!" << std::endl;
        getChar();
        do {
            lex();                              //Call lexical analyzer to generate token
            
        } while (nextToken != EOF);             //Continue until end of file
    }







    return 0;
}
