How to run the program ?
------------------------
In order to remove the old Makefile if any changes was done and to make a new one :

$ make clean main

To run the program with number_of_threads an int representing the number of threads to use and filename the name of the file containing the intervals

The intervals file must contain one interval by line, an interval is two integer which can be very large numbers on a line and with a space between the lower bound and the upper bound :

$ ./main number_of_threads filename

Exemple : $ ./main 200 Exemples\ de\ fichiers/7_long.txt


Author and license
------------------

The code for finding the prime numbers was initially taken from https://github.com/cslarsen/miller-rabin but then changed by Valentin Gendre & Adrien Turchini using the gmp library.

The code for the Tri Fusion in intervals.cpp was taken from https://waytolearnx.com/2019/08/tri-par-fusion-en-c.html

The code for the chrono in Chrono.hpp is from Marc Parizeau, Laboratoire de vision et systemes numeriques, Universite Laval.

