#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class DequeContainer {
private:
    static constexpr size_t SEGMENT_SIZE = 64;

    T** segments_;
    size_t num_segments_;
    size_t capacity_;
    size_t size_;

    size_t front_idx_;
    size_t back_idx_;

    void expand_segments() {
        const size_t new_count = num_segments_ * 2 + 1;
        T** new_segments = new T*[new_count]();

        const size_t offset = (new_count - num_segments_) / 2;
        for (size_t i = 0; i < num_segments_; ++i) {
            new_segments[i + offset] = segments_[i];
        }

        delete[] segments_;
        segments_ = new_segments;
        num_segments_ = new_count;
        capacity_ = num_segments_ * SEGMENT_SIZE;
    }

    T* fetch_segment(size_t segment_index) {
        if (!segments_[segment_index]) {
            segments_[segment_index] = new T[SEGMENT_SIZE];
        }
        return segments_[segment_index];
    }

public:
    DequeContainer() 
        : segments_(new T*[8]()), 
          num_segments_(8), 
          capacity_(8 * SEGMENT_SIZE),
          size_(0),
          front_idx_(4 * SEGMENT_SIZE),
          back_idx_(4 * SEGMENT_SIZE) {
    }

    ~DequeContainer() {
        for (size_t i = front_idx_; i < back_idx_; ++i) {
            const size_t seg = i / SEGMENT_SIZE;
            const size_t elem = i % SEGMENT_SIZE;
            segments_[seg][elem].~T();
        }
        delete[] segments_;
    }

    DequeContainer(const DequeContainer& other) 
        : segments_(new T*[other.num_segments_]() ),
          num_segments_(other.num_segments_),
          capacity_(other.capacity_),
          size_(other.size_),
          front_idx_(other.front_idx_),
          back_idx_(other.back_idx_) {

        try {
            for (size_t i = 0; i < num_segments_; ++i) {
                if (other.segments_[i]) {
                    segments_[i] = new T[SEGMENT_SIZE];
                    std::copy_n(other.segments_[i], SEGMENT_SIZE, segments_[i]);
                }
            }
        } catch (...) {
            for (size_t i = 0; i < num_segments_; ++i) {
                delete[] segments_[i];
            }
            delete[] segments_;
            throw;
        }
    }

    DequeContainer& operator=(const DequeContainer& other) {
        if (this != &other) {
            DequeContainer temp(other);
            std::swap(segments_, temp.segments_);
            std::swap(num_segments_, temp.num_segments_);
            std::swap(capacity_, temp.capacity_);
            std::swap(size_, temp.size_);
            std::swap(front_idx_, temp.front_idx_);
            std::swap(back_idx_, temp.back_idx_);
        }
        return *this;
    }

    void push_back(const T& val) {
        if (back_idx_ >= capacity_) {
            expand_segments();
        }
        const size_t seg = back_idx_ / SEGMENT_SIZE;
        const size_t elem = back_idx_ % SEGMENT_SIZE;
        fetch_segment(seg)[elem] = val;
        ++back_idx_;
        ++size_;
    }

    void push_front(const T& val) {
        if (front_idx_ == 0) {
            expand_segments();
        }
        --front_idx_;
        const size_t seg = front_idx_ / SEGMENT_SIZE;
        const size_t elem = front_idx_ % SEGMENT_SIZE;
        fetch_segment(seg)[elem] = val;
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Deque is empty");
        }
        --back_idx_;
        const size_t seg = back_idx_ / SEGMENT_SIZE;
        const size_t elem = back_idx_ % SEGMENT_SIZE;
        segments_[seg][elem].~T();
        --size_;
    }

    void pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("Deque is empty");
        }
        const size_t seg = front_idx_ / SEGMENT_SIZE;
        const size_t elem = front_idx_ % SEGMENT_SIZE;
        segments_[seg][elem].~T();
        ++front_idx_;
        --size_;
    }

    size_t size() const noexcept { 
        return size_;
    }
    size_t capacity() const noexcept { 
        return capacity_;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }

    void print_elements() const {
        for (size_t i = front_idx_; i < back_idx_; ++i) {
            const size_t seg = i / SEGMENT_SIZE;
            const size_t elem = i % SEGMENT_SIZE;
            std::cout << segments_[seg][elem] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int n, m;
    DequeContainer<int> container;
    std::cout << "*********Deque Class*********" << std::endl;
    std::cout << "pushb n: push back n." << std::endl; 
    std::cout << "pushf n: push forward n." << std::endl; 
    std::cout << "popf: pop forward." << std::endl; 
    std::cout << "popb: pop back." << std::endl; 
    std::cout << "Number of operations: ";
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        std::string command;
        std::cin >> command;
        if (command == "pushb"){
            std::cin >> m;
            container.push_back(m);
        }
        else if (command == "pushf"){
            std::cin >> m;
            container.push_front(m);
        }
        else if (command == "popb"){
            container.pop_back();
        }
        else if (command == "popf"){
            container.pop_front();
        }
        else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
    std::cout << "Container size: " << container.size() << std::endl;
    container.print_elements();
    std::cout << "**********************************" << std::endl;

    return 0;
}