/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_str_2d.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 04:38:42 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	ft_debug_str_2d(char ***arr)
{
	int i;
	int j;

	i = -1;
	ft_printf("[\n");
	while (arr[++i])
	{
		ft_printf("\t[ ");
		j = -1;
		while (arr[i][++j])
		{
			ft_printf("\"%s\"", arr[i][j]);
			if (arr[i][j + 1])
				ft_printf(", ");
		}
		ft_printf(" ]\n");
	}
	ft_printf("]\n");
}
