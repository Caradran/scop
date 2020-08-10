// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   print_debug.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/08/08 17:52:09 by lomasse           #+#    #+#             */
// /*   Updated: 2020/08/08 18:12:05 by lomasse          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../Include/scop.h"


// void	print_index_nb(char *str, int *index, int nb, int ln)
// {
// 	printf("\n%s", str);
// 	for (int i = 0; i < nb; i++)
// 	{
// 		if (!(i%ln))
// 			printf("\n");
// 		if (!(i%ln) && !(i%(ln * 2)))
// 			printf("\n");
// 		printf("%d\t",index[i]);
// 	}
// 	printf("\n");
// }

// void	print_indices(int **indices, t_obj obj)
// {
// 	int i;
// 	int j;
// 	int k;

// 	i = 0;
// 	while (i < obj.max_vs)
// 	{
// 		j = 0;
// 		printf("number of faces of size %d : %d \n",  i + 2, obj.nb_vs_size[i]);
// 		while (j < obj.nb_vs_size[i])
// 		{
// 			k = 0;
// 			while (k < (i + 2) * 3)
// 			{
// 				printf(" %d ", indices[i][j * (i + 2) * 3 + k]);
// 				k++;
// 			}
// 			printf("\n");
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }