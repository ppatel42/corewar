/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/14 15:05:51 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

void		graphics_loop_start(t_graphics *g, t_env *e)
{
	g->current = gettickcount();
	g->elapsed = g->current - g->start_time;
	g->seconds += g->elapsed;
	g->seconds2 += g->elapsed;
	if (g->mgr_cutscene.is_scene_playing ||
		(g->game_over && g->init_game_over_menu))
		g->seconds3 += g->elapsed;
	if (g->mgr_cutscene.is_dialog_playing)
		g->seconds4 += g->elapsed;
	if (g->seconds <= APP_REFRESH_RATE)
		return ;
	g->seconds = 0;
	if (!g->mgr_cutscene.is_scene_playing)
		if (!g->mgr_cutscene.is_dialog_playing)
			if (!g->game_over)
				update_app(g, e);
}

void		graphics_loop_end(t_graphics *g)
{
	g->next_app_tick += SKIP_TICKS;
	g->sleep_time = (g->next_app_tick - gettickcount());
	if (g->sleep_time >= 0)
		usleep((useconds_t)g->sleep_time);
	g->start_time = g->current;
}

void		game_intro(t_env *e, t_graphics *g, int delay)
{
	clear();
	if (ENABLE_SOUND)
		snd_delete_playing_audio(&g->mgr_cutscene);
	g->game_over = false;
	g->init_game_over_menu = false;
	g->restart = false;
	g->mgr_cutscene.is_scene_playing = false;
	g->mgr_cutscene.is_dialog_playing = false;
	introduce_players(e);
	if (!g->game_over)
		play_dialog(g, g->mgr_cutscene.dialog_intro, delay);
}

void		game_loop(t_graphics *g, t_env *e, t_env *backup)
{
	while (g->app_is_running)
	{
		get_keyboard_event(g);
		if (!g->app_is_running)
			break ;
		graphics_loop_start(g, e);
		display_app(g, e);
		graphics_loop_end(g);
		game_over(g, e);
		if (!g->restart)
			continue ;
		cpy_env(e, backup);
		game_intro(e, g, -1000);
	}
}

void		graphics_loop(t_env *e, t_env *backup)
{
	t_graphics		*g;

	g = init_graphics(e);
	graphics_start(g);
	if ((g->offsetx <= 3) || (g->offsety <= 3))
	{
		graphics_end(g);
		ft_putendl_fd("Screen not large enough. Please enlarge screen.\n", 2);
		return ;
	}
	init_player_colors(g, e);
	init_cutscenes(&g->mgr_cutscene);
	game_intro(e, g, -2200);
	game_loop(g, e, backup);
	destroy_cutscenes(&g->mgr_cutscene);
	graphics_end(g);
}
