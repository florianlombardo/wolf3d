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

static int		deal_key(int key, t_env *e)
{
	double	olddir;
	double	oldplane;

	if (key == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(EXIT_SUCCESS);
	}
	else if (key == 0)	//A
	{
		olddir = e->p.dir.x;
		e->p.dir.x = e->p.dir.x * cos(e->rotspeed) - e->p.dir.y * sin(e->rotspeed);
		e->p.dir.y = olddir * sin(e->rotspeed) + e->p.dir.y * cos(e->rotspeed);
		oldplane = e->p.plane.x;
		e->p.plane.x = e->p.plane.x * cos(e->rotspeed) - e->p.plane.y * sin(e->rotspeed);
		e->p.plane.y = oldplane * sin(e->rotspeed) + e->p.plane.y * cos(e->rotspeed);
		mlx_clear_window(e->mlx, e->win);
		raycasting(e);
	}
	else if (key == 2)	//D
	{
		olddir = e->p.dir.x;
		e->p.dir.x = e->p.dir.x * cos(-e->rotspeed) - e->p.dir.y * sin(-e->rotspeed);
		e->p.dir.y = olddir * sin(-e->rotspeed) + e->p.dir.y * cos(-e->rotspeed);
		oldplane = e->p.plane.x;
		e->p.plane.x = e->p.plane.x * cos(-e->rotspeed) - e->p.plane.y * sin(-e->rotspeed);
		e->p.plane.y = oldplane * sin(-e->rotspeed) + e->p.plane.y * cos(-e->rotspeed);
		mlx_clear_window(e->mlx, e->win);
		raycasting(e);
	}
	else if (key == 13)	//S
	{
		if (!map[(int)(e->p.pos.x + e->p.dir.x * e->movespeed)][(int)e->p.pos.y])
			e->p.pos.x +=e->p.dir.x * e->movespeed;
		if (!map[(int)e->p.pos.x][(int)(e->p.pos.y + e->p.dir.y * e->movespeed)])
			e->p.pos.y +=e->p.dir.y * e->movespeed;
		mlx_clear_window(e->mlx, e->win);
		raycasting(e);
	}
	else if (key == 1)	//W
	{
		if (!map[(int)(e->p.pos.x - e->p.dir.x * e->movespeed)][(int)e->p.pos.y])
			e->p.pos.x -= e->p.dir.x * e->movespeed;
		if (!map[(int)e->p.pos.x][(int)(e->p.pos.y - e->p.dir.y * e->movespeed)])
			e->p.pos.y -= e->p.dir.y * e->movespeed;
		mlx_clear_window(e->mlx, e->win);
		raycasting(e);
	}
	return (0);
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
	int		y;
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
		printf("%f %f %f %f\n", e->p.pos.x, e->p.pos.y, e->p.dir.x, e->p.dir.y);
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
			if (map[onmap.x][onmap.y] > 0)
				hit = 1;
		}
		dist = (!side) ? (onmap.x - e->p.pos.x + (1 - step.x) / 2) / raydir.x
			: (onmap.y - e->p.pos.y + (1 - step.y) / 2) / raydir.y;
		height = (int)((double)HEI / dist);
		if ((start = -height / 2 + HEI / 2) < 0)
			start = 0;
		if ((end = height / 2 + HEI / 2) >= HEI)
			end = HEI - 1;
		y = start - 1;
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
		}
	}
}

int				main(void)
{
	t_env	e;

	e.p = init_player();
	if (!(e.mlx = mlx_init()))
		return (1);
	if (!(e.win = mlx_new_window(e.mlx, WID, HEI, "oui")))
		return (1);
	e.time = 0;
	raycasting(&e);
	e.oldtime = e.time;
	e.time = clock();
	e.frametime = 1.0 / ((e.time - e.oldtime) / 1000);
	e.rotspeed = e.frametime * 9.0;
	e.movespeed = e.frametime * 15.0;
	mlx_key_hook(e.win, deal_key, &e);
	mlx_loop(e.mlx);
	return (0);
}
