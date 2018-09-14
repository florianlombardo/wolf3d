#include "../includes/wolf3d.h"

int map[15][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


static int		win_init(t_env *e)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		dprintf(1, "SDL_Init() error: %s\n", SDL_GetError());
		return (0);
	}
	if (SDL_CreateWindowAndRenderer(WID, HEI, SDL_WINDOW_SHOWN, &e->win, &e->rend))
	{
		dprintf(1, "SDL_CreateWindowAndRenderer() error: %s\n", SDL_GetError());
		return (0);
	}
	SDL_SetWindowTitle(e->win, "Wolf3d");
	if (!(e->icon = IMG_Load("textures/icon.png")))
	{
		dprintf(1, "IMG_Load() error: %s\n", IMG_GetError());
		return (0);
	}
	SDL_SetWindowIcon(e->win, e->icon);
	return (1);
}

static void		quit(t_env *e, int status)
{
	if (e->icon)
		SDL_FreeSurface(e->icon);
	if (e->rend)
		SDL_DestroyRenderer(e->rend);
	if (e->win)
		SDL_DestroyWindow(e->win);
	SDL_Quit();
	if (status == 1)
		exit(EXIT_FAILURE);
}

static void		deal_key(t_env *e, SDL_Event event)
{
	double	oldplane;
	double	olddir;

	if (event.key.keysym.sym == SDLK_a && event.key.state == SDL_PRESSED && event.key.repeat == 0)
	{
		olddir = e->p.dir.x;
		e->p.dir.x = e->p.dir.x * cos(0.1) - e->p.dir.y * sin(0.1);
		e->p.dir.y = olddir * sin(0.1) + e->p.dir.y * cos(0.1);
		oldplane = e->p.plane.x;
		e->p.plane.x = e->p.plane.x * cos(0.1) - e->p.plane.y * sin(0.1);
		e->p.plane.y = oldplane * sin(0.1) + e->p.plane.y * cos(0.1);
		if (SDL_RenderClear(e->rend))
			quit(e, 1);
		raycasting(e);
	}
	else if (event.key.keysym.sym == SDLK_d && event.key.state == SDL_PRESSED && event.key.repeat == 0)
	{
		olddir = e->p.dir.x;
		e->p.dir.x = e->p.dir.x * cos(-0.1) - e->p.dir.y * sin(-0.1);
		e->p.dir.y = olddir * sin(-0.1) + e->p.dir.y * cos(-0.1);
		oldplane = e->p.plane.x;
		e->p.plane.x = e->p.plane.x * cos(-0.1) - e->p.plane.y * sin(-0.1);
		e->p.plane.y = oldplane * sin(-0.1) + e->p.plane.y * cos(-0.1);
		if (SDL_RenderClear(e->rend))
			quit(e, 1);
		raycasting(e);
	}
	else if (event.key.keysym.sym == SDLK_w && event.key.state == SDL_PRESSED && event.key.repeat == 0)
	{
		if (!map[(int)e->p.pos.y][(int)(e->p.pos.x + e->p.dir.x * 0.3)])
			e->p.pos.x +=e->p.dir.x * 0.3;
		if (!map[(int)(e->p.pos.y + e->p.dir.y * 0.3)][(int)e->p.pos.x])
			e->p.pos.y +=e->p.dir.y * 0.3;
		if (SDL_RenderClear(e->rend))
			quit(e, 1);
		raycasting(e);
	}
	else if (event.key.keysym.sym == SDLK_s && event.key.state == SDL_PRESSED && event.key.repeat == 0)
	{
		if (!map[(int)e->p.pos.y][(int)(e->p.pos.x - e->p.dir.x * 0.3)])
			e->p.pos.x -= e->p.dir.x * 0.3;
		if (!map[(int)(e->p.pos.y - e->p.dir.y * 0.3)][(int)e->p.pos.x])
			e->p.pos.y -= e->p.dir.y * 0.3;
		if (SDL_RenderClear(e->rend))
			quit(e, 1);
		raycasting(e);
	}
}

static t_plyr	init_player(void)
{
	t_plyr	ret;

	ret.pos.x = 8;
	ret.pos.y = 8;
	ret.dir.x = -1;
	ret.dir.y = 0;
	ret.plane.x = 0;
	ret.plane.y = 0.66;
	return (ret);
}

void			raycasting(t_env *e)
{
	double	camx;
	double	dist;
	t_dpos	raydir;
	t_dpos	delta;
	t_dpos	sidedist;
	t_ipos	onmap;
	t_ipos	step;
	int		x;
	int		hit;
	int		side;
	int		height;
	int		start;
	int		end;

	x = -1;
	while (++x < WID)
	{
		camx = 2 * x / (double)WID - 1;
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
			if (map[onmap.y][onmap.x] > 0)
				hit = 1;
		}
		dist = (!side) ? (onmap.x - e->p.pos.x + (1 - step.x) / 2) / raydir.x
			: (onmap.y - e->p.pos.y + (1 - step.y) / 2) / raydir.y;
		height = (int)((double)HEI / dist);
		if ((start = -height / 2 + HEI / 2) < 0)
			start = 0;
		if ((end = height / 2 + HEI / 2) >= HEI)
			end = HEI - 1;
		/*y = start - 1;
		if (!side)
			while (++y < end)
				mlx_pixel_put(e->mlx, e->win, x, y, 0x0000ff);
		else
			while (++y < end)
				mlx_pixel_put(e->mlx, e->win, x, y, 0x000088);
		while (++y < HEI)
		{
			mlx_pixel_put(e->mlx, e->win, x, y, 0xa9a9a9);
			mlx_pixel_put(e->mlx, e->win, x, HEI - y - 1, 0xa9a9a9);
		}*/
		SDL_SetRenderDrawColor(e->rend, 169, 169, 169, 255);
		SDL_RenderDrawLine(e->rend, x, 0, x, start);
		SDL_RenderDrawLine(e->rend, x, end, x, HEI - 1);
		if (!side)
			SDL_SetRenderDrawColor(e->rend, 0, 0, 255, 255);
		else
			SDL_SetRenderDrawColor(e->rend, 0, 0, 136, 255);
		SDL_RenderDrawLine(e->rend, x, start, x, end);
	}
	SDL_RenderPresent(e->rend);
}

int				main(void)
{
	t_env		e;
	SDL_bool	b;
	SDL_Event	event;

	if (!win_init(&e))
		quit(&e, 1);
	e.p = init_player();
	raycasting(&e);
	b = SDL_FALSE;
	while (!b)
	{
		SDL_WaitEvent(&event);
		deal_key(&e, event);
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			b = SDL_TRUE;
	}
	quit(&e, 0);
	return (EXIT_SUCCESS);
}
