/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:09 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:56:10 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2	add_v2(t_vec2 a, t_vec2 b)
{
	t_vec2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vec3	add_v3(t_vec3 a, t_vec3 b)
{
	t_vec3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec4	add_v4(t_vec4 a, t_vec4 b)
{
	t_vec4 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	return (c);
}

t_vec	add_v(t_vec a, t_vec b)
{
	t_vec	c;
	int		i;

	if ((a.size != b.size) || (!(c = init_v(a.size)).vec))
		return ((t_vec){-1, NULL});
	i = -1;
	while (++i)
		c.vec[i] = a.vec[i] + b.vec[i];
	return (c);
}