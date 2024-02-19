// implementation of the member functions of Person class
#include "Person.hpp"

// a pimpl class which contains the private data members of the Person class
class Person::pImplPerson {
    public: 
    std::string mName;
    std::string mStrength;
    std::string mSpeed;
};

// now all member functions access these data members only through an opaque pointer (a pointer to a data structure through which we cannot see the details)

Person::Person(std::string name) {
    // we need to dynamically allocate memory to this pointer
    mImpl = new pImplPerson;
    mImpl->mName = name;
    mImpl->mSpeed = "n/a";
    mImpl->mStrength = "n/a";
}

Person::~Person() {
    // make sure to de-allocate the memory which has been allocated
    delete mImpl;
}

std::string Person::getAttributes() {
    return mImpl->mName + ", " + mImpl->mStrength + ", " + mImpl->mSpeed;
}