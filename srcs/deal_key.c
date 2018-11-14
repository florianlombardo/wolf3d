/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   deal_key.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 06:17:58 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:51:28 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	rotating_view(t_env *e, SDL_Event event)
{
	double	olddir;
	double	oldplane;

	olddir = e->p.dir.x;
	oldplane = e->p.plane.x;
	if (event.motion.type == SDL_MOUSEMOTION && event.motion.xrel < 0)
	{
		e->p.dir.x = e->p.dir.x * COS - e->p.dir.y * NSIN;
		e->p.dir.y = olddir * NSIN + e->p.dir.y * COS;
		e->p.plane.x = e->p.plane.x * COS - e->p.plane.y * NSIN;
		e->p.plane.y = oldplane * NSIN + e->p.plane.y * COS;
		e->change = 1;
	}
	else if (event.motion.type == SDL_MOUSEMOTION && event.motion.xrel > 0)
	{
		e->p.dir.x = e->p.dir.x * COS - e->p.dir.y * PSIN;
		e->p.dir.y = olddir * PSIN + e->p.dir.y * COS;
		e->p.plane.x = e->p.plane.x * COS - e->p.plane.y * PSIN;
		e->p.plane.y = oldplane * PSIN + e->p.plane.y * COS;
		e->change = 1;
	}
}

static void	strafing(t_env *e, SDL_Event event)
{
	t_dpos	mvmt;
	double	angle;

	if (event.key.keysym.sym == SDLK_a && event.type == SDL_KEYDOWN)
	{
		angle = atan2(e->p.dir.y, e->p.dir.x) - M_PI_2;
		mvmt.y = sin(angle);
		mvmt.x = cos(angle);
		if (!(e->map[(int)e->p.pos.y][(int)(e->p.pos.x + 0.3 * mvmt.x)] == 'M'))
			e->p.pos.x += 0.3 * mvmt.x;
		if (!(e->map[(int)(e->p.pos.y + 0.3 * mvmt.y)][(int)e->p.pos.x] == 'M'))
			e->p.pos.y += 0.3 * mvmt.y;
		e->change = 1;
	}
	else if (event.key.keysym.sym == SDLK_d && event.type == SDL_KEYDOWN)
	{
		angle = atan2(e->p.dir.y, e->p.dir.x) + M_PI_2;
		mvmt.y = sin(angle);
		mvmt.x = cos(angle);
		if (!(e->map[(int)e->p.pos.y][(int)(e->p.pos.x + 0.3 * mvmt.x)] == 'M'))
			e->p.pos.x += 0.3 * mvmt.x;
		if (!(e->map[(int)(e->p.pos.y + 0.3 * mvmt.y)][(int)e->p.pos.x] == 'M'))
			e->p.pos.y += 0.3 * mvmt.y;
		e->change = 1;
	}
}

static void	moving(t_env *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_w && event.type == SDL_KEYDOWN)
	{
		if (!(e->map[(int)e->p.pos.y][(int)(e->p.pos.x +
			e->p.dir.x * 0.3)] == 'M'))
			e->p.pos.x += e->p.dir.x * 0.3;
		if (!(e->map[(int)(e->p.pos.y + e->p.dir.y * 0.3)]
			[(int)e->p.pos.x] == 'M'))
			e->p.pos.y += e->p.dir.y * 0.3;
		e->change = 1;
	}
	else if (event.key.keysym.sym == SDLK_s && event.type == SDL_KEYDOWN)
	{
		if (!(e->map[(int)e->p.pos.y][(int)(e->p.pos.x -
			e->p.dir.x * 0.3)] == 'M'))
			e->p.pos.x -= e->p.dir.x * 0.3;
		if (!(e->map[(int)(e->p.pos.y - e->p.dir.y * 0.3)]
			[(int)e->p.pos.x] == 'M'))
			e->p.pos.y -= e->p.dir.y * 0.3;
		e->change = 1;
	}
}

void		deal_key(t_env *e, SDL_Event event)
{
	rotating_view(e, event);
	strafing(e, event);
	moving(e, event);
	if (e->change == 1)
	{
		e->change = 0;
		if (SDL_RenderClear(e->rend))
			ft_quit(e, E_RENDER);
		raycasting(e);
	}
}
