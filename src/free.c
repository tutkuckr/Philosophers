/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/09/26 17:44:05 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->control.print == 1)
		pthread_mutex_destroy(&data->m_print);
	if (data->control.ready == 1)
		pthread_mutex_destroy(&data->m_ready);
	if (data->control.monitor == 1)
		pthread_mutex_destroy(&data->m_monitor);
	if (data->control.stop == 1)
		pthread_mutex_destroy(&data->m_stop);
	if (data->control.fork == 1)
	{
		i = -1;
		while (++i < data->num_of_philo)
			pthread_mutex_destroy(&data->forks[i]);
	}
	if (data->control.meal == 1)
	{
		i = -1;
		while (++i < data->num_of_philo)
			pthread_mutex_destroy(&data->philos[i].m_meal);
	}
}

static void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->c_monitor)
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
	if (data->control.mutexes == 0)
	{
		destroy_mutexes(data);
		free(data->forks);
		data->forks = NULL;
		return ;
	}
	if (philo)
		join_threads(data);
	destroy_mutexes(data);
	free(data->forks);
	data->forks = NULL;
	free(philo);
	philo = NULL;
}
