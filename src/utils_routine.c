/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:08:24 by tutku             #+#    #+#             */
/*   Updated: 2025/09/23 18:13:00 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// // tell all threads to exit
// // (if one dies or all eats enough)
void	set_stopper_val(t_data *data, int val)
{
	pthread_mutex_lock(&data->m_stop);
	data->c_stop = val;
	pthread_mutex_unlock(&data->m_stop);
}

int	get_stopper_val(t_data *data)
{
	int	stopper;

	pthread_mutex_lock(&data->m_stop);
	stopper = data->c_stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stopper);
}

int	get_ready_val(t_data *data)
{
	int	ready;

	pthread_mutex_lock(&data->m_ready);
	ready = data->ready;
	pthread_mutex_unlock(&data->m_ready);
	return (ready);
}

void	set_ready_val(t_data *data, int val)
{
	pthread_mutex_lock(&data->m_ready);
	data->ready = val;
	pthread_mutex_unlock(&data->m_ready);
}