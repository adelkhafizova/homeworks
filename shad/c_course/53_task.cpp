#include <vector>
#include <iostream>
#include <cstdlib>

template <typename T>
class TStack {
public:
    TStack(int size) {
	memory_block_size = size;
	capacity = 0;
	size = 0
    }
    T& pop() {
	if (size == 0)
	    return NULL;
        else {
	    size--;
	    T temp = *(storage + size);
	}    
    };
    void Pop();
    void Push(const T& element);
private:
    T* storage;
    int size;
    int capacity;
    int memory_block_size;
};

int main() {
}
