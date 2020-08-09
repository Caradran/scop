#include "../../Include/vectors.h"

double	dot_vec2(t_vec2 a, t_vec2 b)
{
	double c;

	c = 0;
	c += a.x * b.x;
	c += a.y * b.y;
	return (c);
}

double	dot_vec3(t_vec3 a, t_vec3 b)
{
	double c;

	c = 0;
	c += a.x * b.x;
	c += a.y * b.y;
	c += a.z * b.z;
	return (c);
}

double dot_vec4(t_vec4 a, t_vec4 b)
{
	double c;

	c = 0;
	c += a.x * b.x;
	c += a.y * b.y;
	c += a.z * b.z;
	c += a.w * b.w;
	return (c);
}

double	vec_dot(t_vec a, t_vec b)
{
	double	c;
	int		i;

	c = 0;
	i = -1;
	while (++i)
		c += a.vec[i] * b.vec[i];
	return (c);
}

t_vec3 cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 c;
	
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}