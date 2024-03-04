#include "my_db.h"

int main(int argc, char* argv[]) {        
    FILE *fin = NULL;    
    init_file(argc, argv, &fin);    
    input_command(fin);
    fclose(fin);
    return EXIT_SUCCESS;
}
