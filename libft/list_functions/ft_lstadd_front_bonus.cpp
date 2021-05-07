/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:42:04 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 10:05:36 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	ft_lstadd_front(t_list **alst, t_list *n)
{
	if (n != NULL)
	{
		(*alst)->prev = n;
		n->next = *alst;
		*alst = n;
	}
}
