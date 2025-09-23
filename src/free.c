/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/09/23 16:37:49 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(philo[j].thread, NULL);
		j++;
	}
}

static void	destroy_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo == NULL)
		return ;
	while (i < data->c_thread)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	data->c_thread = 0;
}

void	free_data(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	if (philo && data->c_thread != 0)
		destroy_threads(data, philo);
	if (data->forks)
	{
		while (++i < data->c_fork)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
		data->c_fork = 0;
	}
	if (data->c_print == 1)
		pthread_mutex_destroy(&data->m_print);
	data->c_print = 0;
	pthread_mutex_destroy(&data->m_monitor);
	pthread_mutex_destroy(&data->m_stop);
	free(philo);
}
