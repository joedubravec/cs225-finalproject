/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() : head_(NULL), tail_(NULL), length_(0)
 {  /*int list */}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(!empty()){
    while(head_ != NULL) {
      ListNode * temp = head_;
      head_ = head_->next;
      delete temp;

    }
  }

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  newNode -> next = head_;
  newNode -> prev = NULL;
  head_ = newNode;
  
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (tail_ != NULL) {
    tail_->next = newNode;
  }
  newNode -> next = NULL;
  newNode -> prev = tail_;
  tail_ = newNode;
  
  if (head_ == NULL) {
    head_ = newNode;
  }
  

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if (splitPoint == 0) {
    return start;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}



/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if ((this->size() <1) || (startPoint == endPoint) || startPoint == NULL || endPoint == NULL) {
    return;
  }
  ListNode *oneBefore = startPoint->prev;
  ListNode *oneAfter = endPoint->next;
  ListNode *curr = startPoint;
  ListNode *end = endPoint;
  ListNode *start = startPoint;
  int i =0;
  while(curr != oneAfter && curr !=NULL) {
   
    ListNode *temp = curr;
    curr = curr->next;
    if( i==0) {
      temp->prev = temp->next;
      temp->next = oneAfter;
    } else if (curr == oneAfter) {
      
      if(curr) {
        temp->next = temp->prev;
        temp->prev = oneBefore;
        curr->prev = start;
        if(oneBefore) {
          oneBefore->next = temp;
        } else {
          head_ = temp;
        }
      } else {
        temp->next = temp->prev;
        temp->prev = oneBefore;
        tail_ = start;
        if(oneBefore) {
          oneBefore->next = temp;
        } else {
          head_ = temp;
        }
      }
    } else {
      
      temp->next = temp->prev;
      temp->prev = curr;
    }
    i++;

  }
}



