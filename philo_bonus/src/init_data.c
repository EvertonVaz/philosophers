/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:22:18 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 14:59:53 by egeraldo         ###   ########.fr       */
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
	t_data	philo[1];
	int		i;

	i = 0;
	philo[0].n_philos = n_philos;
	philo[0].start = start;
	philo[0].id = i + 1;
	philo[0].time_to_die = ft_atol(argv[0]);
	philo[0].time_to_eat = ft_atol(argv[1]);
	philo[0].time_to_sleep = ft_atol(argv[2]);
	philo[0].max_eat = ft_atol(argv[3]);
	philo[0].time_after_eat = start;
	philo[0].n_eat = 0;
	return (philosophers(philo));
}
