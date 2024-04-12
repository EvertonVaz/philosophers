/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:57 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 13:09:27 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_data *philo)
{
	int			is_dead;
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	is_dead = philo->im_dead;
	pthread_mutex_unlock(&monitor->block);
	return (is_dead);
}

t_monitor	*monitor_address(t_monitor *monitor)
{
	static t_monitor	*m;

	if (!m)
		m = monitor;
	return (m);
}

int	is_somebody_dead(t_monitor *monitor, int i)
{
	t_data		*philos;
	long long	time;

	philos = philosophers(NULL);
	while (i < philos[0].n_philos)
	{
		if (is_dead(&philos[i]))
		{
			usleep(1500);
			time = time_ms(philos[i].start);
			printf(RED "%lld, %d died\n" END, time, philos[i].id);
			pthread_mutex_lock(&monitor->block);
			monitor->everyone_is_alive = 0;
			pthread_mutex_unlock(&monitor->block);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	t_data		*philos;
	int			i;

	philos = philosophers(NULL);
	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	monitor->everyone_is_alive = 1;
	pthread_mutex_unlock(&monitor->block);
	monitor->max_eat = 0;
	(void)data;
	usleep(1000);
	while (1)
	{
		i = 0;
		if (is_somebody_dead(monitor, i))
			return (NULL);
	}
	return (NULL);
}