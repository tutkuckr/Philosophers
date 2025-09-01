/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/01 15:43:06 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// first -> right fork
// second -> left fork

void	eating_routine(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	controller_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	controller_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal_time = get_cur_time();
	pthread_mutex_unlock(&philo->m_meal);
	controller_print(philo, "is eating");
	skip_time(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
}

static void	handle_multi_philo(t_philo *philo)
{
	eating_routine(philo);
	controller_print(philo, "is sleeping");
	skip_time(philo->data->time_to_sleep);
}

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
	if ((philo->id % 2) == 0)
		usleep(200);
	philo->last_meal_time = get_cur_time();
	while(get_stopper_val(philo->data) == 0)
	{
		controller_print(philo, "is thinking");
		start_taking_forks(philo);
	}
	return (NULL);
}
