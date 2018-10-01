/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:51 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:52 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	if (*needle == '\0')
		return ((char*)haystack);
	i = -1;
	j = 0;
	while (haystack[++i])
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && needle[j] && haystack[i + j])
				j++;
			if (needle[j] == '\0')
				return ((char*)haystack + i);
			else
			{
				j = 0;
				i = i + j;
			}
		}
	return (0);
}
