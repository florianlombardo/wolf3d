/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 06:17:02 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:00:36 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	fill_vars(t_env *e, t_norm *n)
{
	n->onmap.x = (int)e->p.pos.x;
	n->onmap.y = (int)e->p.pos.y;
	n->delta.x = fabs(1 / n->raydir.x);
	n->delta.y = fabs(1 / n->raydir.y);
	if (n->raydir.x < 0)
	{
		n->step.x = -1;
		n->sidedist.x = (e->p.pos.x - n->onmap.x) * n->delta.x;
	}
	else
	{
		n->step.x = 1;
		n->sidedist.x = (n->onmap.x + 1.0 - e->p.pos.x) * n->delta.x;
	}
	if (n->raydir.y < 0)
	{
		n->step.y = -1;
		n->sidedist.y = (e->p.pos.y - n->onmap.y) * n->delta.y;
	}
	else
	{
		n->step.y = 1;
		n->sidedist.y = (n->onmap.y + 1.0 - e->p.pos.y) * n->delta.y;
	}
}

static void	trace(t_env *e, t_norm *n)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (n->sidedist.x < n->sidedist.y)
		{
			n->sidedist.x += n->delta.x;
			n->onmap.x += n->step.x;
			n->side = 0;
		}
		else
		{
			n->sidedist.y += n->delta.y;
			n->onmap.y += n->step.y;
			n->side = 1;
		}
		if (e->map[n->onmap.y][n->onmap.x] == 'M')
			hit = 1;
	}
	n->dist = (!n->side) ? (n->onmap.x - e->p.pos.x + ((1 - n->step.x) >> 1)) /
	n->raydir.x : (n->onmap.y - e->p.pos.y + ((1 - n->step.y) >> 1))
	/ n->raydir.y;
	n->height = (int)((double)SIZE / n->dist);
	n->start = (-n->height >> 1) + (SIZE >> 1);
}

static void	draw(t_env *e, t_norm *n, int x, int i)
{
	if (n->end >= SIZE)
		n->end = SIZE - 1;
	n->wallx = (n->side) ? e->p.pos.x + n->dist * n->raydir.x :
	e->p.pos.y + n->dist * n->raydir.y;
	n->wallx -= floor(n->wallx);
	if ((n->side && n->onmap.y > e->p.pos.y) ||
	(!n->side && n->onmap.x < e->p.pos.x))
		n->wallx = 1 - n->wallx;
	if (!n->side)
		i = (n->onmap.x < e->p.pos.x) ? 0 : 1;
	else
		i = (n->onmap.y < e->p.pos.y) ? 2 : 3;
	n->y = n->start - 1;
	while (++n->y < n->end)
		n->pixels[n->y * e->buffer->w + x] = ft_argb_to_rgba(n->wpixels[i][(int)
		(((double)(n->y - n->wstart) / (double)(n->wend - n->wstart)) * 64) *
		e->wall[i]->w + (int)(n->wallx * 64)]);
	while (n->y < SIZE)
	{
		n->pixels[n->y * e->buffer->w + x] = ft_rgba(130, 130, 130, 0xFF);
		n->pixels[(SIZE - n->y - 1) * e->buffer->w + x] =
		ft_rgba(80, 80, 80, 0xFF);
		n->y++;
	}
}

static void	end(t_env *e, t_norm *n)
{
	if (SDL_LockSurface(e->buffer))
		ft_quit(e, E_RENDER);
	e->buffer->pixels = n->pixels;
	SDL_UnlockSurface(e->buffer);
	if (!(e->tex = SDL_CreateTextureFromSurface(e->rend, e->buffer)))
		ft_quit(e, E_RENDER);
	SDL_RenderCopy(e->rend, e->tex, NULL, NULL);
	SDL_RenderPresent(e->rend);
	SDL_DestroyTexture(e->tex);
}

void		raycasting(t_env *e)
{
	t_norm	n;
	int		i;
	int		x;

	n.pixels = e->buffer->pixels;
	i = -1;
	while (++i < 4)
		n.wpixels[i] = e->wall[i]->pixels;
	x = -1;
	while (++x < SIZE)
	{
		n.camx = -((x << 1) / (double)SIZE - 1);
		n.raydir.x = e->p.dir.x + e->p.plane.x * n.camx;
		n.raydir.y = e->p.dir.y + e->p.plane.y * n.camx;
		fill_vars(e, &n);
		trace(e, &n);
		n.wstart = n.start;
		if (n.start < 0)
			n.start = 0;
		n.end = (n.height >> 1) + (SIZE >> 1);
		n.wend = n.end;
		draw(e, &n, x, i);
	}
	end(e, &n);
}
