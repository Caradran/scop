/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:49:44 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 17:50:04 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

void	init_glew(void)
{
	GLenum err;

	glewExperimental = GL_TRUE;
	if ((err = glewInit()) != GLEW_OK)
	{
		printf("%s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(1);
	}
	glEnable(GL_DEPTH_TEST);
}
