/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:01:30 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/22 16:59:07 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLUE "\033[34;1m"
# define CYAN "\033[36;1;3;208m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define RED "\033[31;1m"
# define END "\033[0m"

typedef struct s_fork
{
	int				id;
	int				left;
	int				rigth;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_monitor
{
	pthread_t		monitor;
	int				everyone_is_alive;
	int				everyone_is_ate;
	int				max_eat;
	pthread_mutex_t	block;
}					t_monitor;

typedef struct s_data
{
	pthread_t		philo;
	long long		start;
	int				id;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_after_eat;
	long long		time_to_sleep;
	int				max_eat;
	int				n_eat;
	int				n_philos;
	int				im_dead;
	t_fork			fork;
}					t_data;

int					ft_isdigit(int c);
int					ft_isnum(char *str);
long				ft_atol(const char *str);
int					ft_strlen(const char *s);
int					print(int choice, long long time, int id);
int					check_args(int argc, char **argv);
long long int		time_ms(long long start);
void				eating(t_data *philo);
void				sleeping(t_data *philo);
t_data				*init_data(char **argv, int n_philos, long long start);
t_data				*philosophers(t_data *philos);
int					wait_all_philos(t_monitor *monitor, int new_philo,
						int n_philos);
void				create_philos(t_data *philos, int n_philos);
int					is_alive(t_data *philo);
t_monitor			*monitor_address(t_monitor *monitor);
void				*monitor_routine(void *data);
int					check_monitor(t_monitor *monitor);
int					check_philo_alive(t_data *philo);
t_fork				init_fork(int id, int n_philos);
int					take_fork(t_data *philo, t_data *table);
int					lock_fork(t_data *philo, pthread_mutex_t *first,
						pthread_mutex_t *last);
void				add_eat(t_data *philo);

#endif