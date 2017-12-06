/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/11/13 17:13:32 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** t_op contains info about each of the ops.
**
** {name, num_params, cycles, has_type, label_size}
**
** name			(name of the op)
** num_params	(number of params)
** cycles		(how many cycles the op uses)
** has_type		(if the op has a type byte)
** label_size	(if the direct value is of size 2 or 4)
*/

t_op		*get_op_tab(void)
{
	t_op	*op_tab;

	if (!(op_tab = (t_op*)ft_memalloc(sizeof(t_op) * 18)))
		ft_error_errno(NULL);
	op_tab[1] = (t_op){"live", 1, 10, 0, 4};
	op_tab[2] = (t_op){"ld", 2, 5, 1, 4};
	op_tab[3] = (t_op){"st", 2, 5, 1, 4};
	op_tab[4] = (t_op){"add", 3, 10, 1, 4};
	op_tab[5] = (t_op){"sub", 3, 10, 1, 4};
	op_tab[6] = (t_op){"and", 3, 6, 1, 4};
	op_tab[7] = (t_op){"or", 3, 6, 1, 4};
	op_tab[8] = (t_op){"xor", 3, 6, 1, 4};
	op_tab[9] = (t_op){"zjmp", 1, 20, 0, 2};
	op_tab[10] = (t_op){"ldi", 3, 25, 1, 2};
	op_tab[11] = (t_op){"sti", 3, 25, 1, 2};
	op_tab[12] = (t_op){"fork", 1, 800, 0, 2};
	op_tab[13] = (t_op){"lld", 2, 10, 1, 4};
	op_tab[14] = (t_op){"lldi", 3, 50, 1, 2};
	op_tab[15] = (t_op){"lfork", 1, 1000, 0, 2};
	op_tab[16] = (t_op){"aff", 1, 2, 1, 4};
	return (op_tab);
}
