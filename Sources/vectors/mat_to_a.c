/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_spe_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:38 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:20:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

double	*mat4_to_a(t_mat4 mat)
{
	double	*ret;
	int		i;
	int		j;

	if (!(ret = ft_memalloc(sizeof(double) * 16)))
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret[i * 4 + j] = mat.mat[i][j];
	}
	return (ret);
}

double	*mat3_to_a(t_mat3 mat)
{
	double	*ret;
	int		i;
	int		j;

	if (!(ret = ft_memalloc(sizeof(double) * 3)))
		return (NULL);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			ret[i * 3 + j] = mat.mat[i][j];
	}
	return (ret);
}
