#ifndef __RC_H__
#define __RC_H__

typedef enum {
    PROP_OK = 0,
    PROP_FILE_ERR,
    PROP_EOF,
    PROP_MEM_ERR,
    PROP_NO_SEP,
    PROP_DUPL,
} prop_rc;

const char* props_rc_str(prop_rc rc);

#endif /* __RC_H__ */
