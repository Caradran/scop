/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:14 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 18:31:31 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2	init_v2(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec3	init_v3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec	init_v(int size)
{
	t_vec vec;

	if (size <= 0
		|| (!(vec.vec = (double*)ft_memalloc(vec.size * sizeof(double)))))
		return ((t_vec){-1, NULL});
	vec.size = size;
	return (vec);
}

t_mat	init_mat(int w, int h)
{
	t_mat	mat;
	int		i;

	if (w <= 0 || h <= 0)
		return ((t_mat){-1, -1, NULL});
	if (!(mat.mat = ft_memalloc(w * sizeof(double*))))
		return ((t_mat){-1, -1, NULL});
	i = -1;
	while (++i < w)
		if (!(mat.mat[i] = ft_memalloc(h * sizeof(double))))
			return (free_mat_err(&mat, i));
	mat.w = w;
	mat.h = h;
	return (mat);
}
