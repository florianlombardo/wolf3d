/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 13:39:15 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:50:17 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	title_screen(t_env *e, SDL_Event *event)
{
	short		quit;
	Uint8		alpha;

	quit = 0;
	SDL_RenderCopy(e->rend, e->title, NULL, NULL);
	SDL_RenderPresent(e->rend);
	SDL_GetTextureAlphaMod(e->title, &alpha);
	while (!quit)
	{
		SDL_WaitEvent(event);
		if (event->type == SDL_KEYDOWN)
			quit = 1;
	}
	while (alpha > SDL_ALPHA_TRANSPARENT)
	{
		alpha -= 3;
		SDL_SetTextureAlphaMod(e->title, alpha);
		SDL_RenderClear(e->rend);
		SDL_RenderCopy(e->rend, e->title, NULL, NULL);
		SDL_RenderPresent(e->rend);
		if ((alpha - 3) < 0)
			break ;
	}
	SDL_DestroyTexture(e->title);
}

static void	ft_usage(int ac)
{
	if (ac != 2)
	{
		ft_putendl("usage : ./wolf3d [file]");
		exit(EXIT_FAILURE);
	}
}

int			main(int ac, char **av)
{
	t_env		*e;
	int			quit_bool;
	SDL_Event	event;

	ft_usage(ac);
	if (!(e = malloc(sizeof(t_env))))
		ft_quit(e, E_MALLOC);
	e->map = NULL;
	e->change = 0;
	map_init(av[1], e);
	check_error(e);
	init_all(e);
	title_screen(e, &event);
	raycasting(e);
	quit_bool = 1;
	while (quit_bool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE &&
			event.type == SDL_KEYDOWN))
			quit_bool = 0;
		deal_key(e, event);
	}
	ft_quit(e, E_NOERROR);
	return (EXIT_SUCCESS);
}
