#include "option.h"
#include <stdio.h>
/*conv*/
void usage_conv(const char * prog_name){
    fprintf(stderr, "Usage:  %s <fichier_input> [option]...\n", prog_name);
    fprintf(stderr,
                    "\n"
                    "Options:\n"
                    "\t-h\t\t\t show this message\n"
                    "\t-o <file name>\t\t write output to <file name>\n"
                    "\n\n"
                    
                    );
}

void usage_o() {
    fprintf(stderr,
                "bad usage of -o option !\n"
                "Usage: \n"
                "\t-o <file name>\t\t write output in <file name>"
                "\n\n"
    
    
    );
}


/*affichage*/

void usage_aff(const char* prog_name){
    fprintf(stderr, "Usage:  %s <file_graphe> <file_color>\n", prog_name);
}