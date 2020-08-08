/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:55:47 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:19:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

void	print_v2(t_vec2 a)
{
	printf("x : %5lf, y : %5lf\n", a.x, a.y);
}

void	print_v3(t_vec3 a)
{
	printf("x : %5lf, y : %5lf, z : %5lf\n", a.x, a.y, a.z);
}

void	print_v4(t_vec4 a)
{
	printf("x : %5lf, y : %5lf, z : %5lf, w : %5lf\n", a.x, a.y, a.z, a.w);
}

void	print_v(t_vec a)
{
	int i;

	i = -1;
	if (a.size <= 0)
		printf("connot print vector\n");
	while (++i < a.size)
		printf("%5lf\n", a.vec[i]);
}