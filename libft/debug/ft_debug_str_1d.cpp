/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_str_1d.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 04:34:28 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	ft_debug_str_1d(char **arr)
{
	int i;

	i = -1;
	if (arr)
	{
		ft_printf("[ ");
		while (arr[++i])
		{
			ft_printf("\"%s\"", arr[i]);
			if (arr[i + 1])
				ft_printf(", ");
		}
		ft_printf(" ]\n");
	}
	else
		ft_printf("(arr) is NULL");
}
