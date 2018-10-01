/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errorMap.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <stpuget@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 13:59:22 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 12:04:56 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int         check_mur(int i, int j, t_env e, int length)
{
    int     count;

    count = 0;
    if (j > 0)
        if (e.map[i][j - 1] == MUR)
            count++;
    if (j < length) 
        if (e.map[i][j + 1] == MUR)
            count++;
    if (i < e.maxLengthY - 1)
        if (e.map[i + 1][j] == MUR)
            count++;
    if (i > 0)
        if (e.map[i - 1][j] == MUR)
            count++;
    if (count < 2)
        error_map();
    return (0);
}

void        check_error(t_env e)
{
    int     i;
    int     j;
    int     length;
    int     p;
    int     start;
    
    
    i = 0;
	while(e.map[i])
        dprintf(1, "%s\n", e.map[i++]);
    i = -1;
    p = 0;
    while (e.map[++i])
    {
        start = 0;
        j = 0;
        while (e.map[i][j] == ' ')
        {
            start++;
            j++;
        }
        length = ft_strlen(e.map[i]);
        while (e.map[i][j])
        {
            if (e.map[i][j] == SPAWN)
                p++;
            if (p > 1)
                error_map();
            if (i == 0 || i == (e.maxLengthY - 1))
            {
                if (e.map[i][j] != MUR)
                    error_map();
                check_mur(i, j, e, length);
            }
            else
                if (j == start || j == (length - 1))
                {
                    check_mur(i, j, e, length);
                    if (e.map[i][j] != MUR)
                        error_map();
                }
            if (!(e.map[i][j] == SPAWN || e.map[i][j] == MUR || e.map[i][j] == SOL))
                error_map();
            j++;
        }
    }
    if (p == 0)
        error_map();
}