/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:33:35 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 16:06:31 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *error)
{
	const char	*msg = \
	"You are should run\n\
	./philo number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,\
 [number_of_times_each_philosopher_must_eat]\n\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

int	validate_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) <= 0 || !ft_isnum(argv[i]))
			return (print_error("The argument should be a positive number bigger than 0\n"));
		if (ft_strlen(argv[i]) > 10 || ft_atol(argv[i]) > INT_MAX)
			return (print_error("The argument can't be bigger than max int\n"));
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5)
		return (print_error("Too few arguments\n"));
	if (argc > 6)
		return (print_error("Too many arguments\n"));
	else
		return (validate_args(&argv[1]));
}
