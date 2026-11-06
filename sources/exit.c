/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:07:24 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:58:12 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_args(int argc, char **argv)
{
	int	len;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (len > 4 && ft_strncmp(argv[1] + len - 4, ".ber", 5) == 0)
			return ;
	}
	ft_putstr_fd("Error\nUsage: ./so_long <map.ber>\n", 2);
	exit(EXIT_FAILURE);
}

/* Kann jederzeit aufgerufen werden, gibt nur Erstelltes frei. */
void	cleanup(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->img[i])
			mlx_destroy_image(game->mlx, game->img[i]);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->map);
}

void	error_exit(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	cleanup(game);
	exit(EXIT_FAILURE);
}
