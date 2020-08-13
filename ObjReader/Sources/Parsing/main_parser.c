/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:54:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/13 14:11:14 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ObjReader.h"

static int            init_v_malloc(t_obj *obj)
{
    obj->size_face[0] = 0;
    obj->size_face[1] = 64;
    if (!(obj->face = malloc(sizeof(t_face) * 64)))
        return (1);
    obj->size_v[0] = 0;
    obj->size_v[1] = 64;
    if (!(obj->v = malloc(sizeof(t_vertex4) * 64)))
        return (1);
    ft_memset(obj->v, 0, sizeof(t_vertex4) * 64);
    obj->size_vn[0] = 0;
    obj->size_vn[1] = 64;
    if (!(obj->vn = malloc(sizeof(t_vertex) * 64)))
        return (1);
    ft_memset(obj->vn, 0, sizeof(t_vertex) * 64);
    obj->size_vt[0] = 0;
    obj->size_vt[1] = 64;
    if (!(obj->vt = malloc(sizeof(t_vertex) * 64)))
        return (1);
    ft_memset(obj->vt, 0, sizeof(t_vertex) * 64);
    obj->size_vp[0] = 0;
    obj->size_vp[1] = 64;
    if (!(obj->vp = malloc(sizeof(t_vertex) * 64)))
        return (1);
    ft_memset(obj->vp, 0, sizeof(t_vertex) * 64);
    return (0);
}
static char     *ft_ralloc(char **str,  long int oldsize, long int newsize)
{
	char *res;
    if (oldsize <= newsize)
        return (*str);
	if (!(res = ft_strnew(newsize)))
		return (0);
	res = ft_memcpy(res, *str, oldsize);
	ft_memdel((void **)str);
    return (res);
}
static int             adjust_allocation(t_obj *obj)
{
    return (0);
}

// static char             *ft_memjoinfree(char *s1, char *s2, char tofree, long int (*size))
// {
// 	char	*new;
// 	int		i;
// 	int		j;
// 	int		k;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	j = 0;
// 	if (!(new = (char *)malloc(sizeof(char) *
// 					((size)[0] + (size)[1]))))
// 		return (NULL);
//     i = -1;
//     while (++i < (size)[0])
//         new[i] = s1[i];
//     j = -1;
//     while (++j < (size)[1])
//         new[i + j] = s2[j];
// 	tofree & 0b1 ? free((void *)s1) : 0;
// 	tofree & 0b10 ? free((void *)s2) : 0;
//     (size)[0] += (size)[1];
//     (size)[1] = 0;
// 	return (new);
       
// }

void            fill_file(char **file, t_lst_buff *buffer, long int length)
{
    long unsigned int   pos;
    int                 i;
    void                *ptr;

    pos = 0;
    while (buffer != NULL)
    {
        i = -1;
        while (++i < 0b1111111111111110 && i < length)
        {
            (*file)[pos] = buffer->buff[i];
            pos += 1;
        }        
        length -= 0b1111111111111110;
        ptr = buffer;
        buffer = buffer->next;
        free(ptr);
    }
}

