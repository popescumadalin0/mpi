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

-10k words: 1911 microseconds

-64k words: 3222 microseconds

-100k words: 2716 microseconds

-500k words: 6279 microseconds

-1M words: 13604 microseconds

## Parallel execution times

-10k words: 14950 microseconds

-64k words: 14003 microseconds

-100k words: 14474 microseconds

-500k words: 30764 microseconds

-1M words: 58858 microseconds
