# Assignment 3

In formal terms, a monitor is an object which only allows one of its methods to be executed at once.  C# and Java have differing definitions of the same concept, and ways to duplicate the same functionality.

Choose one of these languages, and explain the following:

1. What is the language’s fundamental high-level synchronization construct?
1. How does it relate to monitors as we defined them in class?
1. Does the language provide additional synchronization-related functionality? In brief, what?
1. How could you implement a class satisfying the monitor’s fundamental mutual exclusion property – that is, a class whose  instantiated objects ensured mutual exclusion among their methods? Provide a code fragment as an example.
1. Could you mutually exclude critical sections smaller than an entire method without resorting to mutex locks? If so, how?
1. How would you implement condition variables as we described them in class? Provide a code fragment as an example.
1. Does the implementation differ if you need more than one condition variable? If so, how?

All the rules from Assignment 1 apply--including citing your references, which should include relevant documentation--except the length limit is three pages rather than one.
