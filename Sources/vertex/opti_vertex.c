/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:46 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/18 18:42:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

static int		find_point(float *point, float tmp[13],int max)
{
	int	i;

	i = -1;
	while (++i < max)
		if (!(ft_memcmp(&(point[i * 13]), tmp, 13 * (sizeof(float)))))
			return (i);
	return (-1);
}

static void		fill_tmp(float (*tmp)[13], int *indices, t_obj *obj, int i)
{
	int	index;

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

static int		find_material(t_obj obj, char *mat)
{
	t_material	*ptr;

	ptr = obj.mtl;
	while (ptr)
	{
		if (!(ft_strcmp(mat, ptr->name)))
			return (ptr->id);
		ptr = ptr->next;
	}
	return (-1);
}

int				create_vert(t_obj obj, t_index **ret, int *index, int size, t_group *ptr_grp)
{
	float		tmp[13];
	int			max;
	int			i;
    int	 		j;
	int			find;

	if (!((*ret)->verts = ft_memalloc(sizeof(float) * size * 9 * 13)))
		return (1);
	if (!((*ret)->index = ft_memalloc(sizeof(int) * size * 9)))
		return (1);
    i = -1;
    max = 0;
    find = 0;
    while (++i < size * 3)
    {
        fill_tmp(&tmp, index, &obj, i * 3);
		if (obj.size_face[0] > (long int)100000 || (find = find_point((*ret)->verts, tmp, max)) == -1)
        {
            ft_memcpy(&((*ret)->verts[max * 13]), tmp, 13 * sizeof(float));
            find = max;
            max += 1;
        }
		(*ret)->index[i] = find;
	}
	if (ptr_grp->material)
		(*ret)->index_txt = find_material(obj, ptr_grp->material);
	else
		(*ret)->index_txt = -1;
	(*ret)->verts_size = max * 13;
	(*ret)->face_size = i;
	return (0);
}