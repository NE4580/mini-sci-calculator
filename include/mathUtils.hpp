// math utils
#pragma once
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

enum class AngleMode
{
	DEG,
	RAD
};

extern AngleMode CURRENT_ANGLE_MODE;

double toRadians(double angle);
double fromRadians(double angle);
