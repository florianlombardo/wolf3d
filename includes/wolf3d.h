#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include <SDL2_ttf/SDL_ttf.h>

# define WID 600
# define HEI 600
# define FOV 60

typedef struct	s_ipos
{
	int			x;
	int			y;
}				t_ipos;

typedef struct	s_dpos
{
	double		x;
	double		y;
}				t_dpos;

typedef struct	s_plyr
{
	t_dpos		pos;
	t_dpos		dir;
	t_dpos		plane;
}				t_plyr;

typedef struct	s_env
{
	t_plyr		p;
	SDL_Window	*win;
	SDL_Renderer	*rend;
	SDL_Texture	*tex;
	SDL_Surface	*icon;
	char		*map;
}				t_env;

void			raycasting(t_env *e);

#endif
