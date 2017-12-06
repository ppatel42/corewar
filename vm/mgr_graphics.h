/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/11 19:32:48 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MGR_GRAPHICS_H

# define MGR_GRAPHICS_H
# include <mach-o/dyld.h>
# include "matrix.h"
# include "libft/libft.h"
# include "cutscene.h"
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>
# include <ncurses.h>
# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif
# define WHITE_PAIR 1
# define GREEN_PAIR 2
# define YELLOW_PAIR 3
# define RED_PAIR 4
# define MAGENTA_PAIR 5
# define CYAN_PAIR 6
# define WORLD_WIDTH 254
# define WORLD_HEIGHT 72
# define LOG_WIDTH 60
# define LOG_HEIGHT 70
# define APP_REFRESH_RATE 10
# define MAT_REFRESH_RATE 500
# define FRAMES_PER_SECOND 60
# define SKIP_TICKS 1000 / FRAMES_PER_SECOND
# define APP_KEY_ENTER 10
# define APP_KEY_UP 65
# define APP_KEY_DOWN 66
# define APP_KEY_LEFT 68
# define APP_KEY_RIGHT 67
# define APP_KEY_SPACE 32
# define APP_KEY_SPECIAL 91
# define APP_KEY_ESC 27
# define APP_KEY_INVALID -1
# define BOARD_WIDTH 64
# define BOARD_SPACING 1
# define BOARD_HEIGHT 64
# define ACTUAL_BOARD (BOARD_WIDTH * 2 + BOARD_WIDTH)
# define BOARD_CELL_LENGTH 2
# ifndef MAX_PLAYERS
#  define MAX_PLAYERS 4
# endif

typedef struct s_env	t_env;

typedef struct			s_graphics
{
	WINDOW				*game_window;
	WINDOW				*border_window;
	WINDOW				*log_window;
	WINDOW				*background_window;
	WINDOW				*video_window;
	WINDOW				*dialog_window;
	int					offsetx;
	int					offsety;
	int					max_y;
	int					max_x;
	int					margin_x;
	int					margin_y;
	bool				graphics_end;
	int					i;
	int					j;
	int					flag;
	t_matrix			*mat;
	struct s_column		*col;
	int					window_x;
	int					window_y;
	int					window_index;
	bool				app_is_running;
	bool				game_over;
	bool				player_match;
	bool				init_game_over_menu;
	bool				neo_wins;
	bool				restart;
	int					key_pressed;
	t_mgr_scene			mgr_cutscene;
	t_dword				start_time;
	t_dword				next_app_tick;
	t_dword				current;
	t_dword				elapsed;
	t_dword				seconds;
	t_dword				seconds2;
	t_dword				seconds3;
	t_dword				seconds4;
	t_dword				sleep_time;
	bool				player_id_init[MAX_PLAYERS];
	uint32_t			player_id[MAX_PLAYERS];
	chtype				player_colors[MAX_PLAYERS];
	char				hex[3];
	char				*buffer;
}						t_graphics;

void					ft_error_errno(char *msg);
int						load_check(void);
void					graphics_start(t_graphics *g);
void					graphics_end(t_graphics *g);
void					render_start(t_graphics *g);
void					render_end(t_graphics *g);
void					graphics_print_message(t_graphics *g, char *str);
bool					keyboard_event(void);
void					get_keyboard_event(t_graphics *g);
void					update_app(t_graphics *g, t_env *e);
void					display_app(t_graphics *g, t_env *e);
void					graphics_loop(t_env *e, t_env *backup);
t_dword					gettickcount(void);
void					render_board(t_graphics *g, t_env *e);
void					render_log(t_graphics *g, t_env *e);
void					render_player(t_graphics *g, uint32_t pn);
void					render_process(t_graphics *g, t_env *e);
void					render_stats(t_graphics *g, t_env *e);
t_graphics				*init_graphics(t_env *e);
void					init_player_colors(t_graphics *g, t_env *e);
void					game_over(t_graphics *g, t_env *e);

#endif
