/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:55:25 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/03 19:36:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

void	ft_ask_ai_action(t_grille *g, t_type ai)
{
	t_point	p;
	int		i;

	p = ft_best_move(g);
	i = L;
	while (i >= 0 && g->tab[i - 1][p.x] != EMPTY)
			i--;
		if (i >= 1)
			g->tab[i - 1][p.x] = ai;
}

void	ft_ask_action (t_input *in, t_grille *g, t_type p)
{
	int		col;
	int		i;
	bool	restart;

	restart = true;
	i = L;
	col = in->mousex / 115;
	restart = false;
	if (col < 0 || col >= C)
	{
		puts("Before Invalide Coups : reprenez !");
		restart = true;
	}
	else
		while (i >= 0 && g->tab[i - 1][col] != EMPTY)
			i--;
	if (i >= 1 && in->mouse[SDL_BUTTON_LEFT])
		g->tab[i - 1][col] = p;
	else
	{
		puts("Invalide Coups : reprenez !");
		restart = true;
	}
	in->mouse[SDL_BUTTON_LEFT] = SDL_FALSE;
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
				if (ft_grille_count(g, p, 1, -1) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 1, 0) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 0, 1) >= 4)
					finished = true;
			}
			if (finished)
				return (true);
		}
	}
	return (false);
}

bool		ft_play(t_ptr *ptr, t_input *in, t_grille *g)
{
	static t_type p = RED;

	while (!ft_game_end(g) && !ft_grille_full(g) && !in->quit)
	{
		ft_update_event(in);
		if (in->mouse[SDL_BUTTON_LEFT])
		{
			if (p == RED)
				ft_ask_action(in, g, p);
			p = p == RED ? YELLOW : RED;
			if (p == YELLOW)
				ft_ask_ai_action(g, p);
		}
		ft_game_display(ptr, g);
		SDL_Delay(1);
	}
	if (in->keys[SDL_SCANCODE_A])
		ft_grille_init(g);
	in->keys[SDL_SCANCODE_A] = SDL_FALSE;
	return (true);
}

int		ft_game_display(t_ptr *ptr, t_grille *g)
{
	int			i;
	int			j;
	SDL_Rect	dest;

	i = -1;
	(void)g;
	SDL_QueryTexture(ptr->red, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderClear(ptr->renderer);
	SDL_RenderCopy(ptr->renderer, ptr->bg, NULL, NULL);
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				dest.y = i * 100;
				dest.x = j * 115 + 4; 
				if (g->tab[i][j] == RED)
					SDL_RenderCopy(ptr->renderer, ptr->red, NULL, &dest);
				else 
					SDL_RenderCopy(ptr->renderer, ptr->yellow, NULL, &dest);
			}
		}
	}
	SDL_RenderPresent(ptr->renderer);
	return (0);
}
