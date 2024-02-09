#include <iostream>
#include <string>

int main() {
    std::string base="this is a test string.";
    std::string str2="n example";
    std::string str3="sample phrase";
    std::string str4="useful.";

    // replace signatures used in the same order as described above:

    // Using positions:                 0123456789*123456789*12345
    std::string str=base;           // "this is a test string."
    std::cout << str << std::endl;
    
    // starting pos, length, string to replace
    str.replace(9,5,str2);          // "this is an example string." (1)
    std::cout << str << std::endl;

    // starting pos, length, string to replace, it's starting pos & length
    str.replace(19,6,str3,7,6);     // "this is an example phrase." (2)
    std::cout << str << std::endl;

    str.replace(8,10,"just a");     // "this is just a phrase."     (3)
    std::cout << str << std::endl;

    // only giving the length along with the string
    str.replace(8,6,"a shorty",7);  // "this is a short phrase."    (4)
    std::cout << str << std::endl;

    // giving the character and the number of times you want it to be repeated to replace
    str.replace(22,1,3,'!');        // "this is a short phrase!!!"  (5)
    std::cout << str << std::endl;
    return 0;
} 