import sys
import threading
import queue
import re

from PySide2.QtCore import QTimer


# queue between stdin reader and consumer
# setting size prevets reading all the data from stdin at once and allocating huge buffer for long game
# otherwise buffer allocating ~5kk lines is usual thing to happen
MAX_QUEUE_SIZE = 200


def extract_cycle(line: str):
    m = re.search(r'(?<=")\d+(?=")', line)
    cycle = m.group()
    return cycle


delays = [
    1000,
    750,
    500,
    300,
    200,
    100,
    50,
    10,
    1
]


class StdinListener:
    """
    1) runs a thread that reads stdin in parallel and puts any data read into a queue
    2) runs a timer in gui thread that periodically checks the queue
       and if theres some data -> calls the callback with lines belonging to one cycle of corewar vm
       on first run calls callback with "start" as a notification about data having started arriving on stdin
    """

    def __init__(self, callback, check_interval_ms=1000):
        self.callback = callback
        self.read_started = False
        self.line_next_cycle: str = None
        self.last_cycle: int = 0
        self.speed = 0

        self.timer = QTimer()
        self.timeout = check_interval_ms
        self.timer.timeout.connect(self.read_queue)

        self.stdin_line_queue = queue.Queue(MAX_QUEUE_SIZE)
        self.parallel_reader = threading.Thread(
            target=self.parallel_read_stdin, args=(self.stdin_line_queue,))

        self.parallel_reader.setDaemon(True)  # kill when main pocess exits

    def parallel_read_stdin(self, q: queue):
        """read line from stdin in parallel thread and put line read into the queue"""
        for line in sys.stdin:  # this is blocked until data in stdin available
            self.stdin_line_queue.put(line.rstrip())

    def start_paused(self):
        """start timer and start the thread"""
        self.paused = True
        self.timer.start(self.timeout)
        self.parallel_reader.start()

    def read_queue(self):
        """
        attempts to read from stdin queue and sends data to callback with all lines for one cycle
        """
        # sends "start" notification on first run whe some data arrives from stdin
        if not self.read_started:
            if not self.stdin_line_queue.empty():
                self.callback(0, "start")
                self.read_started = True

        if(not self.paused):
            self.read_next_cycle()

    def read_next_cycle(self):
        if not self.stdin_line_queue.empty() or self.line_next_cycle:
            cycle, lines = self.get_lines_one_cycle()
            self.callback(cycle, lines)

    def get_lines_one_cycle(self):
        """extracts all lines for one cycle, if next cycle occurs returns"""
        current_cycle = None
        lines = []

        # pick up where we ended last time
        if self.line_next_cycle:
            lines.append(self.line_next_cycle)
            current_cycle = extract_cycle(self.line_next_cycle)
            self.line_next_cycle = None

        while True:
            try:
                # parse cycle number from line
                line = self.stdin_line_queue.get(block=False)
                cycle = extract_cycle(line)

                if not current_cycle:
                    current_cycle = cycle

                # remember current line as it belongs to next cycle
                # and should be processed next time
                if cycle != current_cycle:
                    self.line_next_cycle = line
                    break

                lines.append(line)

            except queue.Empty:
                break

        return current_cycle, lines

    def set_interval(self, interval_ms):
        self.timeout = interval_ms
        self.timer.setInterval(interval_ms)

    def set_paused(self, paused=True):
        self.paused = paused

    def slow_down(self):
        if (self.speed > 0):
            self.speed -= 1

        self.set_interval(delays[self.speed])

    def speed_up(self):
        if (self.speed < len(delays) - 1):
            self.speed += 1

        self.set_interval(delays[self.speed])

    def set_speed(self, speed: int):
        self.speed = speed
        self.set_interval(delays[self.speed])
