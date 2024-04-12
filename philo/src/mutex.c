/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:01:14 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/12 09:02:22 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	int	is_alive;

	pthread_mutex_lock(&philo->fork.fork);
	is_alive = time_ms(philo->time_after_eat) < philo->time_to_die;
	pthread_mutex_unlock(&philo->fork.fork);
	return(is_alive);
}
