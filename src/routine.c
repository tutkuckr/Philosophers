/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/13 15:12:38 by tutku            ###   ########.fr       */
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
void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		usleep(200);
	if (get_stopper_val(philo->data) != 1)
		m_print(philo, "is thinking");
	start_taking_forks(philo);

	return (NULL);
}
