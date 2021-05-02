/*
 * The purpose of this little program is to parse a property file and split the data into
 * key value pairs.
 */

#include <stdio.h>

#include "property.h"

int main(int ac, char** av) {
    properties props;
    prop_rc rc = propertiesReadFile(&props, av[1]);

    if (rc != PROP_OK) { 
        propertiesCleanUp(&props);
        return rc;
    }

    propertiesCleanUp(&props);

    return 0;
}
