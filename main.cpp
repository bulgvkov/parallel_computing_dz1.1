#include <iostream>
#include <immintrin.h>
#include <chrono>
#include <cmath>

        uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t) hi << 32) | lo;
}

int main() {
    {
        std::cout << "=============Sum=============";
        for (size_t i = 4; i < 9; ++i) {
            double val1 = 22.0;
            double val2 = 33.0;
            std::size_t operations = pow(10, i);
            auto start = std::chrono::system_clock::now();
            unsigned long long t1 = rdtsc();
            for (size_t j = 0; j < pow(10, i); ++j) {
                val1 = val1 + val2;
            }
            unsigned long long t2 = rdtsc();
            std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
            double seconds = duration.count();
            double operations_per_second = operations / seconds;
            uint64_t processor_clocks = t2 - t1;
            double processor_clocks_per_second = processor_clocks / seconds;
            std::cout << "\noperation " << operations << '\n'
                      << "seconds " << seconds << '\n'
                      << "operations per second " << std::to_string(operations_per_second) << '\n'
                      << "processor clocks " << processor_clocks << '\n'
                      << "processor clocks per second " << std::to_string(processor_clocks_per_second) << '\n';        }
    }
    {
        std::cout << "\n=============Vec sum=============";
        for (size_t i = 4; i < 9; ++i) {
            const double array[2] = {41.0, 41.0};
            const double array2[2] = {55.0, 55.0};
            __m128d val1 = _mm_load_pd(&array[0]);
            __m128d val2 = _mm_load_pd(&array2[0]);
            std::size_t operations = pow(10, i);
            auto start = std::chrono::system_clock::now();
            unsigned long long t1 = rdtsc();
            for (size_t j = 0; j < pow(10, i) / 2; ++j) {
                val1 = _mm_add_pd(val1, val2);
            }
            unsigned long long t2 = rdtsc();
            std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
            double seconds = duration.count();
            double operations_per_second = operations / seconds;
            uint64_t processor_clocks = t2 - t1;
            double processor_clocks_per_second = processor_clocks / seconds;
            std::cout << "\noperation " << operations << '\n'
            << "seconds " << seconds << '\n'
            << "operations per second " << std::to_string(operations_per_second) << '\n'
            << "processor clocks " << processor_clocks << '\n'
            << "processor clocks per second " << std::to_string(processor_clocks_per_second) << '\n';
        }
    }
}
