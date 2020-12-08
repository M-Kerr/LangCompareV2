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

Classes within the module must have an execute() method containing code to
time."""
)

parser.add_argument("-name", type=str, help="Name of module to time",
        required=True)
parser.add_argument("-cname", type=str, help="Name of test class",
        required=True)
parser.add_argument("-fd", type=int, help="Pipe file descriptor",
        required=True)
parser.add_argument("-iter", type=int, default=1, help="Number of test iterations")
parser.add_argument("-limit", type=int, default=0, 
                    help="Running-time limit in seconds for each iteration")
args = parser.parse_args()

try:
    module = importlib.import_module("." + args.name, package="code")
except Exception as ex:
    print("\nModule import failed: " + str(ex))

code = getattr(module, args.cname)()

# Execute timed code
duration = timeit.timeit(code.execute, number=args.iter,
        timer=time.perf_counter_ns)

duration_ns = str(duration).encode()

pipe = open(args.fd, mode='ab', buffering=0)
pipe.write("{}\n".format(len(duration_ns)).encode())
pipe.write(duration_ns)
