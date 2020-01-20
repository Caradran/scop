/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 05:50:39 by esuits            #+#    #+#             */
/*   Updated: 2018/01/06 04:38:53 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <limits.h>

void	ft_putnbr_base(long long nbr, int base, int flag)
{
	unsigned long long	nb;
	int					n;
	char				c;

	if ((base == 10 && flag == 2 && (((long long)nbr) < 0)) && nbr != LONG_MIN)
		return (ft_putnbr((int)-1 * nbr));
	if ((nb = (unsigned long long)nbr) <= (unsigned int)base - 1)
	{
		if (nb < 10)
			c = nb + 48;
		else if (!flag)
			c = nb + 'a' - 10;
		else
			c = nb + 'A' - 10;
		return ((void)write(1, &c, 1));
	}
	ft_putnbr_base(nb / base, base, flag);
	if ((n = nb % base) < 10)
		c = n + 48;
	else if (!flag)
		c = n + 'a' - 10;
	else
		c = n + 'A' - 10;
	write(1, &c, 1);
}
