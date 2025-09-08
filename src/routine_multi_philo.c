/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:38:10 by tutku             #+#    #+#             */
/*   Updated: 2025/09/08 16:47:01 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// first -> right fork
// second -> left fork

static void	eating_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal_time = get_cur_time();
	pthread_mutex_unlock(&philo->m_meal);
	m_print(philo, "is eating");
	skip_time(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
	pthread_mutex_lock(&philo->m_meal);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_meal);
}

void	handle_multi_philo(t_philo *philo)
{
	if (get_stopper_val(philo->data)) //check if correct
		return ;
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	m_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
	m_print(philo, "has taken a fork");
	eating_routine(philo);
	m_print(philo, "is sleeping");
	skip_time(philo->data->time_to_sleep);
}
