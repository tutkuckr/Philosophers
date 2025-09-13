/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/09/13 14:29:02 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void join_threads(t_philo *philo, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		pthread_join(philo[j].thread, NULL);
		j++;
	}
}

t_error_type	start_threads(t_data *data, t_philo *philo)
{
	pthread_t	t_monitor;
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create((&philo[i].thread), NULL, routine, &philo[i]) != 0)
		{
			join_threads(philo, i);
			return (error_msg(ERR_THREAD));
		}
		data->c_thread++;
	}
	if (pthread_create(&t_monitor, NULL, monitor_routine, data) != 0)
	{
		join_threads(philo, data->num_of_philo);
		return (error_msg(ERR_THREAD));
	}
	pthread_join(t_monitor, NULL);
	return (SUCCESS);
}

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
		assign_forks(&(*philo)[i]);
		if (pthread_mutex_init(&(*philo)[i].m_meal, NULL) != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(*philo)[j].m_meal);
			return (free(*philo), error_msg(ERR_MUTEX));
		}
	}
	data->philos = *philo;
	return (SUCCESS);
}

//TODO move fork mutex init loop here!
// t_error_type init_m_fork()
// {

// }

/// @brief mutexes: m_print, , m_monitor, m_stop, m_fork
t_error_type	init_mutexes(t_data *data)
{
	int	j;

	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->c_print = 1;//check if needed
	if (pthread_mutex_init(&data->m_monitor, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print), error_msg(ERR_MUTEX));
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print),
			pthread_mutex_destroy(&data->m_monitor),error_msg(ERR_MUTEX));
	if (pthread_mutex_init(&data->m_is_dead, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_print),
				pthread_mutex_destroy(&data->m_monitor),
				pthread_mutex_destroy(&data->m_stop), error_msg(ERR_MUTEX));
	while (data->c_fork < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[data->c_fork], NULL) != 0)
		{
			j = -1;
			while (++j < data->c_fork)
				pthread_mutex_destroy(&data->forks[j]);
			pthread_mutex_destroy(&data->m_print);
			pthread_mutex_destroy(&data->m_monitor);
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
	data->start_time = get_cur_time(); // TODO: check what to use for
	// data->c_fork = 0; //already 0 because of memset?
	// data->stopper = 0;
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
