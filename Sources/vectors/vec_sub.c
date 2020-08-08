/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:02 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

t_vec2	sub_v2(t_vec2 a, t_vec2 b)
{
	t_vec2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_vec3	sub_v3(t_vec3 a, t_vec3 b)
{
	t_vec3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vec4	sub_v4(t_vec4 a, t_vec4 b)
{
	t_vec4 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
	return (c);
}

t_vec	sub_v(t_vec a, t_vec b)
{
	t_vec	c;
	int		i;

	if ((a.size != b.size) || (!(c = init_v(a.size)).vec))
		return ((t_vec){-1, NULL});
	i = -1;
	while (++i)
		c.vec[i] = a.vec[i] - b.vec[i];
	return (c);
}
