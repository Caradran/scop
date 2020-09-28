/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <esuits@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:55:16 by esuits            #+#    #+#             */
/*   Updated: 2020/08/08 18:11:52 by esuits           ###   ########.fr       */
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
