/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 02:06:45 by esuits            #+#    #+#             */
/*   Updated: 2018/01/20 18:28:58 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int		ft_putuchar(unsigned int c)
{
	int i;
	int j;
	int nb;
	int mask;

	i = ft_bitsize(c);
	if (!(j = 0) && i <= (7 + (MB_CUR_MAX == 1)))
		return (write(1, &c, 1));
	while (++j <= 7 && !(i <= 6 + j * 5))
		;
	if ((mask = 1) && (((c > 0xd7ff && c < 0xe000) || (j >= MB_CUR_MAX)) ||
			c > 0x10ffff))
		return (-1);
	nb = j;
	while (nb--)
		mask = (mask << 1) + 1;
	mask <<= (6 - j + 1);
	nb = (mask | (c >> j * 6));
	write(1, &nb, 1);
	while (j--)
	{
		nb = 0xff & (128 | ((c >> (j * 6)) & 63));
		write(1, &nb, 1);
	}
	return (1);
}

int		ft_putnustr(unsigned int *str, int size)
{
	int len;

	len = ft_lenuchar(*str);
	while (len <= size)
	{
		ft_putuchar(*str);
		str++;
		if (ft_lenuchar(*str) == -1)
			return (-1);
		len += ft_lenuchar(*str);
	}
	if (len > size)
		len -= ft_lenuchar(*str);
	return (len);
}
