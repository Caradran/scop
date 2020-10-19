/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:56:46 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 21:31:05 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/vectors.h"

double	get_value_vec2(t_vec2 a, int b)
{
	if (b == 0)
		return (a.x);
	else if (b == 1)
		return (a.y);
	else
		return (NAN);
}

double	get_value_vec3(t_vec3 a, int b)
{
	if (b == 0)
		return (a.x);
	else if (b == 1)
		return (a.y);
	else if (b == 2)
		return (a.z);
	else
		return (NAN);
}

double	get_value_vec4(t_vec4 a, int b)
{
	if (b == 0)
		return (a.x);
	else if (b == 1)
		return (a.y);
	else if (b == 2)
		return (a.z);
	else if (b == 3)
		return (a.z);
	else
		return (NAN);
}
