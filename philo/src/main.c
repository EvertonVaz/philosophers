/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 13:28:54 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	time_ms(long long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

int	check_monitor(t_monitor *monitor)
{
	int	alive;

	pthread_mutex_lock(&monitor->alive);
	alive = monitor->everyone_is_alive;
	pthread_mutex_unlock(&monitor->alive);
	return (alive);
}

void	print_logs(t_data *philo, char *msg)
{
	t_monitor	*monitor;

	monitor = monitor_address(NULL);
	pthread_mutex_lock(&monitor->print);
	printf("%lld %d %s\n", time_ms(philo->start), philo->id, msg);
	pthread_mutex_unlock(&monitor->print);
}

int	main(int argc, char *argv[])
{
	t_data		*table;
	t_monitor	*monitor;
	int			n_philos;

	if (check_args(argc, argv))
		return (1);
	n_philos = ft_atol(argv[1]);
	table = init_data(&argv[2], n_philos, time_ms(0));
	monitor = init_monitor();
	pthread_create(&monitor->monitor, NULL, monitor_routine, &n_philos);
	usleep(10);
	create_philos(table, n_philos);
	pthread_join(monitor->monitor, NULL);
	free(monitor);
	free(table);
	return (0);
}
