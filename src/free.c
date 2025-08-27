/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/08/27 14:39:26 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	destroy_mutex(t_data *data, int i)
{
	if (data->controller)
		pthread_mutex_destroy(data->controller);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
}

void	free_data(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < data->num_of_philo)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->controller)
	{
		pthread_mutex_destroy(data->controller);
		free(data->controller);
		data->controller = NULL;
	}
	free(philo);
	philo = NULL;
}
