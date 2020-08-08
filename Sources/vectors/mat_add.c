#include "../../Include/vectors.h"

t_mat3	add_mat3(t_mat3 a, t_mat3 b)
{
	int			i;
	int			j;
	int			k;
	t_mat3		c;


	i = -1;
	while (++i < 3 && (j = -1))
		while (++j < 3 && (k = -1))
			c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
	return (c);
}

t_mat4	add_mat4(t_mat4 a, t_mat4 b)
{
	int			i;
	int			j;
	int			k;
	t_mat4		c;


	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4 && (k = -1))
			c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
	return (c);
}

t_mat	add_mat(t_mat a, t_mat b)
{
	int			i;
	int			j;
	t_mat		c;

	if ((a.w != b.h) || !((c = init_mat(a.h, b.w)).mat))
		return ((t_mat){-1, -1, NULL});
	i = -1;
	while (++i < a.w && (j = -1))
		while (++j < b.h)
			c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
	return (c);
}
