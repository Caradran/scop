/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:53:23 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/18 17:35:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

int		setup_texture(t_glstruct *glstruct, GLuint *textureID, char *path, char *base)
{
	static int	index = 0;
	t_tga		*texture;
	int			index_txt;
	char		*tmp;

	// printf("Base Txt : %s\n", base);
	tmp = ft_strrchr(base, '/');
	if (tmp)
		tmp[1] = 0;
	path = ft_strjoin(base, path);
	// printf("Path Txt : [%s]\n", path);
	if (!(texture = load_tga(path)))
		return (0);
	free(path);
	close(texture->fd);
	for (int i = 0; i < (texture->w * texture->h) - 1; i++)
		((unsigned int *)texture->data)[i] = ((((unsigned int *)texture->data)[i] & 0xFF) << 24) +
											((((unsigned int *)texture->data)[i] & 0xFF00) >> 8) +
											((((unsigned int *)texture->data)[i] & 0xFF0000) >> 8) + 
											((((unsigned int *)texture->data)[i] & 0xFF000000) >> 8);
	glGenTextures(1, &(textureID[index]));
	glBindTexture(GL_TEXTURE_2D, textureID[index]);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	free_tga(texture);
	index++;
	return (1);
}