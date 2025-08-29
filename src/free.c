/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:20:48 by tutku             #+#    #+#             */
/*   Updated: 2025/08/29 17:08:16 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static void	destroy_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo == NULL)
		return ;
	while (i < data->t_started)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	data->t_started = 0;
}

void	free_data(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	if (philo && data->t_started != 0)
		destroy_threads(data, philo);
	if (data->forks)
	{
		while (++i < data->f_started)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
		data->f_started = 0;
	}
	if (data->c_inited == 1)
		pthread_mutex_destroy(&data->controller);
	data->c_inited = 0;
	free(philo);
}
