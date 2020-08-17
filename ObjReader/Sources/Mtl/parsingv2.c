/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:08:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/17 17:10:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/MtlReader.h"

void					Ke(char *line, t_material *ptr)
{
    ptr->Ke.x = atof(&(line[2])); // Atof
    ptr->Ke.y = atof(&(line[5])); // Atof
    ptr->Ke.z = atof(&(line[8])); // Atof
}

void					Ni(char *line, t_material *ptr)
{

    ptr->Ni = atof(&(line[2])); // Atof
}

void					d(char *line, t_material *ptr)
{
    ptr->d = atof(&(line[2])); // Atof
}

void					illum(char *line, t_material *ptr)
{
    ptr->illum = atoi(&(line[6])); // Atoi
}

#include <stdio.h>
void					map_Kd(char *line, t_material *ptr)
{
    int i = 0;

    ptr->map_Kd = ft_strdup(&(line[7]));
    i = ft_strlen(ptr->map_Kd) - 1;
    while (i > 0 && ptr->map_Kd[i] == '\r')
    {
        ptr->map_Kd[i] = 0;
        i--;
    }
}
