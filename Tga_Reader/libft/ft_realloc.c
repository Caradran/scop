/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:33:21 by esuits            #+#    #+#             */
/*   Updated: 2018/11/14 09:21:00 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *s, size_t n)
{
	char	*str;

	str = NULL;
	if (n > ft_strlen(s))
		return (NULL);
	str = ft_strdup(&s[n]);
	free(s);
	return (str);
}
