#include "parser.h"
#include <stdlib.h>
#include <errno.h>
#include <string>

static std::string human_readable_suffix("kMGT");

size_t parse_human_readable(std::string rsize) {
    char unit = rsize.back();

    size_t offset = human_readable_suffix.find(unit);
    
    if(offset == std::string::npos) {
        return -1;
    } else {
        double value = std::stof(rsize);
        int shift = (offset+1) * 10;
        return value * (1LU << shift);
    }
}