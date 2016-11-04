### Introduction to Intelligent Computing
# Midterm Project

Implement a computer program that uses MCTS (Monte Carlo Tree Search) to play a __five-in-a-line__ in a Go-game board of __15 by 15__. (The true GO game board is 19 by 19)

## Rules
A five-in-a-line GO game winner is the one who can “firstly” play the stones (Black or White) in a connected line either horizontal or vertical or diagonal in the Go-game board. We assign the board position according to the `Row (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)` and the `Column (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14)`, So the center position is at the coordinate (H,7). You should specify the stone to play at the certain position in term of the format `[Black (H,7)]`; `[White,(G,6)]`, etc. for example, so that every one can use the same representation to show to other where the stones are played.

We assume _Black play first_, and white play the second. So you should allow the program to play either in black stone or the white stone. We also would only the program to spend _no more than 10 seconds_ to play a move. So you should control your MCTS computation resource to explore the space within the time limit. You should consider the “quality score” of a `win`, `tie`, `lose` of a game for backpropragation to a selection node and balance parameters between the exploration and exploitation.You could combine other heuristics or knowledge to enhance the chance of winning.
