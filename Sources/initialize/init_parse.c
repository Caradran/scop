// #include "../../Include/scop.h"

// t_vert	init_vert(void)
// {
// 	float *vert;

// 	if (!(vert = ft_memalloc(5040 * sizeof(float))))
// 		return ((t_vert){-1, NULL});
// 	else
// 		return ((t_vert){0, vert});
// }

// t_p		init_p(void)
// {
// 	int *verts;

// 	if (!(verts = ft_memalloc(1024 * sizeof(float))))
// 		return ((t_p){-1, NULL});
// 	else
// 		return ((t_p){0, verts});
// }

// t_l		init_l(void)
// {
// 	int *verts;
// 	int *vt;

// 	if (!(verts = ft_memalloc(1024 * sizeof(float)))
// 		|| !(vt = ft_memalloc(1024 * sizeof(float))))
// 		return ((t_l){-1, NULL, NULL});
// 	else
// 		return ((t_l){0, verts, vt});
// }

// t_f		init_f(void)
// {
// 	int *verts;
// 	int *vt;
// 	int *vn;

// 	if (!(verts = ft_memalloc(1024 * sizeof(float)))
// 		|| !(vt = ft_memalloc(1024 * sizeof(float)))
// 		|| !(vn = ft_memalloc(1024 * sizeof(float))))
// 		return ((t_f){-1, -1, NULL, NULL, NULL});
// 	else
// 		return ((t_f){0, -1, verts, vt, vn});
// }

// t_obj	init_obj(void)
// {
// 	t_obj	obj;
// 	int		i;

// 	obj.error = 0;
// 	obj.v = init_vert();
// 	obj.vp = (t_vp)init_vert();
// 	obj.vn = (t_vn)init_vert();
// 	obj.vt = (t_vt)init_vert();
// 	obj.p_size = 0;
// 	obj.p = ft_memalloc(1024 * sizeof(t_p));
// 	obj.l_size = 0;
// 	obj.l = ft_memalloc(1024 * sizeof(t_l));
// 	obj.f_size = 0;
// 	obj.f = ft_memalloc(1024 * sizeof(t_f));
// 	i = 0;
// 	while (i < 1024)
// 		obj.f[i++] = init_f();
// 	check_error_obj(&obj);
// 	return (obj);
// }

// t_index init_index(void)
// {
// 	t_index	ind;

// 	if (!(ind.verts = ft_memalloc(1024 * sizeof(float))))
// 		return ((t_index){NULL, NULL});
// 	if (!(ind.index = ft_memalloc(1024 * sizeof(int))))
// 		return ((t_index){NULL, NULL});
// 	return (ind);
// }
