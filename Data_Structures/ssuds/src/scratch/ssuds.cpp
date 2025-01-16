// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>   // <string.h> is the C string library (not this)
#include <person.h>
using namespace std;    // Makes the std:: on stuff optional

int main()
{
    // C-strings-
    char s; //an integer, usually one byte.
    s = 'a'; //97

    char c_string[64] = "wade"; //98, 111, 98, 0, ?, ? .....
    const char* c_string2 = "mark"; //in the gloal variable section of our process
    printf("c_string = %s\n", c_string);
    //c_string = "robert";
    c_string[0] = 'r';
    c_string[1] = 'o';
    c_string[2] = 0;
    strcpy_s(c_string, 64, "robert");
    printf("c_string = %s\n", c_string);
    if (strcmp(c_string, "moo") > 0)
        printf("%s comes after \"moo\"\n", c_string);


    // Same, but with C++
    std::string cpp_string = "bob";     // making an INSTANCE of the string class called cpp_string
                                        // std is the NAMESPACE that the string class exists in
    std::cout << cpp_string << "\n";    // C++ style console output -- a taste of c++ STREAMS (this
                                        //   is an output stream which is why << goes to the left.
    int x = 42;
    std::cout << "a string" << x << "\n";
    cpp_string[0] = 'r';                // The [] operator is OVERLOADED for strings
    cpp_string[1] = 'o';
    cpp_string[2] = 0;
    std::cout << cpp_string << "\n";
    cpp_string = "robert";              // The class handles the memory copy and making enough space
                                        //   to hold this new string (nice!)
    if (cpp_string > "moo")             // Internally probably calling strcmp
        std::cout << cpp_string << "comes after \"moo\"\n";
    c_string2 = cpp_string.c_str();     // Getting the underlying C string...so we can use all our
                                        //   c functions.

    Person p;
    //p.id = 42;
    //p.first_name = "Bob";
    //p.calculate_pay();
    Person q;
    //p.id = 43;
    //p_first_name = "Mark";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
