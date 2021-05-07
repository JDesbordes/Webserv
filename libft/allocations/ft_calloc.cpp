/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:29:03 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:46:32 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allowed;
	size_t	i;

	i = size * nmemb;
	if (!(allowed = malloc(i)))
		return (NULL);
	ft_bzero(allowed, i);
	return (allowed);
}
