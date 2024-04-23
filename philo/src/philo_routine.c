/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/23 09:42:15 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	wait_all_philos(t_monitor *monitor, int new_philo, int n_philos)
{
	static int	philo_created;

	pthread_mutex_lock(&monitor->block);
	philo_created += new_philo;
	usleep(100);
	pthread_mutex_unlock(&monitor->block);
	if (philo_created <= n_philos)
		return (0);
	return (1);
}

int	check_philo_alive(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	if (time_ms(philo->time_after_eat) > philo->time_to_die)
		philo->im_dead = 1;
	pthread_mutex_unlock(&monitor->block);
	return (time_ms(philo->time_after_eat) < philo->time_to_die && monitor->everyone_is_alive);
}

void	add_eat(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	philo->time_after_eat = time_ms(0);
	if (check_philo_alive(philo))
	{
		printf(BLUE "%lld, %d is eating\n" END, time_ms(philo->start),
			philo->id);
		pthread_mutex_lock(&monitor->block);
		monitor->everyone_is_ate++;
		pthread_mutex_unlock(&monitor->block);
		philo->n_eat++;
		usleep(philo->time_to_eat * 1000);
		philo->time_after_eat = time_ms(0);
	}
}

void	eating(t_data *philo)
{
	t_data		*table;
	t_monitor	*monitor;
	int			check_eat;
	int			taked;

	taked = 0;
	table = philosophers(NULL);
	monitor = monitor_address(NULL);
	check_eat = (philo->max_eat > 0 && philo->n_eat == philo->max_eat);
	usleep(1000);
	if (!check_monitor(monitor) && (!check_philo_alive(philo) || check_eat))
		return ;
	taked = take_fork(philo, table);
	if (taked && check_philo_alive(philo) && philo->n_philos > 1)
		add_eat(philo);
	if (taked)
	{
		pthread_mutex_unlock(&table[philo->id].mutex);
		if (philo->n_philos > 1)
			pthread_mutex_unlock(&table[philo->rigth].mutex);
	}
}

void	sleeping(t_data *philo)
{
	t_monitor	*monitor;
	long long	time;

	monitor = monitor_address(NULL);
	time = time_ms(philo->start);
	usleep(1000);
	if (!check_monitor(monitor) || !check_philo_alive(philo))
		return ;
	printf(YELLOW "%lld, %d is sleeping\n" END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
