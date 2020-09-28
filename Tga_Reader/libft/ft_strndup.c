/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:14:53 by esuits            #+#    #+#             */
/*   Updated: 2019/03/06 10:14:55 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t len)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = '\0';
	ft_strncpy(ret, str, len);
	return (ret);
}
