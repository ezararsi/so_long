/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:02:47 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:39:04 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE 64
# define TILES "10PEC"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/*
** map:          gesamte Karte als ein String, Zeilen durch '\n' getrennt
** line_length:  Zeichen pro Zeile inklusive '\n'
** rows:         Anzahl der Zeilen
** img:          ein Bild pro Zeichen in TILES, gleiche Reihenfolge
*/
typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*map;
	int		line_length;
	int		rows;
	int		player;
	int		collectables;
	int		moves;
	void	*img[5];
}	t_game;

/* main.c */
char	*read_map(const char *path);

/* map_check.c */
void	validate_map(t_game *game);

/* render.c */
void	load_images(t_game *game);
void	draw_tile(t_game *game, int pos);
int		render_map(t_game *game);

/* move.c */
int		key_press(int keysym, t_game *game);

/* exit.c */
void	check_args(int argc, char **argv);
void	error_exit(t_game *game, char *msg);
void	cleanup(t_game *game);

#endif
