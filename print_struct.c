#include "scop.h"

void	print_vert(t_vert vert, int type)
{
	int i = 0;

	printf("-------- vert size : %d -------\n", vert.size);
	while (i < vert.size)
	{
		printf("%3f ", vert.v[i]);
		if (!((i + 1) % type))
			printf("\n");
		i++;
	}
	printf("-------------------\n\n");
}

void	print_point(t_p point, int n)
{
	int i = 0;

	printf("\npoint n %d size : %d \n", n, point.size);
	while(i < point.size)
		printf("%d ", point.verts[i++]);
	printf("\n");
}

void	print_points(t_obj obj)
{
	int i = 0;

	printf("\n--- print %d points ---\n", obj.p_size);
	while (i < obj.p_size)
	{
		print_point(obj.p[i], i);
		i++;
	}
	printf("-------------------\n\n");
}

void	print_obj(t_obj obj)
{
	print_vert(obj.v, 4);
	print_vert(obj.vp, 3);
	print_vert(obj.vn, 3);
	print_vert(obj.vt, 3);

/*	print_points(obj.p, obj);
//	print_lines(obj.l, obj);
//	print_faces(obj.f, obj);*/
}