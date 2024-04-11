/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/11 14:59:51 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork(t_data *philo, t_data *philos, char *msg, long long st)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	if (philo->id % 2 == 1 && check_monitor(*monitor))
	{
		pthread_mutex_lock(&philos[philo->fork.rigth].fork.fork);
		if (check_monitor(*monitor))
			printf(CYAN "%lld, %d %s\n" END, time_ms(st), philo->id, msg);
		if (philo->n_philos == 1)
			return (usleep(philo->time_to_die * 1000));
		pthread_mutex_lock(&philos[philo->fork.id].fork.fork);
		if (check_monitor(*monitor))
			printf(CYAN "%lld, %d %s\n" END, time_ms(st), philo->id, msg);
	}
	else if (check_monitor(*monitor))
	{
		pthread_mutex_lock(&philos[philo->fork.id].fork.fork);
		if (check_monitor(*monitor))
			printf(CYAN "%lld, %d %s\n" END, time_ms(st), philo->id, msg);
		pthread_mutex_lock(&philos[philo->fork.rigth].fork.fork);
		if (check_monitor(*monitor))
			printf(CYAN "%lld, %d %s\n" END, time_ms(st), philo->id, msg);
	}
	return (0);
}

void	add_eat(void)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	monitor->max_eat++;
	pthread_mutex_unlock(&monitor->block);
}

void	eating(t_data *philo)
{
	long long	time;
	t_data		*philos;
	t_monitor	*monitor;

	philos = philosophers(NULL);
	monitor = monitor_address(NULL);
	if (!check_monitor(*monitor))
		return ;
	take_fork(philo, philos, "has taken a fork", philo->start);
	philo->time_after_eat = time_ms(0);
	time = time_ms(philo->start);
	if (check_monitor(*monitor) && philo->n_philos > 1)
	{
		printf(BLUE "%lld, %d is eating\n" END, time, philo->id);
		add_eat();
		usleep(philo->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philos[philo->fork.id].fork.fork);
	pthread_mutex_unlock(&philos[philo->fork.rigth].fork.fork);
}

void	sleeping(t_data *philo)
{
	t_monitor	*monitor;
	long long	start_sleeping;
	long long	time;

	monitor = monitor_address(NULL);
	time = time_ms(philo->start);
	start_sleeping = time_ms(0);
	if (!check_monitor(*monitor))
		return ;
	printf(YELLOW "%lld, %d is sleeping\n" END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
