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

# Allows the user to drop modules and submodules into py directory without
# changing their import structure. Possible naming conflict if user adds
# submodule named py/ or module named wrapper.py
sys.path.insert(1, "./code/py")

try:
    module = importlib.import_module("." + args.name, package="py")
except Exception as ex:
    print("\nModule import failed: " + str(ex))

# Execute timed code
duration = timeit.timeit(module.execute, number=args.iter,
        timer=time.perf_counter_ns)

duration_ns = str(duration).encode()

pipe = open(args.fd, mode='ab', buffering=0)
pipe.write("{}\n".format(len(duration_ns)).encode())
pipe.write(duration_ns)
