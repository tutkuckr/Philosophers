/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:22:42 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/09/26 17:44:41 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error_type	init_m_fork(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[j], NULL) != 0)
		{
			while (--j >= 0)
				pthread_mutex_destroy(&data->forks[j]);
			return (error_msg(ERR_MUTEX));
		}
		j++;
	}
	data->control.fork = 1;
	return (SUCCESS);
}

/// @brief mutexes: m_print, , m_monitor, m_stop, m_fork
t_error_type	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.print = 1;
	if (pthread_mutex_init(&data->m_monitor, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.monitor = 1;
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.stop = 1;
	if (pthread_mutex_init(&data->m_ready, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->control.ready = 1;
	if (init_m_fork(data) != SUCCESS)
		return (error_msg(ERR_MUTEX));
	return (SUCCESS);
}
