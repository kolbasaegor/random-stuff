#define DEBUG
using namespace std;

template <typename T>
class BinarySearchTree{
public:
    class Node{
    public:
        Node* left_child;
        Node* right_child;
        T value;
        int index;

        Node(int index,T value = T(), Node* left_child = nullptr, Node* right_child = nullptr){
            this->index = index;
            this->value = value;
            this->left_child = left_child;
            this->right_child = right_child;
        }
    };

    Node *root;

    static int numberOfElements;

    BinarySearchTree(){
        root = nullptr;
    }
#ifdef DEBUG
    void test(){
        std::cout << (root->left_child)->value << std::endl;
        std::cout << (root->right_child)->value << std::endl;
    }
#endif
    void add(T value){
        numberOfElements++;

        if(root == nullptr){
            root = new Node(numberOfElements,value);
        } else {
            Node *current = root;
            while(current != nullptr){
                if(value < current->value){
                    if(current->left_child == nullptr){
                        current->left_child = new Node(numberOfElements,value);
                        break;
                    }
                    else {
                        current = current->left_child;
                    }
                }
                else if(value > current->value){
                    if(current->right_child == nullptr){
                        current->right_child = new Node(numberOfElements,value);
                        break;
                    }
                    else {
                        current = current->right_child;
                    }
                }
            }
        }
    }

    int search(T value){
        int index = -1;
        if(root == nullptr) index = -1;
        else{
            Node *current = root;
            while(current != nullptr){
                if(value < current->value) current = current->left_child;
                else if(value > current->value) current = current->right_child;
                else{
                    index = current->index;
                    break;
                }
            }
        }

        return index;
    }

    void inorderTraversal(Node *node){
        if(node->left_child == nullptr && node->right_child == nullptr){
            std::cout << node->value << " -1 -1" << endl;
        } else if(node->right_child == nullptr){
            inorderTraversal(node->left_child);
            std::cout << node->value << " " << node->left_child->index << " -1" << endl;
        } else if(node->left_child == nullptr){
            std::cout << node->value << " -1 " << node->right_child->index << endl;
            inorderTraversal(node->right_child);
        } else {
            inorderTraversal(node->left_child);
            std::cout << node->value << " " << node->left_child->index << " " << node->right_child->index << endl;
            inorderTraversal(node->right_child);
        }
    }

private:


};

template <typename T>
int BinarySearchTree<T>::numberOfElements = 0;
