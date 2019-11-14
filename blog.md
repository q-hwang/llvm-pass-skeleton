+++
title = "Profile Guided Basic Block Reordering"
extra.author = "Qian Huang and Horace He"
extra.bio = """
Qian Huang is a junior undergraduate studying CS and Mathematics.

Horace He is a senior undergraduate studying CS and Mathematics
"""
+++

# Profile Guided Basic Block Reordering

Instruction order is key to improve cache utilization and avoid branch missing panelty. One simple way to do it is basic block reordering. The idea is to make instructions executed as sequentially as possible before one branching to improve cashe locality.


The de facto code positioning technique is provided in [Profile Guided Code Positioning](http://pages.cs.wisc.edu/~fischer/cs701.f06/code.positioning.pdf)

Codestitcher: Inter-Procedural Basic Block Layout Optimization https://arxiv.org/pdf/1810.00905.pdf


## Design Overview

In this project, we implemeted the algo2 in Profile Guided Code Positioning as an llvm pass. We use clang profiling support via instrumentation to obtain frequencies of each branch. They are used as edges weight as described in algo2. 

The algorithm identify frequently executed "chains", i.e. paths of basic blocks. It starts by setting all basic blocks as individual chains. Then the edges are iterated from highest weight to lowest. For each edge, the chains will merged if that edge is connecting tail and head of two chains. We implemented this by maintaining the start of chains and the next block relationships in hashmaps. Then the chains are merged based on original block ordering.


## Evaluation

In evaluation, we try to evaluate the cache and branch missing rates

### Initial Testing
Initially we wrote simple test cases, 

### Benchmark Testing

We evaluated on PARSEC

### Benchmark Results


### Extensions and Improvement

Ideally we would like to implement more complicated position ordering. 
