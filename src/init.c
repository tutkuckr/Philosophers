/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/09/30 10:57:08 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, int i)
{
	int	left_fork;
	int	right_fork;

	left_fork = i;
	right_fork = (i + 1) % philo->data->num_of_philo;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = right_fork;
		philo->second_fork = left_fork;
	}
	else
	{
		philo->first_fork = left_fork;
		philo->second_fork = right_fork;
	}
}

/// @brief mutexes: m_meal
t_error_type	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!*philo)
		return (error_msg(ERR_MALLOC));
	data->philos = *philo;
	i = -1;
	while (++i < data->num_of_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i;
		assign_forks(&(*philo)[i], i);
		(*philo)[i].meal_count = 0;
		(*philo)[i].is_done_eating = 0;
		(*philo)[i].last_meal_time = get_cur_time();
		if (pthread_mutex_init(&(*philo)[i].m_meal, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philo)[i].m_meal);
			return (free(*philo), *philo = NULL,
				data->philos = NULL, error_msg(ERR_MUTEX));
		}
	}
	data->control.meal = 1;
	return (SUCCESS);
}

static t_error_type	init_m_fork(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[j], NULL) != 0)
		{
			while (--j >= 0)
				pthread_mutex_destroy(&data->forks[j]);
			return (error_msg(ERR_MUTEX));
		}
		j++;
	}
	data->control.fork = 1;
	return (SUCCESS);
}

/// @brief mutexes: m_print, , m_monitor, m_stop, m_fork
t_error_type	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.print = 1;
	if (pthread_mutex_init(&data->m_monitor, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.monitor = 1;
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.stop = 1;
	if (pthread_mutex_init(&data->m_ready, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.ready = 1;
	if (init_m_fork(data) != SUCCESS)
		return (error_msg(ERR_MUTEX));
	return (SUCCESS);
}

t_error_type	init_data(t_data *data, int argc, char *argv[])
{
	t_error_type	status;

	memset(data, 0, sizeof(*data));
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
	if (data->max_eat == 0)
		return (error_msg(ERR_INV_ARGC));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (error_msg(ERR_MALLOC));
	status = init_mutexes(data);
	if (status != SUCCESS)
		return (destroy_mutexes(data), free(data->forks),
			data->forks = NULL, status);
	data->control.mutexes = 1;
	return (SUCCESS);
}
