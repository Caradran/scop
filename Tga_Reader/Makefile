# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 19:24:01 by lomasse           #+#    #+#              #
#    Updated: 2020/08/07 13:48:28 by lomasse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libTga.a

TGA_PATH	=	src/

SRC			=   $(shell ls | grep -E ".+\.c")						\
				$(addprefix $(TGA_PATH), $(TGA_SRC))			\

TGA_SRC			= data.c										\
				  filldata.c									\
				  createpxl.c									\
				  uncompress.c									\
				  rot.c											\
				  tga_main.c

INC			= -I tga_reader.h

LIB_FLAG	= ar r

OBJ			= $(SRC:.c=.o)

all: $(NAME)
	@echo "tga_reader has been created\n"

$(NAME): $(OBJ)
	echo "try"
	$(LIB_FLAG) $(NAME) $(OBJ)
	@rm *.o

%.o: %.c
	gcc $(INC) -o $@ -c $<