/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/23 15:40:06 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	t_monitor		*monitor;
	long long int	time;
	long long int	time_to_die;
	int				result;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	time = time_ms(philo->time_after_eat);
	time_to_die = philo->time_to_die;
	if (time > time_to_die)
		philo->im_dead = 1;
	result = time < time_to_die && monitor->everyone_is_alive;
	pthread_mutex_unlock(&monitor->block);
	return (result);
}

void	add_eat(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	philo->time_after_eat = time_ms(0);
	pthread_mutex_unlock(&monitor->block);
	if (check_philo_alive(philo))
	{
		printf(BLUE "%lld %d is eating\n" END, time_ms(philo->start),
			philo->id);
		pthread_mutex_lock(&monitor->block);
		monitor->everyone_is_ate++;
		philo->n_eat++;
		philo->time_after_eat = time_ms(0);
		pthread_mutex_unlock(&monitor->block);
		usleep(philo->time_to_eat * 1000);
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
	if (!check_monitor(monitor) || !check_philo_alive(philo))
		return ;
	printf(YELLOW "%lld %d is sleeping\n" END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
