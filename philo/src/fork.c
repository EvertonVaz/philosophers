/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:01:14 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/23 10:35:56 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lock_fork(t_data *philo, pthread_mutex_t *first, pthread_mutex_t *last)
{
	t_monitor	*monitor;
	long long	t;
	char		*msg;

	msg = "has taken a fork";
	t = philo->start;
	monitor = monitor_address(NULL);
	if (check_monitor(monitor))
	{
		pthread_mutex_lock(first);
		if (check_philo_alive(philo))
			printf(CYAN "%lld, %d %s\n" END, time_ms(t), philo->id, msg);
		if (philo->n_philos == 1)
		{
			usleep(philo->time_to_die * 1000);
			return (0);
		}
		pthread_mutex_lock(last);
		if (check_philo_alive(philo))
			printf(CYAN "%lld, %d %s\n" END, time_ms(t), philo->id, msg);
		return (1);
	}
	return (0);
}

int	take_fork(t_data *philo, t_data *table)
{
	t_monitor		*monitor;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;

	monitor = monitor_address(NULL);
	if (!monitor->everyone_is_alive)
		return (0);
	right = &table[philo->rigth].mutex;
	left = &table[philo->id].mutex;
	if (philo->id % 2 == 1 && check_philo_alive(philo))
		return (lock_fork(philo, right, left));
	else if (check_philo_alive(philo))
	{
		usleep(philo->time_to_eat * 10);
		return (lock_fork(philo, left, right));
	}
	return (0);
}
