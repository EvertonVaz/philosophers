/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/25 17:11:20 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	time_ms(long long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

void	print_logs(t_data *philo, char *msg)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n", time_ms(philo->start), philo->id, msg);
	if (check_philo_alive(philo))
		sem_post(philo->print);
}

int	main(int argc, char *argv[])
{
	t_data		philo;

	if (check_args(argc, argv))
		return (1);
	init_data(argv, &philo, time_ms(0));
	create_philos(ft_atol(argv[1]));
	return (0);
}
