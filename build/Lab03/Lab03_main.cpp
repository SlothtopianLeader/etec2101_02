#include <iostream>
#include "array_list.h"
#include <iomanip>


int main(int argc, char** argv)
{
    // The basic test program (for floats)
    ssuds::ArrayList<float> float_list;

    std::cout << "test1 (basics):\n=====\n";                        // test1 (basics):                       
    float_list.append(2.3f);                                        // ======
    float_list.append(2.6f);
    std::cout << "\tsize=" << float_list.size() << std::endl;       //     size=2
    std::cout << "\titem0=" << float_list.at(0) << std::endl;       //     item0=2.3
    std::cout << "\titem1=" << float_list.at(1) << std::endl;       //     item1=2.6
    float_list.at(0) -= 0.1f;
    float_list.at(1)++;
    std::cout << "\titem0=" << float_list.at(0) << std::endl;       //     item0=2.2
    std::cout << "\titem1=" << float_list.at(1) << std::endl;       //     item1=3.6

    std::cout << "\ntest2 (insert):\n=====\n";                      // test2 (insert):  
    float_list.insert(1.8f, 0);                                     // ======
    float_list.insert(4.2f, 3);                                     //     item0=1.8 
    float_list.insert(2.2f, 1);                                     //     item1=2.2
    for (unsigned int i = 0; i < float_list.size(); i++)            //     item2=2.2   
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; //     item3=3.6
    //     item4=4.2


    std::cout << "\ntest3 (grow):\n=====\n";                        // test3 (grow):
    // ======
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=5
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=5
    float_list.append(5.6f);   // <= a capacity increase should be triggered here
    float_list.append(2.2f);
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=7
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=10

    for (unsigned int i = 0; i < float_list.size(); i++)            //     item0=1.8              
        std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; //     item1=2.2   
    //     item2=2.2
    //     item3=3.6
    //     item4=4.2
    //     item5=5.6
    //     item6=2.2


    std::cout << "\ntest4 (stream):\n=====\n";                      // test4 (stream):
    // ======
    std::cout << "\t";
    float_list.output(std::cout);
    std::cout << std::endl;                                         //     [1.8, 2.2, 2.2, 3.6, 4.2, 5.6, 2.2]



    std::cout << "\ntest5 (find all):\n=====\n";                    // test5 (find all):
    int index = float_list.find(2.2f, 0);                           // =====
    while (index != -1)                                             //     Found occurrence of 2.2 at index 1
    {                                                               //     Found occurrence of 2.2 at index 2
        std::cout << "\tFound occurrence of 2.2 at index " << index << "\n";
        index++;            // Look at the next spot (or later)
        if (index == float_list.size())                             //     Found occurrence of 2.2 at index 6
            break;
        index = float_list.find(2.2f, index);
    }

    std::cout << "\ntest6 (remove_all [and remove]):\n=====\n";     // test6 (remove_all [and remove])
    // =====
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=7
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=10
    std::cout << "\tremoved " << float_list.remove_all(2.2f);                   // <= a capacity decrease should be triggered here
    std::cout << " items\n";                                        //     removed 3 items
    std::cout << "\t"; float_list.output(std::cout); std::cout << "\n"; //     [1.8, 3.6, 4.2, 5.6]
    std::cout << "\tsize=" << float_list.size() << "\n";            //     size=4
    std::cout << "\tcapacity=" << float_list.capacity() << "\n";    //     capacity=5

#
    return 0;
}


