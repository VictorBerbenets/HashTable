#include "include/hash.h"
#include <sys/stat.h>
#include <sys/types.h>

long GetFileSize(const char *file) {
    
    Validator(file == nullptr, "in opening file", exit(OPEN_FILE_ERROR));

    struct stat buf = {};

    if (stat(file, &buf)) {

        fprintf(stderr, "\033[0;31mERROR\033[0m!!!\nFile <%s>: in function <%s>,  in line '%d' - error in function \"stat\"\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);

        return -1;
    }

    return buf.st_size;
}