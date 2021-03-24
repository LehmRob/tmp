#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <archive.h>

#define APP_NAME "untar"
#define APP_VERSION "1.0.0"

struct app_opts {
    char *filename;
    char *outpath;
};

static int parse_app_opts(int ac, char **av, struct app_opts *opts);
static void app_opts_free(struct app_opts *opts);

int main(int ac, char **av) {
    struct app_opts opts;
    int rc = 0;

    rc = parse_app_opts(ac, av, &opts);
    if (rc < 0) {
        fprintf(stderr, "Can't parse options. Try -h\n");
        rc = -1;
        goto exit;
    } else if (rc > 0) {
        rc = 0;
        goto exit;
    }

    printf("filename  %s\n", opts.filename);
    printf("output directory %s\n", opts.outpath);

exit:
    app_opts_free(&opts);

    return rc;
}

static void show_help(char *appname) {
    printf("usage: %s: optins\n", appname);
    printf("-f, --file FILE\t\tArchive file which should be untared\n");
    printf("-C, --directory DIR\tOutput directory (default: current dir)\n");
    printf("-h, --help \t\tShow this help text\n");
    printf("-v, --version \t\tShow version\n");
}

static struct option long_options[] = {
    {"file", required_argument, 0, 'f'},
    {"directory", required_argument, 0, 'C'},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {NULL, 0, 0, 0}
};

static int parse_app_opts(int ac, char **av, struct app_opts *opts) {
    int optind = 0;
    int c;

    opts->outpath = NULL;
    opts->filename = NULL;

    while ((c = getopt_long(ac, av, "C:f:hv", long_options, &optind)) != -1) {
        switch (c) {
            case 'f':
                if (optarg != NULL) {
                    opts->filename = calloc(strlen(optarg) + 1, sizeof(char));
                    if (opts->filename == NULL) {
                        return -1;
                    }
                    strncpy(opts->filename, optarg, strlen(optarg));
                }
                break;
            case 'C':
                if (optarg != NULL) {
                    opts->outpath = calloc(strlen(optarg) + 1, sizeof(char));
                    if (opts->outpath == NULL) {
                        return -1;
                    }
                    strncpy(opts->outpath, optarg, strlen(optarg));
                }
                break;
            case 'h':
                show_help(APP_NAME);
                return 1;
            case 'v':
                printf("%s -- v%s\n", APP_NAME, APP_VERSION);
                return 1;
        }
    }

    return 0;
}

static void app_opts_free(struct app_opts *opts) {
    if (opts == NULL) {
        return;
    }

    if (opts->filename != NULL) {
        free(opts->filename);
    }

    if (opts->outpath != NULL) {
        free(opts->outpath);
    }
}

