/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:30:59 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/25 19:46:13 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

void	ft_pa(t_list **stack_b, t_list **stack_a)
{
	t_list	*tmp;

	if (!(*stack_b))
		return ;
	tmp = *stack_b;
	(*stack_b) = (*stack_b)->next;
	tmp->next = (*stack_a);
	*stack_a = tmp;
	return ;
}

void	ft_pb(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (!(*stack_a))
		return ;
	tmp = *stack_a;
	(*stack_a) = (*stack_a)->next;
	tmp->next = (*stack_b);
	*stack_b = tmp;
	return ;
}

void	ft_sa(t_list **stack_a)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(*stack_a) || !((*stack_a)->next))
		return ;
	tmp = *stack_a;
	tmp2 = tmp->next;
	*stack_a = tmp2;
	tmp->next = tmp2->next;
	tmp2->next = tmp;
	return ;
}

void	ft_sb(t_list **stack_b)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(*stack_b) || !((*stack_b)->next))
		return ;
	tmp = *stack_b;
	tmp2 = tmp->next;
	*stack_b = tmp2;
	tmp->next = tmp2->next;
	tmp2->next = tmp;
	return ;
}

void	ft_ss(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!(*stack_a) || !((*stack_a)->next)
		|| !(*stack_b) || !((*stack_b)->next))
		return ;
	tmp = *stack_a;
	tmp2 = tmp->next;
	*stack_a = tmp2;
	tmp->next = tmp2->next;
	tmp2->next = tmp;
	tmp = *stack_b;
	tmp2 = tmp->next;
	*stack_b = tmp2;
	tmp->next = tmp2->next;
	tmp2->next = tmp;
	return ;
}

void	ft_ra(t_list **stack_a)
{
	t_list	*bottom;
	t_list	*top;

	if (!(*stack_a) || !((*stack_a)->next))
		return ;
	top = *stack_a;
	bottom = *stack_a;
	while (bottom->next != NULL)
		bottom = bottom->next;
	*stack_a = top->next;
	bottom->next = top;
	top->next = NULL;
	return ;
}

void	ft_rb(t_list **stack_b)
{
	t_list	*bottom;
	t_list	*top;

	if (!(*stack_b) || !((*stack_b)->next))
		return ;
	top = *stack_b;
	bottom = *stack_b;
	while (bottom->next != NULL)
		bottom = bottom->next;
	*stack_b = top->next;
	bottom->next = top;
	top->next = NULL;
	return ;
}

void	ft_rr(t_list **stack_a, t_list **stack_b)
{
	t_list	*bottom;
	t_list	*top;

	if (!(*stack_a) || !((*stack_a)->next))
		return ;
	top = *stack_a;
	bottom = *stack_a;
	while (bottom->next != NULL)
		bottom = bottom->next;
	*stack_a = top->next;
	bottom->next = top;
	top->next = NULL;
	if (!(*stack_b) || !((*stack_b)->next))
		return ;
	top = *stack_b;
	bottom = *stack_b;
	while (bottom->next != NULL)
		bottom = bottom->next;
	*stack_b = top->next;
	bottom->next = top;
	top->next = NULL;
	return ;
}

void	ft_rra(t_list **stack_a)
{
	t_list	*pre_bottom;
	t_list	*bottom;

	if (!(*stack_a) || !((*stack_a)->next))
		return ;
	pre_bottom = *stack_a;
	while (pre_bottom->next->next != NULL)
		pre_bottom = pre_bottom->next;
	bottom = pre_bottom->next;
	bottom->next = *stack_a;
	*stack_a = bottom;
	pre_bottom->next = NULL;
	return ;
}

void	ft_rrb(t_list **stack_b)
{
	t_list	*pre_bottom;
	t_list	*bottom;

	if (!(*stack_b) || !((*stack_b)->next))
		return ;
	pre_bottom = *stack_b;
	while (pre_bottom->next->next != NULL)
		pre_bottom = pre_bottom->next;
	bottom = pre_bottom->next;
	bottom->next = *stack_b;
	*stack_b = bottom;
	pre_bottom->next = NULL;
	return ;
}

void	ft_rrr(t_list **stack_a, t_list **stack_b)
{
	t_list	*pre_bottom;
	t_list	*pre_bottom2;
	t_list	*bottom;
	t_list	*bottom2;

	if (!(*stack_b) || !((*stack_b)->next)
		|| !(*stack_a) || !((*stack_a)->next))
		return ;
	pre_bottom = *stack_a;
	while (pre_bottom->next->next != NULL)
		pre_bottom = pre_bottom->next;
	bottom = pre_bottom->next;
	bottom->next = *stack_a;
	*stack_a = bottom;
	pre_bottom->next = NULL;
	pre_bottom2 = *stack_b;
	while (pre_bottom2->next->next != NULL)
		pre_bottom2 = pre_bottom2->next;
	bottom2 = pre_bottom2->next;
	bottom2->next = *stack_b;
	*stack_b = bottom2;
	pre_bottom2->next = NULL;
	return ;
}

