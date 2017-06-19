#include <iostream>

#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif
#include <openssl/md5.h>
#ifdef __cplusplus
}
#endif

int
main(int ac, char* av[])
{
    if (ac < 1) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }

    unsigned char md5_digest[MD5_DIGEST_LENGTH];
    MD5_CTX md5;
    auto fd = fopen(av[1], "r");
    if (fd == NULL) {
        std::cerr << "Can't open file " << av[1] << std::endl;
        return 1;
    }

    MD5_Init(&md5);

    size_t bytes = 0;
    unsigned char buf[1024];
    while ((bytes = fread(buf, 1, 1024, fd)) != 0) {
        MD5_Update(&md5, buf, bytes);
    }

    MD5_Final(md5_digest, &md5);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", md5_digest[i]);
    }

    printf("%s\n", av[1]);
    fclose(fd);

    return 0;
}