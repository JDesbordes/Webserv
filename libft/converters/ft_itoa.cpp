/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:55:34 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/19 16:40:55 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

char	*ft_itoa(int n1)
{
	char	*r;
	long	cpy;
	long	n;
	int		len;
	int		b;

	n = (long)n1;
	cpy = (long)n1;
	b = ((n < 0) && (n *= -1)) ? 1 : 0;
	len = b + 1;
	while (n > 9 && ++len)
		n /= 10;
	if (!(r = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (b && (cpy *= -1))
		r[0] = '-';
	r[len] = '\0';
	while (cpy > 9)
	{
		r[len - 1] = cpy % 10 + '0';
		cpy /= 10;
		len--;
	}
	r[b++] = cpy + '0';
	return (r);
}