int             main_parser(t_obj *obj)
{
    char    *new;
    int     fd;
    int     error;

    fd = open(obj->path, O_RDONLY);
    if (fd == -1)
        return (objerror(obj, 2));
    if (init_v_malloc(obj))
        return (objerror(obj, 1));

    char        *file;
    long int    mem_size[2];
    size_t      reader;
    size_t      len_read;
    t_lst_buff  *buffer_lst;
    t_lst_buff  *lst;

    len_read = 0b1111111111111110;
    if (!(buffer_lst = malloc(sizeof(t_lst_buff))))
        return (1);
    reader = read(fd, buffer_lst->buff, len_read);
    if (reader == len_read + 1)
        printf("Reader error\n");
    mem_size[1] = reader;
    if (!(buffer_lst->next = malloc(sizeof(t_lst_buff))))
        return (1);
    lst = buffer_lst->next;
    while ((reader = (size_t)read(fd, lst->buff, len_read)) == len_read)
    {
        mem_size[1] += reader;
        if (!(lst->next = malloc(sizeof(t_lst_buff))))
            return (1);
        lst =lst->next;
    }
    lst->next = NULL;
    mem_size[1] += reader;
    printf("SIZE%ld\n", mem_size[1]);
    if (reader == len_read + 1)
        printf("Reader error -1\n");
    printf("Read end\n");
    if (!(file = malloc(mem_size[1])))
        return (1);
    fill_file(&file, buffer_lst, mem_size[1]);
    printf("Fill end\n");
    
    char    *tmp;
    char    *line;
    line = file;
    tmp = line;
    obj->line = 0;
    mem_size[0] = mem_size[1];
    new = skip_whitespace(line, mem_size[0]);
    if (new == NULL)
        return (objerror(obj, 4));
    line = ft_memchr(new, '\n', mem_size[0]);
    line[0] = '\0';
    while (line && new && mem_size[0])
    {
        if (!(obj->line % 1000000))
        {
            printf("%%%d ==> %ld || %lu\n", (int)(100 - ((float)mem_size[0] / (float)mem_size[1]) * 100.0), obj->line, mem_size[0]);
            // printf("Actuellement :\n");
            // printf("\t\t. %ld\t\t= v~\t\t%ld\t(Mallocated)\n", obj->size_v[0], obj->size_v[1]);
            // printf("\t\t. %ld\t\t= vt\t\t%ld\t(Mallocated)\n", obj->size_vt[0], obj->size_vt[1]);
            // printf("\t\t. %ld\t\t= vn\t\t%ld\t(Mallocated)\n", obj->size_vn[0], obj->size_vn[1]);
            // printf("\t\t. %ld\t\t= vp\t\t%ld\t(Mallocated)\n", obj->size_vp[0], obj->size_vp[1]);
            // printf("\t\t. %ld\t\t= f~\t\t%ld\t(Mallocated)\n", obj->size_face[0], obj->size_face[1]);
        }
        if (new == NULL || !new[0])
           ;
        else if (new[0] == 'v')
        {
            if ((error = parsing_vertex(obj, new)))
                return (objerror(obj, error));
        }
        else if (new[0] == 'f')
        {
            if ((error = parsing_face(obj, new)))
                return (objerror(obj, error));
        }
        else if (new[0] == '#')
            ;
        else if (new[0] == 'o')
            ;
        else if (new[0] == 'g')
            ;
        else if (new[0] == 'm')
            ;
        else if (new[0] == 's')
            ;
        else if (new[0] == 'u')
            ;
        else if (new[0] == '\n')
            ;
        else
        {
            printf("Invalid char : %s\n", new);
            return (objerror(obj, 4));
        }
        line = ft_memchr(new, '\0', mem_size[0]);
        if (line == NULL)
            break ;
        line += 1;
        while (mem_size[0] && line[0] == '\n')
        {
            line++;
            mem_size[0] -= 1;
        }
        mem_size[0] -= line - tmp;
        if (mem_size[0] <= 0)
            break ;
        tmp = line;
        if ((obj->line > 51777300))
            printf("Before Skip\n");
        new = skip_whitespace(line, mem_size[0]);
        if (new == NULL)
            break ;
        if ((obj->line > 51777300))
            printf("Skip\n");
        line = ft_memchr(new, '\n', mem_size[0]);
        if ((obj->line > 51777300))
            printf("Skip\n");
        if (line != NULL)
            line[0] = '\0';
        else
            break ;
        obj->line++;
    }
    printf("Parsing Done\n");
    free(file);
    printf("Min : %f\t\t%f\t\t%f\n", obj->min.x, obj->min.y, obj->min.z);
    printf("Max : %f\t\t%f\t\t%f\n", obj->max.x, obj->max.y, obj->max.z);
    printf("Min : %f\t\t%f\t\t%f\n", obj->vtmin.x, obj->vtmin.y, obj->vtmin.z); // useless ?
    printf("Max : %f\t\t%f\t\t%f\n", obj->vtmax.x, obj->vtmax.y, obj->vtmax.z);
    obj->center.x = (obj->min.x + obj->max.x / 2.0);
    obj->center.y = (obj->min.y + obj->max.y / 2.0);
    obj->center.z = (obj->min.z + obj->max.z / 2.0);
    printf("Center : %f\t\t%f\t\t%f\n", obj->center.x, obj->center.y, obj->center.z);
    printf("Il y a :\n");
    printf("\t\t. %ld\t\t= v~\t\t%ld\t(Mallocated)\n", obj->size_v[0], obj->size_v[1]);
    printf("\t\t. %ld\t\t= vt\t\t%ld\t(Mallocated)\n", obj->size_vt[0], obj->size_vt[1]);
    printf("\t\t. %ld\t\t= vn\t\t%ld\t(Mallocated)\n", obj->size_vn[0], obj->size_vn[1]);
    printf("\t\t. %ld\t\t= vp\t\t%ld\t(Mallocated)\n", obj->size_vp[0], obj->size_vp[1]);
    printf("\t\t. %ld\t\t= f~\t\t%ld\t(Mallocated)\n", obj->size_face[0], obj->size_face[1]);
    printf("%s : DONE\n", obj->path);
    return (0);
}