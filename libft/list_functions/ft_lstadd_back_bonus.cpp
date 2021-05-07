/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:16:40 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 10:05:48 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	ft_lstadd_back(t_list **alst, t_list *n)
{
	t_list	*tmp;

	if (*alst == NULL)
		*alst = n;
	else
	{
		tmp = *alst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		n->prev = tmp;
		tmp->next = n;
	}
}
