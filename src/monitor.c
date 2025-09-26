/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:39:42 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/09/26 17:31:11 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// checks every philo for
// is dead, or is all ate

// checks if all philos ate max_eat times
static int	is_done_eating(t_data *data)
{
	int	i;
	int	done_eating;

	i = -1;
	done_eating = 1;
	if (data->max_eat == -1)
		return (0);
	while (++i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].m_meal);
		if (data->philos[i].meal_count < data->max_eat)
			done_eating = 0;
		pthread_mutex_unlock(&data->philos[i].m_meal);
		if (done_eating == 0)
			break ;
	}
	return (done_eating);
}

static int	is_dead(t_data *data)
{
	int				i;
	long long		cur_time;
	long long		last_meal_time;

	i = -1;
	while (++i < data->num_of_philo)
	{
		cur_time = get_cur_time();
		pthread_mutex_lock(&data->philos[i].m_meal);
		last_meal_time = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].m_meal);
		if (cur_time - last_meal_time >= data->time_to_die)
		{
			set_stopper_val(data, 1);
			m_print(&data->philos[i], "died");
			return (1);
		}
	}
	return (0);
}

//monitors deaths or max eats
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (get_ready_val(data) == 0)
		usleep(100);
	while (get_cur_time() < data->start_time)
		usleep(50);
	while (1)
	{
		if (is_dead(data) == 1 || is_done_eating(data) == 1)
		{
			set_stopper_val(data, 1);
			return (NULL);
		}
		usleep(500);
	}
}
