/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/26 10:32:42 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	long long int	time;
	long long int	time_to_die;
	int				result;

	time = time_ms(philo->time_after_eat);
	time_to_die = philo->time_to_die;
	result = (time < time_to_die);
	return (result);
}

void	add_eat(t_data *philo)
{
	if (check_philo_alive(philo))
	{
		print_logs(philo, EATING);
		philo->n_eat++;
		philo->time_after_eat = time_ms(0);
		usleep(philo->time_to_eat * 1000);
	}
}

void	eating(t_data *philo)
{
	int	taked;

	taked = take_fork(philo);
	if (taked && philo->n_philos > 1)
		add_eat(philo);
	if (taked || philo->n_philos == 1)
	{
		sem_post(philo->forks);
		if (philo->n_philos > 1)
			sem_post(philo->forks);
		return ;
	}
}

void	sleeping(t_data *philo)
{
	if (!check_philo_alive(philo))
		return ;
	print_logs(philo, SLEEPING);
	usleep(philo->time_to_sleep * 1000);
}
