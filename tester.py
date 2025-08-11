# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siuol <siuol@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 10:18:21 by siuol             #+#    #+#              #
#    Updated: 2025/08/10 10:33:34 by siuol            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env  python3
import socket
import time
import sys
import threading
from typing import Optional, List, Tuple

#DEFAULT CONFIG INFO
HOST    = "localhost"
PORT    = 6677
PASS    = "test"
TIMEOUT = 3.0

