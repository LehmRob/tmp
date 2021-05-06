#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <stdlib.h>

typedef struct {
    char* key;
    char* val;
} keyval;

typedef struct {
    keyval* content;
    size_t len;
    size_t cap;
} properties;

typedef enum {
    PROP_OK = 0,
    PROP_FILE_ERR,
    PROP_EOF,
    PROP_MEM_ERR,
    PROP_NO_SEP,
} prop_rc;

prop_rc propertiesReadFile(properties *p, const char* filename);
void propertiesCleanUp(properties *p);

#endif /*__PROPERTY_H__*/
