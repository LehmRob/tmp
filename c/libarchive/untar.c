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

static int untar_init(struct appopts *opts, struct archive **archive) {
    struct archive *arch;

    arch = archive_read_new();
    if (arch == NULL) {
        return -ENOMEM;
    }

    /* Enable all formats */
    archive_read_support_filter_all(arch);
    archive_read_support_format_all(arch);

    if (archive_read_open_filename(arch, opts->filename, 10240)) {
        fprintf(stderr, "Unable to open archive %s\n", archive_error_string(arch));
        archive_read_free(arch);
        return -EIO;
    }

    *archive = arch;

    return 0;
}

static int untar_print_archive(struct appopts *opts) {
    struct archive *archive;
    int rc = untar_init(opts, &archive);
    if (rc < 0) {
        return rc;
    }

    struct archive_entry *entry = NULL;
    while (rc != ARCHIVE_EOF) {
        rc = archive_read_next_header(archive, &entry);
        if (rc == ARCHIVE_FATAL) {
            fprintf(stderr, "An error happened %s\n", archive_error_string(archive));
            rc = -EINVAL;
            goto exit;
        } else if (rc != ARCHIVE_EOF) {
            printf("entry %s\n", archive_entry_pathname(entry));
            continue;
        }
    }

    rc = 0;

exit:
    archive_read_close(archive);
    archive_read_free(archive);
    return rc;

}

static int untar_copy(struct archive *read, struct archive *write) {
    int rc = 0;
    const void *bufptr;
    size_t size;
    off_t offset;

    while (rc != ARCHIVE_EOF) {
        rc = archive_read_data_block(read, &bufptr, &size, &offset);
        if (rc != ARCHIVE_EOF && rc != ARCHIVE_OK) {
            return rc;
        }

        if (rc == ARCHIVE_OK) {
            rc = archive_write_data_block(write, bufptr, size, offset);
            if (rc != ARCHIVE_OK) {
                return rc;
            }
        }
    }

    return ARCHIVE_OK;
}

static int untar_extract_entry(struct archive *read, struct archive_entry *entry, 
        struct archive *write) {

    int rc = archive_write_header(write, entry);
    if (rc != ARCHIVE_OK) {
        return rc;
    }

    rc = untar_copy(read, write);
    if (rc != ARCHIVE_OK) {
        return rc;
    }

    return archive_write_finish_entry(write);
}

static int untar_extract_archive(struct appopts *opts) {
    struct archive *readarch = NULL;

    int rc = untar_init(opts, &readarch);
    if (rc < 0) {
        return -ENOMEM;
    }

    struct archive *writedir = archive_write_disk_new();
    if (writedir == NULL) {
        rc = -ENOMEM;
        goto free_read;
    }

    struct archive_entry *entry = NULL;
    rc = 0;
    while (rc != ARCHIVE_EOF) {

        rc = archive_read_next_header(readarch, &entry);
        if (rc == ARCHIVE_FATAL) {
            fprintf(stderr, "error occured %s\n", archive_error_string(readarch));
            rc = -EINVAL;
            goto free_all;
        } else if (rc != ARCHIVE_EOF) {
            rc = untar_extract_entry(readarch, entry, writedir);
            if (rc != ARCHIVE_OK) {
                goto free_all;
            }
        }
    }

free_all:
    archive_write_close(writedir);
    archive_write_free(writedir);

free_read:
    archive_read_close(readarch);
    archive_read_free(readarch);

    return rc;

}

int main(int ac, char **av) {
    struct appopts opts;
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

    rc = untar_print_archive(&opts);
    if (rc < 0) {
        fprintf(stderr, "Error during printing the archive for %s\n", opts.filename);
        goto exit;
    }

    rc = untar_extract_archive(&opts);

exit:
    appopts_free(&opts);

    return rc;
}
