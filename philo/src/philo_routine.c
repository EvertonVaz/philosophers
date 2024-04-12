/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/12 11:22:01 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	if (time_ms(philo->time_after_eat) > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->fork.fork);
		philo->im_dead = 1;
		pthread_mutex_unlock(&philo->fork.fork);
	}
	return (time_ms(philo->time_after_eat) < philo->time_to_die);
}

void	add_eat(t_data *philo)
{
	philo->time_after_eat = time_ms(0);
	printf(BLUE "%lld, %d is eating\n" END, time_ms(philo->start), philo->id);
	philo->n_eat++;
	usleep(philo->time_to_eat * 1000);
	philo->time_after_eat = time_ms(0);
}

void	eating(t_data *philo)
{
	t_data		*table;
	int			check_eat;

	table = philosophers(NULL);
	check_eat = (philo->max_eat > 0 && philo->n_eat == philo->max_eat);
	if (!check_philo_alive(philo) || check_eat)
		return ;
	take_fork(philo, table);
	if (check_philo_alive(philo) && philo->n_philos > 1)
		add_eat(philo);
	pthread_mutex_unlock(&table[philo->fork.id].fork.fork);
	pthread_mutex_unlock(&table[philo->fork.rigth].fork.fork);
}

void	sleeping(t_data *philo)
{
	long long	time;

	time = time_ms(philo->start);
	if (!check_philo_alive(philo))
		return ;
	printf(YELLOW "%lld, %d is sleeping\n" END, time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}
