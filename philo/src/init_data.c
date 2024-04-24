/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:22:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 11:32:57 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_monitor	*monitor_address(t_monitor *monitor)
{
	static t_monitor	*m;

	if (!m)
		m = monitor;
	return (m);
}

t_monitor	*init_monitor(void)
{
	t_monitor	*monitor;
	t_data		*table;

	table = philosophers(NULL);
	monitor = malloc(1 * sizeof(t_monitor));
	pthread_mutex_init(&monitor->alive, NULL);
	pthread_mutex_init(&monitor->print, NULL);
	pthread_mutex_init(&monitor->alive, NULL);
	pthread_mutex_lock(&monitor->alive);
	monitor->max_eat = table->max_eat * table->n_philos;
	pthread_mutex_unlock(&monitor->alive);
	monitor->everyone_is_ate = 0;
	monitor->everyone_is_alive = 1;
	return (monitor_address(monitor));
}

t_data	*philosophers(t_data *table)
{
	static t_data	*philosophers;

	if (!philosophers)
		philosophers = table;
	return (philosophers);
}

t_data	*init_data(char **argv, int n_philos, long long start)
{
	t_data	*table;
	int		i;

	i = 0;
	table = malloc(n_philos * sizeof(t_data));
	while (i < n_philos)
	{
		table[i].n_philos = n_philos;
		table[i].start = start;
		table[i].id = i + 1;
		table[i].time_to_die = ft_atol(argv[0]);
		table[i].time_to_eat = ft_atol(argv[1]);
		table[i].time_to_sleep = ft_atol(argv[2]);
		table[i].max_eat = ft_atol(argv[3]);
		table[i].time_after_eat = start;
		table[i].n_eat = 0;
		table[i].im_dead = 0;
		table[i].rigth = i;
		if (table[i].id == 1)
			table[i].rigth = n_philos;
		pthread_mutex_init(&table[i].mutex, NULL);
		i++;
	}
	return (philosophers(table));
}
