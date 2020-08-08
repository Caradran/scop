/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:55:52 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

t_vec2	scale_v2(double a, t_vec2 b)
{
	return ((t_vec2){b.x * a, b.y * a});
}

t_vec3	scale_v3(double a, t_vec3 b)
{
	return ((t_vec3){b.x * a, b.y * a, b.z * a});
}

t_vec4	scale_v4(double a, t_vec4 b)
{
	return ((t_vec4){b.x * a, b.y * a, b.z * a, b.w * a});
}

t_vec	scale_v(double a, t_vec b)
{
	int i;

	if (b.size <= 0)
		return ((t_vec){-1, NULL});
	i = -1;
	while (++i < b.size)
		b.vec[i] *= a;
	return (b);
}