/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:18:38 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:41:36 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	*read_all(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*map;
	char	*tmp;
	int		bytes;

	map = ft_strdup("");
	bytes = 1;
	while (map && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(map), NULL);
		buf[bytes] = '\0';
		tmp = map;
		map = ft_strjoin(map, buf);
		free(tmp);
	}
	return (map);
}

/* Liest die Datei ein und entfernt ein abschliessendes '\n'. */
char	*read_map(const char *path)
{
	char	*map;
	int		fd;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = read_all(fd);
	close(fd);
	if (!map)
		return (NULL);
	len = ft_strlen(map);
	if (len > 0 && map[len - 1] == '\n')
		map[len - 1] = '\0';
	return (map);
}

static void	init_window(t_game *game)
{
	int	screen_w;
	int	screen_h;
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "Could not initialize MiniLibX");
	width = (game->line_length - 1) * TILE;
	height = game->rows * TILE;
	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	if (width > screen_w || height > screen_h)
		error_exit(game, "Map is too big for the screen");
	load_images(game);
	game->win = mlx_new_window(game->mlx, width, height, "so_long");
	if (!game->win)
		error_exit(game, "Could not create window");
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	ft_bzero(&game, sizeof(game));
	game.map = read_map(argv[1]);
	if (!game.map)
		error_exit(&game, "Could not read map file");
	validate_map(&game);
	init_window(&game);
	render_map(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(game.win, DestroyNotify, 0, mlx_loop_end, game.mlx);
	mlx_expose_hook(game.win, render_map, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
