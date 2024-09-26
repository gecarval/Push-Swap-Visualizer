/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:38:51 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/26 12:28:41 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

// HOOKS
int	mouse_released(int key, t_data *data)
{
	if (key == 1)
		data->click_hold = 0;
	ft_printf("%d\n", key);
	return (0);
}

int	mouse_click(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1 && data->click_hold == 0)
		data->click_hold = 1;
	else
		data->click_hold = 0;
	return (0);
}

void	draw_button(int x, int y, int w, int h, t_data *data, int color)
{
	t_delta	dx;
	t_delta	dy;

	dx = defdel(x, x + w);
	while (h > 0)
	{
		dy = defdel(y + h, y + h);
		draw_line(dx, dy, data, color);
		h--;
	}
	draw_button(x + 1, y - 1, w + 2, h + 2, data, 0xFFFFFF);
}

void	handle_click(t_data *data)
{
	if (data->mposx > (data->winx / 2) - 91 && data->mposx < ((data->winx / 2) - 91) + 145)
	{
		if (data->mposy > 209 && data->mposy < 209 + 27)
		{
			data->anidir = -1;
		}
	}
	if (data->mposx > (data->winx / 2) - 91 && data->mposx < ((data->winx / 2) - 91) + 135)
	{
		if (data->mposy > 249 && data->mposy < 249 + 27)
		{
			data->anidir = 0;
		}
	}
	if (data->mposx > (data->winx / 2) - 91 && data->mposx < ((data->winx / 2) - 91) + 145)
	{
		if (data->mposy > 289 && data->mposy < 289 + 27)
		{
			data->anidir = 1;
		}
	}
}

int	mlx_anim(t_data *data)
{
	if (data->animation_start == 1)
	{
		render_background(data, 0x000000);
		visualize_stack(data, &data->stack_a, &data->stack_b);
		choose_operations(&data->stack_a, &data->stack_b, data, data->anidir);
		draw_button((data->winx / 2) - 90, 250, 133, 25, data, 0x444444);
		draw_button((data->winx / 2) - 90, 210, 143, 25, data, 0x444444);
		draw_button((data->winx / 2) - 90, 290, 143, 25, data, 0x444444);
		mlx_put_image_to_window(data->ini, data->win, data->img->img_ptr, 0, 0);
		control_mark(data);
		mlx_string_put(data->ini, data->win, (data->winx / 2) - 80, 227, 120000, "Click Here to Reverse");
		mlx_string_put(data->ini, data->win, (data->winx / 2) - 80, 267, 120000, "Click Here to Stop");
		mlx_string_put(data->ini, data->win, (data->winx / 2) - 80, 307, 120000, "Click Here to Start");
		if (data->click_hold == 1)
		{
			mlx_mouse_get_pos(data->ini, data->win, &data->mposx, &data->mposy);
			if (data->mposx < 0 || data->mposx > data->winx)
				data->click_hold = 0;
			if (data->mposy < 0 || data->mposy > data->winy)
				data->click_hold = 0;
			handle_click(data);
			data->pmposx = data->mposx;
			data->pmposy = data->mposy;
			data->click_hold = 0;
		}
	}
	return (0);
}

int	mlx_cooked(int key, t_data *data)
{
	if (key == ESC)
		exit_data(data, 0);
	if (key == '1')
		data->animation_start *= -1;
	if (key == ']')
		data->timing += 10000;
	if (key == 'v')
		data->anidir = -1;
	if (key == 'b')
		data->anidir = 0;
	if (key == 'n')
		data->anidir = 1;
	if (key == '[')
		if (data->timing > 9999)
			data->timing -= 10000;
	if (key == ' ')
	{
		render_background(data, 0x000000);
		mlx_put_image_to_window(data->ini, data->win, data->img->img_ptr, 0, 0);
		water_mark(data);
	}
	return (0);
}

// GRAPH
void	pixel_to_img(int x, int y, t_data *data, int color)
{
	char	*pixel;

	if ((x < 0 || x > data->winx) || (y < 0 || y > data->winy))
		return ;
	pixel = data->img->img_px + y * data->img->llen + x * (data->img->bpp / 8);
	*(int *)pixel = color;
}

void	pixel_to_img_float(float_t x, float_t y, t_data *data, int color)
{
	char	*pixel;

	if ((x < 0 || x > data->winx) || (y < 0 || y > data->winy))
		return ;
	pixel = data->img->img_px + (int)y * data->img->llen + (int)x * (data->img->bpp / 8);
	*(int *)pixel = color;
}

void	control_mark(t_data *data)
{
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 15, 120000, "press 1 to stop");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 30, 120000, "press [ to slow down");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 45, 120000, "press ] to speed up");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 60, 120000, "press v to go back");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 75, 120000, "press b to pause");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 90, 120000, "press n to go on");
}

void	water_mark(t_data *data)
{
	mlx_string_put(data->ini, data->win,
		15, 15, 120000, "visualizer by gecarval");
	mlx_string_put(data->ini, data->win,
		15, 60, 120000, "press 1 to start visualizer");
}

void	render_background(t_data *data, int color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->winx)
	{
		y = -1;
		while (++y < data->winy)
			pixel_to_img(x, y, data, color);
	}
}

// FREE
void	ft_free_matrix(void **vec)
{
	int	i;

	i = -1;
	while (vec[++i])
		free(vec[i]);
	free(vec);
}

void	ft_free_tensor(void ***z)
{
	int	i;

	i = -1;
	while (z[++i])
		ft_free_matrix(z[i]);
	free(z);
}

// DELTAS
t_delta	defdel(int ini, int fin)
{
	return ((t_delta){ini, fin});
}

t_delta	revdel(t_delta a)
{
	int	tmp;

	tmp = a.ini;
	a.ini = a.fin;
	a.fin = tmp;
	return (a);
}

// MATH
float_t	rand_float_t(float_t min, float_t max)
{
	return (((float_t)rand() / ((float_t)RAND_MAX / (max - min)) + min));
}

float_t	map(float_t value, float_t inmin, float_t inmax, float_t outmin, float_t outmax)
{
	return (value - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
}
