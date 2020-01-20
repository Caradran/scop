/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:39 by esuits            #+#    #+#             */
/*   Updated: 2018/01/20 15:37:10 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_form
{
	char			flags[5];
	unsigned int	w;
	int				pre;
	char			mod[6];

}				t_form;

int				ft_read_format(va_list *args, char **ptr, t_form *form);
int				ft_read_format_ls(va_list *args, char **ptr, t_form *form);
int				ft_read_format_uu(va_list *args, char **ptr, t_form *form);
int				ft_read_format_c(va_list *args, char **ptr,
					t_form *form, int i);
int				ft_mod_oo(unsigned long long arg, t_form *form);
int				ft_mod_id(long long arg, t_form *form);
int				ft_mod_uu(unsigned long long arg, t_form *form);
int				ft_mod_xx(unsigned long long arg, t_form *form, char **ptr);
int				ft_read_flag(va_list *args, char **ptr);
int				ft_printf(const char *format, ...);

#endif
