/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:01:14 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 14:00:00 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lock_fork(t_data *philo, pthread_mutex_t *first, pthread_mutex_t *last)
{
	if (check_philo_alive(philo))
	{
		pthread_mutex_lock(first);
		if (check_philo_alive(philo))
			print_logs(philo, TAKE_FORK);
		if (philo->n_philos == 1)
		{
			usleep(philo->time_to_die * 1000);
			return (0);
		}
		pthread_mutex_lock(last);
		if (check_philo_alive(philo))
			print_logs(philo, TAKE_FORK);
		return (1);
	}
	return (0);
}

int	take_fork(t_data *philo)
{
	t_data			*table;
	t_monitor		*monitor;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;

	monitor = monitor_address(NULL);
	table = philosophers(NULL);
	if (!check_monitor(monitor))
		return (0);
	right = &table[philo->rigth - 1].mutex;
	left = &table[philo->id - 1].mutex;
	if (philo->id % 2 == 1 && check_philo_alive(philo))
		return (lock_fork(philo, right, left));
	else if (check_philo_alive(philo))
	{
		usleep(philo->time_to_eat);
		return (lock_fork(philo, left, right));
	}
	return (0);
}
