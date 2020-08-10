/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_faces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:11 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/10 16:51:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

int		split_other(int **ret, t_obj *obj, int index, int *i)
{
	int j;
	int	save[3];

	j = -1;
	while (++j < obj->face[index].size - 2)
	{
		save[0] = obj->face[index].i_v[0] - 1;
		save[1] = obj->face[index].i_vt[0] - 1;
		save[2] = obj->face[index].i_vn[0] - 1;
		(*ret)[*i + 0] = save[0];
		(*ret)[*i + 1] = save[1];
		(*ret)[*i + 2] = save[2];
		(*ret)[*i + 3] = obj->face[index].i_v[j + 1] - 1;
		(*ret)[*i + 4] = obj->face[index].i_vt[j + 1] - 1;
		(*ret)[*i + 5] = obj->face[index].i_vn[j + 1] - 1;
		(*ret)[*i + 6] = obj->face[index].i_v[j + 2] - 1;
		(*ret)[*i + 7] = obj->face[index].i_vt[j + 2] - 1;
		(*ret)[*i + 8] = obj->face[index].i_vn[j + 3] - 1;
		*i += 9;
	}
	return (0);
}

int		*fill_ret(int	*ret, t_obj *obj)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (++index < obj->size_face[0])
	{
		if (obj->face[index].size == 3)
		{
			ret[i + 0] = obj->face[index].i_v[0] - 1;
			ret[i + 1] = obj->face[index].i_vt[0] - 1;
			ret[i + 2] = obj->face[index].i_vn[0] - 1;
			ret[i + 3] = obj->face[index].i_v[1] - 1;
			ret[i + 4] = obj->face[index].i_vt[1] - 1;
			ret[i + 5] = obj->face[index].i_vn[1] - 1;
			ret[i + 6] = obj->face[index].i_v[2] - 1;
			ret[i + 7] = obj->face[index].i_vt[2] - 1;
			ret[i + 8] = obj->face[index].i_vn[2] - 1;
			i += 9;
		}
		else
			split_other(&ret, obj, index, &i);
	}
	return (ret);
}

int		*split_faces(t_obj *obj, int *size)
{
	int size_malloc;
	int	i;
	int	*ret;

	i = -1;
	size_malloc = 0;
	while (++i < obj->size_face[0])
		size_malloc += obj->face[i].size - 2;
	if (!(ret = ft_memalloc(size_malloc * 9 * sizeof(int))))
		return (NULL);
	*size = size_malloc;
	ret = fill_ret(ret, obj);
	i = -1;
	while (++i < size_malloc * 9)
		printf("%d\n", ret[i]);
	return (ret);
}

/*
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
		return (NULL);*/
	/* Save the old face */
	// if (obj->nb_vs_size[1])
	// 	ft_memcpy(ret, indices[1], obj->nb_vs_size[1] * 9 * 4);
	/* Split */
// 	int currentpos;
// 	int save[3];
// 	int old;
// 	int k;
// 	int ligne;

// 	currentpos = obj->nb_vs_size[1] * 9;
// 	i = 1;
// 	while (++i < obj->max_vs)
// 	{
// 		ligne = (i + 2) * 3;
// 		j = -1;
// 		while (++j < obj->nb_vs_size[i])
// 		{
// 			save[0] = indices[i][0 + (j * ligne)];
// 			save[1] = indices[i][(1 * (i + 2)) + (j * ligne)];
// 			save[2] = indices[i][(2 * (i + 2)) + (j * ligne)];
// 			k = -1;
// 			while (++k < i)
// 			{
// 				ret[currentpos] = save[0];
// 				ret[currentpos + 1] = indices[i][(j * ligne) + (k + 1)];
// 				ret[currentpos + 2] = indices[i][(j * ligne) + (k + 2)];
// 				ret[currentpos + 3] = save[1];
// 				ret[currentpos + 4] = indices[i][(j * ligne) + (k + 1) + (i + 2)];
// 				ret[currentpos + 5] = indices[i][(j * ligne) + (k + 2) + (i + 2)];
// 				ret[currentpos + 6] = save[2];
// 				ret[currentpos + 7] = indices[i][(j * ligne) + (k + 1) + ((i + 2) * 2)];
// 				ret[currentpos + 8] = indices[i][(j * ligne) + (k + 2) + ((i + 2) * 2)];
// 				currentpos += 9;
// 			}
// 		}
// 	}
// 	i = -1;
// 	while (++i < obj->max_vs)
// 		obj->nb_vs_size[i] = 0;
// 	obj->nb_vs_size[1] = currentpos / 9;
// 	obj->max_vs = 2;
// 	return (ret);
// }*/