/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quit.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 08:29:52 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:37:57 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	ft_print_error(t_errcodes err)
{
	if (err == E_INITFAIL)
		ft_putendl("SDL crashed at its start.");
	else if (err == E_TEXLOAD)
		ft_putendl("Textures could not load.");
	else if (err == E_RENDER)
		ft_putendl("An error occured while rendering the screen.");
	else if (err == E_RENDER)
		ft_putendl("The window was not created properly.");
	else if (err == E_MALLOC)
		ft_putendl("Memory allocation error.");
}

static void	free_loops(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (e->wall[i])
			SDL_FreeSurface(e->wall[i]);
	i = -1;
	while (e->map[++i])
		free(e->map[i]);
	free(e->map);
}

static void	ft_free(t_env *e)
{
	if (e)
	{
		if (e->buffer)
			SDL_FreeSurface(e->buffer);
		if (e->title)
			SDL_DestroyTexture(e->title);
		if (e->icon)
			SDL_FreeSurface(e->icon);
		if (e->rend)
			SDL_DestroyRenderer(e->rend);
		if (e->window)
			SDL_DestroyWindow(e->window);
		free_loops(e);
		free(e);
	}
}

void		ft_quit(t_env *e, t_errcodes err)
{
	ft_free(e);
	SDL_Quit();
	if (err != E_NOERROR)
	{
		ft_print_error(err);
		exit(EXIT_FAILURE);
	}
}
