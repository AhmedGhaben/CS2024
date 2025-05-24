#include <cstring>
#include <iostream>
#include <stdexcept>

class SimpleString {
    static constexpr size_t SSO_BUFFER_SIZE = 15; // 15 chars + null terminator
    
    union {
        char sso[SSO_BUFFER_SIZE + 1]; // SSO buffer
        struct {
            char* heap;      // Heap-allocated string
            size_t heap_capacity; // Allocated capacity (renamed to avoid conflict)
        };
    };
    
    size_t length;    // Current string length
    bool is_heap;     // True if using heap storage

public:
    // Constructor (defaults to empty string)
    SimpleString(const char* str = "") : length(strlen(str)) {
        is_heap = (length > SSO_BUFFER_SIZE);
        
        if (is_heap) {
            heap_capacity = std::max(length, size_t(16)); // Start with at least 16
            heap = new char[heap_capacity + 1];
            strcpy(heap, str);
        } else {
            strcpy(sso, str);
        }
    }

    // Destructor
    ~SimpleString() {
        if (is_heap) {
            delete[] heap;
        }
    }

    // Copy constructor
    SimpleString(const SimpleString& other) : length(other.length), is_heap(other.is_heap) {
        if (is_heap) {
            heap_capacity = other.heap_capacity;
            heap = new char[heap_capacity + 1];
            strcpy(heap, other.heap);
        } else {
            strcpy(sso, other.sso);
        }
    }

    // Move constructor
    SimpleString(SimpleString&& other) noexcept 
        : length(other.length), is_heap(other.is_heap) {
        if (is_heap) {
            heap = other.heap;
            heap_capacity = other.heap_capacity;
            other.heap = nullptr; // Prevent double-free
        } else {
            strcpy(sso, other.sso);
        }
        other.length = 0;
    }

    // Assignment operators
    SimpleString& operator=(const SimpleString& other) {
        if (this != &other) {
            // Clean up current storage
            if (is_heap) delete[] heap;
            
            length = other.length;
            is_heap = other.is_heap;
            
            if (is_heap) {
                heap_capacity = other.heap_capacity;
                heap = new char[heap_capacity + 1];
                strcpy(heap, other.heap);
            } else {
                strcpy(sso, other.sso);
            }
        }
        return *this;
    }

    SimpleString& operator=(SimpleString&& other) noexcept {
        if (this != &other) {
            if (is_heap) delete[] heap;
            
            length = other.length;
            is_heap = other.is_heap;
            
            if (is_heap) {
                heap = other.heap;
                heap_capacity = other.heap_capacity;
                other.heap = nullptr;
            } else {
                strcpy(sso, other.sso);
            }
            
            other.length = 0;
        }
        return *this;
    }

    // Accessors
    size_t size() const { return length; }
    size_t capacity() const { return is_heap ? heap_capacity : SSO_BUFFER_SIZE; }
    
    const char* c_str() const { return is_heap ? heap : sso; }
    
    char& operator[](size_t i) {
        if (i >= length) throw std::out_of_range("Index out of range");
        return is_heap ? heap[i] : sso[i];
    }
    
    const char& operator[](size_t i) const {
        if (i >= length) throw std::out_of_range("Index out of range");
        return is_heap ? heap[i] : sso[i];
    }

    // Modifiers
    void reserve(size_t new_cap) {
        if (new_cap <= capacity()) return;
        
        char* new_data = new char[new_cap + 1];
        strcpy(new_data, c_str());
        
        if (is_heap) delete[] heap;
        
        heap = new_data;
        heap_capacity = new_cap;
        is_heap = true;
    }

    void push_back(char c) {
        if (length == capacity()) {
            reserve(capacity() ? capacity() * 2 : 16);
        }
        
        (is_heap ? heap : sso)[length++] = c;
        (is_heap ? heap : sso)[length] = '\0';
    }

    // Clear the string
    void clear() {
        if (is_heap) {
            delete[] heap;
            is_heap = false;
        }
        length = 0;
        sso[0] = '\0';
    }
};

int main() {
    SimpleString s1("Hello");
    std::cout << s1.c_str() << " (size: " << s1.size() << ", capacity: " << s1.capacity() << ")\n";
    
    s1.push_back('!');
    std::cout << "After push_back: " << s1.c_str() << "\n";
    
    SimpleString s2 = s1;
    std::cout << "Copy: " << s2.c_str() << "\n";
    
    SimpleString s3("This is a very long string that needs heap storage");
    std::cout << s3.c_str() << " (size: " << s3.size() << ", capacity: " << s3.capacity() << ")\n";
    
    s3.reserve(100);
    std::cout << "After reserve(100): " << s3.c_str() << " (capacity: " << s3.capacity() << ")\n";
    
    s3.clear();
    std::cout << "After clear: " << s3.c_str() << "\n";
    
    return 0;
}