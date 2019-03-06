/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:37:01 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/06 22:08:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

typedef struct	s_piece
{
	int			h;
	int			w;
	int			min_x;
	int			min_y;
	int			max_x;
	int			max_y;
	char		**map;
}				t_piece;

extern char		**g_map;
extern int		g_w;
extern int		g_h;
extern char		g_symbol;
extern char		g_symbol_op;
extern t_piece	*g_p;



/*
** read_inp.c
*/
int				read_next(void);
int				init_map(void);
int				read_map(void);
int				read_piece(void);

/*
** free.c
*/
void			free_map(void);
void			free_piece(void);

#endif
