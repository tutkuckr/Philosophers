/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/09/02 16:54:32 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error_type	start_threads(t_data *data, t_philo *philo)
{
	int	i;
	int j;

	data->c_thread = 0;
	i = 0;
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
	data->ready = 1;
	return (SUCCESS);
}

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
			return (error_msg(ERR_MUTEX));
		}
	}
	return (SUCCESS);
}

t_error_type	init_mutexes(t_data *data)
{
	int	j;

	if (pthread_mutex_init(&data->controller, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->c_controller = 1;
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (error_msg(ERR_MUTEX)); //free previous mutex?
	data->c_stop = 1;
	data->stopper = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (error_msg(ERR_MALLOC));
	data->c_fork = 0;
	while (data->c_fork < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[data->c_fork], NULL) != 0)
		{
			j = -1;
			while (++j < data->c_fork)
				pthread_mutex_destroy(&data->forks[j]);
			return (error_msg(ERR_MUTEX)); // should i destroy other mutexes here?
		}
		data->c_fork++;
	}
	return (SUCCESS);
}

t_error_type	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(*data));
	data->num_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->start_time = get_cur_time();
	// data->ready = 0;
	if (data->num_of_philo <= 0 || data->num_of_philo > 200)
		return (error_msg(ERR_PHILO_AMOUNT));
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	return (SUCCESS);
}
