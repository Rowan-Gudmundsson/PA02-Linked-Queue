//--------------------------------------------------------------------------
// PA02 - QueueLinked implimentation file
// Programmer - Rowan Gudmundsson
// Latest build - v1.0 09/11/17
//--------------------------------------------------------------------------

#include "QueueLinked.h"

// Node constructor using data and next pointer
template <typename DT>
QueueLinked<DT>::QueueNode::QueueNode(const DT& nodeData, QueueNode* nextPtr) : dataItem(nodeData), next(nextPtr) {} 

template <typename DT>
QueueLinked<DT>::QueueLinked(int) {
 
    front = NULL; //point to nothing
    back = NULL;
}

// Copy constructor for Linked Queue implimentation
template <typename DT>
QueueLinked<DT>::QueueLinked(const QueueLinked<DT>& other) {
 
    front = NULL; //first need to initialize pointers
    back = NULL;
    
    (*this) = other; //using overloaded assignment operator
}

// Overloaded assignment operator for Linked Queue 
template <typename DT>
QueueLinked<DT>& QueueLinked<DT>::operator = (const QueueLinked<DT>& other) {
 
    clear(); //first deallocate existing

    QueueNode* conductor;
    conductor = other.front; 

    while (conductor != NULL) { //traverse other

        enqueue(conductor->dataItem); //queue the data items of other into *this*
        conductor = conductor->next;
    }

    return *(this); //allowing list1 = list2 = list3
}

// Destructor for Linked Queue 
template <typename DT>
QueueLinked<DT>::~QueueLinked() {
    
    clear(); //clear deallocates memory, using this to deconstruct
}

// Enqueue function, adds items to list
template <typename DT>
void QueueLinked<DT>::enqueue(const DT& newDataItem) throw (logic_error) {
    
    if(isFull()) throw (logic_error("enqueue() queue full"));
    
    if(isEmpty()) { //if our list is empty
        
        back = new QueueNode(newDataItem, NULL); //back pointer is a new node pointing to nothing
        front = back; 
    }
    else {
        
        QueueNode* newNode = new QueueNode(newDataItem, NULL); //inserting a new node
        back->next = newNode;                                  //behind back pointer
        back = newNode;                                        //then moving back to the new node
    }
}

// Dequeue returns items from the list and removes said items 
template <typename DT>
DT QueueLinked<DT>::dequeue() throw (logic_error) {
    
    if(isEmpty()) throw (logic_error("dequeue() queue empty"));
    
    DT tmp = front->dataItem; //taking the data from the frontmost node
    
    if(front == back) { //easiest case
        
        delete[] front; //removing the single node
        front = NULL; //assigning pointers to null to avoid dangling pointers
        back = NULL;
    }
    else {
        
        QueueNode* tmpFront; //need a temporary front so as to not lose front pointer
        tmpFront = front; 
        front = front->next; //moving front to the next node
        tmpFront->next = NULL; //isolating the front node
        delete[] tmpFront;     //then deleting it
    }
    
    return tmp;
}

// Clear deallocates memory made for the list
template <typename DT>
void QueueLinked<DT>::clear() {
    
    while (!isEmpty()) {
        
        dequeue(); //returned data is garbage
    }
}

// Function which returns true if empty else false
template <typename DT>
bool QueueLinked<DT>::isEmpty() const {
    
    if(back == NULL) return true; //intuitive
    else return false;
}

// Function always returns false, Linked list is infinite (memory confined)
template <typename DT>
bool QueueLinked<DT>::isFull() const {
    
    return false; //constraints can be applied
}

// Functions adds item to the front instead of rear
template <typename DT>
void QueueLinked<DT>::putFront(const DT& newDataItem) throw (logic_error) {
 
    if(isFull()) throw (logic_error("putFront() queue full"));
    
    if(isEmpty()) enqueue(newDataItem); //doesn't matter for first node, front == back
    
    else {
        
        QueueNode* newNode = new QueueNode(newDataItem, front); //since front is essentially at the beginning of the list
        front = newNode;                                        //we treat it as though we are insterting behind front
    }
}

// Function removes item from the rear and returns the data 
template <typename DT>
DT QueueLinked<DT>::getRear() throw (logic_error) {
 
    if(isEmpty()) throw (logic_error("getRear() queue empty"));
    
    DT tmp;
    
    if(back == front) tmp = dequeue(); //if 1 item, front == back so the same as dequeue
    
    else {
     
        tmp = back->dataItem; //getting data item from rear
        
        QueueNode* tmpNode; //need to conductor to step through the list
        tmpNode = front;
        
        while (tmpNode->next != back) { //tmpNode will be the one next after back pointer (technically before)
         
            tmpNode = tmpNode->next;
        }
        
        delete[] back; //we already have the data from back
                
        tmpNode->next = NULL; //getting rid of dangling 
        back = tmpNode; //moving back pointer
    }
    
    return tmp;
}

// Returns the number of items in the list
template <typename DT>
int QueueLinked<DT>::getLength() const {
 
    if(isEmpty()) return 0; //intuitive
    
    int counter = 1; //already know its not empty so we start at 1
    
    QueueNode* conductor;
    conductor = front;
    
    while (conductor != back) {
     
        conductor = conductor->next; //every time we move to another node
        ++counter;                   //we incriment the counter
    }
    
    return counter;
}

// Prints the structure of the list, outputs all items
template < class DT >
void QueueLinked<DT>::showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}
