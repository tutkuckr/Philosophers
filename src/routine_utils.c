/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:08:24 by tutku             #+#    #+#             */
/*   Updated: 2025/09/03 11:54:12 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// tell all threads to exit
// (if one dies or all eats enough)
void	set_stopper_val(t_data *data, int val)
{
	pthread_mutex_lock(&data->m_stop);
	data->c_stop = val;
	pthread_mutex_unlock(&data->m_stop);
}

int	get_stopper_val(t_data *data)
{
	int stopper;

	pthread_mutex_lock(&data->m_stop);
	/// TODO: add checker for death or all ate condition
	stopper = data->c_stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stopper);
}
