# spellChecking
A background Spell-Checking object. Depending on the dictionary that you use, initial loading time can be over 2 seconds, but every word you check will be almost immediate.

It is suggested that the load function be used at start-time just after the gui pops up, or on a separate thread if possible. RAM use also determined by the size of the dictionary as the entire book will be loaded into memory.


