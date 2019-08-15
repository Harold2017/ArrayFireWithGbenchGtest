//
// Created by harold on 15/8/2019.
//

#include "utils.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>

using namespace Utils;
using namespace af;

struct Points
{
    float x, y, z;
    Points(float __x, float __y, float __z);
};

Points::Points(float __x, float __y, float __z): x(__x), y(__y), z(__z) {}

void utils::read_file_into_array(const std::string &path_name, array &data) {
    PROFILE_BLOCK("read_file_into_array");
    auto filename = path_name.c_str();
    int size;
    struct stat buf{};
    FILE* pFile = fopen(filename, "r");
    fstat(pFile->_fileno, &buf);
    size = buf.st_size;

    std::vector<Points> points;
    points.reserve((int)size / (4 * 8 * 3 + 1 * 2) * 3);

    char source[size + 1];  // read in the whole file

    float x, y, z;

    if (pFile != NULL) {
        size_t newLen = fread(source, sizeof(char), size, pFile);  // sizeof(char) = 1
        if (ferror(pFile) != 0) {
            fputs("Error reading file", stderr);
        } else {
            source[newLen++] = '\0'; // just to be safe
        }
    }

    char* line = source;
    char* ptr;
    int row_num = 0;

    while(true) {
        x = strtof(line, &ptr);
        y = strtof(ptr, &ptr);
        z = strtof(ptr, &ptr);
        points.emplace_back(x, y, z);
        row_num ++;
        if (*ptr == '\0') break;

        // consume line
        while(*ptr != '\n') {
            // ptr++;
        }
        line = ptr;
    }

    fclose(pFile);

    points.shrink_to_fit();

    data = array(3, row_num, f32);
    data.write(static_cast<void*>(points.data()), points.size() * sizeof(float) * 3);
    std::vector<Points>().swap(points);
    data = data.T();
}
