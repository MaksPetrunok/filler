/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:33:47 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/07 12:26:26 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_map(void)
{
	int	i;

	if (g_map == NULL)
		return ;
	i = 0;
	while (i < g_h)
		free((void *)g_map[i++]);
	free((void *)g_map);
	g_map = NULL;
}

void	free_piece(void)
{
	int	i;

	if (g_p == NULL)
		return ;
	i = 0;
	while (i < g_p->h)
		free((void *)(g_p->map[i++]));
	free((void *)(g_p->map));
	free((void *)g_p);
	g_p = NULL;
}
