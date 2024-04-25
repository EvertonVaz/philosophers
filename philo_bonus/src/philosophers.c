/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:47 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/25 18:11:45 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	close_semaphores(t_data *philo)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_close(philo->forks);
	sem_close(philo->print);
}

int	ate(t_data *philo)
{
	return (philo->max_eat > 0 && philo->n_eat == philo->max_eat);
}

void	philo_routine(t_data *philo, int id)
{
	philo->id = id;
	while (check_philo_alive(philo))
	{
		if (check_philo_alive(philo))
			eating(philo);
		if (ate(philo))
			break ;
		if (check_philo_alive(philo))
			sleeping(philo);
		if (check_philo_alive(philo))
		{
			print_logs(philo, THINKING);
			usleep(100);
		}
	}
	if (!ate(philo) && !check_philo_alive(philo))
	{
		print_logs(philo, DIED);
		close_semaphores(philo);
		exit(EXIT_FAILURE);
	}
	close_semaphores(philo);
	exit(EXIT_SUCCESS);
}

void	i_kill_you(int status, int n_philos, pid_t *pid)
{
	while(waitpid(-1, &status, 0))
	{
		if (status)
		{
			status = -1;
			while (++status < n_philos)
				kill(pid[status], SIGKILL);
			break;
		}
		if (--n_philos == 0)
			break;
	}
}

void	create_philos(int n_philos)
{
	int		status;
	pid_t	pid[n_philos];
	t_data	*philo;

	status = 0;
	philo = philosophers(NULL);
	while (status < n_philos)
	{
		pid[status] = fork();
		if (pid[status] == 0)
			philo_routine(philo, status + 1);
		status++;
	}
	i_kill_you(status, n_philos, pid);
	close_semaphores(philo);
}
