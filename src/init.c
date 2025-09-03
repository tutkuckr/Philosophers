/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/09/03 14:39:33 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// TODO: create a monitoring thread and check for deaths!!!
t_error_type	start_threads(t_data *data, t_philo *philo)
{
	int	i;
	int j;

	data->c_thread = 0;
	i = 0;
	if (pthread_create((&philo->data->monitor), NULL, monitor, philo) != 0) //check, monitor thread
	{
		return (error_msg(ERR_THREAD));
	}
	while (i < data->num_of_philo)
	{
		if (pthread_create((&philo[i].thread), NULL, routine, (&philo[i])) != 0)
		{
			j = -1;
			while (++j < data->c_thread)
				pthread_join(philo[i].thread, NULL);
			data->c_thread = 0;
			return (error_msg(ERR_THREAD));
		}
		i++;
		data->c_thread++;
	}
	//data->ready = 1;
	return (SUCCESS);
}

/// @brief mutexes: m_meal
t_error_type	init_philo(t_data *data, t_philo **philo)
{
	int	i;
	int	j;

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
		if(pthread_mutex_init(&(*philo)[i].m_meal, NULL) != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(*philo)[j].m_meal);
			return (free(philo), error_msg(ERR_MUTEX));
		}
	}
	return (SUCCESS);
}

/// @brief mutexes: m_controller, m_stop, m_fork
t_error_type	init_mutexes(t_data *data)
{
	int	j;

	if (pthread_mutex_init(&data->controller, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->c_controller = 1;
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (pthread_mutex_destroy(&data->controller), error_msg(ERR_MUTEX));
	data->c_stop = 1;
	while (data->c_fork < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[data->c_fork], NULL) != 0)
		{
			j = -1;
			while (++j < data->c_fork)
				pthread_mutex_destroy(&data->forks[j]);
			pthread_mutex_destroy(&data->controller);
			pthread_mutex_destroy(&data->m_stop);
			return (error_msg(ERR_MUTEX));
		}
		data->c_fork++;
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
	data->c_fork = 0;
	data->stopper = 0;
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
