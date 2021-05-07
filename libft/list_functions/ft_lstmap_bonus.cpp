/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 02:22:42 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 10:06:11 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*n;
	t_list		*list;

	if (!lst)
		return (NULL);
	if (!(list = ft_lstnew(f(lst->content))))
		return (NULL);
	n = list;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&n, del);
			return (NULL);
		}
		list = list->next;
	}
	return (n);
}
