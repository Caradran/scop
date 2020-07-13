#include "scop.h"

static int size_num(char *str)
{
	int i;

	i = 0;
	while (IS_NUM(str[i]))
		i++;
	return (i);
}

static int size_white(char *str)
{
	int i;

	i = 0;
	while (IS_WHITESPACE(str[i]))
		i++;
	return (i);
}

static void         parse_vert(char *buffer, t_vert *vert, int type)
{
	int i;

	if (DEBUG)
		printf("\n\ndebug parse vect :\n");
	i = 0;
	while ((vert->size + 1) % type)
	{
		i += size_white(&(buffer[i]));
		if (!IS_NUM(buffer[i]))
		{
			vert->size = -1;
			return ;
		}
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		if (DEBUG)
			printf("buffer : ||%50s||, float : %f\n", &(buffer[i]), vert->v[vert->size]);
		i += size_num(&(buffer[i]));
		vert->size++;
	}
	i += size_white(&(buffer[i]));
	if (IS_NUM(buffer[i]))
	{
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		i += size_num(&(buffer[i]));
		i += size_white(&(buffer[i]));
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

static void        parse_vn(char *buffer, t_vert *vert)
{
	int i;
	int j;

	if (DEBUG)
		printf("\n\ndebug parse vn : size : %d\n", vert->size);
	i = 0;
	j = 0;
	while (j++ < 3)
	{
		i += size_white(&(buffer[i]));
		vert->v[vert->size] = ft_atof(&(buffer[i]));
		if (!IS_NUM(buffer[i]))
		{
			vert->size = -1;
			return ;
		}
		if (DEBUG)
			printf("buffer : ||%50s||, float : %f\n", &(buffer[i]), vert->v[vert->size]);
		i += size_num(&(buffer[i]));
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
	while (j++ < 3)
	{
		i += size_white(&(buffer[i]));
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
		while (IS_NUM(buffer[i]))
			i++;
		vert->size++;
	}
	i += size_white(&(buffer[i]));
	if (buffer[i] && buffer[i] != '#')
		vert->size = -1;
}

static int        nb_face(char *str, int size, int *fsize)
{
	int nb;

	nb = atoi(str);
	if (nb < 0)
		nb = (size / 4) + (nb + 1);
	if (nb <= 0)
		*fsize = -1;
	return (nb);
}

static void parse_faces(char *buffer, t_f *f, t_obj *obj)
{
	int i;
	int j;
	int nb;
	int checkflag;

	if (DEBUG)
		printf("\n\ndebug parse f : size : %d\n", f->size);
	j = 0;
	i = 0;
	checkflag = -1;
	while (buffer[i])
	{	
		i += size_white(&(buffer[i]));
		if (buffer[i] == '#')
			break ;
		else if (!IS_NUM(buffer[i]))
		{
			f->size = -1;
			break ;
		}
		f->flag = 0;
		if (IS_NUM(buffer[i]))
			if ((f->verts[j] = nb_face(&(buffer[i]), obj->v.size, &(f->size))) <= 0)
				break ;
		i += size_num(&(buffer[i]));
		if (buffer[i] == '/' && IS_NUM(buffer[i + 1]))
		{
			f->flag += 1;
			i++;
			if ((f->vt[j] = nb_face(&(buffer[i]), obj->vt.size, &(f->size))) <= 0)
				break ;
			i += size_num(&(buffer[i]));
		}
		if (buffer[i] == '/' && (IS_NUM(buffer[i + 1]) ||
			(buffer[i + 1] == '/' && IS_NUM(buffer[i + 2]) && f->flag == 0)))
		{
			i++;
			f->flag += 2;
			if (!IS_NUM(buffer[i]))
				i++;
			if ((f->vn[j] = nb_face(&(buffer[i]), obj->vn.size, &(f->size))) <= 0)
				break ;
			i += size_num(&(buffer[i]));
		}
		if (checkflag == -1)
			checkflag = f->flag;
		else if (f->flag != checkflag)
		{
			f->size = -1;
			break ;
		}
		j++;
	}
	if (f->size != -1)
		f->size = j;
	else
		obj->f_size = -1;
	if (DEBUG)
	{
		printf("flag %d, j : %d\n", f->flag, j);
		i = 0;
		while (i < j)
		{
			printf("verts %d\n", i);
			if (f->flag >= 0)
				printf("v : %d ", f->verts[i]);
			if (f->flag & 1)
				printf("vt : %d ", f->vt[i]);
			if (f->flag & 2)
				printf("vn : %d", f->vn[i]);
			printf("\n");
			i++;
		}
	}
}

void parse_all_vert(char *buffer, t_obj *obj, int *j)
{
	int i;

	i = 0;
	i += size_white(&(buffer[i]));
	if (buffer[i] == 'v' && IS_WHITESPACE(buffer[i + 1]))
		parse_vert(&(buffer[i + 1]), &(obj->v), 4);
	else if (buffer[i] == 'v' && buffer[i + 1] == 'p' && IS_WHITESPACE(buffer[i + 2]))
		parse_vert(&(buffer[i + 2]), &(obj->vp), 3);
	else if (buffer[i] == 'v' && buffer[i + 1] == 'n' && IS_WHITESPACE(buffer[i + 2]))
		parse_vn(&(buffer[i + 2]), &(obj->vn));
	else if (buffer[i] == 'v' && buffer[i + 1] == 't' && IS_WHITESPACE(buffer[i + 2]))
		parse_vt(&(buffer[i + 2]), &(obj->vt));
	else if (buffer[i] == 'f' && IS_WHITESPACE(buffer[i + 1]))
	{
		parse_faces(&(buffer[i + 1]), &(obj->f[*j]), obj);
		(*j)++;
	}
	else if (!(buffer[i] == '#'|| !buffer[i]))
		obj->vt.size = -1;
}
