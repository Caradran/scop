/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:15:03 by esuits            #+#    #+#             */
/*   Updated: 2019/03/06 10:15:05 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdupfree(char **str, char c)
{
	char *new;

	new = ft_strdup(ft_strchr(*str, c) + 1);
	if (new)
		free(*str);
	return (new);
}
