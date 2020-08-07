/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:55:39 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:55:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3	mult_mat_v3(t_vec3 b, t_mat a)
{
	t_vec3 c;

	if (a.w != 3 || a.h != 3)
		return ((t_vec3){NAN, NAN, NAN});
	c.x = a.mat[0][0] * b.x + a.mat[1][0] * b.y + a.mat[2][0] * b.z;
	c.y = a.mat[0][1] * b.x + a.mat[1][1] * b.y + a.mat[2][1] * b.z;
	c.z = a.mat[0][2] * b.x + a.mat[1][2] * b.y + a.mat[2][2] * b.z;
	return (c);
}

t_vec2	mult_mat_v2(t_vec2 b, t_mat a)
{
	t_vec2 c;

	if (a.w != 2 || a.h != 2)
		return ((t_vec2){NAN, NAN});
	c.x = a.mat[0][0] * b.x + a.mat[1][0] * b.y;
	c.y = a.mat[0][1] * b.x + a.mat[1][1] * b.y;
	return (c);
}

t_vec	mult_mat_v(t_vec b, t_mat a)
{
	t_vec	c;
	int		i;
	int		j;

	if ((a.w != b.size) || ((c = init_v(a.h)).size == -1))
		return ((t_vec){-1, NULL});
	i = -1;
	while (++i < a.h)
	{
		j = -1;
		while (++j < a.w)
			c.vec[i] += a.mat[j][i] * b.vec[j];
	}
	return (c);
}
