template <typename T>
class MinHeap{
public:
    MinHeap(){
        capacity = 0;
        data = new T[0];
        Size = 0;
    }

    void increaseSize(){
        T *buffer = new T[capacity*2];
        for(int i = 0;i<capacity;i++){
            buffer[i] = data[i];
        }
        delete []data;
        data = buffer;
        capacity = capacity*2;
    }

    int size(){
        return Size;
    }

    void insert(T item){
        if(Size == capacity) increaseSize();

        data[Size] = item;
        Size++;
        int i = Size - 1;
        while(i > 0 and data[(i-1)/2] > item){
            std::swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    T removeMin(){
        if(Size == 0) return NULL;

        T itemToReturn = data[0];
        data[0] = data[Size - 1];
        Size--;

        int i = 0;
        int childIndex = findSmallerChild(i);
        while (childIndex != 0 && data[childIndex] < data[i]){
            std::swap(data[childIndex], data[i]);
            i = childIndex;
            childIndex = findSmallerChild(i);
        }

        return itemToReturn;
    }

    T & operator [](int i){
        return data[i];
    }

private:
    T *data;
    int Size, capacity;

    int findSmallerChild(int i){
        if(2*i + 1 < Size)
            if(data[2*i + 1] < data[2*i + 2])
                return 2*i + 1;
            else return 2*i + 2;
        else if(2*i + 1 == Size)
            return 2*i + 1;
        else return 0;
    }
};

template <typename T>
class MaxHeap{
public:
    MaxHeap(){
        capacity = 0;
        data = new T[0];
        Size = 0;
    }

    void increaseSize(){
        T *buffer = new T[capacity*2];
        for(int i = 0;i<capacity;i++){
            buffer[i] = data[i];
        }
        delete []data;
        data = buffer;
        capacity = capacity*2;
    }

    int size(){
        return Size;
    }

    void insert(T item){
        if(Size == capacity) increaseSize();

        data[Size] = item;
        Size++;
        int i = Size - 1;
        while(i > 0 and data[(i-1)/2] < item){
            std::swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    T removeMax(){
        if(Size == 0) return NULL;

        T itemToReturn = data[0];
        data[0] = data[Size - 1];
        Size--;

        int i = 0;
        int childIndex = findMaxChild(i);
        while (childIndex != 0 && data[childIndex] > data[i]){
            std::swap(data[childIndex], data[i]);
            i = childIndex;
            childIndex = findMaxChild(i);
        }

        return itemToReturn;
    }

    T & operator [](int i){
        return data[i];
    }

private:
    T *data;
    int Size, capacity;

    int findMaxChild(int i){
        if(2*i + 1 < Size)
            if(data[2*i + 1] > data[2*i + 2])
                return 2*i + 1;
            else return 2*i + 2;
        else if(2*i + 1 == Size)
            return 2*i + 1;
        else return 0;
    }
};

template <typename T>
void heapSort(T array[], int size, bool reverse = false){
    if(!reverse){
        MinHeap<T> minHeap;
        for (int i = 0; i < size; ++i) {
            minHeap.insert(array[i]);
        }
        for (int i = 0; i < size; ++i) {
            array[i] = minHeap.removeMin();
        }
    } else {
        MaxHeap<T> maxHeap;
        for (int i = 0; i < size; ++i) {
            maxHeap.insert(array[i]);
        }
        for (int i = 0; i < size; ++i) {
            array[i] = maxHeap.removeMax();
        }
    }
}
