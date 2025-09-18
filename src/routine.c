/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/18 15:33:08 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// first -> right fork
// second -> left fork

static void	handle_single_philo(t_philo *philo)
{
	int	first;

	if (get_stopper_val(philo->data))
		return ;
	first = philo->right_fork;
	pthread_mutex_lock(&philo->data->forks[first]);
	m_print(philo, "has taken a fork");
	skip_time(philo->data, philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[first]);
}

void	start_taking_forks(t_philo *philo)
{
	if (philo->data->num_of_philo == 1)
		handle_single_philo(philo);
	else
		handle_multi_philo(philo);
}

/*
Even ID: take right then left
Odd ID: take left then right
*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->c_thread != philo->data->num_of_philo) //loop to wait for all threads
		usleep(10);
	philo->data->start_time = get_cur_time(); //added new, test later
	if ((philo->id % 2) == 0)
		usleep(200);
	if (get_stopper_val(philo->data) != 1)
		print_and_skip_time(philo, "is thinking");
	start_taking_forks(philo);
	return (NULL);
}

t_error_type	start_threads(t_data *data, t_philo *philo)
{
	pthread_t	t_monitor;
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create((&philo[i].thread), NULL, routine, &philo[i]) != 0)
		{
			join_threads(philo, i);
			data->c_thread = 0;
			return (error_msg(ERR_THREAD));
		}
		data->c_thread++;
	}
	if (pthread_create(&t_monitor, NULL, monitor_routine, data) != 0)
	{
		join_threads(philo, data->num_of_philo);
		data->c_thread = 0;
		return (error_msg(ERR_THREAD));
	}
	pthread_join(t_monitor, NULL);
	join_threads(philo, data->num_of_philo);
	data->c_thread = 0;
	return (SUCCESS);
}
