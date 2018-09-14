/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:15:26 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:15:28 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*nv;
	int		i;

	i = 0;
	if (!(nv = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	while (s[i])
	{
		nv[i] = s[i];
		i++;
	}
	nv[i] = '\0';
	return (nv);
}
