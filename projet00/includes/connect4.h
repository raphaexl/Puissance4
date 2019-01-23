/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:20:17 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/23 18:59:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# define SCR_WIDTH 800
# define SCR_HEIGHT 800
# define L 6
# define C 7
# include <SDL2/SDL.h>
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
	SDL_Texture		*texture;
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
int				ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
void			ft_sdl_quit(t_ptr *ptr);
void			ft_ask_action(t_grille *grille, t_type p);
bool			ft_play(t_grille *grille, t_type player);
int				ft_grille_count(t_grille *grille, t_point	start, int dx, int dy);
bool			ft_grille_full(t_grille *grille);
bool			ft_grille_init(t_grille *grille);
void			ft_grille_print(t_grille *grille);
bool			ft_game_end(t_grille *grille);
#endif
