#include "rc.h"

const char* props_rc_str(prop_rc rc) {
    switch (rc) {
    case PROP_OK:
        return "OK";
    case PROP_FILE_ERR:
        return "File IO error";
    case PROP_EOF:
        return "EOF";
    case PROP_MEM_ERR:
        return "Memory error";
    }

    return "Unknown";
}
