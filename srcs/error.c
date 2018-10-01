/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <stpuget@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 15:48:22 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 16:02:10 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void        error_name()
{
    ft_putstr("Incorrect file name.\n");
    exit(EXIT_FAILURE);
}

void        error_malloc()
{
    ft_putstr("Malloc issue.\n");
    exit(EXIT_FAILURE);
}

void        error_map()
{
    ft_putstr("Error map.\n");
    exit(EXIT_FAILURE);
}

void		error_usage(int ac)
{
	if (ac != 2)
	{
		ft_putstr("usage : ./wolf3d [nom du fichier]\n");
		exit(EXIT_FAILURE);
	}
}