#include "../../Include/vectors.h"

void	print_mat3(t_mat3 a)
{
	int			i;
	int			j;
	int			k;


	printf("mat 3 :\n");
	i = -1;
	while (++i < 3 && (j = -1))
	{
		while (++j < 3 && (k = -1))
		{
			printf("%5lf ", a.mat[i][j]);
		}
		printf("\n");
	}
	return ;
}

void	print_mat4(t_mat4 a)
{
	int			i;
	int			j;
	int			k;


	printf("mat 4 :\n");
	i = -1;
	while (++i < 4 && (j = -1))
	{
		while (++j < 4 && (k = -1))
		{
			printf("%5lf ", a.mat[i][j]);
		}
		printf("\n");
	}
	return ;
}

void	print_mat(t_mat a)
{
	int			i;
	int			j;
	t_mat		c;

	if ((a.w <= 0) || (a.h <= 0))
	{
		printf("cannot print matrice\n");
		return ;
	}
	i = -1;
	while (++i < a.w && (j = -1))
	{
		while (++j < a.h)
			printf("%5lf ", a.mat[i][j]);
		printf("\n");
	}
	return ;
}
