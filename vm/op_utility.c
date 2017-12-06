/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:12:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:06:20 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		inc_pc(t_process *process, int inc)
{
	process->regs[0] = get_board_pos(process->regs[0] + inc);
}

void		modify_carry(t_process *process, int val)
{
	process->carry = !val;
}

int			get_board_pos(int val)
{
	return ((0 > (val %= MEM_SIZE)) ? val + MEM_SIZE : val);
}
