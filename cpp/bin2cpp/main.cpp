#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <errno.h>
#include <getopt.h>

namespace {

void printUsage(const char *arg0) {
    printf("Usage %s: [-i inputfile] [-o outputfile.h] [-t type] [-n num] [-hc] -a "
           "varname \n"
           "\t-t type: one of the different types is possible: char, uint8\n"
           "\t-n num: number of elements in a row\n"
           "\t-c : uses plain c arrays, if not set c++ std::arrays are used\n"
           "\t-h : show help text\n",
        arg0);
}

} // namespace

typedef enum varType {
    charType,
    uint8Type,
} varType;

static int openFiles(const char *infile, FILE **in, const char *outfile, FILE **out) {
    if (infile != nullptr) {
        *in = std::fopen(infile, "r");
        if (in == nullptr) {
            return -EIO;
        }
    }

    if (outfile != nullptr) {
        *out = std::fopen(outfile, "w+");
        if (out != nullptr) {
            return -EIO;
        }
    }
    return 0;
}

static int prepareHeader(
    FILE *in, FILE *out, const char *varname, varType vType, bool plainC) {
    fprintf(out, "// This is a generated file by bin2cpp\n");
    fprintf(out, "#pragma once\n");

    if (plainC) {
        fprintf(out, "#include <stdint.h>\n\n");
        fprintf(out, "// clang-format off\n");

        if (vType == charType) {
            fprintf(out, "char %s[] = {\n", varname);
        } else if (vType == uint8Type) {
            fprintf(out, "uint8_t %s[] = {\n", varname);
        }
    } else {
        // TODO: std::array needs the length at compile time
        return -EINVAL;
    }

    return 0;
}

static int bin2cpp(const char *infile, const char *outfile, const char *varname,
    varType vType, int numPerLine, bool plainC) {

    FILE *in = stdin;
    FILE *out = stdout;

    if (openFiles(infile, &in, outfile, &out)) {
        return -EIO;
    }

    if (prepareHeader(in, out, varname, vType, plainC)) {
        return -EIO;
    }

    auto closeFiles = [&]() {
        fclose(in);
        fclose(out);
    };

    bool eof = false;
    std::array<uint8_t, 256> lineBuffer = {0};

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
    }

    std::fprintf(out, "};\n");
    fprintf(out, "// clang-format on\n");

    return 0;
}

int main(int ac, char *av[]) {
    int opt = 0;

    const char *infile = nullptr;
    const char *outfile = nullptr;
    const char *varname = "data";
    varType vType = charType;
    int numPerLine = 10;
    bool plainC = false;

    while ((opt = getopt(ac, av, "i:o:t:n:hca:")) != -1) {
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
        case 'h':
            printUsage(av[0]);
            return 0;
        }
    }

    if (varname == nullptr) {
        std::fprintf(stderr, "You need to declare a variable name\n");
        return -EINVAL;
    }

    auto rc = bin2cpp(infile, outfile, varname, vType, numPerLine, plainC);
    if (rc) {
        return rc;
    }

    return 0;
}
