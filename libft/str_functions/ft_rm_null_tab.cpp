/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_null_tab.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 07:50:30 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 10:08:01 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

int		count_legit(char **tab)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (tab[++i])
		if (ft_strcmp(tab[i], const_cast<char *>(std::string("").c_str())))
			res++;
	return (res);
}

char	**ft_rm_null_tab(char **tab, t_boolean f)
{
	char	**res;
	int		i;
	int		j;

	if (!(res = (char **)ft_calloc(count_legit(tab) + 1, sizeof(char *))))
		return (NULL);
	i = -1;
	j = -1;
	while (tab[++i])
		if (ft_strcmp(tab[i], const_cast<char *>(std::string("").c_str())))
			res[++j] = ft_strdup(tab[i]);
	if (f == TRUE)
		ft_free_strs_tab(tab);
	return (res);
}
