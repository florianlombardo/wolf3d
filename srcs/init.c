/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 03:24:15 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:38:51 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_init_null(t_env *e)
{
	int	i;

	e->window = NULL;
	e->rend = NULL;
	e->tex = NULL;
	e->icon = NULL;
	e->buffer = NULL;
	e->title = NULL;
	i = -1;
	while (++i < 4)
		e->wall[i] = NULL;
}

static t_plyr	init_player(char **map)
{
	t_plyr	ret;
	int		i;
	int		j;

	i = -1;
	while (map[++i] && (j = -1))
		while (map[i][++j])
			if (map[i][j] == 'P')
			{
				ret.pos.x = j + 0.5;
				ret.pos.y = i + 0.5;
			}
	ret.dir.x = -1;
	ret.dir.y = 0;
	ret.plane.x = 0;
	ret.plane.y = 0.66;
	return (ret);
}

void			init_all(t_env *e)
{
	ft_init_null(e);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_quit(e, E_INITFAIL);
	if (SDL_CreateWindowAndRenderer(SIZE, SIZE, SDL_WINDOW_SHOWN,
		&e->window, &e->rend))
		ft_quit(e, E_WINDOW);
	SDL_WarpMouseInWindow(e->window, SIZE >> 1, SIZE >> 1);
	if (SDL_SetRelativeMouseMode(SDL_ENABLE))
		ft_quit(e, E_WINDOW);
	SDL_SetWindowTitle(e->window, "Wolf3d");
	if (!(e->icon = SDL_LoadBMP("textures/icon.bmp")))
		ft_quit(e, E_TEXLOAD);
	SDL_SetWindowIcon(e->window, e->icon);
	load_textures(e);
	e->p = init_player(e->map);
}
