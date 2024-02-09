// friend function and friend classes in CPP
#include <iostream>

// friend function: a non-member function which is able to access the private data members and member functions of a class.
// note that these functions do not belong to the class, and can be invoked without using objects.
// friend functions need object(s) as arguments in order to be able to access private data members. 

// now, there might be a case where multiple functions of a particular class might require access to the private data members
// of another class, and in such a case we cannot keep individually declaring each function as a friend.
// friend class: an external class whose member functions are allowed to access the private members of another class.

// declaring A after B is not working. 
/* error: 
friendfuncclass.cpp:18:27: error: unknown type name 'A'
        void incrementAll(A& a) { a.a_pvt++; a.a_prot++; a.a_pub++; }   
                          ^
*/

// forward declaration used only when B is declared before A here
// now we also need to ensure that the member functions of B are not accessing any members of A because then it will throw this error"
/*
friendfuncclass.cpp:39:36: error: member access into incomplete type 'A'
        void incrementAll(A& a) { a.a_pvt++; a.a_prot++; a.a_pub++; }   
                                   ^
friendfuncclass.cpp:34:7: note: forward declaration of 'A'
class A;
      ^
*/

class A;

// friend class which if not declared as friend will not be able to access private and protected members
class B {
    public: 
        void incrementAll(A& a);
        void decrementAll(A& a);
        void setToValue(A& a, int x, int y, int z);
};

class A {
    private:
        int a_pvt;
    protected:
        int a_prot;
    public: 
        int a_pub;
        A() { a_pvt = 0; a_prot = 1; a_pub = 2; }

        // this function can now be defined outside the class (non-member)
        friend void modifyFriend(A& a, int x, int y, int z);

        // this class has now been declared as a friend
        friend class B;

        void modifyClass(int x, int y, int z) {
            a_pvt = x; a_prot = y; a_pub = z;
        }
        
        void display() {
            std::cout << "private var value: " << a_pvt << std::endl;
            std::cout << "protected var value: " << a_prot << std::endl;
            std::cout << "public var value: " << a_pub << std::endl;
        }
};

void B :: incrementAll(A& a) { a.a_pvt++; a.a_prot++; a.a_pub++; }   
void B :: decrementAll(A& a) { a.a_pvt--; a.a_prot--; a.a_pub--; }   
void B :: setToValue(A& a, int x, int y, int z) { a.a_pvt = x; a.a_prot = y; a.a_pub = z; } 

// declaring B after A is working
// friend class which if not declared as friend will not be able to access private and protected members
/*
class B {
    public: 
        void incrementAll(A& a) { a.a_pvt++; a.a_prot++; a.a_pub++; }   
        void decrementAll(A& a) { a.a_pvt--; a.a_prot--; a.a_pub--; }   
        void setToValue(A& a, int x, int y, int z) { a.a_pvt = x; a.a_prot = y; a.a_pub = z; } 
};
*/

// if this is not declared as a friend then it will not be able to access private and protected members
void modifyFriend(A& a, int x, int y, int z) {
    a.a_pvt = x;
    a.a_prot = y;
    a.a_pub = z;
}

int main()
{
    A a;
    a.modifyClass(12, 13, 14);
    a.display();

    modifyFriend(a,123123,54463,8908);
    a.display();

    B b;
    b.setToValue(a,0,1,2);
    a.display();
    b.incrementAll(a);
    a.display();
    b.decrementAll(a);
    a.display();

    return 0;
}
