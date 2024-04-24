/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 17:20:06 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(t_data *philo)
{
	long long	time;

	time = time_ms(0);
	while (check_philo_alive(philo))
	{
		if (check_philo_alive(philo))
			eating(philo);
		if ((philo->max_eat > 0 && philo->n_eat == philo->max_eat)
			|| philo->n_philos <= 1)
			return (NULL);
		if (check_philo_alive(philo))
			sleeping(philo);
		time = time_ms(philo->start);
		if (check_philo_alive(philo))
			print_logs(philo, THINKING);
	}
	return (NULL);
}

void	create_philos(t_data *table, int n_philos)
{
	int		status;
	pid_t	pid;
	t_data	*philo;

	status = 0;
	philo = philosophers(NULL);
	while (status < n_philos)
	{
		pid = fork();
		if (pid == 0)
			philo_routine(philo);
		status++;
	}
	waitpid(-1, &status, 0);
	if (status)
}
