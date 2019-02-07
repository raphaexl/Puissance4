/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:42:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/07 20:12:05 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

int		ft_evaluate(t_grille *g)
{
	int		i;
	int		j;
	t_point	p;
	bool	finished;

	finished = false;
	i = -1;
	while (++i <= L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				p.x = j;
				p.y = i;
				if (i < 3 && j < 4 && ft_grille_count(g, p, 1, 1) >= 4)
					finished = true;
				if (i > 2 && j > 2 && ft_grille_count(g, p, 1, -1) >= 4)
					finished = true;
				if (j < 4 && ft_grille_count(g, p, 1, 0) >= 4)
					finished = true;
				if (i < 4 && ft_grille_count(g, p, 0, 1) >= 4)
					finished = true;
			}
			if (finished)
				return ((g->tab[i][j] == YELLOW) ? (10) : (-10));
		}
	}
	return (0);
}

int		ft_heuristic(t_grille *g)
{
	t_point	p;
	int		result;
	int		i;
	int		j;

	result = 0;
	i = -1;
	while (++i < L)
	{
		j = -1;
		while (++j < C - 3)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 1, 0);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 1, 0);
		}
	}
	i = -1;
	while (++i < L - 3)
	{
		j = -1;
		while (++j < C)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 0, 1);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 0, 1);
		}
	}
	i = 2;
	while (++i < L)
	{
		j = 3;
		while (++j < C)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 1, 1);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 1, 1);
		}
	}
	i = 1;
	while (++i < L)
	{
		j = 1;
		while (++j < C)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 1, -1);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 1, -1);
		}
	}
	return (result);
}

int		ft_minimax(int depth, t_grille *g, int max)
{
	int		score;
	int		i;
	int		j;
	int		best;

	score = ft_evaluate(g);
	if (ft_grille_full(g))
		return (0);
	if (score == 10)
		return (score);
	if (score == -10)
		return (score);
	if (depth == 2)
		return ((!max ? ft_heuristic(g) : -ft_heuristic(g)));
	if (max)
	{
		i = L;
		best = -10000;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = YELLOW;
					best = ft_max(best, ft_minimax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
	else
	{
		best = 10000;
		i = L;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = RED;
					best = ft_min(best, ft_minimax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
}

t_point		ft_best_move(t_grille *g)
{
	int		best;
	t_point	move;
	int		i;
	int		j;
	int		eval;

	best = -10000;
	move.x = -1;
	move.y = -1;
	i = L;
	while (--i >= 0)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] == EMPTY)
			{
				g->tab[i][j] = YELLOW;
				eval = ft_minimax(0, g, 0);
				g->tab[i][j] = EMPTY;
				if (eval > best)
				{
					printf("\n EVAL %d ", eval);
					move.x = j;
					move.y = i;
					best = eval;
				}
			}
		}
	}
	return (move);
}

