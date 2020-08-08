
NAME			= scop

HEADER 			= $(shell find Include -type f)

SRC_PATH		= $(shell find Sources -type d)

INC_PATH 		= $(shell find Include -type d) $(shell find libft -type d)

SRC_PATH		= $(addprefix Sources/, $(SRC))

SRC				=	main.c				\
					to_array.c			\
					utils.c				\
					get_next_line.c		\
					init_parse.c		\
					parse_vect.c		\
					print_struct.c		\
					readshader.c		\
					parse.c				\

FRAMEWORK		=	Cocoa OpenGL

PKG				=	glfw3 glew

CC				=	cc -g3

CFLAG			=	
#-Wall -Wextra -Werror

all: 
	@echo "relink !"
	@$(CC) $(CFLAG) `pkg-config --cflags $(PKG)` $(SRC_PATH) libft/libft.a libft/include/libft.h Include/scop.h Include/scop.h Include/get_next_line.h `pkg-config --static --libs $(PKG)` $(foreach fmw, $(FRAMEWORK), -framework $(fmw)) -L ./Tga_Reader -l Tga -I Tga_Reader/includes/tga_reader.h
	@mv a.out scop