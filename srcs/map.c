/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 11:14:18 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 22:56:22 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	map_create(char *name, int length, t_env *e)
{
	int		i;
	int		fd;
	int		ret;
	char	*file;

	i = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		ft_maperror(e, E_NAME);
	if (!(e->map = (char **)ft_memalloc(sizeof(char *) * (length + 1))))
		ft_maperror(e, E_MALLOC);
	e->map[length] = 0;
	while ((ret = get_next_line(fd, &file)) > 0)
	{
		if (!(e->map[i] = (char *)ft_memalloc(sizeof(char) *
			(ft_strlen(file) + 1))))
			ft_maperror(e, E_MALLOC);
		ft_strcpy(e->map[i], file);
		if (file)
			free(file);
		i++;
	}
	if (close(fd) < 0 || ret < 0)
		ft_maperror(e, E_NAME);
}

static int	length(char **map)
{
	int		i;
	int		j;
	int		tmp;

	tmp = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > tmp)
			tmp = j;
		i++;
	}
	return (tmp);
}

void		map_init(char *name, t_env *e)
{
	char	*file;
	int		ret;
	int		fd;

	e->maxlengthy = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		ft_maperror(e, E_NAME);
	while ((ret = get_next_line(fd, &file)) > 0)
	{
		e->maxlengthy++;
		if (file)
			free(file);
	}
	if (ret < 0)
		ft_maperror(e, E_NAME);
	if (close(fd) < 0)
		ft_maperror(e, E_NAME);
	map_create(name, e->maxlengthy, e);
	e->maxlengthx = length(e->map);
}
