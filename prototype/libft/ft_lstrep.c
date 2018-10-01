/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstrep.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:12:56 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:12:57 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrep(t_list *lst)
{
	t_list *new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	if (new)
	{
		if (!(new->content = malloc(sizeof(lst->content_size))))
			return (0);
		new->content = lst->content;
		new->content_size = lst->content_size;
		new->next = NULL;
	}
	else
		return (0);
	return (new);
}
