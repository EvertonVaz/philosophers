/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/09 21:18:11 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_data *philo)
{
	printf("time: %lld, philosopher %d eating\n", get_time_ms(philo->start), philo->id);
	philo->time_after_eat = get_time_ms(0);
	while(get_time_ms(philo->time_after_eat) < philo->time_to_eat)
		;
	printf("parou de comer em %lld\n", get_time_ms(philo->time_after_eat));
}