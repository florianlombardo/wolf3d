/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_textures.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/06 13:30:16 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 14:41:39 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	load_menu(t_env *e)
{
	SDL_Surface	*tmp;

	tmp = NULL;
	if (!(tmp = SDL_LoadBMP("textures/title_screen.bmp")))
	{
		SDL_FreeSurface(tmp);
		ft_quit(e, E_TEXLOAD);
	}
	if (!(e->title = SDL_CreateTextureFromSurface(e->rend, tmp)))
	{
		SDL_FreeSurface(tmp);
		ft_quit(e, E_TEXLOAD);
	}
	SDL_FreeSurface(tmp);
}

static void	load_ingame(t_env *e)
{
	if (!(e->wall[0] = SDL_LoadBMP("textures/wall.bmp")))
		ft_quit(e, E_TEXLOAD);
	if (!(e->wall[1] = SDL_LoadBMP("textures/verboten.bmp")))
		ft_quit(e, E_TEXLOAD);
	if (!(e->wall[2] = SDL_LoadBMP("textures/skull.bmp")))
		ft_quit(e, E_TEXLOAD);
	if (!(e->wall[3] = SDL_LoadBMP("textures/dirt.bmp")))
		ft_quit(e, E_TEXLOAD);
	if (!(e->buffer = SDL_CreateRGBSurfaceWithFormat(0, SIZE, SIZE, 32,
		SDL_PIXELFORMAT_RGBA8888)))
		ft_quit(e, E_TEXLOAD);
}

void		load_textures(t_env *e)
{
	load_menu(e);
	load_ingame(e);
}
