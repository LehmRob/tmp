#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <errno.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef BUILDTIME
#define BUILDTIME "unknown"
#endif // BUILDTIME

#ifndef GIT_REV
#define GIT_REV "unknown"
#endif // GIT_REV

#ifndef GIT_BRANCH
#define GIT_BRANCH "unknown"
#endif // GIT_BRANCH

#ifndef APP_VERSION
#define APP_VERSION "unknown"
#endif // APP_VERSION

namespace {

void printUsage(std::string &arg0) {
    printf(
        "Usage %s: [-i inputfile] [-o outputfile.h] [-t type] [-n num] [-l num] [-hc] -a "
        "varname \n"
        "\t-t type: one of the different types is possible: char, uint8\n"
        "\t-n num:  number of elements in a row\n"
        "\t-c:      uses plain c arrays, if not set c++ std::arrays are used\n"
        "\t-l num:  size to read from file in bytes\n"
        "\t-v:      show version\n"
        "\t-h:      show help text\n",
        arg0.c_str());
}

void printVersion(std::string &arg0) {
    printf(
        "%s v%s-%s [%s] %s\n", arg0.c_str(), APP_VERSION, GIT_REV, GIT_BRANCH, BUILDTIME);
}

typedef enum varType {
    charType,
    uint8Type,
} varType;

bool getFileSize(FILE *file, size_t *size) {
    struct stat stat;
    if (fstat(fileno(file), &stat)) {
        return false;
    }

    *size = stat.st_size;

    return true;
}

int openFiles(const char *infile, FILE **in, const char *outfile, FILE **out) {
    if (infile != nullptr) {
        *in = std::fopen(infile, "r");
        if (in == nullptr) {
            return -EIO;
        }
    }

    if (outfile != nullptr) {
        *out = std::fopen(outfile, "w+");
        if (out == nullptr) {
            return -EIO;
        }
    }
    return 0;
}

int prepareHeader(
    FILE *in, FILE *out, const char *varname, varType vType, bool plainC, size_t size) {
    size_t insize = 0;
    if (!getFileSize(in, &insize)) {
        return -EIO;
    }

    fprintf(out, "// This is a generated file by bin2cpp\n");
    fprintf(out, "#pragma once\n");

    if (plainC) {
        fprintf(out, "#include <stdint.h>\n\n");
        fprintf(out, "// clang-format off\n");

        if (vType == charType) {
            fprintf(out, "char %s[%lu] = {\n", varname, insize);
        } else if (vType == uint8Type) {
            fprintf(out, "uint8_t %s[%lu] = {\n", varname, insize);
        }
    } else {
        fprintf(out, "#include <cstdint>\n\n");
        fprintf(out, "#include <array>\n\n");
        fprintf(out, "// clang-format off\n");

        if (vType == charType) {
            fprintf(out, " std::array<char, %lu> %s = {\n", insize, varname);
        } else if (vType == uint8Type) {
            fprintf(out, " std::array<uint8_t, %lu> %s = {\n", insize, varname);
        }
    }

    return 0;
}

int bin2cpp(const char *infile, const char *outfile, const char *varname, varType vType,
    int numPerLine, bool plainC, size_t size = 0) {
    FILE *in = stdin;
    FILE *out = stdout;

    if (openFiles(infile, &in, outfile, &out)) {
        fprintf(stderr, "can't open files\n");
        return -EIO;
    }

    if (prepareHeader(in, out, varname, vType, plainC, size)) {
        fprintf(stderr, "can't prepare header\n");
        return -EIO;
    }

    auto closeFiles = [&]() {
        fflush(out);
        fclose(in);
        fclose(out);
    };

    bool eof = false;
    std::array<uint8_t, 256> lineBuffer = {0};
    size_t rsize = {0};

    while (!eof) {
        auto rbytes = std::fread(lineBuffer.data(), sizeof(uint8_t), numPerLine, in);
        if (rbytes < numPerLine) {
            if (feof(in)) {
                eof = true;
            } else {
                closeFiles();
                return -EIO;
            }
        }

        std::fprintf(out, "    ");

        for (int i = 0; i < rbytes; i++) {
            if (i == (rbytes - 1)) {
                std::fprintf(out, "0x%02x,", lineBuffer[i]);
            } else {
                std::fprintf(out, "0x%02x, ", lineBuffer[i]);
            }
        }
        std::fprintf(out, "\n");

        rsize += rbytes;
        if (size > 0 && rsize >= size) {
            eof = true;
        }
    }

    std::fprintf(out, "};\n");
    fprintf(out, "// clang-format on\n");

    return 0;
}

} // namespace

int main(int ac, char *av[]) {
    int opt = 0;

    const char *infile = nullptr;
    const char *outfile = nullptr;
    const char *varname = "data";
    varType vType = charType;
    int numPerLine = 10;
    bool plainC = false;
    size_t readSize = 0; // readSize is the size of the file which will be read

    while ((opt = getopt(ac, av, "i:o:t:n:hca:vl:")) != -1) {
        switch (opt) {
        case 'i':
            infile = strdup(optarg);
            break;
        case 'o':
            outfile = strdup(optarg);
            break;
        case 't':
            if (!std::strcmp(optarg, "char")) {
                vType = charType;
            } else if (!std::strcmp(optarg, "uint8")) {
                vType = uint8Type;
            }
            break;
        case 'n':
            numPerLine = std::atoi(optarg);
            break;
        case 'c':
            plainC = true;
            break;
        case 'a':
            varname = strdup(optarg);
            break;
        case 'h': {
            std::string name(av[0]);
            printUsage(name);
            return 0;
        }
        case 'v': {
            std::string name(av[0]);
            printVersion(name);
            return 0;
        }
        case 'l': {
            readSize = std::atoi(optarg);
            break;
        }
        }
    }

    if (varname == nullptr) {
        std::fprintf(stderr, "You need to declare a variable name\n");
        return -EINVAL;
    }

    auto rc = bin2cpp(infile, outfile, varname, vType, numPerLine, plainC, readSize);
    if (rc) {
        return rc;
    }

    return 0;
}
