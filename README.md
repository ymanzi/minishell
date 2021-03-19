# minishell

Rewrite a simple shell in c

**Subject**: [Minishell - 42](https://cdn.intra.42.fr/pdf/pdf/19786/en.subject.pdf)

**Members**: :last_quarter_moon_with_face: [Ehafidi](https://github.com/ehafidi) - [Ymanzi](https://github.com/ymanzi) :first_quarter_moon_with_face:

![myImage](https://media.giphy.com/media/l3q2Wl7Wpz09Z5hfi/giphy.gif)

## How to Use It

Using ``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```

## Instruction
* ``'`` and ``"`` work the same as in bash
* Able to run commandes from an absolute, relative or environment PATH, including arguments or options.
* Commands can be separate with ``;``
* Handle redirections ``>`` ``>>`` ``<`` and pipes ``|`` as well
* Environment variables are handled like ``$HOME`` including return code ``$?``
* Like in bash, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF
* some "built-in" were recoded: ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``. 

## RESOURCES

![myImage](https://media.giphy.com/media/1TgECF0mNVirC/giphy.gif)

### SHELL Informations
* [Bash](https://www.aosabook.org/en/bash.html)
* [Shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [ Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [Shell example](https://github.com/Swoorup/mysh)
* [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* [Youtube - Program your own webserv in C](https://www.youtube.com/watch?v=esXw4bdaZkc)
* [Youtube - Socket Programming in C](https://youtu.be/LtXEMwSG5-8)

### Lexer
* [How to write a (shell) lexer by hand](https://stackoverflow.com/questions/5491775/how-to-write-a-shell-lexer-by-hand)
* [lexical analyzer](https://rosettacode.org/wiki/Compiler/lexical_analyzer)
* [syntax analyzer](https://rosettacode.org/wiki/Compiler/syntax_analyzer)

### Parse Tree
* [Generating a parse tree](https://dev.to/oyagci/generating-a-parse-tree-from-a-shell-grammar-f1)

### Pipe - Fork - Execve - dup Functions
* [Connecting n commands with pipes in a shell?](https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell)
* [Communication par tuyau](http://www.zeitoun.net/articles/communication-par-tuyau/start)
* [how to correctly wait for execve to finish?](https://stackoverflow.com/questions/34625123/how-to-correctly-wait-for-execve-to-finish)
* [Pipe, Fork, Exec](https://www.cs.uleth.ca/~holzmann/C/system/pipeforkexec.html)
* [Process creation and interprocess communication](https://cs61.seas.harvard.edu/site/2018/Shell2/)
* [exec and pipe between child process in C](https://stackoverflow.com/questions/47767995/exec-and-pipe-between-child-process-in-c)
* [dup2](https://stackoverflow.com/questions/9084099/re-opening-stdout-and-stdin-file-descriptors-after-closing-them)

### Bash Redirection
* [How bash redirection works](https://brandonwamboldt.ca/how-bash-redirection-works-under-the-hood-1512/)
* [All about redirections](https://catonmat.net/bash-one-liners-explained-part-three)
* [Redirection](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_07)

### Bash Pipe
* [How Linux pipes work](https://brandonwamboldt.ca/how-linux-pipes-work-under-the-hood-1518/)
* [Pipe Demo](https://gist.github.com/mplewis/5279108)

### Exit
* [Unix Exit Codes](https://shapeshed.com/unix-exit-codes/)
* [Exit Codes](https://tldp.org/LDP/abs/html/exitcodes.html)
* [Exit Status for Commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_08_02)

![myImage](https://media.giphy.com/media/xTQXENNW77nUsNVmV4/giphy.gif)
