/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:38:10 by tutku             #+#    #+#             */
/*   Updated: 2025/09/23 17:35:46 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//static int	is_done_eating(t_philo *philo)
//{
//	int	done;

//	pthread_mutex_lock(&philo->m_meal);
//	if (philo->data->max_eat == -1)
//		done = philo->is_done_eating;
//	else
//	{
//		if (philo->meal_count >= philo->data->max_eat)
//			philo->is_done_eating = 1;
//		done = philo->is_done_eating;
//	}
//	pthread_mutex_unlock(&philo->m_meal);
//	return (done);
//}

static void	eating_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	m_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->second_fork]);
	m_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal_time = get_cur_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_meal);
	print_and_skip_time(philo, "is eating");
	pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
}

void	handle_multi_philo(t_philo *philo)
{
	while (get_stopper_val(philo->data) != 1)
	{
		eating_routine(philo);
		if (get_stopper_val(philo->data) == 0)
			print_and_skip_time(philo, "is sleeping");
		if (get_stopper_val(philo->data) == 0)
			print_and_skip_time(philo, "is thinking");
	}
}
