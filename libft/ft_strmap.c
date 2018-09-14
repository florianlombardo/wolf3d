/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:03 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:06 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tab;
	size_t	i;

	if (!s || !f)
		return (0);
	if (!(tab = malloc(sizeof(*tab) * (ft_strlen(s) + 1))))
		return (0);
	tab[ft_strlen(s)] = '\0';
	i = 0;
	while (*s)
		tab[i++] = (*f)(*s++);
	return (tab);
}
