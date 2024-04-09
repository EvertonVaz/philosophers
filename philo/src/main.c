/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:00:42 by egeraldo          #+#    #+#             */
/*   Updated: 2024/04/09 13:50:43 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdio.h>

#define TIMES_TO_COUNT 2100000

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

// This structure contains the count as well as the mutex
// that will protect the access to the variable.
typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

long long int get_time_ms(long long start)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000 + time.tv_usec) / 1000) - start);
}

// int	check_args(char **argv)

void	*thread_routine(void *data)
{
	// Each thread starts here
	pthread_t		tid;
	t_counter		*count; // pointer to the variable created in main
	unsigned int	i;

	tid = pthread_self();
	count = (t_counter *)data;
	// Print the count before this thread starts iterating:
	pthread_mutex_lock(&count->count_mutex);
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, count->count, NC);
	pthread_mutex_unlock(&count->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// Iterate TIMES_TO_COUNT times
		// Increment the counter at each iteration
		// Lock the mutex for the duration of the incrementation
		pthread_mutex_lock(&count->count_mutex);
		count->count++;
		pthread_mutex_unlock(&count->count_mutex);
		i++;
	}
	// Print the final count when this thread
	// finishes its own count
	printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, count->count, NC);
	return (NULL); // Thread ends here.
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	// Variable to keep track of the threads' counts:
	// Structure containing the threads' total count:
	t_counter	counter;

	// There is only on thread here (main thread), so we can safely
	// initialize count without using the mutex.
	counter.count = 0;
	// Initialize the mutex :
	pthread_mutex_init(&counter.count_mutex, NULL);
	// Since each thread counts TIMES_TO_COUNT times and that
	// we have 2 threads, we expect the final count to be
	// 2 * TIMES_TO_COUNT:
	printf("Main: Expected count is %s%u%s\n", GREEN,
					2 * TIMES_TO_COUNT, NC);
	// Thread creation:
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);
	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);
	// Final counter evaluation:
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total counter is %u%s\n", RED, counter.count, NC);
	else
		printf("%sMain: OK. Total counter is %u%s\n", GREEN, counter.count, NC);
	return (0);
}
