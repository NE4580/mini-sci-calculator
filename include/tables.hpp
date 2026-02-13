// Tables
#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct FunctionMetaData
{
	int arity;
	std::function<double(const std::vector<double>&)> fn;
};

// Constants Table
extern const std::unordered_map<std::string, double> CONSTANTS_TABLE;

// FUNCTIONS
extern const std::unordered_map<std::string, FunctionMetaData> FUNCTIONS_TABLE;
