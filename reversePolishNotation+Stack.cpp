#include <iostream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

template <typename T> class Stack{
    vector <T> data;
    int size;
public:
    void push(T content){
        data.push_back(content);
        size++;
    }

    T pop(){
        T c = data[size-1];
        data.pop_back();
        size--;
        return c;
    }

    T peek(){
        return data[size-1];
    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        if(size == 0) return true;
        else return false;
    }
};


int main(){
    //prepare
    char inputString[100];
    gets(inputString);
    //cin >> inputString;
    int maxLen = 0, size = 1;
    int currentLen = 0;

    for(int i = 0; inputString[i] != '\0';i++){
        if(inputString[i] == ' '){
            size++;
            if(currentLen > maxLen) maxLen = currentLen;
            currentLen = 0;
        } else {
            currentLen++;
        }
    }
    int size2 = maxLen + 1;
    char input[size][size2];
    for(int i = 0;i < size;i++){
        for(int j = 0;j<size2;j++){
            input[i][j] = '\0';
        }
    }
    int j = 0,k=0;
    for(int i = 0; inputString[i] != '\0';i++){
        if(inputString[i] == ' '){
            j++;
            k = 0;
        } else {
            input[j][k] = inputString[i];
            k++;
        }
    }

    // start
    vector <string> output;
    Stack<char> *stack = new Stack<char>();
    string translator;

    for(int i = 0;i < size;i++){
        if(isdigit(input[i][0])) output.push_back(input[i]);
        else if(input[i][0] == '*' || input[i][0] == '/'){
            if(stack->isEmpty()) stack->push(input[i][0]);
            else{
                while(1){
                    if(stack->peek() == '+' || stack->peek() == '-' || stack->peek() == '(' || stack->peek() == ')' || stack->isEmpty()){
                        stack->push(input[i][0]);
                        break;
                    } else {
                        translator = stack->pop();
                        output.push_back(translator);
                    }
                }
            }
        }
        else if(input[i][0] == '+' || input[i][0] == '-'){
            if(stack->isEmpty()) stack->push(input[i][0]);
            else{
                while(1){
                    if(stack->peek() == '(' || stack->peek() == ')' || stack->isEmpty()){
                        stack->push(input[i][0]);
                        break;
                    } else{
                        translator = stack->pop();
                        output.push_back(translator);
                    }
                }
            }
        }
        else if (input[i][0] == ')'){
            while(!(stack->isEmpty())){
                if (stack->peek() == '('){
                    stack->pop();
                    break;
                } else {
                    translator = stack->pop();
                    output.push_back(translator);
                }
            }
        } else stack->push(input[i][0]);
    }

    while(!(stack->isEmpty())){
        translator = stack->pop();
        output.push_back(translator);
    }
    /*
    for(int i = 0; i < output.size();i++){
        for(int j = 0; output[i][j] != '\0';j++){
            cout << output[i][j];
    }
    cout << " ";
    } cout << endl;
    */
    Stack<string> *queue = new Stack<string>();
    for(int i = output.size()-1;i>=0;i--){
        queue->push(output[i]);
    }

    Stack<double> *evaluationStack = new Stack<double>();
    double a,b;
    while(!(queue->isEmpty())){
        //cout << queue->peek() << endl;
        if(isdigit(queue->peek()[0])) evaluationStack->push((double)stoi(queue->pop()));
        else{
            if(queue->peek()[0] == '-') {
                a = (double)evaluationStack->pop(); // right element
                b = (double)evaluationStack->pop(); // left element
                evaluationStack->push(b-a);
                queue->pop();
            } else if (queue->peek()[0] == '+'){
                a = (double)evaluationStack->pop(); // right element
                b = (double)evaluationStack->pop(); // left element
                evaluationStack->push(b+a);
                queue->pop();
            } else if(queue->peek()[0] == '/'){
                a = (double)evaluationStack->pop(); // right element
                b = (double)evaluationStack->pop(); // left element
                evaluationStack->push(b/a);
                queue->pop();
            } else if(queue->peek()[0] == '*'){
                a = (double)evaluationStack->pop(); // right element
                b = (double)evaluationStack->pop(); // left element
                evaluationStack->push(b*a);
                queue->pop();
            }
        }
    }
    double finaly = evaluationStack->pop();
    cout << finaly << endl;

    return 0;
}
