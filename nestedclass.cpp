// nested classes - we can declare a class within the scope of another class
// the enclosed class becomes local to the enclosing class - very useful abstraction tool
#include <iostream>
using namespace std;

// the nested class can be described as a private or a public member as per the requirements

class Enclosing
{
    private:
        int b;
        class Nested
        {
            int y;
            // private member of enclosed class can be accessed in the nested class
            void nestedAccess(Enclosing *a)
            {
                cout << "Nested Class" << a->b;
            }
            void read();
        };
        
        // member of nested class cannot be accessed in enclosing class
        void enclosingAccess(Nested *n)
        {
            // cout << "Nested Class" << n->y;
        }
};

void Enclosing::Nested::read() {
    cout << "Read function of nested class defined here but declared inside the class." << endl;
}



int main() {
    
    return 0;
}