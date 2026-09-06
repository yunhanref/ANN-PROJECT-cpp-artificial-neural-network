#pragma once
#include <string>
#include "DenseLayer.h"

class ModelStorage {
public:
    static void saveLayer(const std::string& prefix, const DenseLayer& layer);

    static void loadLayer(const std::string& prefix, DenseLayer& layer);
};
