/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:51:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/08 18:11:25 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

GLuint	ft_shader(char *name, GLenum shader_type)
{
	int			vert_s;
	GLuint		sha;
	const char	*shader = readshad(name, &vert_s);
	GLint success;
    GLchar infoLog[512];

	//printf("%s\n", shader);
	sha = glCreateShader(shader_type);
	glShaderSource(sha, 1, &shader, NULL);
	glCompileShader(sha);
	glGetShaderiv(sha, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(sha, 512, NULL, infoLog);
		if (shader_type == GL_VERTEX_SHADER)
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		if (shader_type == GL_FRAGMENT_SHADER)
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		exit(1);
	}
	ft_memdel((void**)&shader);
	return (sha);
}

GLuint	create_program(void)
{
	GLuint shader_program;
	GLint success;
	GLchar infoLog[512];
	GLuint shaders[2];

	shader_program = glCreateProgram();
	glAttachShader(shader_program,
		(shaders[0] = ft_shader("frag.sha", GL_FRAGMENT_SHADER)));
	glAttachShader(shader_program,
		(shaders[1] = ft_shader("vertex.sha", GL_VERTEX_SHADER)));
	glLinkProgram(shader_program);
 	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
    	glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}
	return (shader_program);
}
