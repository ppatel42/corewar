/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:18:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"
#include <locale.h>

void		reset_player_lives(t_player *player)
{
	while (player)
	{
		player->lives = 0;
		player = player->next;
	}
}

void		perform_check(t_env *env)
{
	kill_processes(env);
	reset_player_lives(env->lst_players);
	if (env->lives_since_check >= NBR_LIVE || env->checks == MAX_CHECKS - 1)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env->options[v] && env->verbose_value == 2)
			P(env->g_ref, env->options[visual],
				"Cycle to die is now %d\n", env->cycle_to_die);
		env->checks = 0;
	}
	else
		env->checks++;
	env->cycles_since_check = 0;
	env->lives_since_check = 0;
}

void		run_game(t_env *env)
{
	while (1)
	{
		if (env->cycles_since_check >= env->cycle_to_die)
			perform_check(env);
		if (env->lst_process == NULL)
			break ;
		if (env->options[d] == 1 && env->dump_value == env->total_cycles)
		{
			dump_memory(env);
			break ;
		}
		execute_cycle(env);
		if (env->options[s] == 1 && (env->total_cycles % env->cycle_value) == 0)
			dump_memory(env);
		env->total_cycles++;
		env->cycles_since_check++;
		if (env->options[v] && env->verbose_value == 2)
			P(env->g_ref, env->options[visual],
				"It is now cycle %d\n", env->total_cycles);
	}
}

t_graphics	*init_graphics(t_env *e)
{
	t_graphics		*g;

	setlocale(LC_ALL, "");
	g = (t_graphics *)malloc(sizeof(t_graphics));
	if (!g)
		error_exit(e, 22);
	g->log_window = NULL;
	g->start_time = gettickcount();
	g->next_app_tick = g->start_time;
	g->sleep_time = 0;
	g->seconds = 0;
	g->seconds2 = 0;
	g->seconds3 = 0;
	g->seconds4 = 0;
	g->app_is_running = t_true;
	g->margin_x = 2;
	g->margin_y = 2;
	g->graphics_end = t_false;
	g->offsetx = (COLS - WORLD_WIDTH) / 2;
	g->offsety = (LINES - WORLD_HEIGHT) / 2;
	e->g_ref = g;
	return (g);
}
