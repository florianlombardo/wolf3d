/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_map.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 13:59:22 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:38:02 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		ft_maperror(t_env *e, t_errcodes err)
{
	int		i;

	if (err == E_MAP)
		ft_putendl("Invalid map format.");
	else if (err == E_MALLOC)
		ft_putendl("Malloc issue.");
	else if (err == E_NAME)
		ft_putendl("Incorrect file name.");
	if (e)
	{
		if (e->map)
		{
			i = -1;
			while (e->map[++i])
				if (e->map[i])
					free(e->map[i]);
		}
		free(e->map);
		free(e);
	}
	exit(EXIT_FAILURE);
}

static int	check_mur(int i, int j, t_env *e, int length)
{
	int		count;

	count = 0;
	if (j > 0)
		if (e->map[i][j - 1] == MUR)
			count++;
	if (j < length)
		if (e->map[i][j + 1] == MUR)
			count++;
	if (i < e->maxlengthy - 1)
		if (e->map[i + 1][j] == MUR)
			count++;
	if (i > 0)
		if (e->map[i - 1][j] == MUR)
			count++;
	if (count < 2)
		ft_maperror(e, E_MAP);
	return (0);
}

static void	check_error2(t_env *e, t_ipos *i, int length, int start)
{
	if (i->x == 0 || i->x == (e->maxlengthy - 1))
	{
		if (e->map[i->x][i->y] != MUR)
			ft_maperror(e, E_MAP);
		check_mur(i->x, i->y, e, length);
	}
	else
	{
		if (i->y == start || i->y == (length - 1))
		{
			check_mur(i->x, i->y, e, length);
			if (e->map[i->x][i->y] != MUR)
				ft_maperror(e, E_MAP);
		}
	}
	if (!(e->map[i->x][i->y] == SPAWN || e->map[i->x][i->y] == MUR ||
		e->map[i->x][i->y] == SOL))
		ft_maperror(e, E_MAP);
	i->y++;
}

void		check_error(t_env *e)
{
	t_ipos	i;
	int		length;
	int		p;
	int		start;

	i.x = -1;
	p = 0;
	while (e->map[++i.x])
	{
		start = 0;
		i.y = -1;
		while (e->map[i.x][++i.y] == ' ')
			start++;
		length = ft_strlen(e->map[i.x]);
		while (e->map[i.x][i.y])
		{
			if (e->map[i.x][i.y] == SPAWN)
				p++;
			if (p > 1)
				ft_maperror(e, E_MAP);
			check_error2(e, &i, length, start);
		}
	}
	if (p == 0)
		ft_maperror(e, E_MAP);
}
