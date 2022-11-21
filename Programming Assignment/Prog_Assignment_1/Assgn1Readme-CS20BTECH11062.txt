/ReadMe for Printing the collatz sequence of numbers
*
*
*
*
*
*
    Make sure to run the program on a linux computer or a virtual machine 
    since the methods fork() and wait() are unique to linux and wont work on 
    other operating systems

    Use a C language compiler (preferably gcc) and run command gcc -o <executable_name> <source_name>
    in the terminal.

    Run command ./<executable_name> <n>

    The program execution must have started now to print its output

    We get the output as follows:

    The control in parent block and is now waiting for child process to complete
    Beginning to print collatz numbers from child process
    
    And the next line contains the list of collatz numbers till 1 for the n specified separated by ':'
    
    The program ends after printing "Back in main" 2 times" (one for each version - parent & child)
*
*
*
*
*
*
/
    