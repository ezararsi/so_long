/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezararsi <ezararsi@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:10:13 by ezararsi          #+#    #+#             */
/*   Updated: 2026/11/05 17:46:51 by ezararsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_player(t_game *game, int offset)
{
	int		target;
	char	tile;

	target = game->player + offset;
	tile = game->map[target];
	if (tile == '1' || (tile == 'E' && game->collectables > 0))
		return ;
	game->moves++;
	ft_putstr_fd("Movements: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
	if (tile == 'E')
	{
		ft_putstr_fd("You Finished The Game\n", 1);
		mlx_loop_end(game->mlx);
		return ;
	}
	if (tile == 'C')
		game->collectables--;
	game->map[game->player] = '0';
	game->map[target] = 'P';
	draw_tile(game, game->player);
	draw_tile(game, target);
	game->player = target;
}

int	key_press(int keysym, t_game *game)
{
	if (keysym == KEY_W || keysym == KEY_UP)
		move_player(game, -game->line_length);
	else if (keysym == KEY_S || keysym == KEY_DOWN)
		move_player(game, game->line_length);
	else if (keysym == KEY_A || keysym == KEY_LEFT)
		move_player(game, -1);
	else if (keysym == KEY_D || keysym == KEY_RIGHT)
		move_player(game, 1);
	else if (keysym == KEY_ESC)
	{
		ft_putstr_fd("Left Game Pressing 'ESC'\n", 1);
		mlx_loop_end(game->mlx);
	}
	return (0);
}
