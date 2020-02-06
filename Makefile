all :
	cc -g3 `pkg-config --cflags glfw3 glew` main.c to_array.c utils.c get_next_line.c init_parse.c parse_vect.c print_struct.c readshader.c parse.c scop.h libft/libft.a `pkg-config --static --libs glfw3 glew` -framework Cocoa -framework OpenGL
