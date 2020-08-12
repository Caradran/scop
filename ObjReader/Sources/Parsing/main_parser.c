/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:54:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/12 16:03:56 by lomasse          ###   ########.fr       */
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

static char             *ft_memjoinfree(char *s1, char *s2, char tofree, long int (*size))
{
	char	*new;
	int		i;
	int		j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	if (!(new = (char *)malloc(sizeof(char) *
					((size)[0] + (size)[1]))))
		return (NULL);
    i = -1;
    while (++i < (size)[0])
        new[i] = s1[i];
    j = -1;
    while (++j < (size)[1])
        new[i + j] = s2[j];
	tofree & 0b1 ? free((void *)s1) : 0;
	tofree & 0b10 ? free((void *)s2) : 0;
    (size)[0] += (size)[1];
    (size)[1] = 0;
	return (new);
       
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

    char    *file;
    char    buffer[0b1111111111111110];
    long int parsed_file[2];
    long int mem_size[2];
    size_t reader;
    size_t   len_read;

    len_read = 0b1111111111111110;
    parsed_file[0] = 0;
    parsed_file[1] = 0;
    reader = read(fd, buffer, len_read);
    if (reader == len_read + 1)
        printf("Reader error\n");
    parsed_file[1] = reader;
    mem_size[0] = 0;
    mem_size[1] = reader;
    file = malloc(1);
    file = ft_memjoinfree(file, buffer, 1, mem_size);
    while ((reader = (size_t)read(fd, buffer, len_read)) == len_read)
    {
        mem_size[1] = reader;
        file = ft_memjoinfree(file, buffer, 1, mem_size);
    }
    mem_size[1] = reader;
    file = ft_memjoinfree(file, buffer, 1, mem_size);
    if (reader == len_read + 1)
        printf("Reader error -1\n");
    
    char    *tmp;
    char    *line;
    line = file;
    tmp = line;
    obj->line = 0;
    new = skip_whitespace(line);
    line = ft_memchr(new, '\n', mem_size[0]);
    line[0] = '\0';
    while (line && mem_size[0])
    {
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
            printf("Invalid char\n");
            return (objerror(obj, 4));
        }
        line = ft_memchr(new, '\0', mem_size[0]);
        line += 1;
        if (line == NULL)
            break ;
        mem_size[0] -= line - tmp;
        if (mem_size[0] == 0)
        break ;
        tmp = line;
        new = skip_whitespace(line);
        line = ft_memchr(new, '\n', mem_size[0]);
        line[0] = '\0';
        obj->line++;
    }
    free(file);
    printf("Min : %f\t\t%f\t\t%f\n", obj->min.x, obj->min.y, obj->min.z);
    printf("Max : %f\t\t%f\t\t%f\n", obj->max.x, obj->max.y, obj->max.z);
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