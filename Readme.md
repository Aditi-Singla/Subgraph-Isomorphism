# Subgraph-Isomorphism

#### Goal

The subgraph isomorphism problem has been formulated and solved as a SAT problem using MINISAT. Formulation as SAT is a valuable skill in AI that will come in handy whenever we are faced with a new problem in NP class. SAT solvers over the years have become quite advanced and are often able to scale to decently sized real-world problems.

#### Scenario

You are an investigative agency working on uncovering a drug mafia. You have got telephone records of various telephone numbers which are believed to be associated with this mafia. You have also got a set of emails related to the mafia. However, you do not know which telephone number corresponds to which email address. The goal is to automatically figure out the mapping between emails and phones if it exists. To solve this problem (for our assignment), you make a few assumptions.

1. Some people are net savvy and use emails. All people know how to use phones. People who use emails regularly use both emails and phones to communicate with each other.
2. If a person X emailed a person Y, he also called Y on phone at some point. If X did not email a person Y (and both of them have email addresses), he did not call Y either.
3. Each person has exactly one email address and exactly one phone number.

You abstract out the problem by creating two graphs – Gphone and Gemail. There exists a directed edge between two nodes in Gphone (or in Gemail) if the first phone number (or email address) called (or emailed) the second. Your goal is find a mapping from emails to phone numbers. Gemail is the smaller graph because fewer people are net-savvy.

#### Problem Statement

There are two directed graphs G and G’. The graphs do not have self-edges. Find a one-one mapping M from nodes in G to nodes in G’ such that there is an edge from v1 to v2 in G if and only if there is an edge from M(v1) to M(v2) in G'.

#### Generation of Graphs

1. To generate an instance (G,G') -

    ```bash
    python generate.py n1 e1 n2 e2
    ```

    where n1,e1 are the number of nodes and edges in the bigger graph (G'), n2,e2 are the number of nodes and edges in the smaller graph (G).

    In the current code, it is guaranteed that G is a subgraph of G'. However, you can change the variable guaranteed_subgraph to false, to generate G,G' where G may not be a subgraph of G'. You can store in the instance in a file by redirecting the output to a file:

    ```bash
    python generate.py n1 e1 n2 e2 > filename
    ```

2. To check whether a mapping (in the given output format) is valid -

    ```bash
    python check.py test.input test.output
    ```
    where test.input is in the described input format, and test.output is in the described output format.


#### Running the code


1. To compile -

    ```bash
    ./scripts/compile.sh
    ```

2. To run - 

    ```bash
    ./scripts/run.sh <test>
    ```

    This takes `data/&lt;test&gt;.graphs` as input  and outputs `data/&lt;test&gt;.mapping`. It creates an intermediate `data/&lt;test&gt;.satinput` which is fed into the minisat solver which outputs `data/&lt;test&gt;.satoutput`, that if further processed to give the mapping.

#### Times


   |     Size     |      Time     |   MINISAT Time   |   Parse Time   |
   | ------------ | ------------- | ---------------- | -------------- |
   |   221.4 KB   |   0.037263 s  |    0.008377 s    |      0.01 s    |
   |   230.6 MB   |   20.8872 s   |    1.96996 s     |      1.73 s    |
   |    445 MB    |   38.0229 s   |    5.32379 s     |      3.20 s    |
   |   509.6 MB   |   69.6111 s   |    4.37252 s     |      4.03 s    |
   |    1.3 GB    |   329.074 s   |    12.0110 s     |      11.61 s   |
   |    1.1 GB    |   300.142 s   |    10.1426 s     |      9.80 s    |
