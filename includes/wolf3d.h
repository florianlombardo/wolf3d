/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 13:40:13 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 17:43:37 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

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

# define SIZE 800
# define MID ((SIZE >> 1) - 1)
# define SPAWN 'P'
# define MUR 'M'
# define SOL 's'

# define X_PLAY_MIN 334
# define X_PLAY_MAX 467
# define Y_PLAY_MIN 430
# define Y_PLAY_MAX 479

# define X_EXIT_MIN 334
# define X_EXIT_MAX 467
# define Y_EXIT_MIN 497
# define Y_EXIT_MAX 546

# define COS 0.995004
# define PSIN 0.099833
# define NSIN -0.099833
# define COS45 0.707107
# define SIN45 0.707107

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
	int				maxLengthX;
	int				maxLengthY;
	short			change;
	char			**map;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Texture		*tex;
	SDL_Surface		*icon;
	SDL_Surface		*buffer;
	SDL_Surface		*wall;
}					t_env;

void				error_usage(int ac);
void				check_error(t_env e);
void				error_name(void);
void				error_malloc(void);
void				error_map(void);
void				error_usage(int ac);
void				launch_main_menu(t_env *e);
int					key_map(int key, t_env *e);
void				map_init(char *name, t_env *e);
t_env				init_game(t_env e);
void				deal_key(t_env *e, SDL_Event event);
void				raycasting(t_env *e);
void				ft_quit(t_env *e, int status);

#endif
