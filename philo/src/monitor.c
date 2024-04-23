/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:57 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/23 14:09:23 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_data *philo)
{
	int			is_dead;
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->block);
	is_dead = time_ms(philo->time_after_eat) > philo->time_to_die;
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

int	is_somebody_dead(t_monitor *monitor)
{
	t_data		*table;
	long long	time;
	int			id;
	int			i;

	table = philosophers(NULL);
	i = 0;
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
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate(t_monitor *monitor)
{
	int	ate;

	pthread_mutex_lock(&monitor->block);
	ate = monitor->everyone_is_ate;
	pthread_mutex_unlock(&monitor->block);
	return (monitor->max_eat > 0 && ate >= monitor->max_eat);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	t_data		*table;
	int			wait;

	table = philosophers(NULL);
	monitor = monitor_address(NULL);
	monitor->everyone_is_ate = 0;
	pthread_mutex_lock(&monitor->block);
	monitor->everyone_is_alive = 1;
	wait = table[0].time_to_die / table[0].n_philos;
	monitor->max_eat = table->max_eat * table->n_philos;
	pthread_mutex_unlock(&monitor->block);
	(void)data;
	while (1)
	{
		usleep(wait);
		if (is_somebody_dead(monitor))
			return (NULL);
		if (everyone_ate(monitor))
			return (NULL);
	}
	return (NULL);
}
