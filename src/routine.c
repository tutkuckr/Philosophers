/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/25 10:58:04 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	int	first;

	if (get_stopper_val(philo->data))
		return ;
	first = 0;
	pthread_mutex_lock(&philo->data->forks[first]);
	m_print(philo, "has taken a fork");
	skip_time(philo->data, philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[first]);
}

static void	eating_routine(t_philo *philo)
{
	if (get_stopper_val(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	m_print(philo, "has taken a fork");
	if (get_stopper_val(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		return ;
	}
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

static void	handle_multi_philo(t_philo *philo)
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

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_ready_val(philo->data) == 0)
		usleep(100);
	if ((philo->id % 2) == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal_time = get_cur_time();
	philo->data->start_time = get_cur_time();
	pthread_mutex_unlock(&philo->m_meal);
	print_and_skip_time(philo, "is thinking");
	if (philo->data->num_of_philo == 1)
		handle_single_philo(philo);
	else
		handle_multi_philo(philo);
	return (NULL);
}

t_error_type	start_threads(t_data *data, t_philo *philo)
{
	pthread_t	t_monitor;
	int			i;

	i = -1;
	data->start_time = get_cur_time() + 100;
	while (++i < data->num_of_philo)
	{
		if (pthread_create((&philo[i].thread), NULL, routine, &philo[i]) != 0)
		{
			join_threads(philo, i);
			return (data->c_thread = 0, error_msg(ERR_THREAD));
		}
		data->c_thread++;
	}
	set_ready_val(data, 1);
	if (pthread_create(&t_monitor, NULL, monitor_routine, data) != 0)
	{
		join_threads(philo, data->num_of_philo);
		return (data->c_thread = 0, error_msg(ERR_THREAD));
	}
	pthread_join(t_monitor, NULL);
	join_threads(philo, data->num_of_philo);
	data->c_thread = 0;
	return (SUCCESS);
}
