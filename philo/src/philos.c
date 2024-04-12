/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 09:11:43 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	init_fork(int id, int n_philos)
{
	t_fork	fork;

	fork.id = id;
	fork.left = id + 1;
	fork.rigth = id - 1;
	if (fork.id == n_philos)
		fork.left = 1;
	if (fork.id == 1)
		fork.rigth = n_philos;
	pthread_mutex_init(&fork.fork, NULL);
	return (fork);
}

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
		philos[i].fork = init_fork(i + 1, n_philos);
		i++;
	}
	return (philosophers(philos));
}

void	*philo_routine(void *data)
{
	t_monitor	*monitor;
	t_data		*philo;
	long long	time;

	monitor = monitor_address(NULL);
	philo = (t_data *)data;
	philo->philo = pthread_self();
	time = time_ms(philo->start);
	while (check_monitor(*monitor))
	{
		if (check_monitor(*monitor))
			eating(philo);
		if (philo->max_eat > 0 && philo->n_eat == philo->max_eat)
			return (NULL);
		if (check_monitor(*monitor) && philo->n_philos > 1)
			sleeping(philo);
		time = time_ms(philo->start);
		if (check_monitor(*monitor) && philo->n_philos > 1)
			printf(GREEN "%lld, %d is thinking\n" END, time, philo->id);
		usleep(1000);
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
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < n_philos)
		pthread_join(philos[i++].philo, NULL);
}
