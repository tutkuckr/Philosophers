/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/09/23 20:13:32 by tcakir-y         ###   ########.fr       */
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
	if (philo)
	{
		while (++i < data->num_of_philo)
			pthread_mutex_destroy(&philo[i].m_meal);
		i = -1;
	}
	while (++i < data->c_fork)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	data->forks = NULL;
	
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_ready);
	pthread_mutex_destroy(&data->m_monitor);
	pthread_mutex_destroy(&data->m_stop);
	free(philo);
}
