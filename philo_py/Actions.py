# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Actions.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeraldo <egeraldo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 01:11:29 by egeraldo          #+#    #+#              #
#    Updated: 2025/09/18 10:51:51 by egeraldo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


from time import sleep, time
from Enums import ShowAction
from Model import Monitor, Table, Philosopher

msleep = lambda x: sleep(x / 1000)


class Action:
    def __init__(self, table:Table, philo:Philosopher):
        self.table = table
        self.philo = philo

    def routine(self):
        if self.is_end_routine(): return

        self.take_forks()
        self.eat()
        self.sleeping()
        self.thinking()


    def take_forks(self):
        if self.is_end_routine(): return

        self.print_action(ShowAction.TAKE_FORK)
        self.philo.fork.acquire()
        self.philo.my_fork = True

        if self.is_end_routine(): return

        self.print_action(ShowAction.TAKE_FORK)
        self.table[self.philo.right_id - 1].fork.acquire()
        self.philo.other_fork = True

    def eat(self):
        if self.is_end_routine(): return

        self.print_action(ShowAction.EATING)
        self.philo.eat_count += 1
        self.philo.last_meal = self.__get_time() - self.philo.last_meal
        msleep(self.philo.time_to_eat)

        self.philo.fork.release()
        self.philo.my_fork = False
        self.table[self.philo.right_id - 1].fork.release()
        self.philo.other_fork = False

    def sleeping(self):
        if self.is_end_routine(): return

        self.print_action(ShowAction.SLEEPING)
        msleep(self.philo.time_to_sleep)

    def thinking(self):
        if self.is_end_routine(): return

        self.print_action(ShowAction.THINKING)

    def die(self):
        Monitor.alive_lock.acquire()
        Monitor.everyone_is_alive = False
        self.print_action(ShowAction.DIED)
        Monitor.alive_lock.release()

        return self.good_bye()

    def good_bye(self):
        if self.philo.satisfied: return True
        Monitor.alive_lock.acquire()
        Monitor.max_eat -= 1
        self.philo.satisfied = True

        if Monitor.max_eat <= 0:
            Monitor.everyone_is_alive = False

        if self.philo.my_fork:
            self.philo.fork.release()
        if self.philo.other_fork:
            self.table[self.philo.right_id - 1].fork.release()
        Monitor.alive_lock.release()
        return True

    def __get_time(self):
        return int((time() - self.philo.start) * 1000)

    def print_action(self, action: ShowAction):
        Monitor.print_lock.acquire()
        print(f'time: {self.__get_time()} id: {self.philo.id} {action}')
        Monitor.print_lock.release()

    def is_end_routine(self) -> bool:
        if Monitor.everyone_is_alive is False:
            return self.good_bye()

        if self.philo.eat_count >= self.philo.max_eat:
            return self.good_bye()

        if self.philo.time_to_die <= self.philo.last_meal + self.philo.time_to_eat:
            return self.die()

        return False