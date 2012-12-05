## Presentation outline ##

* Javascript
** ECMAScript
** Adobe Flash, Mac OS Dashboard widgets, Yahoo! widgets
** Client-side scripting, DOM manipulation

* Why V8?
** Performance comparison
** Fast property access
*** JS is dynamic: object properties may be added/deleted on the fly
*** dynamic lookup vs. hidden class
*** the point example
*** high degree of structure-sharing, no dictionary lookup, class-based optimization like inline caching
** Dynamic machine code
*** directly compiled into machine code
*** no intermediate byte codes or interpreter
*** inline cache code used for the hidden class if predicted correctly
** Efficient garbage collection
*** stops program execution
*** processes only part of the object heap (minimizes impact)
*** accurate objects and pointers locating in memory (avoids memory leaks)

* V8
** Google's open source JS engine
** Written in C++ and used in Chrome
** Implements ECMAScript
** Can run standalone or embedded in C++ applications
** Named after automobile engine
** What does it do?
*** JS execution and compilation
*** memory allocation
*** garbage collection

* V8: 2 compilers
** Full compiler
*** compiles into machine code upon execution
*** a very fast compiler that doesn't do any optimization
** Optimizing compiler
*** types taken from IC (inline caches)
*** operations speculatively get inlined
*** monomorphic functions and constructors can be inlined entirely
*** inlining enables other optimizations
*** d8 --trace-opt primes.js
** better code optimization decisions

* Crankshaft
** Crankshaft uses adaptive compilation to improve both start-up time and peak performance. The idea is to heavily optimize code that is frequently executed and not waste time optimizing code that is not. 
** 1. base compiler
** 2. runtime profiler
** 3. optimizing compiler
** 4. Deopmization support

* V8Profiler
** Samples every millisecond
** results in v8.log

* Benchmarks
** V8: http://v8.googlecode.com/svn/data/benchmarks/v7/run.html
** Page cyclers: http://www.chromium.org/developers/testing/page-cyclers


Welcome to the ee382v-reddi-project wiki!

Let's put our field research summary here.


## Javascript Profiling ##

<a href="https://wiki.mozilla.org/JavaScript:TraceMonkey"> Tracemonkey</a>

<a href="http://code.google.com/p/v8/"> V8 </a>

<a href="http://blog.mozilla.org/javascript/2012/09/12/ionmonkey-in-firefox-18/"> IonMonkey</a>

<a href="https://www.dropbox.com/sh/3dc9vzbykx8tsgf/Co7mmur_y3"> JSMeter papers </a>

<a href="http://www.ditii.com/2010/03/26/jsmeter-microsoft-research-project-measuring-javascript-web-applications-screencast/"> JSMeter Screencast </a>

<a href="http://www.webkit.org/perf/sunspider/sunspider.html"> Sunspider Javascript Benchmark </a>

<a href="https://docs.google.com/open?id=0B7k8gRZJ3pcARTZtdjBMbl9EWjg"> the Javascript paper </a>

## Professor Reddi's papers on web search optimization ##

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2011/8/1_Mobile_Processors_for_Energy-Efficient_Web_Search%2C_In__i_IEEE_Transactions_on_Computer_Systems_(TOCS)__i_%2C_Vol._29%2C_No._4%2C_Article_9%2C_August_2011..html"> Mobile Processors for Energy-Efficient Web Search </a>

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2010/6/1_Web_Search_Using_Mobile_Cores__Quantifying_and_Mitigating_the_Price_of_Efficiency%2C_In__i_Proceedings_of_the_37th_ACM_IEEE_International_Symposium_on_Computer_Architecture_(ISCA)__i_%2C_June_2010..html">Web Search Using Mobile Cores: Quantifying and Mitigating the Price of Efficiency</a>

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2009/8/1_Web_Search_Using_Small_Cores__Quantifying_the_Price_of_Efficiency%2C_In__i_Microsoft_Research_Technical_Report_(MSR-TR)-2009-105__i_%2C_August_2009..html">Web Search Using Small Cores: Quantifying the Price of Efficiency</a>


## Profiling ##

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2007/3/1_Shadow_Profiling__Hiding_Instrumentation_Costs_with_Parallelism%2C_In__i_Proceedings_of_the_5th_International_Conference_on_Code_Generation_and_Optimization_(CGO)__i_%2C_March_2007..html">Shadow Profiling: Hiding Instrumentation Costs with Parallelism</a>

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2005/6/1_Pin__Building_Customized_Program_Analysis_Tools_with_Dynamic_Instrumentation%2C_In__i_Proceedings_of_Programming_Language_Design_and_Implementation_(PLDI)__i_%2C_June_2005..html">Pin: Building Customized Program Analysis Tools with Dynamic Instrumentation</a>

<a href="http://users.ece.utexas.edu/~vjreddi/UT/Publications/Entries/2004/6/1_PIN__A_Binary_Instrumentation_Tool_in_Computer_Architecture_Research_and_Education%2C_In__i_Proceedings_of_the_7th_International_Workshop_on_Computer_Architecture_Education_(WCAE)__i_%2C_June_2004..html">PIN: A Binary Instrumentation Tool in Computer Architecture Research and Education</a>

## Web performance literatures ##

https://www.dropbox.com/sh/p39fh0d9dcsod3h/pZL4E-Y_nO

http://books.google.com/books?hl=en&lr=&id=sX60mAi0eQUC&oi=fnd&pg=PR11&dq=web+performance+compilation+optimization&ots=UlLj7KT3js&sig=xW5de3pgbNjk6PWgYgq8mD-GsQw#v=onepage&q&f=false

http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=1530797&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D1530797


http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=727070&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D727070

http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=780957&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D780957

http://dl.acm.org/citation.cfm?id=1164159
