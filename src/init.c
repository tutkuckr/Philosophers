/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/09/16 16:55:29 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
	else
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
}

/// @brief mutexes: m_meal
t_error_type	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!*philo)
		return (error_msg(ERR_MALLOC));
	i = -1;
	while (++i < data->num_of_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->num_of_philo;
		assign_forks(&(*philo)[i]);
		(*philo)[i].meal_count = 0;
		(*philo)[i].is_done_eating = 0;
		(*philo)[i].last_meal_time = data->start_time;
		if (pthread_mutex_init(&(*philo)[i].m_meal, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philo)[i].m_meal);
			return (free(*philo), error_msg(ERR_MUTEX));
		}
	}
	data->philos = *philo;
	return (SUCCESS);
}

t_error_type	init_m_fork(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[j], NULL) != 0)
		{
			while (--j >= 0)
				pthread_mutex_destroy(&data->forks[j]);
			data->c_fork = 0;
			return (error_msg(ERR_MUTEX));
		}
		j++;
	}
	data->c_fork = data->num_of_philo;
	return (SUCCESS);
}

/// @brief mutexes: m_print, , m_monitor, m_stop, m_fork
t_error_type	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->c_print = 1;
	if (pthread_mutex_init(&data->m_monitor, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print),
			data->c_print = 0, error_msg(ERR_MUTEX));
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print),
			pthread_mutex_destroy(&data->m_monitor),
			data->c_print = 0, error_msg(ERR_MUTEX));
	if (pthread_mutex_init(&data->m_is_dead, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print),
			pthread_mutex_destroy(&data->m_monitor),
			pthread_mutex_destroy(&data->m_stop),
			data->c_print = 0, error_msg(ERR_MUTEX));
	if (init_m_fork(data) != SUCCESS)
	{
		return (pthread_mutex_destroy(&data->m_print),
			pthread_mutex_destroy(&data->m_monitor),
			pthread_mutex_destroy(&data->m_stop),
			pthread_mutex_destroy(&data->m_is_dead),
			data->c_print = 0, error_msg(ERR_MUTEX));
	}
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
	data->start_time = get_cur_time();
	if (data->num_of_philo <= 0 || data->num_of_philo > 200)
		return (error_msg(ERR_PHILO_AMOUNT));
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (error_msg(ERR_MALLOC));
	status = init_mutexes(data);
	if (status != SUCCESS)
		return (free(data->forks), status);
	return (SUCCESS);
}
