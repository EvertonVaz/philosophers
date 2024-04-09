/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 16:07:44 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	get_time_ms(long long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

int	main(int argc, char *argv[])
{
	// number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
	if(check_args(argc, argv))
		return(1);
	
	return (0);
}
