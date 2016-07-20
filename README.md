# Spell Checking
g++ -std=c++11 spellCheck.cpp setWords.cpp

A demo of the spell-checking capability of the setWords object. Depending on the dictionary that you use initial loading time can be over 2 seconds, but every word you check will be almost immediate.

It is suggested that the load function be used at start-time just after the gui pops up and content is initially displayed, or on a separate thread if possible. 

RAM use is also determined by the size of the dictionary as the entire book will be loaded into memory.


You will have to do some pre-processing on these words as the setWords object only does a one-to-one check against the dictionary for spelling errors. Periods, camas and certain other punctuation symbols need to be removed before checking a word.

# Dictionary Building
g++ -std=c++11 buildDictionary.cpp setWords.cpp

Quickly add words to an existing dictionary. 

This program is set up to read all words from a text file and slam them into a compiled dictionary. 
To add words to an existing dictionary, include that dictionary as a file to be read and as the final output.

