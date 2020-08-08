#include "../../Include/vectors.h"

double get_value_vec2(t_vec2 a, int b)
{
	if (b == 0)
		return a.x;
	else if (b == 1)
		return a.y;
	else 
		return NAN;
}

double get_value_vec3(t_vec3 a, int b)
{
	if (b == 0)
		return a.x;
	else if (b == 1)
		return a.y;
	else if (b == 2)
		return a.z;
	else 
		return NAN;
}
double get_value_vec4(t_vec4 a, int b)
{
	if (b == 0)
		return a.x;
	else if (b == 1)
		return a.y;
	else if (b == 2)
		return a.z;
	else if (b == 3)
		return a.z;
	else 
		return NAN;
}