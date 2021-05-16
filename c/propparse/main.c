/*
 * The purpose of this little program is to parse a property file and split the data into
 * key value pairs.
 */

#include <stdio.h>

#include "property.h"

int main(int ac, char** av) {
    properties props;
    prop_rc rc = props_new(&props);
    if (rc != PROP_OK) {
        return rc;
    }

    rc = props_read_file(&props, av[1]);
    if (rc != PROP_OK) {
        goto cleanup;
    }

    rc = props_add(&props, "thisis", "test");
    if (rc != PROP_OK) {
        printf("Error occured %d", rc);
        goto cleanup;
    }


cleanup:
    props_cleanup(&props);

    return rc;
}
