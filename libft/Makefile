.PHONY : all clean fclean re
	
NAME = libft.a
FLAG = -Wall -Wextra -Werror
SRC = ft_strcat.c ft_strcpy.c ft_strdup.c ft_strlen.c ft_strncat.c ft_strncpy.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_putstr.c ft_putchar.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putendl.c ft_putnbr.c ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strlcat.c ft_tolower.c ft_intnsize.c ft_lstrep.c ft_sizeblanc.c ft_sizeword.c ft_sizetab.c ft_strjoinfree.c get_next_line.c
HEADER = -I./libft.h
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\x1b[1;32m LIB CREATED : $(NAME)\n\033[0m"
	@ar rc $(NAME) $(OBJ)
%.o: %.c
	@printf "\033[42m \033[0m"
	@gcc $(FLAG) -I./includes -o $@ -c $<

clean:
	@printf "\033[41m \033[0m"
	@rm -f $(OBJ)
fclean: clean
	@echo "\033[1;31;5m LIB DELETED : $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean all
