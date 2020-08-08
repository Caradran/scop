#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"


void	transformations(t_glstruct glstruct)
{
	t_mat4	ret;
	t_vec3	rot_vec;
	t_vec3	scale_vec;
	float	test[16];

	ret = init_mat4();
	rot_vec = init_v3(0, 0, 1);
	// scale_vec = init_v3(0.5, 0.5, 0.5);
	ret = mult_mat4(ret, rot_mat4(rot_vec, M_PI/4.0));
	// ret = mult_mat4(ret, scaling_mat4(scale_vec));

	int i = -1;
	while (++i < 16)
	{
		if (!(i % 4))
			printf("\n");
		printf("%f ", (float)(mat4_to_a(ret))[i]);
		test[i] = (float)(mat4_to_a(ret))[i];
	}
	printf("\n");

	glUseProgram(glstruct.shader_program);
	unsigned int transformLoc = glGetUniformLocation(glstruct.shader_program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (GLfloat*)test);
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
	printf("~~~~~~~~~~~~Verts~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ret = create_vert(obj, index_split.index, points);
	print_index_nb("Vertex",index_split.index, obj.nb_vs_size[1] * 9, 9);
	if (!ret.index || !ret.verts)
	{
		printf("Index ou Verts non malloc\n (FAUT TOUT FREE SA MERE)\n");
		return (-1);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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


	printf("~~~~~~~~~~~~~~~~TEXTURE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (!setup_texture())
	{
		ft_putendl("Error Mallocated TGA file\n");
		return (-1);
	}
	printf("~~~~~~~~~~~~~~~~SHADER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	glstruct.shader_program = create_program();

	printf("~~~~~~~~~~~~~~~~TRANSFORMATIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	transformations(glstruct);

	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
