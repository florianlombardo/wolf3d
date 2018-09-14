/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:55 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:56 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	unsigned int	i;

	if (!s)
		return (0);
	if (!(tab = ft_strnew(len)))
		return (0);
	i = 0;
	while (i < len)
		tab[i++] = s[start++];
	return (tab);
}
