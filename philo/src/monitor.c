/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:57 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/11 16:25:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_alive(t_data *philo)
{
	t_monitor	*monitor;
	int			is_alive;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	is_alive = time_ms(philo->time_after_eat) < philo->time_to_die;
	pthread_mutex_unlock(&monitor->block);
	if (is_alive)
		return (1);
	return (0);
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
		if (!is_alive(&philos[i]))
		{
			time = time_ms(philos[i].start);
			printf(RED "%lld, %d died\n" END, time, philos[i].id);
			monitor->everyone_is_alive = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate(void)
{
	t_monitor	monitor;
	t_data		philos;
	int			check;

	monitor = *monitor_address(NULL);
	philos = *philosophers(NULL);
	pthread_mutex_lock(&monitor.block);
	check = monitor.max_eat >= philos.n_philos * philos.max_eat;
	pthread_mutex_unlock(&monitor.block);
	if (philos.max_eat > 0 && check)
		return (1);
	usleep(1000);
	return (0);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	t_data		*philos;
	int			i;

	philos = philosophers(NULL);
	monitor = monitor_address(NULL);
	monitor->monitor = pthread_self();
	monitor->everyone_is_alive = 1;
	monitor->max_eat = 0;
	(void)data;
	usleep(1000);
	while (1)
	{
		i = 0;
		if (is_somebody_dead(monitor, i))
			return (NULL);
		if (everyone_ate())
			return (NULL);
	}
	return (NULL);
}
