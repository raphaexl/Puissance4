/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grille.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:44:16 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/07 20:20:36 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

bool		ft_grille_init(t_grille *grille)
{
	int		i;
	int		j;
	

	i = -1;
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			grille->tab[i][j] = EMPTY;
		}
	}
	return (true);
}

bool		ft_grille_full(t_grille *grille)
{
	int		i;
	int		j;
	int		count;
	

	i = -1;
	count = 0;
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			count = grille->tab[i][j] == EMPTY ? count : count + 1;
		}
	}
	return (count == 42);
}

int			ft_grille_count(t_grille *g, t_point start, int dx, int dy)
{
	int		i;
	int		j;
	t_type	player;
	int		count;
	

	j = start.x;
	i = start.y;
	count = 0;
	player = g->tab[i][j];
	while (i < L && j < C && g->tab[i][j] == player)
	{
		i += dy;
		j += dx;
		++count;
	}	
	return (count);
}

void		ft_grille_print(t_grille *grille)
{
	int		i;
	int		j;
	

	i = -1;
	system("clear");
	while (++i < L)
	{
		j = -1;
		write(1, "------------------------------------\n", 38);
		while (++j < C)
		{
			write(1, "| ", 2);
			write (1, &grille->tab[i][j], 1);
			write (1, " |", 2);
		}
		write(1, "\n", 1);
	}
	write(1, "------------------------------------\n", 38);
	write(1, "--1----2----3----4----5----6----7---\n", 38);
	write(1, "------------------------------------\n", 38);
}
