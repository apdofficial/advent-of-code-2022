#pragma once

#include <optional>
#include <string>
#include <charconv>
#include <cstdlib>
#include <span>
#include <cassert>
#include <charconv>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>
#include <system_error>
#include <ranges>
#include <vector>
#include <fstream>

namespace aoc
{
    auto stooi(std::string_view line) -> std::optional<int>;

    auto map_to_int(std::span<const std::string> lines) -> std::vector<std::optional<int>>;

    class File
    {
    public:
        // class uses RAII
        // class invariant is: file.is_open()
        File(std::string_view file_path);

        ~File();

        auto is_valid() -> bool;

        auto read_lines() -> std::vector<std::string>;

    private:
        std::ifstream file;
    };

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

        for (int k = left; k<i; ++k) assert(arr[k] < pivot); // arr[left, i] < pivot
        for (int k = j; k<right+1; ++k) assert(arr[k] >= pivot); // arr[j, right+1] >= pivot

        while (i < j) {
            while (arr[i] < pivot && i<j) i++; // move left bound
            assert(i == j || arr[i] >= pivot); // i == j || arr[i] >= pivot
            for (int k = left; k<i; ++k) assert(i == j || arr[k] < pivot); // i == j || arr[left, i] < pivot

            while (arr[j-1] >= pivot && i<j) j--; // move right bound
            assert(i == j || arr[j-1]<pivot); // i == j || arr[j-1]<pivot
            for (int k = j; k<right+1; ++k) assert(i == j || arr[k] >= pivot); // i == j || arr[j, right+1] >= pivot

            if (i < j) {
                swap(arr, i, j-1);
                i++;
                j--;
            }
            for (int k = left; k<i; ++k) assert(arr[k] < pivot); // arr[left, i] < pivot
            for (int k = j; k<right+1; ++k) assert(arr[k] >= pivot); // arr[j, right+1] >= pivot
        }

        // invariants
        for (int k = left; k<i; ++k) assert(arr[k] < pivot); // arr[left, i] < pivot
        for (int k = j; k<right+1; ++k) assert(arr[k] >= pivot); // arr[j, right+1] >= pivot

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
            quick_sort(arr, left, i-1); // sort left part
            quick_sort(arr, i+1, right); // sort right part
        }
    }

    template<class T>
    void bubble_sort(std::vector<T> &arr)
    {
        // n * n
        for (int i = 0; i < arr.size(); ++i) { // n
            for (int j = 0; j < arr.size() - i - 1; ++j) { // n
                if (arr[j] > arr[j + 1]) swap(arr, j, j + 1);
            }
        }
    }
}