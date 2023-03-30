#pragma once

#include <vector>

namespace aoc
{
    template<class T>
    void swap(std::vector<T> &arr, int i, int j)
    {
        auto tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    template<class T>
    auto quick_sort_partition(std::vector<T> &arr, int left, int right) -> int
    {
        // • maintaining 3 regions: < pivot, > pivot and “unexamined”
        // • move left bound to the right as long as element < pivot
        // • move right bound to the left as long as element > pivot
        // • swap the two elements encountered on the left and right
        // • continue until left and right search meet
        int i = left;
        int j = right;
        int pivot = arr[right]; // pick some pivot
        // arr[left, i] < pivot && arr[j, right+1] >= pivot
        while (i < j) {
            while (arr[i] < pivot && i < j) i++; // move left bound
            // i == j || (arr[left, i] < pivot && arr[i] >= pivot)
            while (arr[j - 1] >= pivot && i < j) j--; // move right bound
            // i == j || (arr[j-1]<pivot && arr[j, right+1] >= pivot)
            if (i < j) {
                swap(arr, i, j - 1);
                i++;
                j--;
            }
            // arr[left, i] < pivot && arr[j, right+1] >= pivot
        }
        // arr[left, i] < pivot &&  arr[j, right+1] >= pivot
        if (pivot < arr[i]) swap(arr, i, right);
        return i;
    }

    template<class T>
    void quick_sort(std::vector<T> &arr, int left, int right)
    {
        // Choose an element from the array to be sorted – called pivot
        // Partition array in two parts: smaller than and at least the pivot
        // Sort parts recursively and squeeze pivot inbetween sorted parts
        if (left < right) {
            auto i = quick_sort_partition(arr, left, right); // i is split point
            quick_sort(arr, left, i - 1); // sort left part
            quick_sort(arr, i + 1, right); // sort right part
        }
    }

    template<class T>
    void bubble_sort(std::vector<T> &arr)
    {
        for (int i = 0; i < arr.size(); ++i) {
            for (int j = 0; j < arr.size() - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) swap(arr, j, j + 1);
            }
        }
    }
}
