/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/09/26 15:01:31 by tcakir-y         ###   ########.fr       */
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

static void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	pthread_join(data->t_monitor, NULL);
	if (data->c_thread != 0)
	{	
		while (++i < data->c_thread)
			pthread_join(data->philos[i].thread, NULL);
		data->c_thread = 0;
	}
}

void	free_data(t_data *data, t_philo *philo)
{
	if (philo)
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