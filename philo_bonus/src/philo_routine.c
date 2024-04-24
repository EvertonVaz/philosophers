/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:34:02 by etovaz            #+#    #+#             */
/*   Updated: 2024/04/24 14:49:02 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_alive(t_data *philo)
{
	long long int	time;
	long long int	time_to_die;
	int				result;

	// SEMAFORO
	time = time_ms(philo->time_after_eat);
	time_to_die = philo->time_to_die;
	result = (time < time_to_die);
	
	return (result);
}

void	add_eat(t_data *philo)
{
	// SEMAFORO
	philo->time_after_eat = time_ms(0);
	if (check_philo_alive(philo))
	{
		print_logs(philo, EATING);
		// SEMAFORO
		// FORMA DE CALCULAR SE TODOS COMERAM O SUFICIENTE
		philo->n_eat++;
		philo->time_after_eat = time_ms(0);
		usleep(philo->time_to_eat * 1000);
	}
}

void	eating(t_data *philo)
{
	t_data	*table;
	int		taked;

	table = philosophers(NULL);
	taked = take_fork(philo);
	if (taked && check_philo_alive(philo) && philo->n_philos > 1)
		add_eat(philo);
	if (taked || philo->n_philos == 1)
	{
		// DESTRAVAR SEMAFOROS
		return ;
	}
}

void	sleeping(t_data *philo)
{
	long long	time;

	time = time_ms(philo->start);
	// VERIFICAR SE ELE ESTA VIVO
	print_logs(philo, SLEEPING);
	usleep(philo->time_to_sleep * 1000);
}
