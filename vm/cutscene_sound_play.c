/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_sound_play.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:39:51 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/09 20:39:52 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void						frame_audio(t_audio *s)
{
	while (s->framesleft > 0)
	{
		sf_seek(s->pb->af->data, s->pb->pos, SEEK_SET);
		if (s->framesleft > (s->pb->af->info.frames - s->pb->pos))
		{
			s->framesread = (t_unint32)(s->pb->af->info.frames - s->pb->pos);
			if (s->pb->loop)
				s->pb->pos = 0;
			else
			{
				s->playbackended = true;
				s->framesleft = s->framesread;
			}
		}
		else
		{
			s->framesread = s->framesleft;
			s->pb->pos += s->framesread;
		}
		sf_readf_int(s->pb->af->data, s->buffercursor, s->framesread);
		s->buffercursor += s->framesread;
		s->framesleft -= s->framesread;
	}
}

void						cursor_audio(t_audio *s, t_mgr_scene *g)
{
	s->i = -1;
	while (++s->i < g->stereoframecount)
	{
		if (s->pb->af->info.channels == 1)
		{
			*s->outputcursor += (0.5 * s->outputbuffer[s->i]);
			++s->outputcursor;
			*s->outputcursor += (0.5 * s->outputbuffer[s->i]);
			++s->outputcursor;
			continue ;
		}
		*s->outputcursor += (0.5 * s->outputbuffer[s->i]);
		++s->outputcursor;
	}
}

t_audio						*ended_audio(t_audio *s, t_mgr_scene *g)
{
	t_audio			*new_s;

	UNUSED(g);
	SAFE_DELETE(s->outputbuffer);
	new_s = s->next;
	if (s->playbackended)
	{
		if (s->prev)
			s->prev->next = s->next;
		if (s->next)
			s->next->prev = s->prev;
		if (s == g->sounds)
			g->sounds = g->sounds->next;
		SAFE_DELETE(s->pb);
		SAFE_DELETE(s);
	}
	return (new_s);
}

/*
** Portaudio callback function. It takes 6 parameters, hence
** breaking the norminette, but it is necessary in order to use the library.
**
** http://portaudio.com/docs/v19-doxydocs/
** portaudio_8h.html#a8a60fb2a5ec9cbade3f54a9c978e2710
**
** typedef int PaStreamCallback(const void *input, void *output,
** unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
** PaStreamCallbackFlags statusFlags, void *userData)
*/

int							portaudiocallback(const void *input,
							void *output,
							unsigned long framecount,
							const PaStreamCallbackTimeInfo *patimeinfo,
							PaStreamCallbackFlags statusflags,
							void *userdata)
{
	UNUSED(input);
	UNUSED(statusflags);
	UNUSED(patimeinfo);
	G->s = G->sounds;
	if (!G->s)
		return (paContinue);
	G->stereoframecount = framecount * CHANNEL_COUNT;
	ft_memset((int *)output, 0, G->stereoframecount * sizeof(int));
	while (G->s)
	{
		G->s->playbackended = false;
		if (!(G->s->outputbuffer = (int *)malloc(sizeof(int)
			* G->stereoframecount)))
			ft_error_errno("malloc failed");
		G->s->buffercursor = G->s->outputbuffer;
		G->s->outputcursor = (int *)output;
		G->s->framesleft = (t_unint32)framecount;
		G->s->framesread = G->s->framesleft;
		frame_audio(G->s);
		cursor_audio(G->s, G);
		G->s = ended_audio(G->s, G);
	}
	if (!G->sounds)
		return (paComplete);
	return (paContinue);
}
