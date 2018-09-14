/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: stpuget <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 14:12:49 by stpuget      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 14:12:50 by stpuget     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	const *content, size_t content_size)
{
	t_list	*add;

	if (!(add = malloc(sizeof(t_list))))
		return (0);
	if (content == NULL)
	{
		add->content = NULL;
		add->content_size = 0;
	}
	else
	{
		add->content = ft_memalloc(content_size);
		ft_memcpy((add->content), content, content_size);
		add->content_size = content_size;
	}
	add->next = NULL;
	return (add);
}
