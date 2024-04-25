/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:01:30 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/25 16:07:36 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define TAKE_FORK "🍽  \033[1;37mhas taken a fork"
# define EATING "🍝 \033[1;33mis eating\033[0m"
# define SLEEPING "💤 \033[1;36mis sleeping\033[0m"
# define THINKING "💡 \033[1;35mis thinking\033[0m"
# define DIED "💀 \033[1;31mdied\033[0m"

typedef struct s_data
{
	long long	start;
	int			id;
	int			rigth;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_after_eat;
	long long	time_to_sleep;
	int			max_eat;
	int			n_eat;
	int			n_philos;
	sem_t		*forks;
	sem_t		*alive;
	sem_t		*print;
}				t_data;

void			*init_data(char **argv, t_data *philo, long long start);
t_data			*philosophers(t_data *philos);
int				ft_isdigit(int c);
int				ft_isnum(char *str);
long			ft_atol(const char *str);
int				ft_strlen(const char *s);
int				print(int choice, long long time, int id);
int				check_args(int argc, char **argv);
long long int	time_ms(long long start);
void			eating(t_data *philo);
void			sleeping(t_data *philo);
void			create_philos(int n_philos);
int				is_alive(t_data *philo);
int				check_philo_alive(t_data *philo);
void			add_eat(t_data *philo);
int				take_fork(t_data *philo);
int				lock_fork(t_data *philo);
void			print_logs(t_data *philo, char *msg);

#endif