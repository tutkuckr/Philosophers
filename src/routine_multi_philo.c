/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_multi_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:38:10 by tutku             #+#    #+#             */
/*   Updated: 2025/09/13 14:53:09 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

void	print_and_skip_time(t_philo *philo, char *message)
{
	if (ft_strcmp(message, "is sleeping") == 0)
	{
		m_print(philo, "is sleeping");
		skip_time(philo->data, philo->data->time_to_sleep);
	}
	else if (ft_strcmp(message, "is thinking") == 0)
	{
		m_print(philo, "is thinking");
		if (philo->data->num_of_philo % 2 && philo->id == philo->data->num_of_philo - 1) //check if correct
			usleep(1000);
	}
	else if (ft_strcmp(message, "is eating") == 0)
	{
		m_print(philo, "is eating");
		skip_time(philo->data, philo->data->time_to_eat);
	}
}

// first -> right fork
// second -> left fork

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

// static int	is_dead(t_philo *philo)
// {
// 	int	dead;

// 	pthread_mutex_lock(&philo->data->m_is_dead);
// 	dead = philo->data->is_dead;
// 	pthread_mutex_unlock(&philo->data->m_is_dead);
// 	return (dead);
// }

static int	is_done_eating(t_philo *philo)
{
	if (philo->data->max_eat == -1)
		return (philo->is_done_eating);
	if (philo->meal_count == philo->data->max_eat)
	{
		pthread_mutex_lock(&philo->m_meal);
		philo->is_done_eating = 1;
		pthread_mutex_unlock(&philo->m_meal);
	}
	return (philo->is_done_eating);
}

void	handle_multi_philo(t_philo *philo)
{
	print_and_skip_time(philo, "is sleeping");
	while (get_stopper_val(philo->data) != 1)
	{
		eating_routine(philo);
		if (is_done_eating(philo) == 1)
			return ;
		if (get_stopper_val(philo->data) == 0)
			print_and_skip_time(philo, "is sleeping");
		if (get_stopper_val(philo->data) == 0)
			print_and_skip_time(philo, "is thinking");
	}
}
