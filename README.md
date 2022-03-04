# COP-4520-Spring-2022-Programming-Assignment-2

## Problem 1: Minotaur’s Birthday Party

### Strategy:
The guests should decide on a leader. The leader is the only guest that is allowed to eat cupcakes. If the leader gets to the end of the labyrinth, they will eat a cupcake if it is on the plate, otherwise, they will do nothing.

For someone that is not the leader, when they get to the end of the labyrinth, if the plate has a cupcake, do nothing. Otherwise, that means the plate is empty, and they will refill the plate **if they have not refilled it before**. If they have already refilled the plate once, they do nothing.

By doing this strategy, this guarentees that everyone excluding the leader refills the plate exactly once each, giving a total of _N_ - 1 cupcakes for the leader to eat. And since the plate begins with a cupcake on it, the leader will eat that single cupcake. In total, the leader will eat (_N_ - 1) + 1 = _N_, and once they have eaten their _N_'th cupcake, they know that every guest has had a chance to enter the maze at least once, and they can let the minotaur know of that.


### Efficiency:
The solution is pretty innefficient. For every time that the leader enters the labyrinth, someone that hasn't refilled the plate must have entered as well. This is somewhat of a linear process for each time the leader enters, and the leader has to enter N times, so the efficiency is probably an average of _O_(_N_^2).
