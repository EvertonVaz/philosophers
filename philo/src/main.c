/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 17:19:45 by egeraldo         ###   ########.fr       */
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
	pthread_t	tid;
	t_data		*philo;

	philo = (t_data *)data;
	tid = pthread_self();
	printf("philosopher id: %d, start thread %lld\n", philo->id, get_time_ms(philo->start));
	printf("philosopher %d eating\n", philo->id);
	printf("philosopher %d sleeping\n", philo->id);
	printf("philosopher %d thinking\n", philo->id);
	return(NULL);
}

void create_threads(t_data *philos, int	n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&philos[i].philo, NULL, philo_routine, &philos[i]);
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	init_data(int n_philos)
{
	int	i;
	t_data philos[n_philos];

	i = 0;
	while (i < n_philos)
	{
		philos[i].id = i + 1;
		philos[i].start = get_time_ms(0);
		i++;
	}
	return (create_threads(philos, n_philos));
}

int	main(int argc, char *argv[])
{
	// number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]

	if(check_args(argc, argv))
		return(1);
	init_data(ft_atol(argv[1]));

	return (0);
}
