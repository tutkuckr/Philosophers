/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:38:10 by tutku             #+#    #+#             */
/*   Updated: 2025/09/05 16:04:58 by tutku            ###   ########.fr       */
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

static void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
	else
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	m_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
	m_print(philo, "has taken a fork");
}

void	handle_multi_philo(t_philo *philo)
{
	
	pick_up_forks(philo);
	eating_routine(philo);
	m_print(philo, "is sleeping");
	skip_time(philo->data->time_to_sleep);

}
