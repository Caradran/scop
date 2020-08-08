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

double	norme_v3(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double	norme_v4(t_vec4 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z, a.w * a.w));
}