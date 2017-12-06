/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:13:26 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:03:45 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s r%d r%d r%d\n",
								process->process_num,
								env->op_tab[process->op].name,
								process->param_val[0],
								process->param_val[1],
								process->param_val[2]);
}

/*
** Takes three registers and adds or subs the two first registers values,
** and then stores it in the third registry.
** P3 = P1 + P2
** PARAM TYPES: T_REG, T_REG, T_REG
*/

void		op_arithmetic(t_env *env, t_process *process)
{
	int	reg_val1;
	int	reg_val2;
	int	result;

	if (process->param_type[0] != REG_CODE
		|| process->param_type[1] != REG_CODE
		|| process->param_type[2] != REG_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	reg_val1 = get_reg_val(process, process->param_val[0]);
	reg_val2 = get_reg_val(process, process->param_val[1]);
	if (process->op == add)
		result = reg_val1 + reg_val2;
	else
		result = reg_val1 - reg_val2;
	set_reg_val(process, process->param_val[2], result);
	modify_carry(process, result);
	print_verbosity_four(env, process);
}
