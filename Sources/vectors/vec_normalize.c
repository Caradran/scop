#include "../../Include/vectors.h"

t_vec2	normalize_v2(t_vec2 a)
{
	double norm;

	if (a.x == 0 && a.y == 0)
		return (a);
	norm = norme_v2(a);
	return (scale_v2(1.0 / norm, a));
}

t_vec3	normalize_v3(t_vec3 a)
{
	double norm;

	if (a.x == 0 && a.y == 0 && a.z == 0)
		return (a);
	norm = norme_v3(a);
	return (scale_v3(1.0 / norm, a));
}


t_vec4	normalize_v4(t_vec4 a)
{
	double norm;

	if (a.x == 0 && a.y == 0 && a.z == 0 && a.w == 0)
		return (a);
	norm = norme_v4(a);
	return (scale_v4(1.0 / norm, a));
}