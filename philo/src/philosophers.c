/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 11:22:54 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *data)
{
	t_data		*philo;
	t_monitor	*monitor;
	long long	time;

	monitor = monitor_address(NULL);
	philo = (t_data *)data;
	time = time_ms(0);
	while (check_philo_alive(philo))
	{
		if (check_monitor(monitor) && check_philo_alive(philo))
			eating(philo);
		if ((philo->max_eat > 0 && philo->n_eat == philo->max_eat)
			|| philo->n_philos <= 1)
			return (NULL);
		if (check_monitor(monitor) && check_philo_alive(philo))
			sleeping(philo);
		time = time_ms(philo->start);
		if (check_monitor(monitor) && check_philo_alive(philo))
			print_logs(philo, THINKING);
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
