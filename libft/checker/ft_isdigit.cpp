/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:26:09 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:47:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

t_boolean	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
