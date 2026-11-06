/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:36:31 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:49:27 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* Gleiche Reihenfolge wie TILES: Wand, Boden, Spieler, Ausgang, Item. */
void	load_images(t_game *game)
{
	static char	*files[5] = {"./img/wall.xpm", "./img/floor.xpm",
		"./img/player.xpm", "./img/exit.xpm", "./img/collect.xpm"};
	int			w;
	int			h;
	int			i;

	i = 0;
	while (i < 5)
	{
		game->img[i] = mlx_xpm_file_to_image(game->mlx, files[i], &w, &h);
		if (!game->img[i])
			error_exit(game, "Could not load images from ./img");
		i++;
	}
}

void	draw_tile(t_game *game, int pos)
{
	char	*tile;

	tile = ft_strchr(TILES, game->map[pos]);
	if (!tile || !*tile)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, game->img[tile - TILES],
		(pos % game->line_length) * TILE, (pos / game->line_length) * TILE);
}

/* Auch Expose-Hook: zeichnet das Fenster neu, wenn es sichtbar wird. */
int	render_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		draw_tile(game, i++);
	return (0);
}
