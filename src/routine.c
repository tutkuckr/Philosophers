/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/03 14:46:52 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// first -> right fork
// second -> left fork

static void	handle_single_philo(t_philo *philo)
{
	int first;

	first = philo->right_fork;
	pthread_mutex_lock(&philo->data->forks[first]);
	controller_print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->forks[first]);
	skip_time(philo->data->time_to_die);
	controller_print(philo, "died");
	set_stopper_val(philo->data, 1);
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
void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// if (philo->data->ready != 1)
	// 	usleep(200);
	if ((philo->id % 2) == 0)
		usleep(200);
	while(get_stopper_val(philo->data) != 1) // TODO: maybe change into monitor
	{
		controller_print(philo, "is thinking");
		start_taking_forks(philo);
	}
	return (NULL);
}
