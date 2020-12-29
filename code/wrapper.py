"""Wraps python code with a timer and returns the duration to the
calling application via pipe.
TODO:
    Implement timing, implement pipe, implement iterations, refactor"""

import os
import sys
import threading
import time
import timeit
import importlib
import argparse
import logging

logging.basicConfig(level=logging.DEBUG,
                    format='(%(threadName)-9s) %(message)s',)

parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="""\
Time some code.

This module wraps python code with a timer and returns the duration to the
calling application via pipe.

"""
)

parser.add_argument("-name", type=str, help="Name of module to time",
        required=True)
parser.add_argument("-fd", type=int, help="Pipe file descriptor",
        required=True)
parser.add_argument("-iter", type=int, default=1, help="Number of test iterations")
parser.add_argument("-limit", type=int, default=0,
                    help="Running-time limit in seconds for each iteration")
args = parser.parse_args()

# Allows user to test packages
sys.path.insert(0, os.path.dirname(args.name))


if __name__ == "__main__":
    duration = 0
    results_lock = threading.Lock()

    def return_results(success: bool):
        results_lock.acquire(blocking= True, timeout= -1)

        if success:
            # Python's bool doesn't encode cleanly into 1 or 0, must do manually
            success_bit = "{}\n".format(str(1)).encode()
            duration_ns = str(duration).encode()
        else:
            success_bit = "{}\n".format(str(0)).encode()
            duration_ns = str(0).encode()
        msg_size ="{}\n".format(len(duration_ns)).encode()

        pipe = open(args.fd, mode='ab', buffering=0)
        pipe.write(success_bit)
        pipe.write(msg_size)
        pipe.write(duration_ns)
        pipe.flush()
        sys.stdout.flush()
        sys.stderr.flush()

        logging.debug("RESULTS SENT: {}".format(duration_ns))
        # Warning: will not exit cleanly, leaving ouputs unflushed etc.
        os._exit(0) 

    try:
        module = importlib.import_module(os.path.basename(args.name))
    except Exception as ex:
        print("\n" + str(ex) + ". PYTHON MODULE IMPORT FAILED!" )

    threading.currentThread().setName("{} main thread".format(module.__name__))

    # start timeout timer
    timeout = None
    if (args.limit > 0):
        timeout = threading.Timer(args.limit, return_results, [False])
        timeout.setName("{} timeout thread".format(module.__name__))
        timeout.start()
    else:
        timeout = None

    # Execute timed code
    # timeit has built-in iterations support via 'number' kwarg
    duration += timeit.timeit(module.execute, number=args.iter,
                                        timer=time.perf_counter_ns)
    return_results(True)
