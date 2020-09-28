/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 22:09:28 by esuits            #+#    #+#             */
/*   Updated: 2020/08/14 15:59:10 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ObjReader.h"

void    free_obj(t_obj *obj) // Need ptr before
{
    int i;
    
    if (obj == NULL)
        if (!(obj = getobj((void *)0)))
            return ;
    while (obj != NULL)
    {
        ft_memdel((void **)(&obj->v));
        ft_memdel((void **)(&obj->vt));
        ft_memdel((void **)(&obj->vn));
        ft_memdel((void **)(&obj->vp));
        i = -1;/* Need to free each group
        while (++i < obj->size_face[0])
        {
            ft_memdel((void **)(&obj->face[i].i_v));
            ft_memdel((void **)(&obj->face[i].i_vt));
            ft_memdel((void **)(&obj->face[i].i_vn));
        }
        ft_memdel((void **)(&obj->face));*/
        obj = obj->next;
    }
    getobj((void *)0x1);
}