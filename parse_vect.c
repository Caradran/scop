#include "scop.h"

static void 	parse_vert(char *buffer, t_vert *vert, int type)
{
	int i;

	if (DEBUG)
		printf("\n\ndebug parse vect :\n");
	i = 0;
	while ((vert->size + 1) % type)
	{
		while (IS_WHITESPACE(buffer[i]))
			i++;
		if (!IS_NUM(buffer[i]))
		{
			vert->size = -1;
			return ;
		}
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		if (DEBUG)
			printf("buffer : ||%50s||, float : %f\n", &(buffer[i]), vert->v[vert->size]);
		while (IS_NUM(buffer[i]))
			i++;
		vert->size++;
	}
	while (IS_WHITESPACE(buffer[i]))
		i++;
	if (IS_NUM(buffer[i]))
	{
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		while (IS_NUM(buffer[i]))
			i++;
		while (IS_WHITESPACE(buffer[i]))
			i++;
		if (!(!buffer[i] || buffer[i] == '#'))
			vert->size = -2;
	}
	else if (!buffer[i] || buffer[i] == '#')
		vert->v[vert->size] = 1.0;
	else if (buffer[i] != '#')
		vert->size = -2;
	vert->size++;
	if (!((vert->size) % (type * 1024)))
		ft_ralloc((char**)vert->v, (type * 1024) * sizeof(float));
}

static void	parse_vn(char *buffer, t_vert *vert)
{
	int i;
	int j;

	if (DEBUG)
		printf("\n\ndebug parse vn : size : %d\n", vert->size);
	i = 0;
	j = 0;
	while (j++ < 3)
	{
		while (IS_WHITESPACE(buffer[i]))
			i++;
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		if (!IS_NUM(buffer[i]))
		{
			vert->size = -1;
			return ;
		}
		if (DEBUG)
			printf("buffer : ||%50s||, float : %f\n", &(buffer[i]), vert->v[vert->size]);
		while (IS_NUM(buffer[i]))
			i++;
		vert->size++;
	}
	if (!((vert->size) % (3 * 1024)))
		ft_ralloc((char**)vert->v, 3 * 1024 * sizeof(float));
}

static void parse_vt(char *buffer, t_vert *vert)
{
	int i;
	int j;

	if (DEBUG)
		printf("\n\ndebug parse vn : size : %d\n", vert->size);
	i = 0;
	j = 0;
	while(j++ < 3)
	{
		while (IS_WHITESPACE(buffer[i]))
			i++;
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		if (DEBUG)
			printf("j : %d, buffer : ||%50s||, float : %f\n", j, &(buffer[i]), vert->v[vert->size]);
		if (j == 1 && !IS_NUM(buffer[i]))
		{
			vert->size = -1;
			return ;
		}
		else if (j > 1 && !IS_NUM(buffer[i]) && buffer[i] != '#' && buffer[i])
		{
			vert->size = -1;
			return ;
		}
		else if (j > 1 && (!buffer[i] || buffer[i] == '#'))
		{
			if (j == 2)
			{
				vert->v[++vert->size] = 0;
				vert->v[++vert->size] = 0;
			}
			else
				vert->v[++vert->size] = 0;
			break ;
		}
		while(IS_NUM(buffer[i]))
			i++;
		vert->size++;
	}
	while (IS_WHITESPACE(buffer[i]))
		i++;
	if (buffer[i] && buffer[i] != '#')
		vert->size = -1;
}

static void parse_faces(char *buffer, t_f *f, t_obj *obj)
{
	int i;
	int j;
	int nb;	

	if (DEBUG)
		printf("\n\ndebug parse f : size : %d\n", f->size);

	i = 0;
	while (buffer[i])
	{
		while (IS_WHITESPACE(buffer[i]))
			i++;
		if (buffer[i] == '#')
			break;
		if (IS_NUM(buffer[i]))
		{
			nb = atoi(buffer[i]);
			if (nb < 0)
				nb = (obj->v.size / 4) + (nb + 1);
			if (nb <= 0)
			{
				f->size = -1;
				break;
			}
			f->verts[j] = nb;
		}
		while (IS_NUM(buffer[i]))
			i++;
		if (buffer[i] == '/' && IS_NUM(buffer[i + 1]))
		{
			i++;
			nb = atoi(buffer[i]);
			if (nb < 0)
				nb = (obj->v.size / 4) + (nb + 1);
			if (nb <= 0)
			{
				f->size = -1;
				break;
			}
			f->vt[j] = nb;
			while(IS_NUM(buffer[i]))
				i++;
		}
		if (buffer[i] == '/' && (IS_NUM(buffer[i + 1]) || (buffer[i + 1] == '/' && IS_NUM(buffer[i + 2]))))
						
	}
	
}



void parse_all_vert(char *buffer, t_obj *obj)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (IS_WHITESPACE(buffer[i]))
		i++;
	if (buffer[i] == 'v' && IS_WHITESPACE(buffer[i + 1]))
		parse_vert(&(buffer[i + 1]), &(obj->v), 4);
	else if (buffer[i] == 'v' && buffer[i + 1] == 'p' && IS_WHITESPACE(buffer[i + 2]))
		parse_vert(&(buffer[i + 2]), &(obj->vp), 3);
	else if (buffer[i] == 'v' && buffer[i + 1] == 'n' && IS_WHITESPACE(buffer[i + 2]))
		parse_vn(&(buffer[i + 2]), &(obj->vn));
	else if (buffer[i] == 'v' && buffer[i + 1] == 't' && IS_WHITESPACE(buffer[i + 2]))
		parse_vt(&(buffer[i + 2]), &(obj->vt));
	else if (buffer[i] == 'f' && IS_WHITESPACE(buffer[i + 1]))
		parse_faces(&(buffer[i + 1]), &(obj->f[j++]), obj);
	else if (!(buffer[i] == '#'|| !buffer[i]))
		obj->vt.size = -1;
}