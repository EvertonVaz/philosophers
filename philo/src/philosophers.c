/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/22 16:51:26 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		table[i].fork = init_fork(i + 1, n_philos);
		i++;
	}
	return (philosophers(table));
}

void	*philo_routine(void *data)
{
	t_data		*philo;
	t_monitor	*monitor;
	long long	time;

	monitor = monitor_address(NULL);
	philo = (t_data *)data;
	time = time_ms(0);
	while (wait_all_philos(monitor, 1, philo->n_philos))
		;
	while (check_philo_alive(philo))
	{
		if (check_philo_alive(philo))
			eating(philo);
		if (check_philo_alive(philo) && philo->n_philos > 1)
			sleeping(philo);
		time = time_ms(philo->start);
		if (check_monitor(monitor) && check_philo_alive(philo)
			&& philo->n_philos > 1)
			printf(GREEN "%lld, %d is thinking\n" END, time, philo->id);
		if (philo->max_eat > 0 && philo->n_eat == philo->max_eat)
			return (NULL);
	}
	return (NULL);
}

void	create_philos(t_data *table, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&table[i].philo, NULL, philo_routine, &table[i]);
		i++;
	}
	i = 0;
	while (i < n_philos)
		pthread_join(table[i++].philo, NULL);
}
