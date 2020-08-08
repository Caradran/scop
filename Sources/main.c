#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"

char	*readshad(char *source, int *i);

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

void	init_glfw(void)
{
	if (!glfwInit())
		print_error(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void	init_glew(void)
{
	GLenum err;

	glewExperimental = GL_TRUE;
	if ((err = glewInit()) != GLEW_OK)
	{
		//printf("%s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(1);
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void	generate_vbo(GLuint *vbo, float points[], int len)
{
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), points, GL_STATIC_DRAW);
}

void	generate_ebo(GLuint *ebo, float points[], int len)
{
	glGenBuffers(1, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, len * sizeof(float), points, GL_STATIC_DRAW); 
}

void	generate_vao(GLuint *vao, GLuint vbo)
{
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,13 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,13 * sizeof(GLfloat), (void *)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,13 * sizeof(GLfloat), (void *)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

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

void	print_indices(int **indices, t_obj obj)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < obj.max_vs)
	{
		j = 0;
		printf("number of faces of size %d : %d \n",  i + 2, obj.nb_vs_size[i]);
		while (j < obj.nb_vs_size[i])
		{
			k = 0;
			while (k < (i + 2) * 3)
			{
				printf(" %d ", indices[i][j * (i + 2) * 3 + k]);
				k++;
			}
			printf("\n");
			j++;
		}
		printf("\n");
		i++;
	}
}

void	set_max_vs(t_obj	*obj)
{
	int i;
	int max_vs;
	int *nb_vs_size;

	i = 0;
	max_vs = 0;
	while (i < obj->f_size)
	{
		if (max_vs < obj->f[i].size)
			max_vs = obj->f[i].size;
		i++;
	}
	max_vs--;

	nb_vs_size = ft_memalloc(sizeof(int) * (max_vs + 1));
	i = 0;
	while (i <= obj->f_size)
	{
		if (obj->f[i].size >= 2)
			nb_vs_size[obj->f[i].size - 2]++;
		i++;
	}

	obj->max_vs = max_vs;
	obj->nb_vs_size = nb_vs_size;
}


int				find_point(float *point, float tmp[13],int max)
{
	int	i;

	i = -1;
	while (++i < max)
		if (!(ft_memcmp(&(point[i * 13]), tmp, 13)))
			return (i);
	return (-1);
}

void			fill_tmp(float (*tmp)[13], int *indices, float *points, int i)
{
	int	index;
	int save;

	index = -1;
	while (++index < 4)
		(*tmp)[index] = points[(indices[i] * 13) + index];
	save = (indices[i] * 13);
	index = -1;
	while (++index < 3)
		(*tmp)[index + 4] = points[(indices[i + 3] * 13) + index + 4];
	index = -1;
	while (++index < 3)
		(*tmp)[index + 7] = points[(indices[i + 6] * 13) + index + 10];
	index = -1;
	while (++index < 3)
		(*tmp)[index + 10] = 0;
	index = 4;
	while (++index < 13)
		if ((*tmp)[index] == -1)
			(*tmp)[index] = points[save + ((index - 4) % 3)];
}

t_index			create_vert(t_obj obj, int *index, float *points)
{
	t_index		ret;
	float		tmp[13];
	int			size;
	int			i;
	int			find;

	if (!(ret.verts = malloc(sizeof(t_index) * obj.nb_vs_size[1] * 3 * 13)))
		return ((t_index){NULL, NULL});
	if (!(ret.index = malloc(sizeof(t_index) * obj.nb_vs_size[1] * 3)))
		return ((t_index){NULL, NULL});
	i = -1;
	size = 0;
	while (++i < obj.nb_vs_size[1] * 3)
	{
		fill_tmp(&tmp, index, points, (i % 3) + ((i / 3) * 9));
		if ((find = find_point(ret.verts, tmp, size)) == -1)
		{
			ft_memcpy(&(ret.verts[size * 13]), tmp, 13 * 4);
			find = size;
			size += 1;
		}
		ret.index[i] = find;
	}
	ret.size = size;
	ret.index_size = i;
	return (ret);
}

int		setup_texture()
{
	static int	index = 0;
	t_tga		*texture;
	int			index_txt;
	GLuint		textureID;

	if (!(texture = load_tga("Jinx_split.tga")))
		return (0);
	for (int i = 0; i < (texture->w * texture->h) - 1; i++)
		((unsigned int *)texture->data)[i] = ((((unsigned int *)texture->data)[i] & 0xFF) << 24) +
											((((unsigned int *)texture->data)[i] & 0xFF00) >> 8) +
											((((unsigned int *)texture->data)[i] & 0xFF0000) >> 8) + 
											((((unsigned int *)texture->data)[i] & 0xFF000000) >> 8);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	index++;
	return (1);
}
int		*split_faces(int **indices, t_obj *obj)
{
	int i;
	int j;
	int size;
	int size_malloc;
	int *ret;
	int *tmp;

	i = 1;
	size_malloc = 0;
	while (i < obj->max_vs)
	{
		size_malloc += obj->nb_vs_size[i] * 3 * i;
		i++;
	}
	if (!(ret = ft_memalloc(size_malloc * sizeof(int) * 3)))
		return (NULL);
	/* Save the old face */
	if (obj->nb_vs_size[1])
		ft_memcpy(ret, indices[1], obj->nb_vs_size[1] * 9 * 4);
	/* Split */
	int currentpos;
	int save[3];
	int old;
	int k;
	int ligne;

	currentpos = obj->nb_vs_size[1] * 9;
	i = 1;
	while (++i < obj->max_vs)
	{
		ligne = (i + 2) * 3;
		j = -1;
		while (++j < obj->nb_vs_size[i])
		{
			save[0] = indices[i][0 + (j * ligne)];
			save[1] = indices[i][(1 * (i + 2)) + (j * ligne)];
			save[2] = indices[i][(2 * (i + 2)) + (j * ligne)];
			k = -1;
			while (++k < i)
			{
				ret[currentpos] = save[0];
				ret[currentpos + 1] = indices[i][(j * ligne) + (k + 1)];
				ret[currentpos + 2] = indices[i][(j * ligne) + (k + 2)];
				ret[currentpos + 3] = save[1];
				ret[currentpos + 4] = indices[i][(j * ligne) + (k + 1) + (i + 2)];
				ret[currentpos + 5] = indices[i][(j * ligne) + (k + 2) + (i + 2)];
				ret[currentpos + 6] = save[2];
				ret[currentpos + 7] = indices[i][(j * ligne) + (k + 1) + ((i + 2) * 2)];
				ret[currentpos + 8] = indices[i][(j * ligne) + (k + 2) + ((i + 2) * 2)];
				currentpos += 9;
			}
		}
	}
	obj->nb_vs_size[2] = 0;
	obj->nb_vs_size[1] = currentpos / 9;
	obj->nb_vs_size[0] = 0;
	printf("==>%d\n", obj->nb_vs_size[1]);
	obj->max_vs = 2;
	return (ret);
}

void	print_index_nb(char *str, int *index, int nb, int ln)
{
	printf("\n%s", str);
	for (int i = 0; i < nb; i++)
	{
		if (!(i%ln))
			printf("\n");
		if (!(i%ln) && !(i%(ln * 2)))
			printf("\n");
		printf("%d\t",index[i]);
	}
	printf("\n");
}

int		main(int argc, char **argv)
{
	t_glstruct	glstruct;
	t_obj		obj;

	float		*points;

	int 		**indices;
	t_index		ret;
	t_index		index_split;


	if (argc == 1)
		return (0);
	obj = parse(argv[1]);
	set_max_vs(&obj);
	init_glfw();
	if (!(glstruct.window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL)))
		print_error(2);
	glfwMakeContextCurrent(glstruct.window);
	init_glew();

	indices = faces_toa(obj);
	points = vect_toa(obj);

	index_split.index = split_faces(indices, &obj);
	print_index_nb("splited",index_split.index, obj.nb_vs_size[1] * 9, 9);
	printf("~~~~~~~~~~~~Verts~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ret = create_vert(obj, index_split.index, points);
	print_index_nb("Vertex",index_split.index, obj.nb_vs_size[1] * 9, 9);
	if (!ret.index || !ret.verts)
	{
		printf("Index ou Verts non malloc\n (FAUT TOUT FREE SA MERE)\n");
		return (-1);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (DEBUG)
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}

	printf("~~~~~~~~~~~~~~~~GENERATE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	generate_vbo(&glstruct.vbo, ret.verts, sizeof(float) * ret.size * 13);
	generate_vao(&glstruct.vao, glstruct.vbo);
	generate_ebo(&glstruct.ebo, (float*)ret.index, (ret.index_size) * sizeof(int));

	printf("~~~~~~~~~~~~~~~~TEXTURE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (!setup_texture())
	{
		ft_putendl("Error Mallocated TGA file\n");
		return (-1);
	}
	printf("~~~~~~~~~~~~~~~~SHADER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	glstruct.shader_program = create_program();
	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(glstruct.shader_program);
		glBindVertexArray(glstruct.vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glstruct.ebo);
		glDrawElements(GL_TRIANGLES, ret.index_size, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 1, 4);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(glstruct.window);
	}
	glDeleteVertexArrays(1 , &glstruct.vao);
	glDeleteBuffers(1, &glstruct.vbo);
	glfwTerminate();
	return (0);
}
