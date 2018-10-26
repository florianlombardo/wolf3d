# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/23 14:10:08 by flombard     #+#   ##    ##    #+#        #
#    Updated: 2018/10/15 14:07:43 by flombard    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = wolf3d

SRCS_DIR = srcs/
SRCS_FILES = 	main.c \
				map.c \
				error.c \
				errorMap.c \
				deal_key.c \
				raycasting.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))

INCLUDES = ./includes/

LIB_DIR = libft/
LIB_FILE = libft.a
LIB = $(addprefix $(LIB_DIR), $(LIB_FILE))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -F./Frameworks -O3
SDLFLAGS = 	-rpath ./Frameworks -F./Frameworks 	-framework SDL2 \
												-framework SDL2_image \
												-framework SDL2_mixer \
												-framework SDL2_ttf
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJS) $(INCLUDES)
	@$(CC) $(LIB) $(SDLFLAGS) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\033[1;37m EXECUTABLE CREATED : $(NAME) \033[0m\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)wolf3d.h
	@printf "\033[47m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIB):
	@make -C $(LIB_DIR)

clean:
	@printf "\033[41m \033[0m"
	@make -C $(LIB_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@$(RM) $(NAME)

re: fclean all
