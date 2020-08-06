/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:35:59 by esuits            #+#    #+#             */
/*   Updated: 2020/08/06 15:31:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1tmp;
	unsigned char	*s2tmp;
	size_t			i;

	s1tmp = (unsigned char*)s1;
	s2tmp = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (s1tmp[i] == s2tmp[i])
			i++;
		else
			return ((int)(s1tmp[i] - s2tmp[i]));
	}
	return (0);
}
