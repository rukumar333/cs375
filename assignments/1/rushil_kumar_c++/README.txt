How to Compile
--------------

Use the command "make" to compile the program into "submission"
Use the command "make clean" to remove all object files and submission.

How to Run
----------

Use "./submission input.txt output.txt" where input.txt has keys
separated by newlines ('\n') and output.txt displays all keys who
are equal to the difference between two other keys followed by the
two keys in decreasing order. "input.txt" and "output.txt" can be any files
from which the keys can be in read in from and the output can be written to.

Example input
1
2
3
7
15
22

Example output
1 3 2
2 3 1
7 22 15
15 22 7
