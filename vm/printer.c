/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:49:15 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:18:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			introduce_players(t_env *env)
{
	t_player	*player;

	P(env->g_ref, env->options[visual], "Introducing contestants...\n");
	player = env->lst_players;
	while (player)
	{
		P(env->g_ref, env->options[visual],
			"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
								player->prog_num * -1, player->size,
								player->name, player->comment);
		player = player->next;
	}
}

void			declare_winner(t_env *env)
{
	t_player *player;

	if (env->options[d] && env->lst_process != NULL)
		return ;
	if (!env->last_live_name)
	{
		player = env->lst_players;
		while (player->next)
			player = player->next;
		P(env->g_ref, env->options[visual],
		"Contestant %d, \"%s\", has won !\n",
		player->prog_num * -1, player->name);
		env->last_live_num = player->prog_num;
		env->last_live_name = player->name;
		return ;
	}
	P(env->g_ref, env->options[visual],
	"Contestant %d, \"%s\", has won !\n",
	env->last_live_num * -1,
	env->last_live_name);
}
