/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:10 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 15:59:10 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int n)
{
	int		i;

	i = 0;
	while (i * i < n && i < 46341)
		i++;
	return (i * i == n ? i : i - 1);
}
