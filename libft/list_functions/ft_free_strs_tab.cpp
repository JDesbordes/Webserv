/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs_tab.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:31:10 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

#include <stdio.h>

int	ft_free_strs_tab(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
		free(tab[len++]);
	free(tab[len]);
	free(tab);
	return (1);
}
