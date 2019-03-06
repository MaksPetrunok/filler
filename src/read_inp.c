/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:07:34 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/06 21:29:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "fcntl.h"

extern int	dbg;

void	normalize(t_piece *p)
{
	int	i;
	int	j;

	p->min_x = p->w - 1;
	p->min_y = p->h - 1;
	p->max_x = 0;
	p->max_y = 0;
	i = -1;
	while (++i < p->h)
	{
		j = -1;
		while (++j < p->w)
			if (p->map[i][j] == '*')
			{
				p->min_x = j < p->min_x ? j : p->min_x;
				p->min_y = i < p->min_y ? i : p->min_y;
				p->max_x = j > p->max_x ? j : p->max_x;
				p->max_y = i > p->max_y ? i : p->max_y;
			}
	}
}

int	read_piece(void)
{
	char	*inp;
	int		i;

	i = 0;
	if ((g_p = malloc(sizeof(t_piece))) == NULL)
		return (0);
	if (get_next_line(0, &inp) > 0)
	{
		while (inp[i] != ' ')
			i++;
		g_p->h = ft_atoi(inp + i++);
		while (inp[i] != ' ')
			i++;
		g_p->w = ft_atoi(inp + i);
		free((void *)inp);
		if ((g_p->map = malloc(sizeof(char **) * g_p->h)) == NULL)
			return (0);
		i = 0;
		while (i < g_p->h)
			if (get_next_line(0, &(g_p->map[i++])) <= 0)
				return (0);
		normalize(g_p);
		return (1);
	}
	return (0);
}

int	init_map(void)
{
	char	*inp;
	int		i;

	i = 0;
	if (get_next_line(0, &inp) > 0)
	{
		while (inp[i] != ' ')
			i++;
		g_h = ft_atoi(inp + i++);
		while (inp[i] != ' ')
			i++;
		g_w = ft_atoi(inp + i);
		free((void *)inp);
		if ((g_map = malloc(sizeof(char **) * (g_h))) == NULL)
			return (0);
		return (1);
	}
	return (0);
}

int	read_map(void)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	get_next_line(0, &tmp);
	free((void *)tmp);
	while (i < g_h)
	{
		j = 0;
		if (get_next_line(0, &tmp) <= 0)
		{
			ft_dprintf(2, "map reading error\n");
			return (0);
		}
		while (tmp[j++] != ' ')
			;
		g_map[i++] = ft_strdup(tmp + j);
		free((void *)tmp);
	}
	return (1);
}

int	read_next(void)
{
	if (!read_map() || !read_piece())
	{
		free_map();
		free_piece();
		return (0);
	}
	return (1);
}
