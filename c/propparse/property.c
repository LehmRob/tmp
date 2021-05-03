#include "property.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

const size_t defCap = 10;

static prop_rc initStruct(properties *p) {
    p->len = 0;

    p->content = calloc(defCap, sizeof(keyval));
    if (p->content == NULL) {
        return PROP_MEM_ERR;
    }

    p->cap = defCap;
    p->line = NULL;

    return PROP_OK;
}

static prop_rc parseKeyValue(char* line, keyval *kv) {
    /* first thing we need to do is to find the seperator between key and value.
     * this parser can '=' or ':' with 0-N whitespaces for separation
     */
    char* sep = strchr(line, '=');
    if (sep == NULL) {
        sep = strchr(line, ':');
        if (sep == NULL) {
            return PROP_NO_SEP;
        }
    }

    size_t keylen = sep - line;
    size_t vallen = strlen(line) - keylen - 1;

    printf("keylen %d; vallen %d\n", keylen, vallen);

    char* key = calloc(keylen + 1, sizeof(char));
    if (key == NULL) {
        return PROP_MEM_ERR;
    }

    char* val = calloc(vallen + 1, sizeof(char));
    if (val == NULL) {
        return PROP_MEM_ERR;
    }

    strncpy(key, line, keylen);
    strncpy(val, sep + 1, vallen);

    

    return PROP_OK;
}

static prop_rc parseNextLine(properties *p, FILE *fp) {
    size_t linesize;

    ssize_t rbytes = getline(&p->line, &linesize, fp);
    if (rbytes < 0) {
        if (errno == 0) {
            return PROP_EOF;
        }
        return PROP_FILE_ERR;
    }

    /* strip trailing newline characters */
    char *cr = strrchr(p->line, '\n');
    if (cr != NULL) {
        *cr = '\0';
    }

    keyval kv;
    prop_rc rc = parseKeyValue(p->line, &kv);
    if (rc != PROP_OK) {
        return rc;
    }

    return PROP_OK;
}

prop_rc propertiesReadFile(properties *p, const char* filename) {
    prop_rc rc = initStruct(p);
    if (rc != PROP_OK) {
        return rc;
    }

    FILE *fd = fopen(filename, "r");
    if (fd == NULL) {
        rc = PROP_FILE_ERR;
        goto rcexit;
    }

    rc = PROP_OK;
    while (rc == PROP_OK) {
        rc = parseNextLine(p, fd);
    }

    if (rc != PROP_EOF) {
        goto closefile;
    }

    rc = PROP_OK;


closefile:
    fclose(fd);

rcexit:
    return rc;
}

void propertiesCleanUp(properties *p) {
    free(p->line);
    
    for (int i = 0; i < p->len; i++) {
        free(p->content->key);
        free(p->content->val);
    }

    free(p->content);
}
