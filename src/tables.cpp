#include "tables.hpp"
#include <cmath>

const std::unordered_map<std::string, double> CONSTANTS_TABLE = {{"pi", M_PIf},
                                                                 {"e", M_Ef}};

const std::unordered_map<std::string, FunctionMetaData> FUNCTIONS_TABLE = {

    {"sin", {1, [](auto& args) { return sin(args[0]); }}},
    {"cos", {1, [](auto& args) { return sin(args[0]); }}},
    {"tan", {1, [](auto& args) { return sin(args[0]); }}},
    {"asin", {1, [](auto& args) { return sin(args[0]); }}},
    {"acos", {1, [](auto& args) { return sin(args[0]); }}},
    {"atan", {1, [](auto& args) { return sin(args[0]); }}},
    {"sqrt", {1, [](auto& args) { return sqrt(args[0]); }}},
    {"cbrt", {1, [](auto& args) { return sqrt(args[0]); }}},
    {"pow", {2, [](auto& args) { return pow(args[0], args[1]); }}},
};
