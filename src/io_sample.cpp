//
// Created by harold on 15/8/2019.
//

#include "utils/utils.h"

using namespace af;

int main(int argc, char **argv) {

    // load pts into data
    if (argc <= 1) {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }
    array data;
    Utils::utils::read_file_into_array(argv[1], data);
    printf("dimensions of array: %lld, %lld\n", data.dims()[0], data.dims()[1]);

    // array IO
    std::string filename = "data";
    std::string key = "data";
    array d;

    // saveArray
    {
        PROFILE_BLOCK("save array");
        saveArray(key.c_str(), data, filename.c_str(), false);
    }

    // readArray
    {
        PROFILE_BLOCK("read array");
        d = readArray(filename.c_str(), key.c_str());
    }
    printf("dimensions of array: %lld, %lld\n", d.dims()[0], d.dims()[1]);

    if (argc <= 2) {
        return 0;
    }

    // loadImage
    // require `libfreeimage.so`: `sudo apt-get install -y libfreeimage-dev`
    array img;
    std::string img_name = argv[2];
    {
        PROFILE_BLOCK("load image");
        img = loadImage(img_name.c_str(), true);
    }
    printf("dimensions of array: %lld, %lld\n", img.dims()[0], img.dims()[1]);

    return 0;
}

/*
 * io_sample usage:
 * ./io_sample sample_files/sample.txt sample_files/sample.jpg
 */

