/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:08:14 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:46:33 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned const char		*s;
	unsigned char			*d;
	size_t					i;

	i = 0;
	s = (unsigned const char*)src;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == (unsigned char)c)
			return (d + i + 1);
		i++;
	}
	return (0);
}
