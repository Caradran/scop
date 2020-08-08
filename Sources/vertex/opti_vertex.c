/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:46 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/08 18:13:11 by lomasse          ###   ########.fr       */
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

static void		fill_tmp(float (*tmp)[13], int *indices, float *points, int i)
{
	int	index;
	int save;

	index = -1;
	while (++index < 4)
		(*tmp)[index] = points[(indices[i] * 13) + index];
	save = (indices[i] * 13);
	index = -1;
	while (++index < 3)
		(*tmp)[index + 4] = points[(indices[i + 3] * 13) + index + 4];
	index = -1;
	while (++index < 3)
		(*tmp)[index + 7] = points[(indices[i + 6] * 13) + index + 10];
	index = -1;
	while (++index < 3)
		(*tmp)[index + 10] = 0;
	index = 4;
	while (++index < 13)
		if ((*tmp)[index] == -1)
			(*tmp)[index] = points[save + ((index - 4) % 3)];
}

t_index			create_vert(t_obj obj, int *index, float *points)
{
	t_index		ret;
	float		tmp[13];
	int			size;
	int			i;
	int			find;

	if (!(ret.verts = malloc(sizeof(t_index) * obj.nb_vs_size[1] * 3 * 13)))
		return ((t_index){NULL, NULL});
	if (!(ret.index = malloc(sizeof(t_index) * obj.nb_vs_size[1] * 3)))
		return ((t_index){NULL, NULL});
	i = -1;
	size = 0;
	while (++i < obj.nb_vs_size[1] * 3)
	{
		fill_tmp(&tmp, index, points, (i % 3) + ((i / 3) * 9));
		if ((find = find_point(ret.verts, tmp, size)) == -1)
		{
			ft_memcpy(&(ret.verts[size * 13]), tmp, 13 * 4);
			find = size;
			size += 1;
		}
		ret.index[i] = find;
	}
	ret.size = size;
	ret.index_size = i;
	return (ret);
}