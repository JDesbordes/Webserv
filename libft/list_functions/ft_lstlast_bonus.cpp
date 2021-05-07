/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:09:26 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:08 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		return (ft_lstlast(lst->next) ? ft_lstlast(lst->next) : lst);
	return (0);
}
