#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

#include <cstddef>
#include <utility>
#include <memory>
#include <stdexcept>

template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtr {
    static_assert(std::is_invocable_v<Deleter, T*>,
        "Deleter must be able to delete a T*");

    T* ptr_ = nullptr;
    size_t* ref_count_ = nullptr;
    Deleter deleter_;

    void cleanup() {
        if (!ref_count_) return;
        
        if (--(*ref_count_) == 0) {
            deleter_(ptr_);
            delete ref_count_;
            ptr_ = nullptr;
        }
        ref_count_ = nullptr;
    }

public:
    explicit SharedPtr(T* ptr = nullptr, Deleter deleter = Deleter())
        : ptr_(ptr), deleter_(std::move(deleter)) 
    {
        if (ptr_) {
            try {
                ref_count_ = new size_t(1);
            } catch (...) {
                deleter_(ptr_);
                throw;
            }
        }
    }

    SharedPtr(const SharedPtr& other) noexcept
        : ptr_(other.ptr_), ref_count_(other.ref_count_), deleter_(other.deleter_)
    {
        if (ref_count_) {
            ++(*ref_count_);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept
        : ptr_(other.ptr_), ref_count_(other.ref_count_), deleter_(std::move(other.deleter_))
    {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    ~SharedPtr() {
        cleanup();
    }

    SharedPtr& operator=(const SharedPtr& rhs) {
        if (this != &rhs) {
            cleanup();
            ptr_ = rhs.ptr_;
            ref_count_ = rhs.ref_count_;
            deleter_ = rhs.deleter_;
            if (ref_count_) ++(*ref_count_);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& rhs) noexcept {
        if (this != &rhs) {
            cleanup();
            ptr_ = rhs.ptr_;
            ref_count_ = rhs.ref_count_;
            deleter_ = std::move(rhs.deleter_);
            rhs.ptr_ = nullptr;
            rhs.ref_count_ = nullptr;
        }
        return *this;
    }

    T* get() const noexcept { return ptr_; }
    size_t use_count() const noexcept { return ref_count_ ? *ref_count_ : 0; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T& operator*() const {
        if (!ptr_) throw std::logic_error("Dereferencing null SharedPtr");
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    void reset(T* new_ptr = nullptr) {
        cleanup();
        ptr_ = new_ptr;
        if (ptr_) {
            ref_count_ = new size_t(1);
        }
    }

    void swap(SharedPtr& other) noexcept {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(ref_count_, other.ref_count_);
        swap(deleter_, other.deleter_);
    }
};

template<typename T, typename D>
void swap(SharedPtr<T, D>& a, SharedPtr<T, D>& b) noexcept {
    a.swap(b);
}

#endif