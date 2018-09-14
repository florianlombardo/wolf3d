/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:13:02 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:13:03 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t n)
{
	void	*mem;

	if (!(mem = malloc(sizeof(*mem) * n)))
		return (0);
	ft_memset(mem, 0, n);
	return (mem);
}
