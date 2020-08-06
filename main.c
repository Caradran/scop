#include <stdio.h>
#include <stdlib.h>
#include "scop.h"

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
		printf("%s\n", glewGetErrorString(err));
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
}

GLuint	ft_shader(char *name, GLenum shader_type)
{
	int			vert_s;
	GLuint		sha;
	const char	*shader = readshad(name, &vert_s);
	GLint success;
    GLchar infoLog[512];

	printf("%s\n", shader);
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


int		main(int argc, char **argv)
{
	t_glstruct	glstruct;
	t_obj		obj;

	float		*points;

	int 		**indices;


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
	printf("coucou\n");
	points = vect_toa(obj);

	if (DEBUG)
	{
		print_indices(indices, obj);
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}


	generate_vbo(&glstruct.vbo, points, sizeof(float) * max_4(obj.v.size, obj.vn.size, obj.vp.size, obj.vt.size) * 4);
	generate_vao(&glstruct.vao, glstruct.vbo);
	generate_ebo(&glstruct.ebo, (float*)indices[1], obj.max_vs * sizeof(int) * 3 * 3);

	glstruct.shader_program = create_program();

	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(glstruct.shader_program);
		glBindVertexArray(glstruct.vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glstruct.ebo);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
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
