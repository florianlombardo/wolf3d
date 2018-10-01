/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:10 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:10 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tab;
	size_t	i;

	if (!s || !f)
		return (0);
	if (!(tab = ft_strnew(ft_strlen(s))))
		return (0);
	i = 0;
	while (*s)
	{
		tab[i] = (*f)(i, *s++);
		i++;
	}
	return (tab);
}
