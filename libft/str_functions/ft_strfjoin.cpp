/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 02:08:26 by gbaud             #+#    #+#             */
/*   Updated: 2021/03/08 14:02:48 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

char	*ft_strfjoin(const char *s1, const char *s2, int j)
{
	char	*r;
	char	*res;
	char	*sa;
	char	*sb;

	sa = (char *)s1;
	sb = (char *)s2;
	if (!(r = (char *)ft_calloc(ft_strlen(sa) + ft_strlen(sb) + 1, sizeof(char))))
		return (NULL);
	res = r;
	while (*sa != '\0')
		*res++ = *sa++;
	while (*sb != '\0')
		*res++ = *sb++;
	*res = '\0';
	if (j >= 1)
		free(const_cast<char*>(s1));
	if (j > 1)
		free(const_cast<char*>(s2));
	return (r);
}
