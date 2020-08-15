/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_faces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:54:11 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/15 18:51:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../Include/scop.h"

int		split_other(int **ret, t_obj *obj, int index, int *i, t_group *ptr)
{
	int j;
	int	save[3];

	j = -1;
	save[0] = ptr->face[index].i_v[0] - 1;
	save[1] = ptr->face[index].i_vt[0] - 1;
	save[2] = ptr->face[index].i_vn[0] - 1;
	while (++j < ptr->face[index].size - 2)
	{
		(*ret)[*i + 0] = save[0];
		(*ret)[*i + 1] = save[1];
		(*ret)[*i + 2] = save[2];
		(*ret)[*i + 3] = ptr->face[index].i_v[j + 1] - 1;
		(*ret)[*i + 4] = ptr->face[index].i_vt[j + 1] - 1;
		(*ret)[*i + 5] = ptr->face[index].i_vn[j + 1] - 1;
		(*ret)[*i + 6] = ptr->face[index].i_v[j + 2] - 1;
		(*ret)[*i + 7] = ptr->face[index].i_vt[j + 2] - 1;
		(*ret)[*i + 8] = ptr->face[index].i_vn[j + 2] - 1;
		*i += 9;
	}
	return (0);
}
static int		*fill_ret(int	*ret, t_obj *obj, int *i, int **txt)
{
	int		index;
	int		group;
	int		save;
	t_group *ptr;

	*i = 0;
	ptr = obj->group;
	group = 0;
	save = 0;
	while (ptr)
	{
		index = -1;
		while (++index < ptr->size_face[0])
		{
			if (ptr->face[index].size == 3)
			{
				ret[*i + 0] = ptr->face[index].i_v[0] - 1;
				ret[*i + 1] = ptr->face[index].i_vt[0] - 1;
				ret[*i + 2] = ptr->face[index].i_vn[0] - 1;
				ret[*i + 3] = ptr->face[index].i_v[1] - 1;
				ret[*i + 4] = ptr->face[index].i_vt[1] - 1;
				ret[*i + 5] = ptr->face[index].i_vn[1] - 1;
				ret[*i + 6] = ptr->face[index].i_v[2] - 1;
				ret[*i + 7] = ptr->face[index].i_vt[2] - 1;
				ret[*i + 8] = ptr->face[index].i_vn[2] - 1;
				*i += 9;
			}
			else
				split_other(&ret, obj, index, i, ptr);
			(*txt)[(*i / 9)] = group % 2;
		}
		group += 1;
		ptr = ptr->next;
	}
	return (ret);
}
int		*split_faces(t_obj *obj, int *size, t_index *ret)
{
	int 		size_malloc;
	int			i;
	t_group 	*ptr;

	ptr = obj->group;
	size_malloc = 0;
	while (ptr)
	{
		i = -1;
		while (++i < ptr->size_face[0])
			size_malloc += ptr->face[i].size - 2;
		ptr = ptr->next;
	}
	if (!(ret->index = ft_memalloc(size_malloc * 9 * sizeof(int))))
		return (NULL);
	if (!(ret->index_txt = ft_memalloc((size_malloc * 9 * sizeof(int)) / 3)))
		return (NULL);
	*size = size_malloc;
	i = -1;
	ret->index = fill_ret(ret->index, obj, &i, &ret->index_txt);
	size_malloc = i;
	i = -1;
	return (ret->index);
}