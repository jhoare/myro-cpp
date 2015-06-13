---
layout: page
title: FAQs
permalink: /faq/
---
{:toc}

##  When I try to compile my program, I get "Myro.h": file not found Or something similar ##
This probably means you're not compiling your program correctly. Suppose you have a file called Driver.cpp which you wish to compile. Then, you would compile it by running:

```
g++ `myro-cpp-config --cflags --libs` Driver.cpp -o Driver
```

Which would create a program called 'Driver' that you can run. If you're a student at UTK and you're working on a lab, you should be using a "Makefile" which means you should just run "make" which will do all that for you.


## What does an example program/makefile look like? ##

Example programs are installed into the "doc" directory. In linux/osx it will be at:

```
  /usr/share/doc/myro-cpp-x.x.x/examples
```

Where x.x.x is the version you have installed.
