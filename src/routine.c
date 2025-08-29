/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:55:50 by tutku             #+#    #+#             */
/*   Updated: 2025/08/29 13:56:14 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Even ID: take right then left
Odd ID: take left then right
*/
void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!philo) // to silence compile error
		return (NULL);
	return (NULL);
}
