// implementing unique_ptr and shared_ptr from scratch
#include <iostream>
#include <memory>

// generic typed RAII style class for unique pointer
template<typename T>
class uniquePtr {
    private:
        // a pointer which points to the resource
        T* res;

    public:
        // regular parameterised constructor with initialiser list
        uniquePtr(T* ptr = nullptr) : res(ptr) {
            std::cout << "constructor" << std::endl;
        }   

        // since this pointer can have only one pointing to a particular resource, the copy constructor and copy assignment operators
        // are 'deleted' - which ensures that these constructors remain disabled 
        uniquePtr(const uniquePtr<T>& ptr) = delete;
        uniquePtr& operator=(const uniquePtr<T>& ptr) = delete;

        // move constructor - since the pointer being assigned does not have any value, no need to delete it, just assign it the resource
        // and unlink 'ptr' from that same resource, to ensure only one pointer points to the resource at a time
        uniquePtr(uniquePtr<T>&& ptr) {
            std::cout << "move constructor" << std::endl;
            res = ptr.res;
            ptr.res = nullptr;
        }

        // move assignment operator - now, we need to make sure we do not end up doing ptr = ptr and causing unexpected behaviour, so for that
        // we provide a condition which checks whether the pointers are the same or not, and perform the move assignment only when not same
        // in move assigning, the pointer being assigned is unlinked from its previous resource first, and then this new resource is assigned
        uniquePtr& operator=(uniquePtr<T>&& ptr) {
            std::cout << "move assignment" << std::endl;
            if(this != &ptr) {
                if(res) delete res;
                res = ptr.res;
                ptr.res = nullptr;
            }
            return *this;
        }

        T* operator->() {
            return res;
        }

        T& operator*() {
            return *res;
        }

        T* get() {
            return res;
        }

        // reset functionality just involves unlinking the pointer from its current resource, and assigning it a new resource
        void reset(T* newRes) {
            if(res) delete res;
            res = newRes;
        }

        // destructor makes sure that all the dynamically allocated resources are de-allocated when the object goes out of scope
        ~uniquePtr() {
            if(res) {
                delete res;
                res = nullptr;
            }
            std::cout << "destructor" << std::endl;
        }
};

// generic typed RAII style class for shared pointer
template<typename T>
class sharedPtr {
    private: 
        // along with a pointer to resource, this smart pointer also keeps track of a counter
        // which acutally helps track how many pointers are pointing to this particular resource
        T* res;
        int* counter;

        // private function to increment counter
        void incrementCounter() {
            if(counter) (*counter)++;
        }

        // private function to decrement counter - note that if the count becomes zero, the resource is unlinked 
        // and the smart pointer is reset
        void decrementCounter() {
            if(counter) {
                (*counter)--;
                if((*counter) == 0) {
                    if(res) {
                        delete res;
                        delete counter;
                        res = nullptr;
                        counter = nullptr;
                    }
                }
            }
        }

    public:
        // constructor 
        sharedPtr(T* ptr = nullptr) : res(ptr), counter(new int(1)) {
            std::cout << "constructor" << std::endl;
        }

        // copy constructor - increments the counter after assigning the resource to the shared pointer
        sharedPtr(const sharedPtr<T>& ptr) {
            std::cout << "copy constructor" << std::endl;
            res = ptr.res;
            counter = ptr.counter;
            incrementCounter();
        }
        
        // copy assignment operator - now, both 'this' and 'ptr' are pointing to different resources, so we first decrement the counter
        // assign the resources and counter of 'ptr' to the current shared pointer, and then increment pointer
        // note that, both ptr and 'this' should not be equal, to avoid undefined behaviour
        sharedPtr& operator=(const sharedPtr<T>& ptr) {
            std::cout << "copy assignment" << std::endl;
            if(this != &ptr) {
                decrementCounter();
                res = ptr.res;
                counter = ptr.counter;
                incrementCounter();
            }
            return *this;
        }   

        // move constructor - we just need to move the ownership from 'ptr' to the current pointer
        // count does not change
        sharedPtr(sharedPtr<T>&& ptr) {
            std::cout << "move constructor" << std::endl;
            res = ptr.res;
            counter = ptr.counter;
            // no need to increment count
        }

        // move assignment operator - now both 'ptr' and 'this' point to different resources, so we first decrement the count of
        // current pointer, assign it to point to the new resource, and make 'ptr' point to nothing since ownership has now been transferred
        // again, we cannot have both 'this' and 'ptr' point to the same resource, so we check that before doing any operation
        sharedPtr& operator=(sharedPtr<T>&& ptr) {
            std::cout << "move assignment" << std::endl;
            if(this != &ptr) {
                decrementCounter();
                res = ptr.res;
                counter = ptr.counter;
                ptr.res = nullptr;
                ptr.counter = nullptr;
            }
            return *this;
        }

        // reset - decrement the counter, then assign new resource to the current pointer
        // now since the pointer points to a new resource, we need a new counter as well, to keep track
        // of the number of shared pointers pointing to that resource
        void reset(T* newRes) {
            decrementCounter();
            res = newRes;
            counter = new int(1);
        }

        int getCount() { if(counter) return *counter; }

        T* operator->() { return res; }
        T& operator*() { if(res) return *res; }
        T* get() { return res; }

        // we have taken care of the resource destruction logic in the decrementCounter function
        ~sharedPtr() {
            std::cout << "destructor" << std::endl;
            decrementCounter();
        }

};

int main() {
    /*
    // parameterised constructor
    uniquePtr<int> ptr1(new int(3));
    
    // copy constructors
    uniquePtr<int> ptr2(ptr1);
    uniquePtr<int> ptr3 = ptr1;

    // copy assignment operator
    uniquePtr<int> ptr4(new int(500));
    ptr4 = ptr3;
    uniquePtr<int> ptr3(new int(100));

    // move constructor
    uniquePtr<int> ptr4 = std::move(ptr1);

    // move assignment operator
    uniquePtr<int> ptr5;
    ptr5 = std::move(ptr3);

    */
    sharedPtr<int> ptr1(new int(123));

    sharedPtr<int> ptr2(ptr1);
    sharedPtr<int> ptr3 = ptr1;

    sharedPtr<int> ptr4 = std::move(ptr1);

    sharedPtr<int> ptr5;
    ptr5 = std::move(ptr2);


    return 0;
}