#include "wolf3d.h"

static t_plyr	init_player(void)
{
	t_plyr	ret;

	ret.posx = 8;
	ret.posy = 8;
	//ret.dist_plane = 277;	//(WID / 2) / tan(M_PI * 30 / 180)
	ret.mid_angle = 0;
	return (ret);
}

/*static int		find_horizontal(t_plyr p, int map[15][15], double angle)
{
	int		ax;
	int		ay;
	int		xa;
	int		ya;
	int		pd;

	pd = 0;
	if (angle <= 180)
	{
		ay = (int)floor((double)p.posy / 64.0) * 64 -1;
		ya = -64;
	}
	else
	{
		ay = (int)floor((double)p.posy / 64.0) * 64 + 64;
		ya = 64;
	}
	ax = p.posx + (int)((double)(p.posy - ay) / tan(3.14159 * angle / 180));
	xa = (int)((double)ya / tan(3.14159 * angle / 180));
	while (map[ay / 64][ax / 64] != 1)
	{
		ay += ya;
		ax += xa;
	}
	printf("%d %d    xa: %d\n", ax / 64, ay / 64, xa);
	pd = (int)sqrt((double)((p.posx - ax) * (p.posx - ax) + (p.posy - ay) * (p.posy - ay)));
	return (pd);
}

static int		find_vertical(t_plyr p, int map[15][15], double angle)
{
	int		bx;
	int		by;
	int		xa;
	int		ya;
	int		pe;

	pe = 0;
	if (angle >= 270 && angle <= 90)
	{
		bx = (int)floor((double)p.posx / 64.0) * 64 + 64;
		xa = 64;
	}
	else
	{
		bx = (int)floor((double)p.posx / 64) * 64 - 1;
		xa = -64;
	}
	by = p.posy + (p.posx - bx) * (int)tan(3.14159 * angle / 180);
	ya = 64 * (int)tan(3.14159 * angle / 180);
	while (map[by / 64][bx / 64] != 1)
	{
		by += ya;
		bx += xa;
	}
	pe = (int)sqrt((double)((p.posx - bx) * (p.posx - bx) + (p.posy - by) * (p.posy - by)));
	return (pe);
}

static void		draw_line(t_plyr p, int x, int dist, SDL_Surface *oui)
{
	int		projected;
	int		start;
	int		end;

	projected = (int)(64 / (dist * p.dist_plane));
	start = (HEI / 2) - (projected / 2);
	end = (HEI / 2) + (projected / 2);
	//printf("%d %d proj: %d   dist: %d\n", start, end, projected, dist);
	while (start <= end)
	{
		*((Uint32*)(oui->pixels) + x + start * oui->w) = SDL_MapRGB(oui->format, 0x00, 0x00, 0xFF);
		start++;
	}
}

static void		trace_ray(t_plyr p, int map[15][15], double angle, int x, SDL_Surface *oui)
{
	int		v;
	int		h;

	h = find_horizontal(p, map, angle);
	v = find_vertical(p, map, angle);
	if (v > h)
		draw_line(p, x, h, oui);
	else
		draw_line(p, x, v, oui);
}

static void		ft_draw(t_plyr p, int map[15][15], SDL_Surface *oui)
{
	double	angle;
	int		i;

	if (p.mid_angle >= 30)
		angle = (double)p.mid_angle - 30.0;
	else
		angle = 360.0 - (30.0 - (double)p.mid_angle);
	i = -1;
	while (++i < WID)
	{
		trace_ray(p, map, angle, i, oui);
		printf("i: %d   angle :%f\n", i, angle);
		angle += 60.0 / (double)WID;
		if (angle > 360.0)
			angle -= 360.0;
		if (angle < 0.0)
			angle += 360.0;
	}
}*/

static void	ft_draw(t_plyr p, int map[15][15], SDL_Surface *screen)
{
	double	angle;
	double	dist;
	double	eyex;
	double	eyey;
	int		x;
	int		wallhit;
	int		testx;
	int		testy;

	x = -1;
	while (++x < WID)
	{
		angle = (p.mid_angle - 60.0 / 2.0) + ((float)x / WID) * 60.0;
		dist = 0;
		wallhit = 0;
		eyex = sin(angle);
		eyey = cos(angle);
		while (!wallhit)
		{
			dist += 0.1;
			testx = (int)(p.posx + eyex * dist);
			testy = (int)(p.posy + eyey * dist);
			if (map[testy][testx] == 1)
				wallhit = 1;
		}
		int		ceiling = (int)((double)(HEI / 2.0) - HEI / dist);
		int		floor = HEI - ceiling;
		int		y = -1;
		while (++y < HEI)
		{
			if (y < ceiling)
			{
				*((Uint32*)(screen->pixels) + x + y * screen->w)
					= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
			}
			else if (y >= ceiling && y < floor)
			{
				*((Uint32*)(screen->pixels) + x + y * screen->w)
					= SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
			}
			else
			{
				*((Uint32*)(screen->pixels) + x + y * screen->w)
					= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
			}
		}
	}
}

int				main(void)
{
	t_plyr		p;
	int map[15][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	SDL_Surface	*screen;
	SDL_Event	event;

	p = init_player();
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return (1);
	if (!(screen = SDL_SetVideoMode(WID, HEI, 32, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return (1);
	}
	ft_draw(p, map, screen);
	printf("draw done\n");
	SDL_Flip(screen);
	do
	{
		SDL_WaitEvent(&event);
	} while (event.type != SDL_KEYDOWN);
	SDL_Quit();
	return (0);
}
