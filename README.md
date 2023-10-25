# "Advanced Programming Methods"

This is repository for keeping project associated with "Advanced Programming Methods" course at WUST, for Control Systems and Robotics students.

### The provided Makefile allows the achievement of three main targets and one auxiliary target.

The default target is to compile, link, and then run the program. To accomplish this, you should run the command:

> `make`

Second target allows for the removal of all compilation and linking products. To do this, run the command:

> `make clean`

Third target enables the generation of documentation. To do this, run the command:

> `make doc`

Note: After generating the documentation, the `less` program is launched, which allows you to review the list of errors and warnings reported by the Doxygen program. To exit the browsing mode, press the *`'Q'`* key.

An auxiliary target, it allows you to display a list of all the targets achievable using the provided Makefile. To do this, issue the command:

> `make help`