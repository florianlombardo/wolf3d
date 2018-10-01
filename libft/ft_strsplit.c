/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:47 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:48 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	base;

	if (!s || !c)
		return (0);
	if (!(tab = (char **)malloc(sizeof(*tab) * (ft_sizetab(s, c)) + 1)))
		return (0);
	i = 0;
	base = 0;
	while (i < ft_sizetab(s, c))
	{
		while (s[base] == c && s[base])
			base++;
		tab[i] = ft_strsub(s, base, ft_sizeword(s, c, base));
		base = base + ft_sizeword(s, c, base);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
