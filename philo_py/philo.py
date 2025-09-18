# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    philo.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeraldo <egeraldo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 01:21:57 by egeraldo          #+#    #+#              #
#    Updated: 2025/09/18 10:47:45 by egeraldo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


from time import sleep, time
from multiprocessing.pool import ThreadPool

from Actions import Action
from Model import Monitor, Philosopher, Table

msleep = lambda x: sleep(x / 1000)

table:Table = Table(
    n_philo=200,
    time_to_die=1000,
    time_to_eat=1,
    time_to_sleep=2,
    max_eat=3
)

def routine(philosopher:Philosopher):
    actions:Action = Action(table.table, philosopher)
    Monitor.max_eat = len(table.table)
    while Monitor.everyone_is_alive:
        if philosopher.id % 2 == 0:
            msleep(0.001)
        actions.routine()
        if philosopher.satisfied: return

pool = ThreadPool(processes=len(table.table))
start = time()
threads = []

for philosopher in table.table:
    async_result = pool.apply_async(routine, (philosopher,))
    threads.append(async_result)

letters_list = [result.get() for result in threads]

end = time()
print(f'tempo de execução da tradução: {end - start}')
