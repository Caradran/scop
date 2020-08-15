/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:53:23 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/15 17:40:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

int		setup_texture(t_glstruct *glstruct, GLuint *textureID)
{
	static int	index = 0;
	t_tga		*texture,*texture2;
	int			index_txt;

	glUseProgram(glstruct->shader_program);
	
	if (!(texture = load_tga("Jinx.tga")))
		return (0);
	for (int i = 0; i < (texture->w * texture->h) - 1; i++)
		((unsigned int *)texture->data)[i] = ((((unsigned int *)texture->data)[i] & 0xFF) << 24) +
											((((unsigned int *)texture->data)[i] & 0xFF00) >> 8) +
											((((unsigned int *)texture->data)[i] & 0xFF0000) >> 8) + 
											((((unsigned int *)texture->data)[i] & 0xFF000000) >> 8);
	glGenTextures(1, &(textureID[0]));
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	/* V2 */
	if (!(texture2 = load_tga("demontxt.tga")))
		return (0);
	for (int i = 0; i < (texture2->w * texture2->h) - 1; i++)
		((unsigned int *)texture2->data)[i] = ((((unsigned int *)texture2->data)[i] & 0xFF) << 24) +
											((((unsigned int *)texture2->data)[i] & 0xFF00) >> 8) +
											((((unsigned int *)texture2->data)[i] & 0xFF0000) >> 8) + 
											((((unsigned int *)texture2->data)[i] & 0xFF000000) >> 8);
	glGenTextures(1, &(textureID[1]));
	glBindTexture(GL_TEXTURE_2D, (textureID[1]));
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, texture2->w, texture2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture2->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glUniform1i(glGetUniformLocation(glstruct->shader_program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(glstruct->shader_program, "texture2"), 1);
	free_tga(texture);
	free_tga(texture2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (textureID[0]));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, (textureID[1]));
	index++;
	return (1);
}