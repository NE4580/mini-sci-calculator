#include "tables.hpp"
#include <cmath>

const std::unordered_map<std::string, double> CONSTANTS_TABLE = {{"pi", M_PIf},
                                                                 {"e", M_Ef}};

const std::unordered_map<std::string, FunctionMetaData> FUNCTIONS_TABLE = {

    {"sin", {1, [](auto& args) { return std::sin(args[0]); }}},
    {"cos", {1, [](auto& args) { return std::cos(args[0]); }}},
    {"tan", {1, [](auto& args) { return std::tan(args[0]); }}},
    {"asin", {1, [](auto& args) { return std::asin(args[0]); }}},
    {"acos", {1, [](auto& args) { return std::acos(args[0]); }}},
    {"atan", {1, [](auto& args) { return std::atan(args[0]); }}},
    {"atan2", {2, [](auto& args) { return std::atan2(args[0], args[1]); }}},
    {"sqrt", {1, [](auto& args) { return std::sqrt(args[0]); }}},
    {"cbrt", {1, [](auto& args) { return std::cbrt(args[0]); }}},
    {"root", {2, [](auto& args) { return pow(args[0], 1.0F / args[1]); }}},
    {"pow", {2, [](auto& args) { return std::pow(args[0], args[1]); }}},
    {"max", {2, [](auto& args) { return std::max(args[0], args[1]); }}},
    {"floor", {1, [](auto& args) { return std::floor(args[0]); }}},
    {"ceil", {1, [](auto& args) { return std::ceil(args[0]); }}},
    {"round", {1, [](auto& args) { return std::round(args[0]); }}},
    {"abs", {1, [](auto& args) { return std::abs(args[0]); }}},
    {"min", {2, [](auto& args) { return std::min(args[0], args[1]); }}},
    {"log",
     {2, [](auto& args) { return std::log(args[0]) / std::log(args[1]); }}},
    {"log10", {1, [](auto& args) { return std::log10(args[0]); }}},
    {"exp", {1, [](auto& args) { return std::exp(args[0]); }}},
    {"hyp", {2, [](auto& args) { return std::hypot(args[0], args[1]); }}},
};
