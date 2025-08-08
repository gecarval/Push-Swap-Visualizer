/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:32:15 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/25 19:52:54 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

void	free_part(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int	exit_data(t_data *data, int fd)
{
	if (data != NULL && data->img != NULL && data->img->img_ptr != NULL)
		mlx_destroy_image(data->ini, data->img->img_ptr);
	if (data != NULL && data->img != NULL)
		free(data->img);
	if (data != NULL && data->operations != NULL)
		ft_free_matrix((void **)data->operations);
	if (data != NULL && data->operation_n != NULL)
		free(data->operation_n);
	if (data != NULL && data->stack_a != NULL)
		free_part(data->stack_a);
	if (data != NULL && data->stack_b != NULL)
		free_part(data->stack_b);
	if (data != NULL && data->win != NULL)
		mlx_clear_window(data->ini, data->win);
	if (data != NULL && data->win != NULL)
		mlx_destroy_window(data->ini, data->win);
	if (data != NULL && data->ini != NULL)
		mlx_destroy_display(data->ini);
	if (data != NULL && data->ini != NULL)
		free(data->ini);
	if (data != NULL)
		free(data);
	exit(fd);
	return (0);
}

void	display_error(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit_data(data, 1);
}

void	ft_init_program(t_data *data)
{
	data->ini = mlx_init();
	if (!data->ini)
		display_error(data, "init error\n");
	data->win = mlx_new_window(data->ini, data->winx, data->winy, "Push Swap Visualizer");
	if (!data->win)
		display_error(data, "window error\n");
	data->img = (t_img *)malloc(sizeof(t_img));
	if (!data->img)
		display_error(data, "img malloc error\n");
	data->img->img_ptr = mlx_new_image(data->ini, data->winx, data->winy);
	if (!data->img->img_ptr)
		display_error(data, "img ptr error\n");
	data->img->img_px = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp,
			&data->img->llen, &data->img->end);
	if (!data->img->img_px)
		display_error(data, "img data error\n");
	data->prevbutton = (t_button){
		{(WINX / 2.0f) - 90, 210},
		{145, 25},
		"Click Here to Reverse",
		0xdddddd,
		0x444444,
		0x777777,
		false,
	};
	data->nextbutton = (t_button){
		{(WINX / 2.0f) - 90, 250},
		{130, 25},
		"Click Here to Start",
		0xdddddd,
		0x444444,
		0x777777,
		false,
	};
	data->pausebutton = (t_button){
		{(WINX / 2.0f) - 90, 290},
		{130, 25},
		"Click Here to Pause",
		0xdddddd,
		0x444444,
		0x777777,
		false,
	};
	data->resetbutton = (t_button){
		{(WINX / 2.0f) - 90, 330},
		{130, 25},
		"Click Here to Reset",
		0xffaaaa,
		0x444444,
		0x777777,
		false,
	};
}
