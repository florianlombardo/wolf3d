/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:16:38 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:16:39 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char*)haystack);
	i = -1;
	j = 0;
	while (haystack[++i] && i < len)
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && needle[j]
					&& haystack[i + j] && ((i + j) < len))
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
