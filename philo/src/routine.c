/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/10 15:02:40 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_data *philo)
{
	long long	time;
	t_data		*philos;

	philos = philosophers(NULL);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philos[philo->fork.rigth].fork.fork);
		pthread_mutex_lock(&philos[philo->fork.id].fork.fork);
		philo->time_after_eat = get_time_ms(0);
	}
	else
	{
		pthread_mutex_lock(&philos[philo->fork.id].fork.fork);
		pthread_mutex_lock(&philos[philo->fork.rigth].fork.fork);
		philo->time_after_eat = get_time_ms(0);
	}
	time = get_time_ms(philo->start);
	printf(BLUE"%lld, philosopher %d eating\n"END, time, philo->id);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philos[philo->fork.id].fork.fork);
	pthread_mutex_unlock(&philos[philo->fork.rigth].fork.fork);
}

void	sleeping(t_data *philo)
{
	long long	start_sleeping;
	long long	time;

	time = get_time_ms(philo->start);
	start_sleeping = get_time_ms(0);
	printf(CYAN"%lld, philosopher %d sleeping\n"END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
