#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct logger {
    clock_t start_time;
    FILE* file;
};

static int get_time(struct logger* l) {
    clock_t cur = clock();

    return (int)(cur - l->start_time) / CLOCKS_PER_SEC;
}

int fl_write(struct logger* l, char* msg) {
    int ret;

    ret = fprintf(l->file, "[%d] %s\n", get_time(l), msg);

    if (ret < 0) {
        return ret;
    }
    return 0;
}

int main(int ac, char** av) {
    if (ac < 2) {
        fprintf(stderr, "Not enough argumnets\n");
        return EINVAL;
    }

    clock_t start = clock();

    FILE* f = fopen(av[1], "aw+");
    if (f == NULL) {
        fprintf(stderr, "Can't open log file %s\n", av[1]);
        return EINVAL;
    }

    struct logger my_logger = {
        .start_time = start,
        .file = f,
    };
    printf("Reach here\n");

    int i;
    for (i = 0; i < 100; i++) {
        fl_write(&my_logger, "I'm log it");
        sleep(1);
    }

    fclose(f);

    return 0;
}
