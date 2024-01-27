#define null 0

namespace ufl_cap4053 {
    namespace fundamentals {

        template <class T>
        class LinkedList {
            
        private:

            template <class T>
            class LinkedListNode {

            private:

                friend class LinkedList;
                friend class Iterator;

                T data;
                LinkedListNode* prev;
                LinkedListNode* next;

                LinkedListNode<T>() {
                    LinkedListNode(null);
                }

                LinkedListNode<T>(T newData) {
                    LinkedListNode(newData, nullptr, nullptr);
                }

                LinkedListNode<T>(T newData, LinkedListNode* prev, LinkedListNode* next) {
                    this->data = newData;
                    this->prev = prev;
                    this->next = next;
                }

            };

            LinkedListNode<T>* front;
            LinkedListNode<T>* back;

        public:
            
            class Iterator {

            private:
                LinkedListNode<T>* node;

            public:

                Iterator() {
                    this->node = nullptr;
                }

                Iterator(LinkedListNode<T>* node) {
                    this->node = node;
                }

                T operator*() const {
                    //Return the element at the iterator's current position in the queue.
                    return this->node->data;
                }

                Iterator& operator++() {
                    //Pre-increment overload; advance the operator one position in the list. Return this iterator. NOTE: if the
                    //iterator has reached the end of the list (past the last element), it should be equal to LinkedList<T>::end().
                    if (this->node == nullptr) {
                        return *this;
                    }
                    this->node = this->node->next;
                    return *this;
                }

                bool operator==(Iterator const& rhs) {
                    //Returns true if both iterators point to the same node in the list, and false otherwise.
                    return (rhs.node == this->node);
                }

                bool operator!=(Iterator const& rhs) {
                    //Returns false if both iterators point to the same node in the list, and true otherwise.
                    return (rhs.node != this->node);
                }
            };

            LinkedList<T>() {
                //This is the constructor for LinkedList.
                this->front = nullptr;
                this->back = nullptr;
            }

            ~LinkedList<T>() {
                this->clear();
            }

            Iterator begin() const {
                //Returns an Iterator pointing to the beginning of the list.
                return LinkedList::Iterator(this->front);
            }

            Iterator end() const {
                //Returns an Iterator pointing past the end of the list (an invalid, unique state).
                return LinkedList::Iterator(nullptr);
            }

            bool isEmpty() const {
                //Returns true if there are no elements, false otherwise.
                return (front == nullptr && back == nullptr);
            }

            T getFront() const {
                //Returns the first element in the list.
                if (this->front != nullptr) {
                    return this->front->data;
                }
                return null;
            }

            T getBack() const {
                //Returns the last element in the list.
                if (this->back != nullptr) {
                    return this->back->data;
                }
                return null;

            }

            void enqueue(T element) {
                //Inserts the specified element at the end of the list.
                if (this->front == nullptr) {
                    LinkedListNode<T>* temp = new LinkedListNode<T>(element, nullptr, nullptr);
                    this->front = temp;
                    this->back = temp;
                    return;
                }

                LinkedListNode<T>* temp = new LinkedListNode<T>(element, this->back, nullptr);
                this->back->next = temp;
                this->back = temp;
            }

            void dequeue() {
                //Removes the first element from the list.
                if (this->front == nullptr) {
                    return;
                }
                if (this->front == this->back) {
                    delete this->front;
                    this->front = nullptr;
                    this->back = nullptr;
                    return;
                }

                LinkedListNode<T>* oldFront = this->front;

                this->front = this->front->next;
                this->front->prev = nullptr;

                delete oldFront;
            }

            void pop() {
                //Removes the last element from the list.
                if (this->back == nullptr) {
                    return;
                }
                if (this->front == this->back) {
                    delete this->front;
                    this->front = nullptr;
                    this->back = nullptr;
                    return;
                }

                LinkedListNode<T>* oldBack = this->back;

                this->back = this->back->prev;
                this->back->next = nullptr;

                delete oldBack;
            }

            void clear() {
                //Removes all elements from the list.
                while (this->front != nullptr) {
                    pop();
                }
            }

            bool contains(T element) const {
                //Returns true if you find a node whose data equals the specified element, false otherwise.
                LinkedListNode<T>* node = this->front;

                while (node != nullptr) {
                    if (node->data == element) {
                        return true;
                    }
                    node = node->next;
                }

                return false;
            }

            void remove(T element) {
                //Removes the first node you find whose data equals the specified element
                LinkedListNode<T>* node = this->front;

                while (node != nullptr) {
                    if (node->data == element) {

                        if (node == this->front) {
                            dequeue();
                            return;
                        }
                        if (node == this->back) {
                            pop();
                            return;
                        }
                        if (this->front == this->back) {
                            delete this->front;
                            this->front = nullptr;
                            this->back = nullptr;
                            return;
                        }

                        LinkedListNode<T>* prev = node->prev;
                        LinkedListNode<T>* next = node->next;

                        delete node;

                        prev->next = next;
                        next->prev = prev;

                        return;
                    }
                    node = node->next;
                }
            }

        };

    };
};