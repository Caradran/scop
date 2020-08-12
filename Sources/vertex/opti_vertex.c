/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:46 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/12 18:34:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

static int		find_point(float *point, float tmp[13],int max)
{
	int	i;

	i = -1;
	while (++i < max)
		if (!(ft_memcmp(&(point[i * 13]), tmp, 13)))
			return (i);
	return (-1);
}

static void		fill_tmp(float (*tmp)[13], int *indices, t_obj *obj, int i)
{
	int	index;

	// if (indices[i] > obj->size_v[0] || indices[i] < 0)
	// 	printf("Error size_v, %d\n", indices[i]);
	// if (indices[i + 1] > obj->size_vt[0] || indices[i + 1] < 0)
	// 	printf("Error size_vt, %d\n", indices[i + 1]);
	// if (indices[i + 2] > obj->size_vn[0] || indices[i + 2] < 0)
	// 	printf("Error size_vn, %d\n", indices[i + 2]);
	(*tmp)[0] = obj->v[indices[i]].x;
	(*tmp)[1] = obj->v[indices[i]].y;
	(*tmp)[2] = obj->v[indices[i]].z;
	(*tmp)[3] = obj->v[indices[i]].w;
	if (indices[i + 1] == -1)
	{
		(*tmp)[4] = ((*tmp)[0] + fabs(obj->min.x)) / (obj->max.x + fabs(obj->min.x));
		(*tmp)[5] = ((*tmp)[1] + fabs(obj->min.y)) / (obj->max.y + fabs(obj->min.y));
		(*tmp)[6] = ((*tmp)[2] + fabs(obj->min.z)) / (obj->max.z + fabs(obj->min.z));
	}
	else
	{
		(*tmp)[4] = obj->vt[indices[i + 1]].x;
		(*tmp)[5] = obj->vt[indices[i + 1]].y;
		(*tmp)[6] = obj->vt[indices[i + 1]].z;
	}
	if (indices[i + 2] == -1)
	{
		(*tmp)[7] = ((*tmp)[0] + fabs(obj->min.x)) / (obj->max.x + fabs(obj->min.x));
		(*tmp)[8] = ((*tmp)[1] + fabs(obj->min.y)) / (obj->max.y + fabs(obj->min.y));
		(*tmp)[9] = ((*tmp)[2] + fabs(obj->min.z)) / (obj->max.z + fabs(obj->min.z));
	}
	else
	{
		(*tmp)[7] = obj->vn[indices[i + 2]].x;
		(*tmp)[8] = obj->vn[indices[i + 2]].y;
		(*tmp)[9] = obj->vn[indices[i + 2]].z;
	}
	(*tmp)[10] = 0;
	(*tmp)[11] = 0;
	(*tmp)[12] = 0;
}

t_index			create_vert(t_obj obj, int *index, int size)
{
	t_index		tmpi;
	t_index		ret;
	float		tmp[13];
	int			max;
	int			i;
    int	 		j;
	int			find;

	if (!(tmpi.verts = ft_memalloc(sizeof(float) * size * 9 * 13)))
		return ((t_index){NULL, NULL});
	if (!(tmpi.index = ft_memalloc(sizeof(int) * size * 9)))
		return ((t_index){NULL, NULL});
    i = -1;
    max = 0;
    find = 0;
    while (++i < size * 3)
    {
        fill_tmp(&tmp, index, &obj, i * 3);
        if ((find = find_point(tmpi.verts, tmp, max)) == -1)
        {
            ft_memcpy(&(tmpi.verts[max * 13]), tmp, 13 * sizeof(float));
            find = max;
            max += 1;   
        }
		tmpi.index[i] = find;
	}
	if (!(ret.verts = malloc(sizeof(float) * max * 13)))
		return ((t_index){NULL, NULL});
	if (!(ret.index = malloc(sizeof(int) * i * 9)))
		return ((t_index){NULL, NULL});
	ret.size = max * 13;
	ret.index_size = i;
	i = -1;
	while (++i < ret.index_size)
		ret.index[i] = tmpi.index[i];
	i = -1;
	while (++i < ret.size)
		ret.verts[i] = tmpi.verts[i];
	free(tmpi.index);
	free(tmpi.verts);
	return (ret);
}