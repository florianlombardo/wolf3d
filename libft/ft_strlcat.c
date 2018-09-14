/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:15:51 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:15:52 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dest);
	if (size <= len)
		return (size + ft_strlen(src));
	else
	{
		ft_strncat(dest, src, size - len - 1);
		return (len + ft_strlen(src));
	}
}
