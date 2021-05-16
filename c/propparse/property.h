#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "rc.h"

#include <stdlib.h>

typedef struct {
    char *key;
    char *val;
} keyval;

typedef struct {
    keyval *content;
    size_t len;
    size_t cap;
} properties;

prop_rc props_new(properties *p);
prop_rc props_read_file(properties *p, const char *filename);
prop_rc props_add(properties *p, const char *key, const char *value);
void props_cleanup(properties *p);

#endif /*__PROPERTY_H__*/
