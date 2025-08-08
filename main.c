/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:57:08 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/26 16:46:51 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		display_error(data, "malloc error\n");
	data->winx = WINX;
	data->winy = WINY;
	ft_init_program(data);
	create_visualizer(data, ac, av);
	data->animation_start = -1;
	data->steper = 0;
	data->anidir = 0;
	data->click_hold = 0;
	data->timing = 0;
	water_mark(data);
	mlx_mouse_hook(data->win, mouse_click, data);
	mlx_hook(data->win, DestroyNotify, 0, exit_data, data);
	mlx_key_hook(data->win, mlx_cooked, data);
	mlx_loop_hook(data->ini, mlx_anim, data);
	mlx_loop(data->ini);
	return (0);
}
