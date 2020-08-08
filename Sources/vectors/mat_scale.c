#include "../../Include/vectors.h"

t_mat3	scale_mat3(double a, t_mat3 b)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			b.mat[i][j] *= a;
	}
	return (b);
}

t_mat4	scale_mat4(double a, t_mat4 b)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			b.mat[i][j] *= a;
	}
	return (b);
}

t_mat	scale_mat(double a, t_mat b)
{
	int i;
	int j;

	i = -1;
	while (++i < b.h)
	{
		j = -1;
		while (++j < b.w)
			b.mat[i][j] *= a;
	}
	return (b);
}