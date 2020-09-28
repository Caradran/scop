/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 22:10:28 by esuits            #+#    #+#             */
/*   Updated: 2020/08/14 16:19:16 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ObjReader.h"

char        *skip_whitespace(char *str, long int max)
{
    int     i;
    char    *ret;

    i = -1;
    while ((str[++i] == ' ' || str[i] == '\t'
        || str[i] == '\f' || str[i] == '\r') && str[i] && max)
        max--;
    if (!str[i])
        return (0x0);
    return (str + i);
}