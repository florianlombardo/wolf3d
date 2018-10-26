/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 06:17:02 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 15:59:52 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static Uint32	ft_color_rgba(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = red & 0xFF;
	g = green & 0xFF;
	b = blue & 0xFF;
	a = alpha & 0xFF;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

static Uint32	ft_argb_to_rgba(Uint32 pixel)
{
	return (((pixel >> 24) & 0xFF) | (pixel << 8));
}

void			raycasting(t_env *e)
{
	double	camx;
	double	dist;
	double	wallx;
	t_dpos	raydir;
	t_dpos	delta;
	t_dpos	sidedist;
	t_ipos	onmap;
	t_ipos	step;
	int		x;
	int		y;
	int		hit;
	int		side;
	int		height;
	int		start;
	int		end;
	int		wstart;
	int		wend;
	Uint32	*pixels;
	Uint32	*wpixels;

	pixels = e->buffer->pixels;
	wpixels = e->wall->pixels;
	x = -1;
	while (++x < SIZE)
	{
		camx = -((x << 1) / (double)SIZE - 1);
		raydir.x = e->p.dir.x + e->p.plane.x * camx;
		raydir.y = e->p.dir.y + e->p.plane.y * camx;
		onmap.x = (int)e->p.pos.x;
		onmap.y = (int)e->p.pos.y;
		delta.x = fabs(1 / raydir.x);
		delta.y = fabs(1 / raydir.y);
		if (raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (e->p.pos.x - onmap.x) * delta.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (onmap.x + 1.0 - e->p.pos.x) * delta.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (e->p.pos.y - onmap.y) * delta.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (onmap.y + 1.0 - e->p.pos.y) * delta.y;
		}
		hit = 0;
		while (!hit)
		{
			if (sidedist.x < sidedist.y)
			{
				sidedist.x += delta.x;
				onmap.x += step.x;
				side = 0;
			}
			else
			{
				sidedist.y += delta.y;
				onmap.y += step.y;
				side = 1;
			}
			if (e->map[onmap.y][onmap.x] == 'M')
				hit = 1;
		}
		dist = (!side) ? (onmap.x - e->p.pos.x + ((1 - step.x) >> 1)) / raydir.x
			: (onmap.y - e->p.pos.y + ((1 - step.y) >> 1)) / raydir.y;
		height = (int)((double)SIZE / dist);
		start = (-height >> 1) + (SIZE >> 1);
		wstart = start;
		if (start < 0)
			start = 0;
		end = (height >> 1) + (SIZE >> 1);
		wend = end;
		if (end >= SIZE)
			end = SIZE - 1;
		wallx = (side) ? e->p.pos.x + dist * raydir.x : e->p.pos.y + dist * raydir.y;
		wallx -= floor(wallx);
		if ((side && onmap.y > e->p.pos.y) || (!side && onmap.x < e->p.pos.y))
			wallx = 1 - wallx;
		y = start - 1;
		while (++y < end)
			pixels[y * e->buffer->w + x] = ft_argb_to_rgba(wpixels[(int)(((double)(y - wstart)
				/ (double)(wend - wstart)) * 64) * e->wall->w + (int)(wallx * 64)]);
		while (y < SIZE)
		{
			pixels[y * e->buffer->w + x] = ft_color_rgba(130, 130, 130, 0xFF);
			pixels[(SIZE - y - 1) * e->buffer->w + x] = ft_color_rgba(80, 80, 80, 0xFF);
			y++;
		}
	}
	if (SDL_LockSurface(e->buffer))
		ft_quit(e, 1);
	e->buffer->pixels = pixels;
	SDL_UnlockSurface(e->buffer);
	if (!(e->tex = SDL_CreateTextureFromSurface(e->rend, e->buffer)))
		ft_quit(e, 1);
	SDL_RenderCopy(e->rend, e->tex, NULL, NULL);
	SDL_RenderPresent(e->rend);
	SDL_DestroyTexture(e->tex);
}
