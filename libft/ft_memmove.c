/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:13:33 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:13:43 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src <= dest)
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}
