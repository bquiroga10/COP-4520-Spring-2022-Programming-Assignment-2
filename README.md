# COP-4520-Spring-2022-Programming-Assignment-2

## Problem 1: Minotaur’s Birthday Party

### Strategy:
The guests should decide on a leader. The leader is the only guest that is allowed to eat cupcakes. If the leader gets to the end of the labyrinth, they will eat a cupcake if it is on the plate, otherwise, they will do nothing.

For someone that is not the leader, when they get to the end of the labyrinth, if the plate has a cupcake, do nothing. Otherwise, that means the plate is empty, and they will refill the plate **if they have not refilled it before**. If they have already refilled the plate once, they do nothing.

By doing this strategy, this guarentees that everyone excluding the leader refills the plate exactly once each, giving a total of _N_ - 1 cupcakes for the leader to eat. And since the plate begins with a cupcake on it, the leader will eat that single cupcake. In total, the leader will eat (_N_ - 1) + 1 = _N_, and once they have eaten their _N_'th cupcake, they know that every guest has had a chance to enter the maze at least once, and they can let the minotaur know of that.


### Efficiency:
The solution is pretty inefficient. For every time that the leader enters the labyrinth, someone that hasn't refilled the plate must have entered as well. This is somewhat of a linear process for each time the leader enters, and the leader has to enter N times, so the efficiency is probably an average of _O_(_N_^2).


### Instructions to run problem 1

Run the command `g++ --std=c++17 -pthread -O2 -o assignment2part1 assignment2part1.cpp` to compile the code.

Run the command `./assignment2part1` to run the code.


## Problem 2: Minotaur’s Crystal Vase

### Strategy 1:
Strategy 1 is really inefficient, mostly because anyone can try and go into the showroom. By allowing that, every guest that wants to go in is trying to go inside constantly. It's possible that a guest can't get in there since it's not queue based. For example, if there are 5 guests, and guests 1, 2, 3, 4 continuously go in while guest 5 is stuck outside, guest 5 would be stuck never getting to go inside.

### Strategy 2:
Strategy 2 is better than strategy 1, but is still troublesome. It's basically first come first serve for when the room is available, but, if you know that the room is unavailable, you can do other things before trying to come back and check again. You run into the same issues as strategy 1, where a guest might never be able to enter because others will come by and go into the showroom while that guest is busy doing other things. The benefit though is that a guest doesn't have to waste time. This is just strategy 1, but you don't have to wait at the door to see if you can enter.

### Strategy 3:
Strategy 3 is a good strategy. The benefit to strategy 3 is that everyone will eventually get their turn, since a guest can just enter the queue and wait for their turn. The disadvantage is that it takes time, since you have to wait in the queue. This is just strategy 1 but with the guarantee that everyone will eventually get to go in.
