/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/09/26 13:32:47 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_ready);
	pthread_mutex_destroy(&data->m_monitor);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_thread);
	i = -1;
	while (++i < data->c_fork)
		pthread_mutex_destroy(&data->forks[i]);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->philos[i].m_meal);
	free(data->forks);
	data->forks = NULL;
}

//static	void join_monitor(t_data *data)

static void	join_threads(t_data *data)
{
	int	i;
	int	c_monitor;
	int	c_thread;

	pthread_mutex_lock(&data->m_monitor);
	c_monitor = data->c_monitor;
	pthread_mutex_unlock(&data->m_monitor);
	if (c_monitor == 1)
	{
		pthread_join(data->t_monitor, NULL);
		pthread_mutex_lock(&data->m_monitor);
		 data->c_monitor = 0;
		pthread_mutex_unlock(&data->m_monitor);
	}
	pthread_mutex_lock(&data->m_thread);
	c_thread = data->c_thread;
	pthread_mutex_unlock(&data->m_thread);
	if (c_thread != 0)
	{	
		i = -1;
		while (++i < data->num_of_philo)
		{
			if (data->philos[i].started)
			{
				pthread_join(data->philos[i].thread, NULL);
				data->philos[i].started = 0;
			}
		}
		pthread_mutex_lock(&data->m_thread);
		data->c_thread = 0;
		pthread_mutex_unlock(&data->m_thread);
	}
}


void	free_data(t_data *data, t_philo *philo)
{
	join_threads(data);
	destroy_mutexes(data);
	free(philo);
	philo = NULL;
}

/*
if all works;
at the end free:
. forks malloc
. m_print, m_monitor, m_stop, m_ready
. philo
. 
*/