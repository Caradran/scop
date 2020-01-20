/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 01:47:54 by esuits            #+#    #+#             */
/*   Updated: 2018/01/05 01:50:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putunbr(unsigned long long int n)
{
	char c;

	if (n <= 9)
	{
		c = n + 48;
		write(1, &c, 1);
		return ;
	}
	ft_putunbr(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}
