/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:12:43 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:12:43 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*prm;

	if (!lst || !f)
		return (0);
	if (!(new = ft_lstrep(f(lst))))
		return (0);
	lst = lst->next;
	prm = new;
	while (lst)
	{
		if (!(new->next = ft_lstrep(f(lst))))
			return (0);
		lst = lst->next;
		new = new->next;
	}
	return (prm);
}
