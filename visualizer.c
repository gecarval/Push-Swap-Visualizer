/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:18:49 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/26 18:38:09 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

int	choose_operations(t_list **a, t_list **b, t_data *data, int dir)
{
	const int	operation_size = ft_av_size(data->operations);
	static int	ldir = 1;
	static int	i = -1;

	if (data->operations == NULL || (i == 0 && data->steper == 1 && dir == -1))
		return (i);
	else if (dir == -1 && i < 0)
		return (0);
	else if (dir == 1 && i >= operation_size)
		return (operation_size - 1);
	i += dir;
	if (dir == -1 && ldir == 1)
		i++;
	else if (dir == 1 && ldir == -1)
		i--;
	ldir = dir;
	if (dir == 1 && i >= 0 && i < operation_size)
	{
		if (ft_strncmp(data->operations[i], "pa", 3) == 0)
			ft_pa(b, a);
		if (ft_strncmp(data->operations[i], "pb", 3) == 0)
			ft_pb(a, b);
		if (ft_strncmp(data->operations[i], "sa", 3) == 0)
			ft_sa(a);
		if (ft_strncmp(data->operations[i], "sb", 3) == 0)
			ft_sb(b);
		if (ft_strncmp(data->operations[i], "ss", 3) == 0)
			ft_ss(a, b);
		if (ft_strncmp(data->operations[i], "ra", 3) == 0)
			ft_ra(a);
		if (ft_strncmp(data->operations[i], "rb", 3) == 0)
			ft_rb(b);
		if (ft_strncmp(data->operations[i], "rr", 3) == 0)
			ft_rr(a, b);
		if (ft_strncmp(data->operations[i], "rra", 4) == 0)
			ft_rra(a);
		if (ft_strncmp(data->operations[i], "rrb", 4) == 0)
			ft_rrb(b);
		if (ft_strncmp(data->operations[i], "rrr", 4) == 0)
			ft_rrr(a, b);
	}
	else if (dir == -1 && i >= 0 && i < operation_size)
	{
		if (ft_strncmp(data->operations[i], "pa", 3) == 0)
			ft_pb(a, b);
		if (ft_strncmp(data->operations[i], "pb", 3) == 0)
			ft_pa(b, a);
		if (ft_strncmp(data->operations[i], "sa", 3) == 0)
			ft_sa(a);
		if (ft_strncmp(data->operations[i], "sb", 3) == 0)
			ft_sb(b);
		if (ft_strncmp(data->operations[i], "ss", 3) == 0)
			ft_ss(a, b);
		if (ft_strncmp(data->operations[i], "ra", 3) == 0)
			ft_rra(a);
		if (ft_strncmp(data->operations[i], "rb", 3) == 0)
			ft_rrb(b);
		if (ft_strncmp(data->operations[i], "rr", 3) == 0)
			ft_rrr(a, b);
		if (ft_strncmp(data->operations[i], "rra", 4) == 0)
			ft_ra(a);
		if (ft_strncmp(data->operations[i], "rrb", 4) == 0)
			ft_rb(b);
		if (ft_strncmp(data->operations[i], "rrr", 4) == 0)
			ft_rr(a, b);
	}
	return (i);
}

static void	draw_node(t_list **stack, t_data *data, int dir)
{
	int	i;
	int	j;
	t_delta	dx;
	t_delta	dy;
	t_list	*tmp;

	if (!(*stack))
		return ;
	tmp = *stack;
	j = 0;
	while (tmp != NULL)
	{
		dx = defdel(0, (map((tmp->index + 1), 0, data->max_index, 0, data->winx / 2.5)));
		if (dir == 1)
			dx = defdel(data->winx, data->winx - (map((tmp->index + 1), 0, data->max_index, 0, data->winx / 2.5)));
		i = 0;
		while (++i <= data->space)
		{
			dy = defdel((j * data->space) + i, (j * data->space) + i);
			draw_line(dx, dy, data, tmp->color);
		}
		tmp = tmp->next;
		j++;
	}
}

void	visualize_stack(t_data *data, t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = *a;
	if (tmp != NULL)
	{
		draw_node(&tmp, data, 0);
		tmp = tmp->next;
	}
	tmp = *b;
	if (tmp != NULL)
	{
		draw_node(&tmp, data, 1);
		tmp = tmp->next;
	}
}
