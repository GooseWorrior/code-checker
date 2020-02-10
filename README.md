# code-checker
This is a code checker that can identify different kinds of comments in a program file

This code checker is a prototype and there are a few things you can do to extend its functionalities or to meet specific requirements and fit it in the system.

1. This program reads from stdin by default, you can use it by running this command "./checker < [programfile]"; however, you can bind the input to other source by making trivial changes to the "main" function (parameters of the constructor).

2. This program sends output to stdout by default, you can redirect the output to somewhere else by making trivial changes to the "main" function (parameters of the constructor).

3. This program consumes C/C++ files by default, you can change lanaguage supporting by making trivial changes to the "main" function (call "loadLanguage(vector<string> list) function"). Language supporting for Python and Java has been set up.
