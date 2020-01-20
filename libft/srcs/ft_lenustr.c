/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putustr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 03:51:01 by esuits            #+#    #+#             */
/*   Updated: 2018/01/20 18:48:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_lenuchar(unsigned int c)
{
	int i;
	int j;

	i = ft_bitsize(c);
	if (!(j = 0) && (i <= 7 + (MB_CUR_MAX == 1)))
		return (1);
	if (i == 8)
		j--;
	while (++j <= 7)
		if (i <= 6 + j * 5)
			break ;
	if ((c > 0x10ffff || (c >= 0xd800 && c <= 0xdfff) || j >= MB_CUR_MAX))
		return (-1);
	return (j + 1);
}

int		ft_lenustri(unsigned int *str)
{
	int i;
	int len;

	len = 0;
	while (*str)
	{
		i = ft_lenuchar(*str);
		len += i;
		if (i == -1)
			return (-1);
		str++;
	}
	return (len);
}

int		ft_lenunstri(unsigned int *str, int n)
{
	int i;
	int len;

	len = 0;
	while (len <= n && *str)
	{
		i = ft_lenuchar(*str);
		if (i == -1 && len != n)
			return (-1);
		else if (len == n && i == -1)
			break ;
		len += i;
		str++;
	}
	if (len > n && i != -1)
		len -= i;
	return (len);
}
