#include <bits/stdc++.h>

using namespace std;

// We'll fix the value of N to 30
const int N = 30;

// who's turn it is
int turn = -1;

mutex m;
condition_variable cv;
vector<thread> guests;

void guest(int x) {
  // wait for this guest's turn
  unique_lock<mutex> lock(m);
  cv.wait(lock, [&]{ return x == turn; });

  // make the current turn as no one
  turn = -1;

  // unlock and notify all other threads
  lock.unlock();
  cv.notify_all();
}

// have guest x enter the showroom
void enterShowroom(int x) {
  // Set the turn to be guest x
  {
    lock_guard<mutex> lock(m);
    turn = x;
  }

  // notify all threads to check their predicate
  cv.notify_all();

  // wait for the current guest in the showroom to exit
  {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [&]{ return turn == -1; });
  }

  // join their thread to wait for completion
  guests[x].join();
}

int main() {
  // create guest threads
  for(int i = 0; i < N; i++)
    guests.push_back(thread(guest, i));

  // seed our random number generator
  srand(time(0));


  // put all the guests in the queue randomly
  queue<int> q;
  vector<int> allGuests;
  for(int i = 0; i < N; i++)
    allGuests.push_back(i);
  for(int i = 0; i < 1000; i++) {
    int a = rand() % N;
    int b = rand() % N;
    swap(allGuests[a], allGuests[b]);
  }
  for(int i = 0; i < N; i++) {
    cout << "Guest " << allGuests[i] << " entered the queue." << endl;
    q.push(allGuests[i]);
  }

  // while there are guests left that want to enter the showroom
  while(q.size() > 0) {
    // grab the guest at the front of the line
    int x = q.front();
    q.pop();

    cout << "Guest " << x << " entered the showroom." << endl;
    enterShowroom(x);
    cout << "Guest " << x << " exited the showroom." << endl;

    // Let's just assume that there is a 50/50 that the guest will get back into the queue
    int chance = rand() % 2;
    if(chance == 0) {
      cout << "Guest " << x << " entered the queue." << endl;
      guests[x] = thread(guest, x);
      q.push(x);
    }
  }

  cout << "The queue is now empty." << endl;

  return 0;
}
