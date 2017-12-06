/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 12:07:19 by douglas           #+#    #+#             */
/*   Updated: 2017/07/06 16:47:51 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		SAFE_DELETE(split[i++]);
	SAFE_DELETE(split);
}
