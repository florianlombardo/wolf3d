/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sizetab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:14:47 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:14:48 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sizetab(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			while (*s != c && *s)
				s++;
			i++;
		}
	}
	return (i);
}