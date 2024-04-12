/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 16:13:55 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



t_data	*philosophers(t_data *philos)
{
	static t_data	*philosophers;

	if (!philosophers)
		philosophers = philos;
	return (philosophers);
}

t_data	*init_data(char **argv, int n_philos, long long start)
{
	t_data	*philos;
	int		i;

	i = 0;
	philos = malloc(n_philos * sizeof(t_data));
	while (i < n_philos)
	{
		philos[i].n_philos = n_philos;
		philos[i].start = start;
		philos[i].id = i + 1;
		philos[i].time_to_die = ft_atol(argv[0]);
		philos[i].time_to_eat = ft_atol(argv[1]);
		philos[i].time_to_sleep = ft_atol(argv[2]);
		philos[i].max_eat = ft_atol(argv[3]);
		philos[i].time_after_eat = start;
		philos[i].n_eat = 0;
		philos[i].im_dead = 0;
		philos[i].fork = init_fork(i + 1, n_philos);
		i++;
	}
	return (philosophers(philos));
}

void	*philo_routine(void *data)
{
	t_data		*philo;
	t_monitor	*monitor;
	long long	time;

	monitor = monitor_address(NULL);
	philo = (t_data *)data;
	time = time_ms(philo->start);
	while (check_philo_alive(philo))
	{
		if (check_philo_alive(philo))
			eating(philo);
		if (check_philo_alive(philo) && philo->n_philos > 1)
			sleeping(philo);
		time = time_ms(philo->start);
		if (check_monitor(monitor) && check_philo_alive(philo) && philo->n_philos > 1)
			printf(GREEN "%lld, %d is thinking\n" END, time, philo->id);
		usleep(1000);
		if (philo->max_eat > 0 && philo->n_eat == philo->max_eat)
			return (NULL);
	}
	return (NULL);
}

void	create_philos(t_data *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&philos[i].philo, NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < n_philos)
		pthread_join(philos[i++].philo, NULL);
}
