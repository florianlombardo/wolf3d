#include "../includes/wolf3d.h"

int map[15][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				   {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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

static void error(t_env *e, int oui)
{
	mlx_destroy_window(e->mlx, e->win);
	switch (oui)
	{
		case 1:
			dprintf(1, "erreur de create\n");
			
		case 2:
			dprintf(1, "erreur de join\n");
			break;
		case 3:
			dprintf(1, "erreur de mutex_lock\n");
			break;
		case 4:
			dprintf(1, "erreur de mutex_unlock\n");
			break;
	}
	exit(EXIT_FAILURE);
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

void			*algo(void *p)
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
	t_args	*a;

	a = p;
	x = a->start - 1;
	while (++x < a->end)
	{
		camx = 2 * x / (double)WID - 1;
		raydir.x = a->e->p.dir.x + a->e->p.plane.x * camx;
		raydir.y = a->e->p.dir.y + a->e->p.plane.y * camx;
		onmap.x = (int)a->e->p.pos.x;
		onmap.y = (int)a->e->p.pos.y;
		delta.x = fabs(1 / raydir.x);
		delta.y = fabs(1 / raydir.y);
		if (raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (a->e->p.pos.x - onmap.x) * delta.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (onmap.x + 1.0 - a->e->p.pos.x) * delta.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (a->e->p.pos.y - onmap.y) * delta.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (onmap.y + 1.0 - a->e->p.pos.y) * delta.y;
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
		dist = (!side) ? (onmap.x - a->e->p.pos.x + (1 - step.x) / 2) / raydir.x
			: (onmap.y - a->e->p.pos.y + (1 - step.y) / 2) / raydir.y;
		height = (int)((double)HEI / dist);
		if ((start = -height / 2 + HEI / 2) < 0)
			start = 0;
		if ((end = height / 2 + HEI / 2) >= HEI)
			end = HEI - 1;
		y = start - 1;
		if (pthread_mutex_lock(&a->m))
			error(a->e, 3);
		if (!side)
			while (++y < end)
				mlx_pixel_put(a->e->mlx, a->e->win, x, y, 0x0000ff);
		else
			while (++y < end)
				mlx_pixel_put(a->e->mlx, a->e->win, x, y, 0x000088);
		while (++y < HEI)
		{
			mlx_pixel_put(a->e->mlx, a->e->win, x, y, 0xa9a9a9);
			mlx_pixel_put(a->e->mlx, a->e->win, x, HEI - y - 1, 0xa9a9a9);
		}
		if (pthread_mutex_unlock(&a->m))
			error(a->e, 4);
	}
	return (NULL);
}

void	raycasting(t_env *e)
{
	pthread_t	left;
	pthread_t	midl;
	pthread_t	midr;
	pthread_t	right;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	t_args		a;

	a.e = e;
	a.m = m;
	a.start = 0;
	a.end = WID / 4;
	if (pthread_create(&left, NULL, algo, &a))
		error(e, 1);
	if (pthread_join(left, NULL))
		error(e, 2);
	a.start = WID / 4;
	a.end = WID / 2;
	if (pthread_create(&midl, NULL, algo, &a))
		error(e, 1);
	if (pthread_join(midl, NULL))
		error(e, 2);
	a.start = WID / 2;
	a.end = WID - (WID / 4);
	if (pthread_create(&midr, NULL, algo, &a))
		error(e, 1);
	if (pthread_join(midr, NULL))
		error(e, 2);
	a.start = WID - (WID / 4);
	a.end = WID;
	if (pthread_create(&right, NULL, algo, &a))
		error(e, 1);
	if (pthread_join(right, NULL))
		error(e, 2);
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
