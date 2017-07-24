# Two Windows

This application serves to demonstrate why and how to offload intensive tasks to seperate
threads in Qt. This allows the GUI thread to remain responsive.

## Single-Threaded

The single\_thread directory serves to illustrate how the GUI can be frozen during intensive
calculations in a single threaded application. Note, that the 'calculation' is really just
a call to nanosleep. See `man 2 nanosleep`.

## Multi-Threaded

The multi\_thread directory serves to illustrate how the GUI can be kept responsive even
during intensive calculations by utilising multiple threads. Note, that the 'calculation' is
really just a call to nanosleep. See `man 2 nanosleep`. The multi-threaded application also
demonstrates message passing between threads utilizing the Qt signal/slot paradigm. This is
necessary since the thread's execution is asynchronous. Waiting for the thread to return a 
value would reintroduce the problem of the GUI thread halting execution.
