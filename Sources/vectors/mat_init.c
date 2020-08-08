#include "../../Include/vectors.h"

t_mat	init_mat(int w, int h)
{
	t_mat	mat;
	int		i;

	if (w <= 0 || h <= 0)
		return ((t_mat){-1, -1, NULL});
	if (!(mat.mat = ft_memalloc(w * sizeof(double*))))
		return ((t_mat){-1, -1, NULL});
	i = -1;
	while (++i < w)
		if (!(mat.mat[i] = ft_memalloc(h * sizeof(double))))
			return (free_mat_err(&mat, i));
	mat.w = w;
	mat.h = h;
	return (mat);
}

t_mat3 init_mat3(void)
{
	int			i;
	int			j;
	t_mat3		c;

	i = -1;
	while (++i < 3 && (j = -1))
		while (++j < 3)
			c.mat[i][j] = (i == j);
	return (c);
}

t_mat4 init_mat4(void)
{
	int			i;
	int			j;
	t_mat4		c;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
			c.mat[i][j] = (i == j);
	return (c);
}