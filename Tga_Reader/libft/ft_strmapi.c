/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:43:47 by esuits            #+#    #+#             */
/*   Updated: 2018/11/11 05:29:48 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		str[i] = (*f)(i, s[i]);
	str[i] = '\0';
	return (str);
}
