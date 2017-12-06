/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/13 18:46:23 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

void		print_instructions(void)
{
	ft_printf("Usage: ./corewar [-dump N -s N -v N "
		"| --visual] [-a] <[-n N] champion1.cor> <...>\n");
	ft_printf("\tExample              : ./corewar --visual filename.cor\n");
	ft_printf("\t-a     : Prints output from \"aff\"\n");
	ft_printf("\t-n N   : set champion number\n");
	ft_printf("#### TEXT OUTPUT MODE #######################################"
		"###################\n");
	ft_printf("\t-dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("\t-s N   : Runs N cycles, dumps memory, then repeats\n");
	ft_printf("\t-v N   : Verbosity levels, can be added together to enable "
		"several\n");
	ft_printf("\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t- 1 : Show lives\n");
	ft_printf("\t\t- 2 : Show cycles\n");
	ft_printf("\t\t- 4 : Show operations (Params are NOT literal ...)\n");
	ft_printf("\t\t- 8 : Show deaths\n");
	ft_printf("\t\t- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("#### NCURSES OUTPUT MODE #######################################"
		"################\n");
	ft_printf("\t--visual  : Visual output mode\n");
	ft_printf("################################################################"
		"################\n");
}

void		error_msg_2(int i)
{
	if (i == 11)
		ft_putstr_fd("\x1b[31m[Too few args for dump/s/v flag]\x1b[0m ", 2);
	else if (i == 12)
		ft_putstr_fd("\x1b[31m[arg value is larger than int max]\x1b[0m ", 2);
	else if (i == 13)
		ft_putstr_fd("\x1b[31m[Invalid argument for -v flag]\x1b[0m ", 2);
	else if (i == 14)
		ft_putstr_fd("\x1b[31m[Non numerical chars in numb input]\x1b[0m ", 2);
	else if (i == 15)
		ft_putstr_fd("\x1b[31m[Wrong int value for dump/s/v flag.]\x1b[0m ", 2);
	else if (i == 16)
		ft_putstr_fd("\x1b[31m[Wrong file type. Usage: .cor]\x1b[0m ", 2);
	else if (i == 17)
		ft_putstr_fd("\x1b[31m[The file size is too large.]\x1b[0m ", 2);
	else if (i == 18)
		ft_putstr_fd(
			"\x1b[31m[Too few arguments for --visual flag]\x1b[0m ", 2);
	else if (i == 19)
		ft_putstr_fd("\x1b[31m[Wrong int value for -dump flag]\x1b[0m ", 2);
	else if (i == 20)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m ", 2);
	else if (i == 21)
		ft_putstr_fd("\x1b[31m[Unknown Argument]\x1b[0m ", 2);
	ft_putstr_fd("\n", 2);
}

void		error_msg(int i)
{
	if (i == 1)
		ft_putstr_fd("\x1b[31m[Failed to open]\x1b[0m ", 2);
	else if (i == 2)
		ft_putstr_fd("\x1b[31m[Failed to read file]\x1b[0m ", 2);
	else if (i == 3)
		ft_putstr_fd("\x1b[31m[Failed to close file]\x1b[0m ", 2);
	else if (i == 4)
		ft_putstr_fd("\x1b[31m[Wrong Corewar Exec Magic]\x1b[0m ", 2);
	else if (i == 5)
		ft_putstr_fd("\x1b[31m[Incorrect Name Chars]\x1b[0m ", 2);
	else if (i == 6)
		ft_putstr_fd("\x1b[31m[Player size too big]\x1b[0m ", 2);
	else if (i == 7)
		ft_putstr_fd("\x1b[31m[Wrong int value]\x1b[0m ", 2);
	else if (i == 8)
		ft_putstr_fd("\x1b[31m[Too many players]\x1b[0m ", 2);
	else if (i == 9)
		ft_putstr_fd("\x1b[31m[Duplicate player number]\x1b[0m ", 2);
	else if (i == 10)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m ", 2);
	else
		ft_putstr_fd("\x1b[31m[ERROR]\x1b[0m ", 2);
	ft_putstr_fd("\n", 2);
}

void		error_exit(t_env *e, int i)
{
	if (i > 0 && i < 11)
		error_msg(i);
	else if (i >= 11 && i <= 21)
		error_msg_2(i);
	else if (i == 22)
		ft_putstr_fd("\x1b[31m[Unable to init graphics]\x1b[0m ", 2);
	else
	{
		ft_putstr_fd("\x1b[31m[Unknown Error Message: ]\x1b[0m ", 2);
		ft_printf("Code %i\n", i);
	}
	delete_env(e);
	exit(1);
}

int			load_check(void)
{
	int		error;

	error = 0;
	error += access(SOUND_BACKGROUND + 1, R_OK);
	error += access(SOUND_BULLET_TIME + 1, R_OK);
	error += access(SOUND_THE_ONE + 1, R_OK);
	error += access(SOUND_GAMEOVER + 1, R_OK);
	error += access(VIDEO_NEO_WINS + 1, R_OK);
	error += access(VIDEO_NEO_LOSE + 1, R_OK);
	error += access(SOUND_BEEP + 1, R_OK);
	error += access(VIDEO_BULLET_TIME + 1, R_OK);
	error += access(VIDEO_THE_ONE + 1, R_OK);
	error += access(VIDEO_PILL + 1, R_OK);
	error += access(DIALOG_INTRO_VID + 1, R_OK);
	error += access(DIALOG_INTRO_SUB + 1, R_OK);
	error += access(DIALOG_INTRO_SND + 1, R_OK);
	error != 0 ? ft_putendl_fd("ERROR: missing files", 2) : 0;
	return (error);
}
