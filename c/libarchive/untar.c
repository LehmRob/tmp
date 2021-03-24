#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <archive.h>

#define APP_NAME "untar"

static struct option long_options[] = {
    {"file", required_argument, 0, 0},
    {"help", no_argument, 0, 0},
    {NULL, 0, 0, 0}
};

struct app_opts {
    char filename[30];
};

static void show_help(char *appname) {
    printf("usage: %s: [-f FILE] [-h]\n");
}

static int parse_app_opts(int ac, char **av, struct app_opts *opts) {
    int optind = 0;
    int c = getopt_long(ac, av, "f:h", long_options, &optind);
    if (c == -1) {
        return -1;
    }

    switch (c) {
        case 'f':
            if (optarg != NULL) {
                strncpy(opts->filename, optarg, sizeof(opts->filename));
            }
            break;
        case 'h':
            show_help(APP_NAME);
            return 1;
    }

    return 0;
}

int main(int ac, char **av) {
    printf("Hello friend\n");
    struct app_opts opts;

    int rc = parse_app_opts(ac, av, &opts);
    if (rc < 0) {
        fprintf(stderr, "Can't parse options. Try -h\n");
        return -1;
    } else if (rc > 0) {
        return 0;
    }


    return 0;
}
