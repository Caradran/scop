/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:24:51 by esuits            #+#    #+#             */
/*   Updated: 2018/11/12 14:45:46 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (n == 0)
		return (1);
	n--;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
		i++;
	if (s1[i] != s2[i])
		return (0);
	return (1);
}
