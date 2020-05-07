#include <stdio.h>
#include <string.h>

#include "option.h"
#include "graphe.h"
#include "dimacs_w.h"

int main(int argc , char* argv[]){
    char * file_input = NULL;
    char * file_out = "./out.DIMACS";

    if (argc < 2) {
        usage_conv(argv[0]);
        return 1;
    }
    int arg = 1;
    while (arg < argc) {
        if (strcmp(argv[arg], "-h") == 0) {
            usage_conv(argv[0]);
            return 1;
        }
        else if (strcmp(argv[arg], "-o") == 0) {
            arg++;
            if (arg == argc || argv[arg][0] == '-')
            {
                usage_o();
                return 1;
            }else
            {
                file_out = argv[arg];
                arg++;
            }            
        }
        else if (argv[arg][0] == '-') {
            fprintf(stderr, "Unknown option: '%s'\n", argv[arg]);
            return 1;
        }
        else if (file_input == NULL) {
            file_input = argv[arg];
            arg++;
        }
        else{
            fprintf(stderr, "Too much argument: '%s'\n", argv[arg]);
            return 1;
        }
    }
    
    #ifdef _DEBUG
        printf("nom du fichier d'input: %s\n", file_input);
        printf("nom du fichier d'output: %s\n", file_out);
    #endif // _DEBUG

    graphe g;
    g = readFile(file_input, 1);

    #ifdef _DEBUG
        printf("\nLe fichier a bien eté lu\n\n");
    #endif // _DEBUG

    writeDimacs(file_out, g);

    printf("le fichier %s vient d'etre crée !\n", file_input);

    return 1;
}