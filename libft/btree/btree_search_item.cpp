/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 08:53:25 by gbaud             #+#    #+#             */
/*   Updated: 2021/02/08 09:46:34 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.hpp"

void	*btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	if (!root || !data_ref)
		return (0);
	if (cmpf(data_ref, root->item) == 0)
		return (root->item);
	if (root->left)
		return (btree_search_item(root->left, data_ref, cmpf));
	if (root->right)
		return (btree_search_item(root->right, data_ref, cmpf));
	return (0);
}
