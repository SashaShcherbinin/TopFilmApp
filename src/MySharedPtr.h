//
// Created by Oleksandr Shcherbinin on 01.04.2024.
//
#ifndef TASK2_MY_SHARED_PTR_H
#define TASK2_MY_SHARED_PTR_H

#include <cstddef>

template<typename T>
class MySharedPtr {
private:
    T *ptr = nullptr;
    size_t *ref_count = nullptr;

public:
    explicit MySharedPtr(T *value = nullptr) : ptr(value), ref_count(new size_t(1)) {
        if (value == nullptr) {
            *ref_count = 0;
        }
    }

    MySharedPtr(const MySharedPtr<T> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    MySharedPtr(MySharedPtr<T> &&other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    MySharedPtr<T> &operator=(const MySharedPtr<T> &other) {
        if (this != &other) {
            if (ref_count != nullptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    MySharedPtr<T> &operator=(MySharedPtr<T> &&other) noexcept {
        if (this != &other) {
            if (ref_count != nullptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    size_t getSize() {
        return *ref_count;
    }


    T &operator*() const {
        return *ptr;
    }

    T *operator->() const {
        return ptr;
    }

    ~MySharedPtr() {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }
};


#endif //TASK2_MY_SHARED_PTR_H
