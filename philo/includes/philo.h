/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:01:30 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 15:58:34 by egeraldo         ###   ########.fr       */
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

int		ft_isdigit(int c);
int		ft_isnum(char *str);
long	ft_atol(const char *str);
int		ft_strlen(const char *s);
int		check_args(int argc, char **argv);

#endif