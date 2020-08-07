/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:26 by esuits            #+#    #+#             */
/*   Updated: 2019/04/24 17:56:27 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	norme_v2(t_vec2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vec2	normalize_v2(t_vec2 a)
{
	double norm;

	if (a.x == 0 && a.y == 0)
		return (a);
	norm = norme_v2(a);
	return (scale_v2(1 / norm, a));
}

double	norme_v3(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	normalize_v3(t_vec3 a)
{
	double norm;

	if (a.x == 0 && a.y == 0 && a.z == 0)
		return (a);
	norm = norme_v3(a);
	return (scale_v3(1 / norm, a));
}
