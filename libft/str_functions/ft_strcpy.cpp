/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:54:15 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:08 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*r;

	r = dest;
	while (*src != 0)
		*dest++ = *src++;
	*dest++ = 0;
	return (r);
}
