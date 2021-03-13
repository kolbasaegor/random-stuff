template <typename T>
class List{
public:
    List(){
        Size = 0;
        head = nullptr;
    }

    ~List(){ clear(); }

    int size(){ return Size; }

    bool isEmpty() { return Size == 0; }

    void push_back(T data){
        if(head == nullptr){
            head = new Node<T>(data);
        } else {
            Node<T> *current = this->head;

            while(current->pNext != nullptr){
                current = current->pNext;
            }

            current->pNext = new Node<T>(data);
        }
        Size++;
    }

    T & operator [] (const int index) {
        Node<T> *current = head;
        int currentIndex = 0;

        while(current != nullptr){
            if(currentIndex == index){
                return current->data;
            } else {
                current = current->pNext;
                currentIndex++;
            }
        }
    }

    void pop_front(){
        Node<T> *tmp = head;
        if(head->pNext == nullptr) head = nullptr;
        else head = head->pNext;
        Size--;
        delete tmp;
    }

    void clear(){ while(Size > 0) pop_front(); }

    void push_front(T data){
        head = new Node<T>(data, head);
        Size++;
    }

    void pop_back(){ removeAt(Size-1); }

    void insert(T data, int index){
        Node<T> *current = head;
        int currentIndex = 0;

        while(current != nullptr){
            if(currentIndex == index){
                Node<T> *tmp = current->pNext;
                current->pNext = new Node<T>(data, tmp);
                Size++;
                break;
            } else {
                current = current->pNext;
                currentIndex++;
            }
        }
    }

    void removeAt(int index){
        Node<T> *current = head;
        int currentIndex = 0;

        if(index == 0) { pop_front(); }
        else {
            while(current != nullptr){
                if(currentIndex == index - 1){
                    Node<T> *tmp = current->pNext;
                    current->pNext = tmp->pNext;
                    delete tmp;
                    Size--;
                    break;
                } else {
                    current = current->pNext;
                    currentIndex++;
                }
            }
        }
    }


private:
    template <typename U>
    class Node{
    public:
        Node *pNext;
        T data;
        Node(T data = T(), Node *pNext = nullptr){
            this->data = data;
            this->pNext = pNext;
        }
    };

    Node<T> *head;
    int Size;
};
