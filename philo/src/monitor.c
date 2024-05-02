/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:57 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/25 21:47:26 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_data *philo)
{
	int			is_dead;
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->alive);
	is_dead = time_ms(philo->time_after_eat) > philo->time_to_die;
	pthread_mutex_unlock(&monitor->alive);
	return (is_dead);
}

int	is_somebody_dead(t_monitor *monitor)
{
	t_data		*table;
	int			i;

	table = philosophers(NULL);
	i = 0;
	while (i < table[0].n_philos)
	{
		if (is_dead(&table[i]))
		{
			pthread_mutex_lock(&monitor->alive);
			monitor->everyone_is_alive = 0;
			print_logs(&table[i], DIED);
			pthread_mutex_unlock(&monitor->alive);
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate(t_monitor *monitor)
{
	int	ate;

	pthread_mutex_lock(&monitor->alive);
	ate = monitor->everyone_is_ate;
	pthread_mutex_unlock(&monitor->alive);
	return (monitor->max_eat > 0 && ate >= monitor->max_eat);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	(void)data;
	while (1)
	{
		usleep(200);
		if (is_somebody_dead(monitor))
			return (NULL);
		if (everyone_ate(monitor))
			return (NULL);
	}
	return (NULL);
}
