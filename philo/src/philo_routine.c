/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/12 15:28:13 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	if (time_ms(philo->time_after_eat) > philo->time_to_die)
		philo->im_dead = 1;
	pthread_mutex_unlock(&monitor->block);
	return (time_ms(philo->time_after_eat) < philo->time_to_die);
}

void	add_eat(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);

	if (!check_monitor(monitor))
		return ;
	philo->time_after_eat = time_ms(0);
	printf(BLUE "%lld, %d is eating\n" END, time_ms(philo->start), philo->id);
	philo->n_eat++;
	usleep(philo->time_to_eat * 1000);
	philo->time_after_eat = time_ms(0);
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
	if (!check_monitor(monitor) && (!check_philo_alive(philo) || check_eat))
		return ;
	taked = take_fork(philo, table);
	if (check_philo_alive(philo) && philo->n_philos > 1)
		add_eat(philo);
	if (taked)
	{
		pthread_mutex_unlock(&table[philo->fork.id].fork.fork);
		pthread_mutex_unlock(&table[philo->fork.rigth].fork.fork);
	}
}

void	sleeping(t_data *philo)
{
	t_monitor	*monitor;
	long long	time;

	monitor = monitor_address(NULL);
	time = time_ms(philo->start);
	if (!check_monitor(monitor) || !check_philo_alive(philo))
		return ;
	printf(YELLOW "%lld, %d is sleeping\n" END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
