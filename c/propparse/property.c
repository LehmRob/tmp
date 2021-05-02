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

    /*
     *keyval kv;
     *prop_rc = parseKeyValue(line, &kv);
     *if prop+
     */

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
    free(p->content);
}
