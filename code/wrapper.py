"""Wraps python code with a timer and returns the duration to the
calling application via pipe.
TODO:
    Implement timing, implement pipe, implement iterations, refactor"""

import os
import sys
import time
import timeit
import importlib
import argparse
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

try:
    module = importlib.import_module(os.path.basename(args.name))
except Exception as ex:
    print("\n" + str(ex) + ". PYTHON MODULE IMPORT FAILED!" )

# Execute timed code
duration = timeit.timeit(module.execute, number=args.iter,
        timer=time.perf_counter_ns)

duration_ns = str(duration).encode()

pipe = open(args.fd, mode='ab', buffering=0)
pipe.write("{}\n".format(len(duration_ns)).encode())
pipe.write(duration_ns)
