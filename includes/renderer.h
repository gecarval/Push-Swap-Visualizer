/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gecarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:05:06 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/02 14:34:58 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

// LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <stdbool.h>
# include <aio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// WINDOW MACROS
# define ESC	65307 
# define WINX	1900
# define WINY	1000

// STRUCTS
typedef struct s_objinf
{
	float_t	pox;
	float_t	poy;
	float_t	sx;
	float_t	sy;
	float_t	color;
}	t_objinf;

typedef struct s_delta
{
	int	ini;
	int	fin;
}	t_delta;

typedef struct s_vector
{
	float_t	x;
	float_t	y;
}	t_vector;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_px;
	int		end;
	int		llen;
	int		bpp;
}	t_img;

typedef struct s_button
{
	t_vector	pos;
	t_vector	len;
	char		*text;
	int			txt_col;
	int			btt_col;
	int			outln_color;
	bool		pressed;
}	t_button;

typedef struct s_textbox
{
	t_vector	pos;
	char		*text;
	int			txt_col;
	int			outln_color;
}	t_textbox;

typedef struct s_menu
{
	t_vector	pos;
	t_button	*button;
	t_textbox	*text_box;
	int			num_of_particlesicle;
	int			part_num;
	int			radius;
	int			bg_col;
	int			outln_col;
}	t_menu;


typedef struct s_data
{
	void		*ini;
	void		*win;
	t_img		*img;
	t_menu		*menu;
	t_button	prevbutton;
	t_button	nextbutton;
	t_button	pausebutton;
	t_list		*stack_a;
	t_list		*stack_b;
	char		**operations;
	char		*operation_n;
	int			anidir;
	int			steper;
	int			space;
	int			max_index;
	int			winx;
	int			winy;
	int			animation_start;
	int			click_hold;
	int			pmposx;
	int			pmposy;
	int			mposx;
	int			mposy;
	int			timing;
}	t_data;

// PROCESS CALLS
void	display_error(t_data *data, char *msg);
void	create_tensor(t_data *data);
void	ft_init_program(t_data *data);
void	ft_free_matrix(void **vec);
void	ft_free_tensor(void ***z);
int		exit_data(t_data *data, int fd);
// MAP READ
void	create_visualizer(t_data *data, int ac, char **av);
void	display_error(t_data *data, char *msg);
// VISUALIZER
void	visualize_stack(t_data *data, t_list **a, t_list **b);
int		choose_operations(t_list **a, t_list **b, t_data *data, int dir);
// HOOKS
int		mlx_cooked(int	key, t_data *data);
int		mlx_anim(t_data *data);
int		mouse_click(int key, int x, int y, t_data *data);
int		mouse_released(int key, t_data *data);
//PIXEL PUTS
void	pixel_to_img(int x, int y, t_data *data, int color);
void	pixel_to_img_float(float_t x, float_t y, t_data *data, int color);
void	render_background(t_data *data, int color);
void	draw_line_y(t_delta x, t_delta y, t_data *data, int color);
void	draw_line_x(t_delta x, t_delta y, t_data *data, int color);
void	draw_line(t_delta x, t_delta y, t_data *data, int color);
void	drawcircle(int xc, int yc, int x, int y, t_data *data, int color);
void	circlebres(int xc, int yc, int r, t_data *data, int color);
// WATER MARKS
void	water_mark(t_data *data);
void	control_mark(t_data *data);
// DELTAS
t_delta	defdel(int ini, int fin);
t_delta	revdel(t_delta a);
// MATH
float_t	rand_float_t(float_t min, float_t max);
float_t	map(float_t value, float_t inmin, float_t inmax, float_t outmin, float_t outmax);
// PUSH SWAP OPS
void	ft_pa(t_list **stack_b, t_list **stack_a);
void	ft_pb(t_list **stack_a, t_list **stack_b);
void	ft_sa(t_list **stack_a);
void	ft_sb(t_list **stack_b);
void	ft_ss(t_list **stack_a, t_list **stack_b);
void	ft_ra(t_list **stack_a);
void	ft_rb(t_list **stack_b);
void	ft_rr(t_list **stack_a, t_list **stack_b);
void	ft_rra(t_list **stack_a);
void	ft_rrb(t_list **stack_b);
void	ft_rrr(t_list **stack_a, t_list **stack_b);
void	ft_free_args(char **av);
void	ft_init_stack(t_data *data, char **av, char **av_int);
void	ft_free_stacks(t_list **stack);
int		ft_atoi_stack(const char *str, t_data *data, char **av, char **av_int);
int		ft_av_size(char **av);
int		ft_check_repeat(t_list **stack);
int		ft_verif_sort(t_list **stack);
int		start_stack(int ac, char **av, t_data *data);

#endif
