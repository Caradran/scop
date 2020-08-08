/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_faces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:11 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/08 18:14:37 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

int		*split_faces(int **indices, t_obj *obj)
{
	int i;
	int j;
	int size;
	int size_malloc;
	int *ret;
	int *tmp;

	i = 1;
	size_malloc = 0;
	while (i < obj->max_vs)
	{
		size_malloc += obj->nb_vs_size[i] * 3 * i;
		i++;
	}
	if (!(ret = ft_memalloc(size_malloc * sizeof(int) * 3)))
		return (NULL);
	/* Save the old face */
	if (obj->nb_vs_size[1])
		ft_memcpy(ret, indices[1], obj->nb_vs_size[1] * 9 * 4);
	/* Split */
	int currentpos;
	int save[3];
	int old;
	int k;
	int ligne;

	currentpos = obj->nb_vs_size[1] * 9;
	i = 1;
	while (++i < obj->max_vs)
	{
		ligne = (i + 2) * 3;
		j = -1;
		while (++j < obj->nb_vs_size[i])
		{
			save[0] = indices[i][0 + (j * ligne)];
			save[1] = indices[i][(1 * (i + 2)) + (j * ligne)];
			save[2] = indices[i][(2 * (i + 2)) + (j * ligne)];
			k = -1;
			while (++k < i)
			{
				ret[currentpos] = save[0];
				ret[currentpos + 1] = indices[i][(j * ligne) + (k + 1)];
				ret[currentpos + 2] = indices[i][(j * ligne) + (k + 2)];
				ret[currentpos + 3] = save[1];
				ret[currentpos + 4] = indices[i][(j * ligne) + (k + 1) + (i + 2)];
				ret[currentpos + 5] = indices[i][(j * ligne) + (k + 2) + (i + 2)];
				ret[currentpos + 6] = save[2];
				ret[currentpos + 7] = indices[i][(j * ligne) + (k + 1) + ((i + 2) * 2)];
				ret[currentpos + 8] = indices[i][(j * ligne) + (k + 2) + ((i + 2) * 2)];
				currentpos += 9;
			}
		}
	}
	i = -1;
	while (++i < obj->max_vs)
		obj->nb_vs_size[i] = 0;
	obj->nb_vs_size[1] = currentpos / 9;
	obj->max_vs = 2;
	return (ret);
}