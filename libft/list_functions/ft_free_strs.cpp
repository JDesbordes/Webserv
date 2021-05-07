/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:24:13 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

int	ft_free_strs(int count, ...)
{
	va_list list;

	va_start(list, count);
	while (count--)
		free(va_arg(list, char *));
	return (1);
}
