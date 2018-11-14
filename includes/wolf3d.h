/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 13:40:13 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 15:48:03 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
**		INCLUDES
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include <SDL2_ttf/SDL_ttf.h>
# include "../libft/libft.h"

/*
**		DEFINES
*/

# define SIZE 800
# define MID ((SIZE >> 1) - 1)

# define SPAWN 'P'
# define MUR 'M'
# define SOL 's'

# define COS 0.995004
# define PSIN 0.099833
# define NSIN -0.099833
# define COS90 0
# define SIN90 1

/*
**		STRUCTURES
*/

typedef enum		e_errcodes
{
	E_NOERROR,
	E_INITFAIL,
	E_TEXLOAD,
	E_RENDER,
	E_WINDOW,
	E_MALLOC,
	E_MAP,
	E_NAME
}					t_errcodes;

typedef struct		s_ipos
{
	int				x;
	int				y;
}					t_ipos;

typedef struct		s_dpos
{
	double			x;
	double			y;
}					t_dpos;

typedef struct		s_plyr
{
	t_dpos			pos;
	t_dpos			dir;
	t_dpos			plane;
}					t_plyr;

typedef	struct		s_env
{
	t_plyr			p;
	int				maxlengthx;
	int				maxlengthy;
	short			change;
	short			frame;
	char			**map;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Texture		*tex;
	SDL_Texture		*title;
	SDL_Surface		*icon;
	SDL_Surface		*buffer;
	SDL_Surface		*wall[4];
}					t_env;

typedef struct		s_norm
{
	double	camx;
	double	dist;
	double	wallx;
	t_dpos	raydir;
	t_dpos	delta;
	t_dpos	sidedist;
	t_ipos	onmap;
	t_ipos	step;
	int		y;
	int		side;
	int		height;
	int		start;
	int		end;
	int		wstart;
	int		wend;
	Uint32	*pixels;
	Uint32	*wpixels[4];
}					t_norm;

/*
**		FUNCTIONS
*/

/*
** map.c
*/

void				map_init(char *name, t_env *e);

/*
** error_map.c
*/

void				check_error(t_env *e);
void				ft_maperror(t_env *e, t_errcodes err);

/*
** init.c
*/

void				init_all(t_env *e);

/*
** load_textures.c
*/

void				load_textures(t_env *e);

/*
** raycasting.c
*/

void				raycasting(t_env *e);

/*
** utilities.c
*/

Uint32				ft_rgba(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
Uint32				ft_argb_to_rgba(Uint32 pixel);

/*
** deal_key.c
*/

void				deal_key(t_env *e, SDL_Event event);

/*
** quit.c
*/

void				ft_quit(t_env *e, t_errcodes err);

#endif
