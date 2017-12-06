/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:27:07 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:18:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			get_no_type_val(t_env *env, t_process *process,
								uint8_t op, int pc)
{
	int val;

	if (op == e_fork || op == lfork)
		val = get_board_val(env->board, pc + 1, IND_SIZE);
	else if (op == live)
		val = get_board_val(env->board, pc + 1, 4);
	else
		val = get_board_val(env->board, pc + 1, IND_SIZE);
	process->param_val[0] = val;
}

void			get_params(t_env *env, t_process *process, int op)
{
	uint8_t		types;
	uint8_t		type;
	int			pc;
	int			i;
	int			param_size;

	types = process->types;
	pc = process->regs[0];
	if (!env->op_tab[op].has_type)
		return (get_no_type_val(env, process, op, pc));
	i = 0;
	param_size = 0;
	pc = pc + 2;
	while (i < 3)
	{
		type = (types & 0b11000000) >> 6;
		process->param_type[i] = type;
		param_size = get_param_size(type, env->op_tab[op].label_size);
		process->param_val[i] = get_board_val(env->board, pc, param_size);
		types = types << 2;
		pc += param_size;
		i++;
	}
}

int				get_ind_val(t_env *env, t_process *process, int16_t param_val)
{
	int		pc;
	int		val;

	pc = process->regs[0];
	if (process->op == lld)
		val = (int16_t)get_board_val(env->board, pc + param_val, 2);
	else
		val = get_board_val(env->board, pc + (param_val % IDX_MOD), 4);
	return (val);
}

int				get_param_val(t_env *env, t_process *process, int which_param)
{
	int		val;
	uint8_t	param_type;
	int		param_val;

	param_val = process->param_val[which_param];
	param_type = process->param_type[which_param];
	if (param_type == REG_CODE)
		val = get_reg_val(process, param_val);
	else if (param_type == IND_CODE)
		val = get_ind_val(env, process, (int16_t)param_val);
	else
		val = (env->op_tab[process->op].label_size == 4)
										? param_val : (int16_t)param_val;
	return (val);
}

int				check_param_reg_nums(t_process *process)
{
	return ((process->param_type[0] == REG_CODE
			&& is_reg_num_invalid(process->param_val[0]))
		|| (process->param_type[1] == REG_CODE
			&& is_reg_num_invalid(process->param_val[1]))
		|| (process->param_type[2] == REG_CODE
			&& is_reg_num_invalid(process->param_val[2])));
}
