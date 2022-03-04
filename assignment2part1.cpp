#include <bits/stdc++.h>

using namespace std;

// We'll fix the value of N to 10
const int N = 30;

// how many cupcakes have been eaten so far
int eatenCounter = 0;

// whether or not a cupcake is on the plate or not
// it is explicitly stated that the plate begins with a cupcake,
// so start it as true
bool cupcakeOnPlate = true;

// if a guest has already refilled the plate or not
array<bool, N> hasRefilled;

// only the leader can write to it, main only checks the condition
atomic<bool> allGuestsHaveVisited;

// who's turn it is to enter the labyrinth
// no one's turn is marked as -1 (and begins as such)
int turn = -1;

mutex m;
condition_variable cv;
vector<thread> guests;

void guest(int x) {
  // wait for this guest's turn
  unique_lock<mutex> lock(m);
  cv.wait(lock, [&]{ return x == turn; });

  // they are the leader
  if(x == 0) {
    // eat cupcake if available
    if(cupcakeOnPlate) {
      cupcakeOnPlate = false;
      eatenCounter++;

      // if the leader has eaten N cupcakes, they know
      // everyone has entered the labyrinth
      if(eatenCounter == N) {
        allGuestsHaveVisited = true;
      }
    }
  } else {
    // if this guest (that isn't a leader) hasn't refilled the plate
    // and the plate is empty, they should refill it
    if(!cupcakeOnPlate && !hasRefilled[x]) {
      cupcakeOnPlate = true;
      hasRefilled[x] = true;
    }
  }

  // make the current turn as no one
  turn = -1;

  // unlock and notify all other threads
  lock.unlock();
  cv.notify_all();
}

// have guest x enter the labyrinth
void enterLabyrinth(int x) {
  // Set the turn to be guest x
  {
    lock_guard<mutex> lock(m);
    turn = x;
  }

  // notify all threads to check their predicate
  cv.notify_all();

  // wait for the current guest in the labyrinth to exit
  {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [&]{ return turn == -1; });
  }

  // join their thread to wait for completion
  guests[x].join();
}

int main() {
  // fill hasRefilled with false
  for(int i = 0; i < N; i++)
    hasRefilled[i] = false;

  // create guest threads
  for(int i = 0; i < N; i++)
    guests.push_back(thread(guest, i));

  // seed our random number generator
  srand(time(0));

  // run while we don't know if all guests have visited
  while(!allGuestsHaveVisited) {
    // pick a random guest
    int x = rand() % N;

    // have this guest enter the labyrinth
    enterLabyrinth(x);

    // remake guest x's thread so they can wait to be called again
    guests[x] = thread(guest, x);
  }

  cout << "All guests have entered the labyrinth!" << endl;

  // have everyone "enter the labyrinth" one more time
  // so their threads closes
  for(int i = 0; i < N; i++) {
    enterLabyrinth(i);
  }

  return 0;
}
