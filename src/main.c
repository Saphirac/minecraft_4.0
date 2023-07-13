/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:53:37 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/13 13:56:16 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Destroy the window, image and display of the mlx and free the mlx ptr.
 * 
 * @param data to terminate.
 */
void	mlx_terminate(t_info *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img_data.img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

/**
 * @brief Set the params of t_data struct data
 * 
 * @param t_data to set
 * @return EXIT_FAILURE if mlx fail and EXIT_SUCCESS otherwise. 
 */
int	set_params(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit(0);
	data->lg = 1200;
	data->wd = 700;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->lg, data->wd, "cub3d");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), perror("Mlx error"), EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx_ptr, data->lg, data->wd);
	if (!data->img)
		return (free(data->win_ptr), perror("Mlx error"), EXIT_FAILURE);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (EXIT_SUCCESS);
}

int	create_map(t_map_data *map, char *file)
{
	int	fd;

	ft_bzero(map, sizeof(t_map_data));

	fd = open_file(file);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (get_all_data(map, fd) || check_border(map) == false)
		return (EXIT_FAILURE);
	if (close(fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// TODO : Open and check args
int	main(int ac, char **av)
{
	t_info		data;
	t_map_data	map;

	if (ac != 2)
		return (1);
	if (create_map(&map, av[1]))
		return (1);
	//if (set_params(&data) == EXIT_FAILURE)
	//	return (1);
	raycaster(&data, &map);
	
	//draw_mini_map(&data.img_data, &map);
	//mlx_put_image_to_window(data.mlx, data.win, &data.img_data.img, 0, 0);
	// mlx_loop_hook(data.mlx, &handle_no_event, &data);
	// mlx_key_hook(data.win, &handle_input, &data);
	// mlx_hook(data.win, 17, 0L, &handle_cross, &data);
	// mlx_loop(data.mlx);
	mlx_terminate(&data);
	return (0);
}
