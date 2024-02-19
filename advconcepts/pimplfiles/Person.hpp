// header file for the class Person
#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person {
    private: 
    // a pointer with a forward declared class
    class pImplPerson;
    pImplPerson* mImpl;

    // all these members can be moved to a class - and accessed through a pointer to that class
    // std::string mName;
    // std::string mStrength;
    // std::string mSpeed;

    public: 

    Person(std::string name);
    ~Person();
    std::string getAttributes();
};

#endif