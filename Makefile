
NAME			= scop

HEADER 			= $(shell find Include -type f)

SRC_PATH		= $(addprefix Sources/, $(SRC))

INC_PATH 		= $(shell find Include -type d) $(shell find libft -type d)

SRC				=	main.c							\
					initialize/init_glew.c			\
					initialize/init_glfw.c			\
					initialize/init_parse.c			\
					opengl/generate.c				\
					opengl/shader.c					\
					opengl/texture.c				\
					other/error.c					\
					other/print_debug.c				\
					other/print_struct.c			\
					other/utils.c					\
					parsing/get_next_line.c			\
					parsing/parse.c					\
					parsing/parse_vect.c			\
					parsing/readshader.c			\
					parsing/to_array.c				\
					vectors/mat_add.c				\
					vectors/mat_init.c				\
					vectors/mat_mult.c				\
					vectors/mat_print.c				\
					vectors/mat_scale.c				\
					vectors/mat_spe.c				\
					vectors/mat_sub.c				\
					vectors/mat_to_a.c				\
					vectors/vec_add.c				\
					vectors/vec_free.c				\
					vectors/vec_get_value.c			\
					vectors/vec_init.c				\
					vectors/vec_mult.c				\
					vectors/vec_mult_mat.c			\
					vectors/vec_norm.c				\
					vectors/vec_normalize.c			\
					vectors/vec_print.c				\
					vectors/vec_rot.c				\
					vectors/vec_scale.c				\
					vectors/vec_sub.c				\
					vertex/opti_vertex.c			\
					vertex/setup_vs_max.c			\
					vertex/split_faces.c			\

FRAMEWORK		=	Cocoa OpenGL

PKG				=	glfw3 glew

CC				=	cc -g3

CFLAG			=	
#-Wall -Wextra -Werror

all: 
	@echo "relink !"
	@$(CC) $(CFLAG) `pkg-config --cflags $(PKG)` $(SRC_PATH) libft/libft.a libft/include/libft.h Include/scop.h Include/scop.h Include/get_next_line.h `pkg-config --static --libs $(PKG)` $(foreach fmw, $(FRAMEWORK), -framework $(fmw)) -L ./Tga_Reader -l Tga -I Tga_Reader/includes/tga_reader.h
	@mv a.out scop