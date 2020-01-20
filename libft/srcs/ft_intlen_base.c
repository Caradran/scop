/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 07:36:30 by esuits            #+#    #+#             */
/*   Updated: 2018/01/06 04:21:30 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_uintlen_base(unsigned long long nb, int base, int flag)
{
	int len;

	len = 1;
	while (nb /= base)
		len++;
	if (flag && base == 16)
		len += 2;
	if (flag && base == 8)
		len++;
	return (len);
}
