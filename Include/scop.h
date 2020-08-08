#ifndef SCOP_H
# define SCOP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../libft/include/libft.h"
# include "get_next_line.h"
# include "vectors.h"
# include "../Tga_Reader/includes/tga_reader.h"
# include <stdio.h>
# define DEBUG 1
# define IS_NUM(x) ((x >= '0' && x <= '9') || x == '-' || x == '.')
# define IS_WHITESPACE(x) (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\r')

typedef struct	s_glstruct
{
	GLFWwindow	*window;
	GLuint		vbo;
	GLuint		vao;
	GLuint		ebo;
	GLuint		shader_program;
}				t_glstruct;

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
	int			flag;
	int 		*verts;
	int 		*vt;
	int			*vn;
}				t_f;

typedef struct	s_index
{
	float		*verts;
	int			*index;
	int			index_size;
	int			size;
}				t_index;

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
	int			max_vs;
	int			*nb_vs_size;
}				t_obj;

/*
*	Init functions for t_obj structs in it.
*/

t_obj		init_obj(void);
t_vert		init_vert(void);
t_p			init_p(void);
t_l			init_l(void);
t_f			init_f(void);
t_index		init_index(void);

/*
*	Init OpenGL
*/

void		init_glew(void);
void		init_glfw(void);
/* ------------------- */

/* 
*	core parsing functions.
*/

char		*readshad(char *source, int *i);
t_obj		parse(char *filename);
void		parse_all_vert(char *buffer, t_obj *obj, int *j);

float		*vect_toa(t_obj obj);
int 		**faces_toa(t_obj obj);

int			check_error_obj(t_obj *obj);

/* ------------------- */

/*
*	OpenGL Function
*/


int			setup_texture(void);
GLuint		ft_shader(char *name, GLenum shader_type);
GLuint		create_program(void);
void		generate_vbo(GLuint *vbo, float points[], int len);
void		generate_ebo(GLuint *ebo, float points[], int len);
void		generate_vao(GLuint *vao, GLuint vbo);

/*
*	Vertex
*/

t_index		create_vert(t_obj obj, int *index, float *points);
void		set_max_vs(t_obj	*obj);
int			*split_faces(int **indices, t_obj *obj);

/*
*	Verbose debuging functions.
*/

void	print_obj(t_obj obj);
void	print_vert(t_vert vert, int type);
void	print_array(float *array, t_obj obj);
void	print_error(int i);
void	print_index_nb(char *str, int *index, int nb, int ln);
void	print_indices(int **indices, t_obj obj);

/* ------------------- */

/*
*	Utils.
*/

int				ft_max_vs(t_obj obj);
int				ft_ralloc(char **str, int size);
double			ft_atof(const char *str);
int				max_4(int a, int b, int c, int d);
int				max(int a, int b);


/* ------------------- */

#endif