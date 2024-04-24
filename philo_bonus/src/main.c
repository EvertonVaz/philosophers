/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/24 16:46:14 by egeraldo         ###   ########.fr       */
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
	//USAR SEMAFORO AQUI
	printf("%lld %d %s\n", time_ms(philo->start), philo->id, msg);
}

int	main(int argc, char *argv[])
{
	t_data		*philo;
	int			n_philos;

	if (check_args(argc, argv))
		return (1);
	n_philos = ft_atol(argv[1]);
	philo = init_data(&argv[2], n_philos, time_ms(0));
	create_philos(philo, n_philos);

	return (0);
}
