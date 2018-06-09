// Compares 2 implementations of quicksort.
// For each implementation:
//      For {sorted, random} arraytype:
//          For a set of sizes:
//              Runs <> samples and prints average elapsed time 
#include <iostream>
#include <random>
#include <chrono>


template<typename T = int>
T getRandomUniformInt(T low, T high) {
    static std::random_device rd;
    static std::mt19937 e2(rd());
    static std::uniform_int_distribution<T> dist(low, high);

    return dist(e2);
}


bool validate(int array[], unsigned int size) {
    for (unsigned int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }

    return true;
}


void quickSort1(int array[], int left, int right) {
    int i = left;
    int j = right;
    const int pivot = array[(left + right) / 2];

    while (i <= j) {
        while (array[i] < pivot) {
            i++;
        }
        while (pivot < array[j]) {
            j--;
        }

        if (i <= j) {
            const int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort1(array, left, j);
    }
    if (i < right) {
        quickSort1(array, i, right);
    }
}


void quickSort2(int array[], int low, int high) {
    if (low < high) {
        static const auto partition = [](int array[], int low, int high){
            const int pivot = array[low];
            int i = low - 1;
            int j = high + 1;
            while (true) {
                do {
                    i++;
                } while (array[i] < pivot);
                do {
                    j--;
                } while (array[j] > pivot);

                if (i >= j) {
                    return j;
                }

                const int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        };

        const unsigned int p = partition(array, low, high);
        quickSort2(array, low, p);
        quickSort2(array, p + 1, high);
    }
}


enum ArrayType {
    sortedArray, randomArray
};

void generateArray(int array[], unsigned int size,
        ArrayType arrayType = ArrayType::randomArray) {
    switch (arrayType) {
        case sortedArray:
            for (unsigned int i = 0; i < size; i++) {
                array[i] = i;
            }
            break;
        case randomArray:
            for (unsigned int i = 0; i < size; i++) {
                array[i] = getRandomUniformInt<>(0, (int) (size << 1));
            }
            break;
    }
}


int main() {
    const unsigned int samples = 10;
    const unsigned int MAX_SIZE = 10000;

    int* array = new int[MAX_SIZE];
    for (unsigned int sortingType = 1; sortingType <= 2; sortingType++) {
        std::cout << "-------- QuickSort " << sortingType << " ---------" << std::endl;
        const auto sortingMethod = (sortingType == 1) ? quickSort1 : quickSort2;
        for (unsigned int arrayTypeInt = ArrayType::sortedArray;
                arrayTypeInt <= ArrayType::randomArray;
                arrayTypeInt++) {
            const ArrayType arrayType = static_cast<ArrayType>(arrayTypeInt);
            switch (arrayType) {
                case sortedArray:
                    std::cout << "*** Sorted ***" << std::endl;
                    break;
                case randomArray:
                    std::cout << "*** Random ***" << std::endl;
                    break;
            }

            for (unsigned int size = 100; size <= MAX_SIZE; size *= 10) {
                std::cout << "  SIZE = " << size << std::endl;
                double timeSum = 0.0;

                for (unsigned int sample = 0; sample < samples; sample++) {
                    generateArray(array, size, arrayType);
                    const auto start = std::chrono::steady_clock::now();
                    {
                        sortingMethod(array, 0, size - 1);
                    }
                    timeSum +=
                        std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::steady_clock::now() - start
                        ).count();

                    if (!validate(array, size)) {
                        std::cout << "INVALID SORTING" << std::endl;
                    }
                }

                timeSum /= samples;
                std::cout << "    Elapsed = " << timeSum << " micros" << std::endl;
            }
        }
    }

    delete[] array;

    return 0;
}
