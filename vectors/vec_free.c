/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:55:29 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:55:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	free_v(t_vec *a)
{
	ft_memdel((void **)a->vec);
}

void	free_mat(t_mat *a)
{
	int j;

	j = -1;
	while (++j < a->w)
		ft_memdel((void**)a->mat[j]);
	ft_memdel((void**)a->mat);
}

t_mat	free_mat_err(t_mat *mat, int i)
{
	int j;

	j = -1;
	while (++j < i)
		ft_memdel((void**)mat->mat[j]);
	ft_memdel((void**)mat->mat);
	return ((t_mat){-1, -1, NULL});
}
