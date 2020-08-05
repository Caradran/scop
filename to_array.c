#include "scop.h"

// ssot = size, step, offset, type
void	fill_ret(float **ret, int ssot[4], float *vert)
{
	int i;
	int j;

	i = 0;
	while (i < ssot[0] / ssot[3])
	{
		j = 0;
		while (j < ssot[3])
		{
			(*ret)[i * ssot[1] + ssot[2] + j] = vert[i * ssot[3] + j];
			j++;
		}
		i++;
	}
}

float	*vect_toa(t_obj obj)
{
	float *ret;

	if (!(ret = ft_memalloc(sizeof(float) * max_4(obj.v.size, obj.vn.size, obj.vp.size, obj.vt.size) * 4)))
		return (NULL);
	fill_ret(&ret, (int[4]){obj.v.size, 13, 0, 4}, obj.v.v);
	fill_ret(&ret, (int[4]){obj.vn.size, 13, 4, 3}, obj.vn.v);
	fill_ret(&ret, (int[4]){obj.vp.size, 13, 7, 3}, obj.vp.v);
	fill_ret(&ret, (int[4]){obj.vt.size, 13, 10, 3}, obj.vt.v);
	print_array(ret, obj);
	return (ret);
}

void	print_array(float *array, t_obj obj)
{
	int i;

	i = 0;
	while (i < max_4(obj.v.size, obj.vn.size, obj.vp.size, obj.vt.size) * 4)
	{
		printf("%f ", array[i]);
		i++;
		if (!((i - 4) % 13))
			printf("\n");
		if (!((i - 7) % 13))
			printf("\n");
		if (!((i - 10) % 13))
			printf("\n");
		if (!(i % 13))
			printf("\n");
	}
	printf("\n");
}


void	ft_concat_n(int **indices, t_f f, int n, int nb_cp)
{
	int i;

	i = 0;
	while (i < n)
	{
		(*indices)[nb_cp * 3 * n + i] = f.verts[i] - 1;
		i++;
	}
	i = 0;
	while (i < n)
	{
		(*indices)[nb_cp * 3 * n + 1 * n + i] = f.vn[i] - 1;
		i++;
	}
	i = 0;
	while (i < n)
	{
		(*indices)[nb_cp * 3 * n + 2 * n + i] = f.vt[i] - 1;
		i++;
	}
}

int	*faces_n_toa(t_obj obj, int size)
{
	int i;
	int *indices;
	int nb_vs;
	int nb_cp;

	i = 0;
	nb_vs = 0;
	while (i < obj.f_size)
	{
		if (size == obj.f[i].size)
			nb_vs++;
		i++;
	}
	if (!(indices = ft_memalloc(sizeof(int) * nb_vs * 3 * size)))
		return (NULL);
	i = 0;
	nb_cp = 0;
	while (i < obj.f_size)
	{
		if (size == obj.f[i].size)
			ft_concat_n(&indices, obj.f[i], size, nb_cp++);
		i++;
	}
	i = 0;
	while (i < nb_vs)
	{
		nb_cp = 0;
		while (nb_cp < size * 3)
		{
			printf("%d ", indices[i * size * 3 + nb_cp]);
			nb_cp++;
		}
		printf("\n");
		i++;
	}
	return (indices);
}

int **faces_toa(t_obj obj)
{
	int i;
	int **indices;

	i = 0;


	if (!(indices = ft_memalloc(sizeof(int*) * obj.max_vs)))
		return (NULL);
	i = 0;
	while (i < obj.max_vs)
	{
		indices[i] = faces_n_toa(obj, i + 2);
		i++;
	}
	return (indices);
}

