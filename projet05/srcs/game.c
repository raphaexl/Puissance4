/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:55:25 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/05 19:09:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

void	ft_ai_play(t_grille *g, t_type p)
{
	t_point	pos;
	int		i;
	int		col;

	pos = ft_best_move(g);
	i = L;
	col = pos.x;
	while (i >= 0 && g->tab[i - 1][col] != EMPTY)
		i--;
	if (i >= 1)
		g->tab[i - 1][col] = p;
}

void	ft_ask_action (t_grille *g, t_type p)
{
	int		col;
	int		i;
	bool	restart;

	i = L;
	restart = true;
	while (restart)
	{
		printf(" Joueur %c Votre Tour : Cas ? :\t", p);
		scanf("%d", &col);
		col -= 1;
		restart = false;
		if (col < 0 || col >= C)
			restart = true;
		while (!restart && i >= 0 && g->tab[i - 1][col] != EMPTY)
			i--;
		if (i >= 1)
			g->tab[i - 1][col] = p;
		else
		{
			puts("Invalide Coups : reprenez !");
			restart = true;
		}
	}
}

bool	ft_game_end(t_grille *g)
{
	int		i;
	int		j;
	bool	finished;
	t_point	p;

	i = -1;
	finished = false;
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				p.x = j;
				p.y = i;
				if (ft_grille_count(g, p, 1, 1) >= 4)
					finished = true;
				if (ft_grille_count(g, p, -1, 1) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 1, 0) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 0, 1) >= 4)
					finished = true;			}
			if (finished)
			{
				printf("Player : %c, Gagne", g->tab[i][j]);
				return (true);
			}
		}
	}
	return (false);
}

bool		ft_play(t_grille *g, t_type p)
{
	ft_grille_print(g);
	while (!ft_game_end(g) && !ft_grille_full(g))
	{
		if (p == RED)
			ft_ask_action(g, p);
		else
			ft_ai_play(g, p);
		p = p == RED ? YELLOW : RED;
		ft_grille_print(g);
	}
	ft_grille_print(g);
	return (true);
}
