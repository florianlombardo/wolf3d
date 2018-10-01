/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 13:39:15 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 15:41:22 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			ft_quit(t_env *e, int status)
{
	int		i;

	if (e->wall)
		SDL_FreeSurface(e->wall);
	if (e->buffer)
		SDL_FreeSurface(e->buffer);
	if (e->icon)
		SDL_FreeSurface(e->icon);
	if (e->rend)
		SDL_DestroyRenderer(e->rend);
	if (e->window)
		SDL_DestroyWindow(e->window);
	SDL_Quit();
	i = -1;
	while (e->map[++i])
		free(e->map[i]);
	free(e->map);
	if (status == 1)
	{
		ft_putendl("Error, please contact an administrator.");
		exit(EXIT_FAILURE);
	}
}

static void		init_sdl2(t_env *e)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_quit(e, 1);
	if (SDL_CreateWindowAndRenderer(SIZE, SIZE, SDL_WINDOW_SHOWN,
		&e->window, &e->rend))
			ft_quit(e, 1);
	SDL_SetWindowTitle(e->window, "Wolf3d");
	if (!(e->icon = IMG_Load("textures/icon.png")))
		ft_quit(e, 1);
	SDL_SetWindowIcon(e->window, e->icon);
	if (!(e->wall = IMG_Load("textures/wall.png")))
		ft_quit(e, 1);
	if (!(e->buffer = SDL_CreateRGBSurfaceWithFormat(0, SIZE, SIZE, 32, SDL_PIXELFORMAT_RGBA8888)))
		ft_quit(e, 1);
	SDL_WarpMouseInWindow(e->window, SIZE >> 1, SIZE >> 1);
	if (SDL_SetRelativeMouseMode(SDL_ENABLE))
		ft_quit(e, 1);
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
				ret.pos.x = j;
				ret.pos.y = i;
			}
	ret.dir.x = -1;
	ret.dir.y = 0;
	ret.plane.x = 0;
	ret.plane.y = 0.66;
	return (ret);
}

int				main(int ac, char **av)
{
	t_env		e;
	int			quit_bool;
	SDL_Event	event;

	e.map = 0;
	e.change = 0;
	error_usage(ac);
	map_init(av[1], &e);
	check_error(e);
	init_sdl2(&e);
	e.p = init_player(e.map);
	raycasting(&e);
	quit_bool = 1;
	while (quit_bool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN))
			quit_bool = 0;
		deal_key(&e, event);
	}
	ft_quit(&e, 0);
	return (EXIT_SUCCESS);
}