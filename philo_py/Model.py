# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Model.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeraldo <egeraldo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 00:14:43 by egeraldo          #+#    #+#              #
#    Updated: 2025/09/18 10:42:38 by egeraldo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


from threading import Lock
from time import sleep, time
from typing import List

from Enums import ShowAction


class Monitor:
    everyone_is_alive: bool = True
    everyone_is_ate: bool = False
    max_eat: int = 0
    print_lock: Lock = Lock()
    alive_lock: Lock = Lock()


class Philosopher:
    def __init__(self, **kwargs):
        self.id: int = kwargs.get('id')
        self.start = time()
        self.right_id: int = self.id % kwargs.get('n_philo') + 1
        self.time_to_die: int = kwargs.get('time_to_die')
        self.time_to_eat: int = kwargs.get('time_to_eat')
        self.time_to_sleep: int = kwargs.get('time_to_sleep')
        self.last_meal: int = 0
        self.eat_count: int = 0
        self.max_eat: int = kwargs.get('max_eat')
        self.fork: Lock = Lock()
        self.satisfied: bool = False
        self.my_fork: bool = False
        self.other_fork: bool = False


class Table:
    table: List[Philosopher] = []
    def __init__(self, **kwargs):
        n_philo: int = kwargs.get('n_philo')
        for i in range(n_philo):
            philosopher = Philosopher(
                id=i + 1,
                time_to_die=kwargs.get('time_to_die'),
                time_to_eat=kwargs.get('time_to_eat'),
                time_to_sleep=kwargs.get('time_to_sleep'),
                max_eat=kwargs.get('max_eat'),
                n_philo=n_philo
            )

            self.table.append(philosopher)