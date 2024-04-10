Comp 310 - Forth
# Working on making Forth interpreter in C #

## Working Components as of right now: ##
- identifying token and token types for words,numbers,symbols,boolean,operator
- working stack
- Function/Method for Boolean
- Tests for Operators, Booleans
  - Made the tests return value 0 or -1 like gforth. Where -1 is true and 0 is false
- Started to get forth compiler to work with operations and printing with "." and it ends the session with the phrase "bye"
  - working on getting other functions,words,variables,loops to work


## Parts I will be adding soon: ##
- Variables and constants
- Add support for conditionals (e.g. if-else) and loops  *https://www.forth.com/starting-forth/6-forth-do-loops/ 
- Add support for functions *
- Add support for the "REPL" of FORTH
  - Connect to main file!

## Parts working on Changing: ##
How the main component works. As of right now it was only working with running once and with one line. So I will be making it run as long as until a certain phrase is typed to end the input.
