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
			(*ret)[i * ssot[1] + ssot[2] + j] = vert[i + j];
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