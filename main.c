#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

void	generate_vao(GLuint *vao, GLuint vbo)
{
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
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
 	glGetProgramiv( shader_program, GL_LINK_STATUS, &success );
    if (!success)
    {
    	glGetProgramInfoLog( shader_program, 512, NULL, infoLog );
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}
	return (shader_program);
}

int		main(int argc, char **argv)
{
	GLFWwindow	*window;
	float		points[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

	GLuint		vbo;
	GLuint		vao;
	GLuint		shader_program;

	if (argc == 1)
		return (0);
	parse(argv[1]);
	init_glfw();
	if (!(window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL)))
		print_error(2);
	glfwMakeContextCurrent(window);
	init_glew();

	if (DEBUG)
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
	}

	generate_vbo(&vbo, points, 30);
	generate_vao(&vao, vbo);

	shader_program = create_program();

	while (!glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		// glDrawArrays(GL_TRIANGLES, 1, 4);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1 , &vao);
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	while(1);
	return (0);
}
