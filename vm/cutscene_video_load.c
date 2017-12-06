/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_video_load.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:35:08 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/11 19:28:16 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void					break_video(t_cutscene *s)
{
	SAFE_DELETE(s->line);
	s->prev = s->current;
	s->index = 0;
	s->current = s->current->next;
}

void					new_frame(t_cutscene *s)
{
	s->index = 0;
	if (!(s->current = (t_scene_frame *)malloc(sizeof(t_scene_frame))))
		ft_error_errno("malloc fail");
	if (!(s->current->frame = (char**)malloc(sizeof(char*) * CUTSCENE_HEIGHT)))
		ft_error_errno("malloc fail");
	ft_memset(s->current->frame, 0, sizeof(char *) * CUTSCENE_HEIGHT);
	s->current->next = NULL;
	if (s->prev)
		s->prev->next = s->current;
}

void					load_cutscene_video(t_cutscene *s)
{
	s->pfd = open(s->full_path, O_RDONLY);
	s->current = s->animation;
	s->prev = NULL;
	while ((s->status = get_next_line(s->pfd, &s->line)))
	{
		if (!ft_strcmp("<br>", s->line))
		{
			break_video(s);
			continue ;
		}
		if (!s->current)
			new_frame(s);
		if (s->index < CUTSCENE_HEIGHT)
			s->current->frame[s->index] = s->line;
		else
			SAFE_DELETE(s->line);
		s->index++;
		if (!s->animation)
			s->animation = s->current;
	}
	SAFE_DELETE(s->line);
	close(s->pfd);
}
