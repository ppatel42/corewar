/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:37:30 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/11 17:28:37 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

int			vp(t_graphics *g, char *str, ...)
{
	va_list		argptr;

	if (!g)
		return (0);
	if (!g->log_window)
		return (0);
	va_start(argptr, str);
	waddstr(g->log_window, " ");
	vw_printw(g->log_window, str, argptr);
	va_end(argptr);
	return (0);
}
