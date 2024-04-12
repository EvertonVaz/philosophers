/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 11:25:21 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	time_ms(long long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

int	check_monitor(t_monitor monitor)
{
	int	i;

	pthread_mutex_lock(&monitor.block);
	i = monitor.everyone_is_alive;
	pthread_mutex_unlock(&monitor.block);
	return (i);
}

int	main(int argc, char *argv[])
{
	t_data		*philos;
	t_monitor	*monitor;
	int			n_philos;

	if (check_args(argc, argv))
		return (1);
	monitor = malloc(1 * sizeof(t_monitor));
	monitor = monitor_address(monitor);
	pthread_mutex_init(&monitor->block, NULL);
	n_philos = ft_atol(argv[1]);
	philos = init_data(&argv[2], n_philos, time_ms(0));
	pthread_create(&monitor->monitor, NULL, monitor_routine, &n_philos);
	create_philos(philos, n_philos);
	pthread_join(monitor->monitor, NULL);
	free(monitor);
	free(philos);
	return (0);
}
