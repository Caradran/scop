/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:55:16 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/08 18:11:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/scop.h"

void	print_error(int i)
{
	if (i == 1)
		printf("ERROR: could not start GLFW3/n");
	if (i == 2)
	{
		printf("ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}
	exit(1);
}
