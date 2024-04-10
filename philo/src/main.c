/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/10 17:52:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	get_time_ms(long long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

void	*philo_routine(void *data)
{
	t_data		*philo;
	long long	time;

	philo = (t_data *)data;
	philo->philo = pthread_self();
	time = get_time_ms(philo->start);
	while (is_alive(philo))
	{
		if (is_alive(philo))
			eating(philo);
		if (is_alive(philo))
			sleeping(philo);
		time = get_time_ms(philo->start);
		if (is_alive(philo))
			printf(GREEN"%lld, philosopher %d thinking\n"END, time, philo->id);
	}
	return (NULL);
}

void	create_threads(t_data *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&philos[i].philo, NULL, philo_routine, &philos[i]);
		usleep(1000);
		i++;
	}
	i = -1;
	while (++i < n_philos)
		pthread_join(philos[i].philo, NULL);
}

int	main(int argc, char *argv[])
{
	t_data		*philos;
	t_monitor	monitor;
	long long	start;
	int			n_philos;

	// number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
	start = get_time_ms(0);
	if (check_args(argc, argv))
		return (1);
	n_philos = ft_atol(argv[1]);
	philos = init_data(&argv[2], n_philos, start);
	pthread_create(&monitor.monitor, NULL, monitor_routine, &n_philos);
	create_threads(philos, n_philos);
	free(philos);
	return (0);
}
