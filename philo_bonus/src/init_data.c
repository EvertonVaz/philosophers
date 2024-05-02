/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:22:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/25 17:09:50 by egeraldo         ###   ########.fr       */
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

void	*init_data(char **argv, t_data *philo, long long start)
{
	philo->start = start;
	philo->id = 0;
	philo->n_philos = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->max_eat = ft_atol(argv[5]);
	philo->time_after_eat = start;
	philo->n_eat = 0;
	sem_unlink("fork");
	sem_unlink("print");
	philo->forks = sem_open("fork", O_CREAT | O_RDWR, 0666, philo->n_philos);
	philo->print = sem_open("print", O_CREAT | O_RDWR, 0666, 1);
	return (philosophers(philo));
}
