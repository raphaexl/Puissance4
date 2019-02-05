/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:20:17 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/24 23:46:15 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# define SCR_WIDTH 800
# define SCR_HEIGHT 600
# define L 6
# define C 7
# define MAX 10
# define MIN -10
# define ft_min(a, b) (((a) < (b)) ? (a) : (b))
# define ft_max(a, b) (((a) > (b)) ? (a) : (b))
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <libft.h>

typedef	enum		s_type
{
	EMPTY = ' ', RED='X', YELLOW = 'Y'
}					t_type;

typedef struct		s_input
{
	int		quit;
	int		mousex;
	int		mousey;
	int		xwheel;
	int		ywheel;
	int		mousexrel;
	int		mouseyrel;
	int		mouse[6];
	int		keys[SDL_NUM_SCANCODES];
}					t_input;

typedef	struct		s_ptr
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*bg;
	SDL_Texture		*red;
	SDL_Texture		*yellow;
}					t_ptr;

typedef struct	 s_point
{
	int		x;
	int		y;
}				t_point;

typedef	struct	 s_grille
{
	char	tab[L][C];
}				t_grille;

SDL_Texture		*ft_sdl_load_texture(SDL_Renderer *renderer, const char *file_name);
void			ft_update_event(t_input *in);
int				ft_game_display(t_ptr *ptr, t_grille *g);
int				ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
void			ft_sdl_quit(t_ptr *ptr);
void			ft_ask_action (t_input *in, t_grille *g, t_type p);
bool			ft_play(t_ptr *ptr, t_input *in, t_grille *g);
int				ft_grille_count(t_grille *grille, t_point	start, int dx, int dy);
bool			ft_grille_full(t_grille *grille);
bool			ft_grille_init(t_grille *grille);
void			ft_grille_print(t_grille *grille);
bool			ft_game_end(t_grille *grille);
void			ft_ask_ai_action(t_grille *g, t_type p);
int				ft_evaluate(t_grille *g);
int				ft_minmax(int depth, t_grille *g, bool max);
t_point			ft_best_move(t_grille *g);
#endif
