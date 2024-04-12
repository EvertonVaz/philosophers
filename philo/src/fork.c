/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:01:14 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 15:34:47 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	init_fork(int id, int n_philos)
{
	t_fork	fork;

	fork.id = id;
	fork.left = id + 1;
	fork.rigth = id - 1;
	if (fork.id == n_philos)
		fork.left = 1;
	if (fork.id == 1)
		fork.rigth = n_philos;
	pthread_mutex_init(&fork.fork, NULL);
	return (fork);
}

int	lock_fork(t_data *philo, pthread_mutex_t *first, pthread_mutex_t *last)
{
	t_monitor	*monitor;
	long long	t;
	char		*msg;

	msg = "has taken a fork";
	t = philo->start;
	monitor = monitor_address(NULL);
	if (!check_monitor(monitor))
		return (0);
	pthread_mutex_lock(first);
	if (check_philo_alive(philo))
		printf(CYAN "%lld, %d %s\n" END, time_ms(t), philo->id, msg);
	if (philo->n_philos == 1)
		return (usleep(philo->time_to_die * 1000));
	pthread_mutex_lock(last);
	if (check_philo_alive(philo))
		printf(CYAN "%lld, %d %s\n" END, time_ms(t), philo->id, msg);
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
	right = &table[philo->fork.rigth].fork.fork;
	left = &table[philo->fork.id].fork.fork;
	if (philo->id % 2 == 1 && check_philo_alive(philo))
		lock_fork(philo, right, left);
	else if (check_philo_alive(philo))
		lock_fork(philo, left, right);
	return (1);
}
