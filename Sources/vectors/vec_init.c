/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:14 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

t_vec2	init_v2(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec3	init_v3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec4	init_v4(double x, double y, double z, double w)
{
	return ((t_vec4){x, y, z, w});
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
