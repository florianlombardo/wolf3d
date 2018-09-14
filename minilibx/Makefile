#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -rcs $(NOM) $(OBJ)
	@ranlib $(NOM)
	@printf "\033[33m libmlx.a \xE2\x9C\x94\033[0m\n"

%.o: %.c
	@printf "\033[43m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.m
	@printf "\033[43m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all
