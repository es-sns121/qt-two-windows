# Two Windows

This application serves to demonstrate why and how to offload intensive tasks to seperate
threads in Qt. This allows the GUI thread to remain responsive.

Both versions of the application implement two windows. The first window is a counter. The 
counter displays a value that starts at 1. The value is incremented every 250ms and is reset
to 1 upon reaching 100. The second window implements a calculation. Every 5 seconds a 'calculation' 
is performed. This calulcation takes 1.5 seconds to complete. When the calculation is taking place
the second window displays a 'Performing calculation' message. When it is done, 'Done' is displayed.

## Single-Threaded

The single\_thread directory serves to illustrate how the GUI can be frozen during intensive
calculations in a single threaded application. Note, that the 'calculation' is really just
a call to nanosleep. 

See `man 2 nanosleep`.

## Multi-Threaded

The multi\_thread directory serves to illustrate how the GUI can be kept responsive even
during intensive calculations by utilising multiple threads. Note, that the 'calculation' is
really just a call to nanosleep. 

See `man 2 nanosleep`. 

The multi-threaded application also demonstrates message passing between threads utilizing 
the Qt signal/slot paradigm. This is necessary since the thread's execution is asynchronous. 
Waiting for the thread to return a value would reintroduce the problem of the GUI thread 
halting execution.
