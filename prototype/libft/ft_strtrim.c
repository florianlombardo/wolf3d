/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:58 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:59 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*tab;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	len = ft_sizeblanc(s);
	if (!(tab = (char *)ft_memalloc(len + 1)))
		return (0);
	i = 0;
	while (*s && (*s == '\t' || *s == '\n' || *s == ' '))
		s++;
	while (*s && i < len)
		tab[i++] = *s++;
	tab[i] = '\0';
	return (tab);
}
