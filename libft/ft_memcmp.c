/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:13:19 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:13:20 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *sp1;
	unsigned char *sp2;

	sp1 = (unsigned char*)s1;
	sp2 = (unsigned char*)s2;
	while (n-- != 0)
	{
		if (*sp1 != *sp2)
			return (*sp1 - *sp2);
		sp1++;
		sp2++;
	}
	return (0);
}
