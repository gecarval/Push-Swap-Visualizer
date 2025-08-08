/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:37:31 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/24 18:40:17 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

void	create_visualizer(t_data *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	if (start_stack(ac, av, data) == 1)
		display_error(data, "no inputs\n");
	data->operation_n = ft_itoa(ft_av_size(data->operations));
}
