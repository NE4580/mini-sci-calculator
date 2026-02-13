// utils.cpp
#include "mathUtils.hpp"
#include "cmath"

AngleMode CURRENT_ANGLE_MODE = AngleMode::RAD;

double toRadians(double angle)
{
	if (CURRENT_ANGLE_MODE == AngleMode::DEG) { return angle * M_PIf / 180.0F; }
	return angle;
}

double fromRadians(double angle)
{
	if (CURRENT_ANGLE_MODE == AngleMode::DEG) { return angle * 180.0F / M_PIf; }
	return angle;
}
