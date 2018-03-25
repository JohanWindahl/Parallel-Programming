#ifndef lacpp_sorted_list_hpp
#define lacpp_sorted_list_hpp lacpp_sorted_list_hpp

#include <thread>
#include <mutex>
#include <atomic>
/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */

using namespace std;

  std::atomic_bool listlock;
/* struct for list nodes */
template<typename T>
struct node {
  T value;
  node<T>* next;
};

/* non-concurrent sorted singly-linked list */
template<typename T>
class sorted_list {
  node<T>* first = nullptr;

public:
  /* default implementations:
   * default constructor
   * copy constructor (note: shallow copy)
   * move constructor
   * copy assignment operator (note: shallow copy)
   * move assignment operator
   *
   * The first is required due to the others,
   * which are explicitly listed due to the rule of five.
   */
  sorted_list() = default;
  sorted_list(const sorted_list<T>& other) = default;
  sorted_list(sorted_list<T>&& other) = default;
  sorted_list<T>& operator=(const sorted_list<T>& other) = default;
  sorted_list<T>& operator=(sorted_list<T>&& other) = default;
  ~sorted_list() {
    while(first != nullptr) {
      remove(first->value);
    }
  listlock = false;
  }

  void tatas_lock(atomic<bool> lock)
  {
      do {
          while (lock) continue;
      } while (lock.exchange(1));
      return;
  }

  void tatas_lock_unlock(atomic<bool> lock){

    listlock.exchange(0);
  }


  /* insert v into the list */
  void insert(T v) {
    do {
        while (listlock) continue;
    } while (listlock.exchange(1));

      /* first find position */
      node<T>* pred = nullptr;
    node<T>* succ = first;
    while(succ != nullptr && succ->value < v) {
      pred = succ;
      succ = succ->next;
    }

    /* construct new node */
    node<T>* current = new node<T>();
    current->value = v;

    /* insert new node between pred and succ */
    current->next = succ;
    if(pred == nullptr) {
      first = current;
    } else {
      pred->next = current;
    }

    listlock.exchange(0);
  }

  void remove(T v) {
    do {
        while (listlock) continue;
    } while (listlock.exchange(1));
    /* first find position */
    node<T>* pred = nullptr;
    node<T>* current = first;
    while(current != nullptr && current->value < v) {
      pred = current;
      current = current->next;
    }
    if(current == nullptr || current->value != v) {
      listlock.exchange(0);
      /* v not found */
      return;
    }
    /* remove current */
    if(pred == nullptr) {
      first = current->next;
    } else {
      pred->next = current->next;
    }
    delete current;
    listlock.exchange(0);
  }

  /* count elements with value v in the list */
  std::size_t count(T v) {

    do {
        while (listlock) continue;
    } while (listlock.exchange(1));

    std::size_t cnt = 0;
    /* first go to value v */
    node<T>* current = first;
    while(current != nullptr && current->value < v) {
      current = current->next;
    }
    /* count elements */
    while(current != nullptr && current->value == v) {
      cnt++;
      current = current->next;
    }
    listlock.exchange(0);
    return cnt;
  }


};

#endif // lacpp_sorted_list_hpp
