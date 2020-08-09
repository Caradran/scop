#include <stdio.h>
#include <stdlib.h>
#include "../Include/scop.h"


t_mat4 creat_mat_camera(t_camera *camera)
{
	t_mat4 ret;
	t_mat4 P;

	ret = init_mat4();
	P = init_mat4();
	ret.mat[0][0] = camera->right.x;
	ret.mat[0][1] = camera->right.y;
	ret.mat[0][2] = camera->right.z;
	ret.mat[1][0] = camera->up.x;
	ret.mat[1][1] = camera->up.y;
	ret.mat[1][2] = camera->up.z;
	ret.mat[2][0] = camera->front.x;
	ret.mat[2][1] = camera->front.y;
	ret.mat[2][2] = camera->front.z;

	P.mat[0][3] = camera->pos.x;
	P.mat[1][3] = camera->pos.y;
	P.mat[2][3] = camera->pos.z;
	return (mult_mat4(ret, P));
}

void	creat_camera(t_vec3 pos, t_vec3 target, t_camera *camera)
{

	camera->pos = pos;
	camera->front = normalize_v3(sub_v3(target, camera->pos));
	camera->up = init_v3(0, 1, 0);
	if (!norme_v3(sub_v3(camera->up, camera->front)))
		camera->up = init_v3(0, 0, 1);
	camera->right = normalize_v3(cross_vec3(camera->up, camera->front));
	camera->up = cross_vec3(camera->front, camera->right);
}

t_mat4	model_mat(t_vec3 scale_vec, t_vec3 trans_vec, t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, translation_mat4(init_v3(-0.39 - 0.5 , -0.39 - 0.5, -0.39 - 0.5)));
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	return (ret);
}

t_mat4 view_mat(t_vec3 scale_vec, t_vec3 trans_vec, t_vec3 rot_vec, float theta)
{
	t_mat4 ret;

	ret = init_mat4();
	ret = mult_mat4(ret, rot_mat4(rot_vec, theta));
	ret = mult_mat4(ret, scaling_mat4(scale_vec));
	ret = mult_mat4(ret, translation_mat4(trans_vec));
	return (ret);
}

t_mat4 proj_mat(float fov, float far, float near)
{
	t_mat4 ret;

	ret = init_mat4();
	ret.mat[0][0] = 1.0 / tan(fov);
	ret.mat[1][1] = 1.0 / tan(fov);
	ret.mat[2][2] = -far / (far - near);
	ret.mat[3][2] = -1;
	ret.mat[2][3] = -far * near / (far - near);
	ret.mat[3][3] = 0;
	return (ret);
}

void	transformations(t_glstruct glstruct, t_camera *camera)
{
	t_mat4	ret;
	float	test[16];

	ret = proj_mat(90.0f * M_PI / 360.0, 1000.0f,  0.1f);
	ret = mult_mat4(ret, creat_mat_camera(camera));
	ret = mult_mat4(ret, model_mat(init_v3(3, 3, 3), init_v3(0.39, 0.39, 0.39), normalize_v3(init_v3(1, 1, 1)), (float)glfwGetTime()));

	// print_mat4(ret);
	int i = -1;
	while (++i < 16)
		test[i] = (float)(mat4_to_a(ret))[i];

	glUseProgram(glstruct.shader_program);
	unsigned int transformLoc = glGetUniformLocation(glstruct.shader_program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (GLfloat*)test);
}

void	update_camera(t_glstruct *glstruct, t_camera *camera)
{
	static float deltaTime = 0;
	static float lastFrame = 0;
	float currentFrame;

	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;  

    camera->speed = 2.50f * deltaTime;
    if (glfwGetKey(glstruct->window, GLFW_KEY_W) == GLFW_PRESS)
       camera->pos = add_v3(camera->pos, scale_v3(camera->speed, camera->front));
    if (glfwGetKey(glstruct->window, GLFW_KEY_S) == GLFW_PRESS)
        camera->pos = sub_v3(camera->pos, scale_v3(camera->speed, camera->front));
    if (glfwGetKey(glstruct->window, GLFW_KEY_A) == GLFW_PRESS)
        camera->pos = sub_v3(camera->pos, scale_v3(camera->speed, camera->up));
    if (glfwGetKey(glstruct->window, GLFW_KEY_D) == GLFW_PRESS)
        camera->pos = add_v3(camera->pos, scale_v3(camera->speed, camera->up));
}

int		main(int argc, char **argv)
{
	t_glstruct	glstruct;
	t_obj		obj;

	float		*points;

	int 		**indices;
	t_index		ret;
	t_index		index_split;
	t_camera 	camera;

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


	printf("~~~~~~~~~~~~~~~~LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	creat_camera(init_v3(0,0,-3), init_v3(0,0,0), &camera);
	while (!glfwWindowShouldClose(glstruct.window))
	{
		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		transformations(glstruct, &camera);
		update_camera(&glstruct, &camera);
		glUseProgram(glstruct.shader_program);
		glBindVertexArray(glstruct.vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glstruct.ebo);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
