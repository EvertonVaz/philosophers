# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Enum.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeraldo <egeraldo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 01:21:57 by egeraldo          #+#    #+#              #
#    Updated: 2025/09/18 10:47:45 by egeraldo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from enum import Enum


class ShowAction(Enum):
    TAKE_FORK = "🍽  \033[1;37mhas taken a fork"
    EATING = "🍝 \033[1;33mis eating\033[0m"
    SLEEPING = "💤 \033[1;36mis sleeping\033[0m"
    THINKING = "💡 \033[1;35mis thinking\033[0m"
    DIED = "💀 \033[1;31mdied\033[0m"

    def __str__(self):
        return self.value

