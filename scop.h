#ifndef SCOP_H
# define SCOP_H

# include "libft/include/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# define DEBUG 1
# define IS_NUM(x) ((x >= '0' && x <= '9') || x == '-' || x == '.')
# define IS_WHITESPACE(x) (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\r')

typedef struct	s_vert
{
	int			size;
	float		*v;	
}				t_vert;

typedef	t_vert	t_vp;
typedef t_vert	t_vn;
typedef	t_vert	t_vt;

typedef struct	s_p
{
	int 	size;
	int 	*verts;
}				t_p;

typedef struct	s_l
{
	int size;
	int *verts;
	int *vt;
}				t_l;

typedef struct	s_f
{
	int 		size;
	int 		*verts;
	int 		*vt;
	int			*vp;
}				t_f;

typedef struct	s_obj
{
	int			error;
	int			p_size;
	int			l_size;
	int			f_size;
	t_vert		v;
	t_vp		vp;
	t_vn		vn;
	t_vt		vt;
	t_p			*p;
	t_l			*l;
	t_f			*f;
}				t_obj;

/*
*	Init functions for t_obj structs in it.
*/

t_obj		init_obj(void);
t_vert		init_vert(void);
t_p			init_p(void);
t_l			init_l(void);
t_f			init_f(void);

/* ------------------- */

/* 
*	core parsing functions.
*/

t_obj	parse(char *filename);
void	parse_all_vert(char *buffer, t_obj *obj);

int		check_error_obj(t_obj *obj);

/* ------------------- */

/*
*	Verbose debuging functions.
*/

void	print_obj(t_obj obj);
void	print_vert(t_vert vert, int type);

/* ------------------- */

/*
*	Utils.
*/

int				ft_ralloc(char **str, int size);
double			ft_atof(const char *str);



/* ------------------- */

#endif