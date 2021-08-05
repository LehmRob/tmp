#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <archive.h>
#include <archive_entry.h>

#define APP_NAME "untar"
#define APP_VERSION "1.0.0"

struct appopts {
    char *filename;
    char *outdir;
};

static void show_help(char *appname) {
    printf("usage: %s: optins\n", appname);
    printf("-f, --file FILE\t\tArchive file which should be untared\n");
    printf("-C, --directory DIR\tOutput directory (default: current dir)\n");
    printf("-h, --help \t\tShow this help text\n");
    printf("-v, --version \t\tShow version\n");
}

static struct option long_options[] = {{"file", required_argument, 0, 'f'},
    {"directory", required_argument, 0, 'C'}, {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'}, {NULL, 0, 0, 0}};

static int parse_appopts(int ac, char **av, struct appopts *opts) {
    int optind = 0;
    int c;

    opts->outdir = NULL;
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
                opts->outdir = calloc(strlen(optarg) + 1, sizeof(char));
                if (opts->outdir == NULL) {
                    return -1;
                }
                strncpy(opts->outdir, optarg, strlen(optarg));
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

static void show_options(struct appopts *opts) {
    printf("Filename :%s\n", opts->filename);
    printf("Output :%s\n", opts->outdir);
}

static void appopts_free(struct appopts *opts) {
    if (opts == NULL) {
        return;
    }

    if (opts->filename != NULL) {
        free(opts->filename);
    }

    if (opts->outdir != NULL) {
        free(opts->outdir);
    }
}

struct untar {
    struct archive *archive;
    char *filename;
    char *outdir;
};

static int untar_init(struct untar *u, struct appopts *opts) {
    u->archive = NULL;
    u->filename = NULL;
    u->outdir = NULL;

    u->archive = archive_read_new();
    if (u->archive == NULL) {
        return -ENOMEM;
    }

    /* Enable all formats */
    archive_read_support_filter_all(u->archive);
    archive_read_support_format_all(u->archive);

    size_t len = strlen(opts->filename);
    u->filename = calloc(len + 1, sizeof(char));
    if (u->filename == NULL) {
        return -ENOMEM;
    }

    strncpy(u->filename, opts->filename, len);

    len = strlen(opts->outdir);
    u->outdir = calloc(len + 1, sizeof(char));
    if (u->outdir == NULL) {
        return -ENOMEM;
    }

    strncpy(u->outdir, opts->outdir, len);
    printf("Reading file %s\n", u->filename);

    if (archive_read_open_filename(u->archive, u->filename, 10240)) {
        fprintf(stderr, "Unable to open archive %s\n", archive_error_string(u->archive));
        return -EIO;
    }

    return 0;
}

static int untar_print(struct untar *u) {
    struct archive_entry *entry = NULL;
    int rc = ARCHIVE_OK;

    while (rc != ARCHIVE_EOF) {
        rc = archive_read_next_header(u->archive, &entry);
        if (rc == ARCHIVE_FATAL) {
            fprintf(stderr, "An error happened %s\n", archive_error_string(u->archive));
            return -EINVAL;
        } else if (rc != ARCHIVE_EOF) {
            printf("entry %s\n", archive_entry_pathname(entry));
            continue;
        }
    }

    return 0;
}

static void untar_free(struct untar *u) {
    if (u == NULL) {
        return;
    }

    if (u->archive != NULL) {
        archive_read_free(u->archive);
    }

    if (u->archive != NULL) {
        free(u->filename);
    }

    if (u->outdir != NULL) {
        free(u->outdir);
    }
}

int main(int ac, char **av) {
    struct appopts opts;
    struct untar untar;
    int rc = 0;

    rc = parse_appopts(ac, av, &opts);
    if (rc < 0) {
        fprintf(stderr, "Can't parse options. Try -h\n");
        rc = -1;
        goto exit;
    } else if (rc > 0) {
        rc = 0;
        goto exit;
    }

    show_options(&opts);

    if (opts.filename == NULL || opts.outdir == NULL) {
        fprintf(stderr, "Invalid option. Try -h\n");
        goto exit;
    }

    rc = untar_init(&untar, &opts);
    if (rc != 0) {
        goto free_untar;
    }

    rc = untar_print(&untar);
    if (rc != 0) {
        goto free_untar;
    }

free_untar:
    untar_free(&untar);

exit:
    appopts_free(&opts);

    return rc;
}
