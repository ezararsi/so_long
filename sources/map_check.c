/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:36:08 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:52:09 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* Alle Zeilen gleich breit: '\n' genau am Ende jeder Zeile. */
static int	is_rectangular(t_game *game)
{
	int	i;
	int	width;

	width = 0;
	while (game->map[width] && game->map[width] != '\n')
		width++;
	if (width < 3 || !game->map[width])
		return (0);
	game->line_length = width + 1;
	i = 0;
	while (game->map[i])
	{
		if ((i % game->line_length == width) != (game->map[i] == '\n'))
			return (0);
		i++;
	}
	game->rows = (i + 1) / game->line_length;
	return (i % game->line_length == width && game->rows >= 3);
}

static int	is_enclosed(t_game *game)
{
	int	i;
	int	col;
	int	row;

	i = -1;
	while (game->map[++i])
	{
		col = i % game->line_length;
		row = i / game->line_length;
		if (game->map[i] == '\n' || game->map[i] == '1')
			continue ;
		if (row == 0 || row == game->rows - 1
			|| col == 0 || col == game->line_length - 2)
			return (0);
	}
	return (1);
}

/* Nur gueltige Zeichen, genau ein P und ein E, mindestens ein C. */
static int	has_valid_tiles(t_game *game)
{
	int	i;
	int	exits;
	int	players;

	i = -1;
	exits = 0;
	players = 0;
	while (game->map[++i])
	{
		if (!ft_strchr(TILES "\n", game->map[i]))
			return (0);
		exits += (game->map[i] == 'E');
		game->collectables += (game->map[i] == 'C');
		if (game->map[i] == 'P')
		{
			game->player = i;
			players++;
		}
	}
	return (players == 1 && exits == 1 && game->collectables > 0);
}

/* Der Ausgang ist erreichbar, blockiert aber wie im Spiel den Weg. */
static void	flood_fill(char *map, int pos, int line_length)
{
	char	tile;

	tile = map[pos];
	if (tile == '1' || tile == 'X')
		return ;
	map[pos] = 'X';
	if (tile == 'E')
		return ;
	flood_fill(map, pos - 1, line_length);
	flood_fill(map, pos + 1, line_length);
	flood_fill(map, pos - line_length, line_length);
	flood_fill(map, pos + line_length, line_length);
}

void	validate_map(t_game *game)
{
	char	*copy;
	int		reachable;

	if (!is_rectangular(game))
		error_exit(game, "Map must be rectangular with at least 3x3 tiles");
	if (!has_valid_tiles(game))
		error_exit(game, "Map needs one P, one E, at least one C");
	if (!is_enclosed(game))
		error_exit(game, "Map must be surrounded by walls");
	copy = ft_strdup(game->map);
	if (!copy)
		error_exit(game, "Out of memory");
	flood_fill(copy, game->player, game->line_length);
	reachable = !ft_strchr(copy, 'C') && !ft_strchr(copy, 'E');
	free(copy);
	if (!reachable)
		error_exit(game, "Exit or collectables are not reachable");
}
