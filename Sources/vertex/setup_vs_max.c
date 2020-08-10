/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_vs_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:56:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/09 19:22:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"
/*
void	set_max_vs(t_obj	*obj)
{
	int i;
	int max_vs;
	int *nb_vs_size;

	i = 0;
	max_vs = 0;
	while (i < obj->f_size)
	{
		if (max_vs < obj->f[i].size)
			max_vs = obj->f[i].size;
		i++;
	}
	max_vs--;

	nb_vs_size = ft_memalloc(sizeof(int) * (max_vs + 1));
	i = 0;
	while (i <= obj->f_size)
	{
		if (obj->f[i].size >= 2)
			nb_vs_size[obj->f[i].size - 2]++;
		i++;
	}

	obj->max_vs = max_vs;
	obj->nb_vs_size = nb_vs_size;
}*/