#include "vectors.h"

t_mat	mult_mat(t_mat a, t_mat b)
{
	int			i;
	int			j;
	int			k;
	t_mat		c;

	if ((a.w != b.h) || !((c = init_mat(a.h, b.w)).mat))
		return ((t_mat){-1, -1, NULL});
	i = -1;
	while (++i < a.w && (j = -1))
		while (++j < b.h && (k = -1))
			while (++k < a.h)
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
	return (c);
}

t_mat3 mult_mat3(t_mat3 a, t_mat3 b)
{
	int			i;
	int			j;
	int			k;
	t_mat3		c;

	i = -1;
	while (++i < 3 && (j = -1))
		while (++j < 3 && (k = -1))
			while (++k < 3)
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
	return (c);
}

t_mat4 mult_mat4(t_mat4 a, t_mat4 b)
{
	int			i;
	int			j;
	int			k;
	t_mat4		c;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4 && (k = -1))
			while (++k < 4)
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
	return (c);
}