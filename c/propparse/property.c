#include "property.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

const size_t defCap = 10;

static prop_rc init_struct(properties *p) {
    p->len = 0;

    p->content = calloc(defCap, sizeof(keyval));
    if (p->content == NULL) {
        return PROP_MEM_ERR;
    }

    p->cap = defCap;

    return PROP_OK;
}

static prop_rc add_keyval(properties *p, keyval *kv) {
    p->content[p->len].key = kv->key;
    p->content[p->len].val = kv->val;

    p->len++;
    if (p->len > p->cap) {
        /* Relloc storate */
        p->cap += defCap;

        keyval *ptr = reallocarray(p->content, sizeof(keyval), p->cap);
        if (ptr == NULL) {
            p->cap -= defCap;
            return PROP_MEM_ERR;
        }
        p->content = ptr;
    }

    return PROP_OK;
}

static char* clean_whitespace(char *data) {
    char* start = NULL;

    /* is it neccessary to trim trailing whitespaces */
    if (isblank(data[0])) {
        /* check for whitespaces in the front first */
        for (int i = 0; i < strlen(data); i++) {
            if (!isblank(data[i])) {
                /* check the start of the string */
                start = &data[i];
                break;
            }
        }
    } else {
        start = data;
    }

    /* check for trailing whitespaces */
    char* trail = strrchr(start, ' ');
    if (trail != NULL) {
        *trail = '\0';
    } else {
        trail = strrchr(start, '\t');
        if (trail != NULL) {
            *trail = '\0';
        }
    }

    size_t len = strlen(start) + 1;

    /* create a buffer for copy the actual string back and forth */
    char* buf = calloc(len, sizeof(char));
    if (buf == NULL) {
        return NULL;
    }

    strncpy(buf, start, len);
    strncpy(data, buf, len);
    free(buf);

    return data;
}

static prop_rc parse_keyval(char* line, keyval *kv) {
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

    char* key = calloc(keylen + 1, sizeof(char));
    if (key == NULL) {
        return PROP_MEM_ERR;
    }

    char* val = calloc(vallen + 1, sizeof(char));
    if (val == NULL) {
        return PROP_MEM_ERR;
    }

    /* do 0 termination of the string */
    key[keylen] = '\0';
    val[vallen] = '\0';

    strncpy(key, line, keylen);
    strncpy(val, sep + 1, vallen);

    kv->key = clean_whitespace(key);
    kv->val = clean_whitespace(val);

    return PROP_OK;
}

static void keyvalstr(keyval *kv) {
    printf("key: %s val: %s\n", kv->key, kv->val);
}

static bool has_key(properties *p, const char *key) {
    for (int i = 0; i < p->len; i++) {
        keyval elem = p->content[i];
        if (strstr(elem.key, key) != NULL) {
            return true;
        }
    }

    return false;
}

static prop_rc parse_next_line(properties *p, FILE *fp) {
    size_t linesize;
    char *line = NULL;
    prop_rc rc = PROP_OK;

    ssize_t rbytes = getline(&line, &linesize, fp);
    if (rbytes < 0) {
        if (errno == 0) {
            rc = PROP_EOF;
            goto exit;
        }
        rc = PROP_FILE_ERR;
        goto exit;
    }

    /* strip trailing newline characters */
    char *cr = strrchr(line, '\n');
    if (cr != NULL) {
        *cr = '\0';
    }

    keyval kv;
    rc = parse_keyval(line, &kv);
    if (rc != PROP_OK) {
        goto exit;
    }


    keyvalstr(&kv);
    rc = add_keyval(p, &kv);

exit:
    free(line);
    return rc;
}

prop_rc props_new(properties *p) {
    return init_struct(p);
}

prop_rc props_read_file(properties *p, const char* filename) {
    prop_rc rc = PROP_OK;

    FILE *fd = fopen(filename, "r");
    if (fd == NULL) {
        rc = PROP_FILE_ERR;
        goto rcexit;
    }

    while (rc == PROP_OK) {
        rc = parse_next_line(p, fd);
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

void props_cleanup(properties *p) {
    for (int i = 0; i < p->len; i++) {
        keyval kv = p->content[i];
        free(kv.key);
        free(kv.val);
    }

    free(p->content);
}

prop_rc props_add(properties *p, const char *key, const char *val) {
    if (has_key(p, key)) {
        return PROP_DUPL;
    }

    return PROP_OK;
}
