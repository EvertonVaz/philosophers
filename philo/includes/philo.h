/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:01:30 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 18:52:20 by etovaz           ###   ########.fr       */
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

typedef struct s_data
{
	pthread_t	philo;
	long long	start;
	int			id;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_after_eat;
	long long	time_to_sleep;
	long long	number_of_eat;
}				t_data;

int				ft_isdigit(int c);
int				ft_isnum(char *str);
long			ft_atol(const char *str);
int				ft_strlen(const char *s);
int				check_args(int argc, char **argv);
long long int	get_time_ms(long long start);
void			eating(t_data *philo);

#endif