int	ft_atoi_stack(const char *str, t_data *data, char **av, char **av_int)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str) == 1)
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	if ((*str != 0 || !ft_isdigit(*(str - 1))) || ((result * sign) < -2147483648 
		|| (result * sign) > 2147483647))
	{
		if (av_int && av[1] != av_int[0])
			ft_free_args(av_int);
		display_error(data, "bad input numbers\n");
	}
	return ((int)(result * sign));
}

void	ft_init_stack(t_data *data, char **av, char **av_int)
{
	int	i;

	i = ft_av_size(av_int) - 1;
	while (i >= 0)
	{
		if (!(data->stack_a))
			data->stack_a = ft_lstnew(ft_atoi_stack(av_int[i], data, av, av_int));
		else
			ft_lstadd_front(&data->stack_a, ft_lstnew(ft_atoi_stack(av_int[i], data, av, av_int)));
		i--;
	}
}

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	getcolor_fromvalue(float_t value, int minvalue, int maxvalue)
{
	int		red;
	int		blue;
	int		green;
	int		midvalue;
	float_t	ratio;

	if (value < minvalue)
		value = minvalue;
	if (value > maxvalue)
		value = maxvalue;
	midvalue = (minvalue + maxvalue) / 2;
	if (value <= midvalue)
	{
		ratio = map(value, minvalue, midvalue, 0.0, 1.0);
		blue = (int)(255 * (1 - ratio));
		green = (int)(255 * ratio);
		red = 0;
	}
	else
	{
		ratio = map(value, midvalue, maxvalue, 0.0, 1.0);
		red = (int)(255 * ratio);
		green = (int)(255 * (1 - ratio));
		blue = 0;
	}
	return (create_color(red, green, blue));
}

int	assign_color(t_data *data, t_list **stack)
{
	t_list	*tmp;

	if (!(*stack))
		display_error(data, "stack does not exist\n");
	tmp = *stack;
	while (tmp != NULL)
	{
		tmp->color = getcolor_fromvalue(tmp->index, 0, data->max_index);
		tmp = tmp->next;
	}
	return (0);
}

int	get_index(t_list **stack, int content)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = *stack;
	while (tmp != NULL)
	{
		if (content > tmp->content)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	assign_index(t_data *data, t_list **stack)
{
	t_list	*tmp;

	if (!(*stack))
		display_error(data, "stack does not exist\n");
	tmp = *stack;
	data->max_index = -1;
	while (tmp != NULL)
	{
		tmp->index = get_index(stack, tmp->content);
		if (data->max_index < tmp->index)
			data->max_index = tmp->index;
		tmp = tmp->next;
	}
	return (0);
}

void	get_operations(t_data *data)
{
	int	i;
	int	fd;
	char	buf[100000];


	fd = open("./result.txt", O_RDONLY);
	i = read(fd, buf, 100000);
	buf[i] = '\0';
	close(fd);
	data->operations = ft_split(buf, '\n');
}

int	start_stack(int ac, char **av, t_data *data)
{
	char	**av_int;

	data->stack_a = NULL;
	data->stack_b = NULL;
	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (1);
	else if (ac == 2)
		av_int = ft_split(av[1], ' ');
	else
		av_int = av + 1;
	ft_init_stack(data, av, av_int);
	if (ft_check_repeat(&data->stack_a))
	{
		if (av_int && av[1] != av_int[0])
			ft_free_args(av_int);
		display_error(data, "repeated numbers\n");
	}
	if (av_int && &av[1] != &av_int[0])
		ft_free_args(av_int);
	assign_index(data, &data->stack_a);
	assign_color(data, &data->stack_a);
	get_operations(data);
	data->space = data->winy / (data->max_index + 1);
	return (0);
}

int	ft_av_size(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	ft_check_repeat(t_list **stack)
{
	t_list	*curr;
	t_list	*run;

	curr = *stack;
	if (!(*stack))
		return (1);
	while (curr)
	{
		run = curr->next;
		while (run)
		{
			if (run->content == curr->content)
				return (1);
			else
				run = run->next;
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_verif_sort(t_list **stack)
{
	t_list	*curr;
	t_list	*run;

	curr = *stack;
	if (!(*stack))
		return (1);
	while (curr)
	{
		run = curr->next;
		while (run)
		{
			if (curr->content > run->content)
				return (0);
			else
				run = run->next;
		}
		curr = curr->next;
	}
	return (1);
}

void	ft_free_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

void	ft_free_stacks(t_list **stack)
{
	t_list	*tmp;

	while ((*stack))
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
	stack = NULL;
}
