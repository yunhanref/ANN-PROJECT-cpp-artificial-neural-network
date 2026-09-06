#pragma once
#include <string>
#include "Matrix.h"


class DataHandler {
public:
    
    static Matrix loadCSV(const std::string& path, bool hasHeader = false);


    static void saveCSV(const std::string& path, const Matrix& m);
};
