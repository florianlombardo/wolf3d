/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 11:14:18 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 06:15:50 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char        **map_create(char *name, int length)
{
    int     i;
    int     fd;
    int     ret;
    char    *file;
    char    **map;
    
    i = 0;
    if ((fd = open(name, O_RDONLY)) < 0)
        error_name();
    if (!(map = (char **)ft_memalloc(sizeof(char *) * (length + 1))))
		error_malloc();
    map[length] = 0;
    while ((ret = get_next_line(fd, &file)) > 0)
    {
        if (!(map[i] = (char *)ft_memalloc(sizeof(char) * (ft_strlen(file)+ 1))))
		    error_malloc();
        map[i] = ft_strcpy(map[i], file);
        if (file)
            free(file);
        i++;
    }
    if (ret < 0)
        error_name();
    if (close(fd) < 0)
        error_name();
    return (map);
}

static int    length(char **map)
{
    int i;
    int j;
    int tmp;

    tmp = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            j++;
        }
        if (j > tmp)
            tmp = j;
        i++;
    }
    return (tmp);
}

void         map_init(char *name, t_env *e)
{
    char    *file;
    int     ret;
    int     fd;
    
    e->maxLengthY = 0;
    if ((fd = open(name, O_RDONLY)) < 0)
        error_name();
    while ((ret = get_next_line(fd, &file)) > 0)
    {
        e->maxLengthY++;
        if (file)
            free(file);
    }
    if (ret < 0)
        error_name();
    if (close(fd) < 0)
        error_name();
    e->map = map_create(name, e->maxLengthY);
    e->maxLengthX = length(e->map);
}