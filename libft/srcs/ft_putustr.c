/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putustr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 03:51:01 by esuits            #+#    #+#             */
/*   Updated: 2018/01/20 18:48:54 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int		ft_putustr(unsigned int *str)
{
	int				i;
	int				mask;
	unsigned int	c;

	i = 0;
	while (*str)
	{
		c = 0;
		if (*str < (mask = 128))
			write(1, str, 1);
		else if (ft_putuchar(*str) == -1)
			return (-1);
		str += 1;
		i += ft_lenuchar(*str);
	}
	return (i);
}
