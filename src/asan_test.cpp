#include <vector>
#include <iostream>
#include <fmt/core.h>
#include <thread>
#include <chrono>

#include <sanitizer/lsan_interface.h>

// export ASAN_OPTIONS=halt_on_error=0:verbosity=1:detect_leaks=1

// if do not wana exit when leak detected:
// export LSAN_OPTIONS=exitcode=0

void memory_leak() {
    int *p = new int(42);
    *p = 100;
    // 不释放内存
    fmt::print("Value of p: {}\n", *p);
    double *p2 = new double(1.2);
    fmt::print("Value of p2: {}\n", *p2);
    return;
}

void use_after_free() {
    int* p = new int(42);
    delete p;
    std::cout << *p << std::endl;
}

void buffer_overflow() {
    int arr[10];
    // 越界访问
    arr[10] = 42;
}

int main() {
    size_t count = 10;
    while (true) {
        fmt::print("Running Address Sanitizer tests...\n");

        fmt::print("1. Testing memory leak...\n");
        memory_leak();

        fmt::print("2. Testing use after free...\n");
        use_after_free();

        fmt::print("3. Testing buffer overflow...\n");
        buffer_overflow();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        __lsan_do_leak_check();

        fmt::print("Address Sanitizer tests completed.\n");
    }
    return 0;
}