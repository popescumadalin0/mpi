<h1 align="center"> Procesarea de text (en. Text Processing) </h1> <br>
<p align="center">
</p>

## Table of Contents

- [Introduction](#introduction)
- [Programming language](#programming_language)
- [Framework](#framework)
- [Machine specs](#machine_specs)
- [Sequential execution times](#sequential-execution-times)
- [Parallel execution times](#parallel-execution-times)

## Introduction

Counting the frequency of words in a large text file can be parallelized by processing different parts of the file on separate threads or processors.

## Programming language

* C++
  
## Framework

* MPI + STL

## Machine specs

* OS:  Windows 11 Pro;
* CPU:  AMD Ryzen 7 4800H;
* RAM: 16.0 GB ;
* Storage: SSD 1TB;
* Compiler: Visual Studio 2022

## Sequential execution times

-10k words: 8824 microseconds

-50k words: 24353 microseconds

-100k words: 43662 microseconds

-500k words: 209091 microseconds

-1M words: 419079 microseconds

## Parallel execution times

-10k words: 14950 microseconds

-64k words: 14003 microseconds

-100k words: 14474 microseconds

-500k words: 30764 microseconds

-1M words: 58858 microseconds
