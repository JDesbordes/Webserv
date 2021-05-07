/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:42:17 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 10:06:56 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	char			*t;
	unsigned int	i;

	i = 0;
	t = (char *)s;
	if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(t) + 1))))
		return (NULL);
	while (t[i] != '\0')
	{
		r[i] = f(i, t[i]);
		i++;
	}
	r[i] = '\0';
	return (r);
}
