/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/08/19 14:51:35 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error_type	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!*philo)
		return (error_msg(ERR_MALLOC));
	i = 0;
	while (i < data->num_of_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->num_of_philo;
		i++;
	}
	return (SUCCESS);
}

t_error_type	init_data(t_data *data, int argc, char *argv[])
{
	data->num_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->num_of_philo <= 0 || data->num_of_philo > 200)
		return (error_msg(ERR_PHILO_AMOUNT));
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	return (SUCCESS);
}
