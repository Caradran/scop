/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 07:21:21 by esuits            #+#    #+#             */
/*   Updated: 2018/11/10 02:34:00 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		i;

	i = ft_strlen(s);
	ret = (char *)s;
	while (i)
	{
		if (ret[i] == c)
			return (&ret[i]);
		i--;
	}
	if (i == 0 && ret[i] != c)
		return (NULL);
	return (&ret[i]);
}
