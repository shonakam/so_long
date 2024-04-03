/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:40:35 by shonakam          #+#    #+#             */
/*   Updated: 2024/04/03 12:38:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// move: [up, left, down, right]
static void	data_setup(t_data *data, int flag)
{
	if (flag == 0)
	{
		data->w = 0;
		data->h = 0;
		data->playerflag = 0;
		data->state.c_flag = 0;
		data->state.g_flag = 0;
		data->state.move_counter = 0;
		data->prev = '0';
		data->map = NULL;
	}
	else if (flag == 1)
	{
		data->moves[0] = -data->w;
		data->moves[1] = -1;
		data->moves[2] = data->w;
		data->moves[3] = 1;
	}
}

static void	handle_errors()
{
	
}

static char	*parse_arg(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (ft_strncmp((s + (len - 4)), ".ber", 4) == 0)
	{
		return (s);
	}
	perror("Invalid argument");
	exit(1);
}

static void	game_setup(t_data *data)
{
	data_setup(data, 0);
	load_textures(data);
	load_map(data);
	data_setup(data, 1);
	handle_errors();
	validate_map(data);
	data->win = mlx_new_window(data->mlx,
			(data->w * MATERIAL_SIZE), ((data->h) * MATERIAL_SIZE),
			"./so_long");
	if (!data->win)
	{
		free(data->win);
		free(data->map);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	set_textures(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit(1);
	data.path_ber = parse_arg(av[1]);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	game_setup(&data);
	mlx_key_hook(data.win, observe_esc, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, on_destroy, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, sl_controller, &data);
	mlx_loop(data.mlx);
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q so_long");
}
