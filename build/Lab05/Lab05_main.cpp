#include <iostream>
#include <fstream>
#include <chrono>
#include <ostream>
#include "array_list.h"
#include "array_list_utility.h"

void tests(int maxSize, int steps)
{
    std::ofstream file("data.csv");
    file << "Size,QuickSort,BubbleSort,Shuffle,BinarySearch,LinearSearch\n";

    for (int size = 1000; size <= maxSize; size += steps)
    {
        ssuds::ArrayList<float> list;
        for (int i = 0; i < size; i++)
            list.append(i + 0.5);

        auto start = std::chrono::high_resolution_clock::now();
        shuffle(list);
        auto stop = std::chrono::high_resolution_clock::now();
        auto shuffle_Time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        ssuds::ArrayList<float> bubbleSort_List = list;
        if (size <= 300000)
        {
            start = std::chrono::high_resolution_clock::now();
            bubbleSort(bubbleSort_List, SortOrder::ASCENDING);
            stop = std::chrono::high_resolution_clock::now();
        }
        auto bubbleSort_Time = (size <= 300000) ? std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() : -1;

        start = std::chrono::high_resolution_clock::now();
        quickSort(list, SortOrder::ASCENDING);
        stop = std::chrono::high_resolution_clock::now();
        auto quickSort_Time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        ssuds::ArrayList<float> random_elements;
        for (int i = 0; i < 1000; i++)
        {
            random_elements.append(list[i * (size / 1000)]);
        }

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            binarySearch(list, random_elements[i], SortOrder::ASCENDING);
        }
        stop = std::chrono::high_resolution_clock::now();
        auto binarySearch_Time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            int found = -1;
            for (int j = 0; j < size; j++)
            {
                if (list[j] == random_elements[i])
                {
                    found = j;
                    break;
                }
            }
        }
        stop = std::chrono::high_resolution_clock::now();
        auto linearSearch_Time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

        file << size << "," << quickSort_Time << "," << binarySearch_Time << "," << shuffle_Time << "," << binarySearch_Time << "," << linearSearch_Time << "\n";

        std::cout << "Completed test for size: " << size << std::endl;
    }

    file.close();
}

int main()
{
    tests(1000000, 5000);
    std::cout << "Tests complete." << std::endl;
    return 0;
}