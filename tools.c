/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:38:51 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/26 18:38:24 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

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

void mlx_operation_ui(t_data *data, int i)
{
	if (data->operations == NULL)
		return ;
	char *tmp = NULL;
	tmp = ft_itoa(data->timing / 1000);
	mlx_string_put(data->ini, data->win, (WINX / 2.0f) - 75, 185, 0xffffff, "delay:");
	mlx_string_put(data->ini, data->win, (WINX / 2.0f) - 35, 185 + 1, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(data->ini, data->win, (data->winx / 2) - 0, 121, 0xdddddd, data->operation_n);
	mlx_string_put(data->ini, data->win,
				(data->winx / 2) - 75, 120, 120000, "Operations:");
	mlx_string_put(data->ini, data->win,
				(data->winx / 2) - 75, 135, 120000, "Current->");
	mlx_string_put(data->ini, data->win,
				(data->winx / 2) - 75, 150, 120000, "Next->");
	mlx_string_put(data->ini, data->win,
				(data->winx / 2) - 75, 165, 120000, "Next->");
	if (i > -1 && i < ft_av_size(data->operations))
	{
		if (i - 1 > -1)
		{
			mlx_string_put(data->ini, data->win,
				  (data->winx / 2) - 15, 135, 120000, data->operations[i - 1]);
		}
		mlx_string_put(data->ini, data->win,
				 (data->winx / 2) - 15, 150, 120000, data->operations[i]);
		if (i + 1 < ft_av_size(data->operations))
		{
			mlx_string_put(data->ini, data->win,
				  (data->winx / 2) - 15, 165, 120000, data->operations[i + 1]);
		}
	}
}

void	draw_button(t_button *b, t_data *data, bool draw_out_lines)
{
	unsigned int color;
	t_delta	dx;
	t_delta	dy;
	int h;

	color = b->btt_col;
	if (b->pressed)
		color -= 0x111111;
	h = b->len.y + 1;
	dx = defdel(b->pos.x, b->pos.x + b->len.x);
	while (--h > 0)
	{
		dy = defdel(b->pos.y + h, b->pos.y + h);
		if (b->pressed)
			draw_line(dx, dy, data, color);
		else if (!b->pressed)
			draw_line(dx, dy, data, color);
	}
	if (draw_out_lines == false)
		return ;
	// Vertical outlines
	dy = defdel(b->pos.y, b->pos.y);
	draw_line(dx, dy, data, b->outln_color);
	dy = defdel(b->pos.y + b->len.y, b->pos.y + b->len.y);
	draw_line(dx, dy, data, b->outln_color);
	// Horizontal outlines
	dy.ini = b->pos.y;
	dx = defdel(b->pos.x, b->pos.x);
	draw_line(dx, dy, data, b->outln_color);
	dx = defdel(b->pos.x + b->len.x, b->pos.x + b->len.x);
	draw_line(dx, dy, data, b->outln_color);
}

void	handle_button_click(t_button *b, t_data *data)
{
	if (data->mposx > b->pos.x && data->mposx < b->pos.x + b->len.x)
	{
		if (data->mposy > b->pos.y && data->mposy < b->pos.y + b->len.y)
		{
			if (!b->pressed)
				b->pressed = true;
			else
				b->pressed = false;
			return ;
		}
	}
	b->pressed = false;
}

void	draw_button_text(t_button *b, t_data *data)
{
	mlx_string_put(data->ini, data->win, b->pos.x + 10, b->pos.y + (b->len.y / 1.5), b->txt_col, b->text);
}

int	mlx_anim(t_data *data)
{
	static const int	BLACK = 0;
	int					i = 0;

	render_background(data, BLACK);
	visualize_stack(data, &data->stack_a, &data->stack_b);
	if (data->animation_start == 1)
		i = choose_operations(&data->stack_a, &data->stack_b, data, data->anidir);
	draw_button(&data->prevbutton, data, true);
	draw_button(&data->nextbutton, data, true);
	draw_button(&data->pausebutton, data, true);
	mlx_put_image_to_window(data->ini, data->win, data->img->img_ptr, 0, 0);
	control_mark(data);
	mlx_operation_ui(data, i);
	draw_button_text(&data->prevbutton, data);
	draw_button_text(&data->nextbutton, data);
	draw_button_text(&data->pausebutton, data);
	if (data->click_hold == 1)
	{
		mlx_mouse_get_pos(data->ini, data->win, &data->mposx, &data->mposy);
		handle_button_click(&data->prevbutton, data);
		handle_button_click(&data->nextbutton, data);
		handle_button_click(&data->pausebutton, data);
		if (data->nextbutton.pressed)
		{
			data->animation_start = 1;
			data->anidir = 1;
		}
		else if (data->prevbutton.pressed)
		{
			data->animation_start = 1;
			data->anidir = -1;
		}
		data->pmposx = data->mposx;
		data->pmposy = data->mposy;
		data->click_hold = 0;
	}
	if (data->steper == 1)
	{
		data->steper = 0;
		data->animation_start = -1;
		data->pausebutton.pressed = true;
	}
	if (data->timing > 0)
		usleep(data->timing);
	if (data->pausebutton.pressed)
		data->animation_start = -1;
	else if (!data->pausebutton.pressed)
		data->animation_start = 1;
	return (0);
}

int	mlx_cooked(int key, t_data *data)
{
	if (key == ESC)
		exit_data(data, 0);
	if (key == ' ')
	{
		data->animation_start *= -1;
		data->pausebutton.pressed = data->animation_start == 1 ? false : true;
	}
	if (key == 'v')
	{
		data->prevbutton.pressed = false;
		data->nextbutton.pressed = true;
		data->animation_start = 1;
		data->anidir = -1;
	}
	if (key == 'n')
	{
		data->prevbutton.pressed = true;
		data->nextbutton.pressed = false;
		data->animation_start = 1;
		data->anidir = 1;
	}
	if (key == 'a')
	{
		data->animation_start = 1;
		data->anidir = -1;
		data->steper = 1;
	}
	if (key == 'd')
	{
		data->animation_start = 1;
		data->anidir = 1;
		data->steper = 1;
	}
	if (key == '[')
		data->timing += 10000;
	if (key == ']')
		if (data->timing >= 10000)
			data->timing -= 10000;
	if (key == '1')
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
		(data->winx / 2) - 75, 15, 120000, "press Space to stop");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 30, 120000, "press [ to slow down");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 45, 120000, "press ] to speed up");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 60, 120000, "press v to go back");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 75, 120000, "press n to go on");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 90, 120000, "press a back one operation");
	mlx_string_put(data->ini, data->win,
		(data->winx / 2) - 75, 105, 120000, "press d to do one operation");
}

void	water_mark(t_data *data)
{
	mlx_string_put(data->ini, data->win,
		15, 15, 120000, "visualizer by gecarval");
	mlx_string_put(data->ini, data->win,
		15, 60, 120000, "press Space to start visualizer");
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
