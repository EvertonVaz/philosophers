/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/24 13:56:34 by egeraldo         ###   ########.fr       */
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
	pthread_mutex_lock(&monitor->alive);
	time = time_ms(philo->time_after_eat);
	time_to_die = philo->time_to_die;
	result = (time < time_to_die && monitor->everyone_is_alive);
	pthread_mutex_unlock(&monitor->alive);
	return (result);
}

void	add_eat(t_data *philo)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->alive);
	philo->time_after_eat = time_ms(0);
	pthread_mutex_unlock(&monitor->alive);
	if (check_philo_alive(philo))
	{
		print_logs(philo, EATING);
		pthread_mutex_lock(&monitor->alive);
		monitor->everyone_is_ate++;
		philo->n_eat++;
		philo->time_after_eat = time_ms(0);
		pthread_mutex_unlock(&monitor->alive);
		usleep(philo->time_to_eat * 1000);
	}
}

void	eating(t_data *philo)
{
	t_data	*table;
	int		taked;

	table = philosophers(NULL);
	taked = take_fork(philo);
	if (taked && check_philo_alive(philo) && philo->n_philos > 1)
		add_eat(philo);
	if (taked || philo->n_philos == 1)
	{
		pthread_mutex_unlock(&table[philo->rigth - 1].mutex);
		if (philo->n_philos > 1)
			pthread_mutex_unlock(&table[philo->id - 1].mutex);
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
	print_logs(philo, SLEEPING);
	usleep(philo->time_to_sleep * 1000);
}
