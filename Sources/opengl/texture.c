/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:53:23 by esuits            #+#    #+#             */
/*   Updated: 2020/08/18 17:35:46 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

static void	setup_texture2(t_tga *texture, GLuint *texture_id, int index)
{
	glGenTextures(1, &(texture_id[index]));
	glBindTexture(GL_TEXTURE_2D, texture_id[index]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
}

int			setup_texture(t_glstruct *glstruct, GLuint *texture_id,
	char *path, char *base)
{
	t_tga		*texture;
	int			index_txt;
	char		*tmp;
	static int	index = 0;
	int			i;

	tmp = ft_strrchr(base, '/');
	if (tmp)
		tmp[1] = 0;
	path = ft_strjoin(base, path);
	if (!(texture = load_tga(path)))
		return (0);
	free(path);
	close(texture->fd);
	i = 0;
	while (i++ < (texture->w * texture->h) - 1)
		((unsigned int *)texture->data)[i - 1] =
				((((unsigned int *)texture->data)[i - 1] & 0xFF) << 24) +
				((((unsigned int *)texture->data)[i - 1] & 0xFF00) >> 8) +
				((((unsigned int *)texture->data)[i - 1] & 0xFF0000) >> 8) +
				((((unsigned int *)texture->data)[i - 1] & 0xFF000000) >> 8);
	setup_texture2(texture, texture_id, index);
	free_tga(texture);
	index++;
	return (1);
}
