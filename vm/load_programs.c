/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_programs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:18:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 17:18:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		write_program_to_board(t_env *env, t_player *player,
										int offset, int fd)
{
	uint8_t		c;
	int			read_return;
	uint32_t	champ_size;

	c = 0;
	champ_size = 0;
	while (0 < (read_return = read(fd, &c, 1)))
	{
		env->board[offset % MEM_SIZE] = c;
		env->prog_num_board[offset % MEM_SIZE] = player->prog_num;
		offset++;
		champ_size++;
	}
	if (read_return == -1)
		ft_error_errno(NULL);
	if (champ_size != player->size)
		ft_error("The player's size is different from"
					" the size defined in the header");
}

uint32_t	rev_endian(uint32_t num)
{
	return (((num << 24))
			| ((num << 8) & 0x00ff0000)
			| ((num >> 8) & 0x0000ff00)
			| ((num >> 24)));
}

int			check_magic(t_env *env, int fd)
{
	uint32_t	magic;

	magic = 0;
	if (-1 == read(fd, &magic, sizeof(4)))
		ft_error_errno(NULL);
	if (rev_endian(magic) != COREWAR_EXEC_MAGIC)
		error_exit(env, 4);
	return (fd);
}

void		reader(t_env *env, t_player *player, char *arg)
{
	int			fd;
	uint32_t	magic;
	int			read_return;

	if (-1 == (fd = open(arg, O_RDONLY)))
		ft_error_errno(NULL);
	fd = check_magic(env, fd);
	if (-1 == read(fd, player->name, PROG_NAME_LENGTH))
		ft_error_errno(NULL);
	if (-1 == lseek(fd, 4, SEEK_CUR))
		ft_error_errno(NULL);
	if (-1 == read(fd, &player->size, sizeof(player->size)))
		ft_error_errno(NULL);
	if ((player->size = rev_endian(player->size)) > CHAMP_MAX_SIZE)
		ft_error("Champ is too large");
	if (-1 == read(fd, player->comment, COMMENT_LENGTH))
		ft_error_errno(NULL);
	if (-1 == (read_return = read(fd, &magic, 4)))
		ft_error_errno(NULL);
	if (read_return < 4)
		ft_error("File is too small to be a champion");
	write_program_to_board(env, player, env->offset, fd);
	if (-1 == close(fd))
		ft_error_errno(NULL);
}
