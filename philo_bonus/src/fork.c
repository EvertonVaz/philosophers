/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:01:14 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/26 09:43:43 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lock_fork(t_data *philo)
{
	if (check_philo_alive(philo))
	{
		sem_wait(philo->forks);
		if (philo->n_philos > 1)
			sem_wait(philo->forks);
		if (check_philo_alive(philo))
			print_logs(philo, TAKE_FORK);
		if (philo->n_philos == 1)
		{
			usleep(philo->time_to_die * 1000);
			return (0);
		}
		if (check_philo_alive(philo))
			print_logs(philo, TAKE_FORK);
		return (1);
	}
	return (0);
}

int	take_fork(t_data *philo)
{
	if (philo->id % 2 == 1 && check_philo_alive(philo))
		return (lock_fork(philo));
	else if (check_philo_alive(philo))
	{
		usleep(philo->time_to_eat);
		return (lock_fork(philo));
	}
	return (0);
}
