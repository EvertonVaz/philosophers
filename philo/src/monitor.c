/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:57 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/13 21:50:48 by etovaz           ###   ########.fr       */
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
	t_data		*table;
	long long	time;
	int			id;

	table = philosophers(NULL);
	while (i < table[0].n_philos)
	{
		if (is_dead(&table[i]))
		{
			pthread_mutex_lock(&monitor->block);
			monitor->everyone_is_alive = 0;
			time = time_ms(table[i].start);
			id = table[i].id;
			printf(RED "%lld, %d died\n" END, time, id);
			pthread_mutex_unlock(&monitor->block);
			usleep(1000);
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate(t_monitor *monitor)
{
	int ate;
	pthread_mutex_lock(&monitor->block);
	ate = monitor->everyone_is_ate;
	pthread_mutex_unlock(&monitor->block);
	return (monitor->max_eat > 0 && ate >= monitor->max_eat);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	t_data		*table;
	int			i;

	table = philosophers(NULL);
	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	monitor->everyone_is_alive = 1;
	pthread_mutex_unlock(&monitor->block);
	monitor->max_eat = table->max_eat * table->n_philos;
	(void)data;
	while (wait_all_philos(monitor, 0, table->n_philos))
		usleep(5000);
	while (1)
	{
		i = 0;
		if (is_somebody_dead(monitor, i))
			return (NULL);
		if (everyone_ate(monitor))
			return (NULL);
	}
	return (NULL);
}
