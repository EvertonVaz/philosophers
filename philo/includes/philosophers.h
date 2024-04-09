/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:01:30 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 11:54:56 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef struct	s_philos
{
	int	id;
}	t_philos;

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

#endif