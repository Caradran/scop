/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 07:18:37 by esuits            #+#    #+#             */
/*   Updated: 2018/11/11 07:34:53 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(dst);
	if (size <= i)
		return (size + ft_strlen(src));
	ft_strncat(dst, src, size - (i + 1));
	return (i + ft_strlen(src));
}
