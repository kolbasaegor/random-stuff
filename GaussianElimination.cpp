#include <iostream>
//#define DETAILS
//#define EXE_TIME
using namespace std;

#ifdef EXE_TIME
#include <chrono>
class ExecutionTime{
public:
    ExecutionTime(){
        start = std::chrono::steady_clock::now();
    }

    ~ExecutionTime(){
        end = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = end - start;
        std::cout << "Execution time: " << (int)(duration.count() * 1000) << " ms." << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
};
#endif

template <typename T>
class Matrix{
public:
    T **data;
    int n;

    void clear(){
        for (int i = 0; i < this->n; i++)
        {
            delete [] this->data[i];
        }
        delete [] this->data;
    }

    void random(){
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->m; ++j) {
                this->data[i][j] = rand() % 1000;
            }
        }
    }

    Matrix(int n, int m){
        this->n = n;
        this->m = m;
        data = new T *[n];
        for(int i = 0;i<n;i++){ data[i] = new T[m]; }
    }

    ~Matrix(){
        clear();
    }

    Matrix(const Matrix &other){
        this->n = other.n;
        this->m = other.m;
        this->data = new T *[this->n];
        for(int i = 0;i<this->n;i++){ this->data[i] = new T[this->m]; }
        for(int i = 0;i<this->n;i++){
            for(int j =0;j<this->m;j++){
                this->data[i][j] = other.data[i][j];
            }
        }
    }

    int getN(){return this->n;}
    int getM(){return this->m;}

    template<typename U>
    friend ostream &operator << (ostream &out, Matrix<U> &matrix);
    template<typename U>
    friend istream &operator >> (istream &in, Matrix<U> &matrix);



    Matrix & operator = (const Matrix &other){
        clear();
        this->n = other.n;
        this->m = other.m;
        this->data = new T *[this->n];
        for(int i = 0;i<this->n;i++){ this->data[i] = new T[this->m]; }

        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                this->data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    Matrix & operator + (const Matrix &other){
        Matrix *sum = new Matrix(this->n, this->m);
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                sum->data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }

        return *sum;
    }

    Matrix & operator - (const Matrix &other){
        Matrix *dif = new Matrix(this->n, this->m);
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                dif->data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }

        return *dif;
    }

    Matrix & operator * (const Matrix &other){
        Matrix *product = new Matrix(this->n, other.m);
        for(int i = 0; i < this->n; i++)
            for(int j = 0; j < other.m; j++)
            {
                product->data[i][j] = 0;
                for(int k = 0; k < this->m; k++)
                    product->data[i][j] += this->data[i][k] * other.data[k][j];
            }

        return *product;
    }


    void transpose(){
        T **copy;
        copy = new T *[this->n];
        for(int i = 0;i<this->n;i++){ copy[i] = new T[this->m]; }
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                copy[i][j] = this->data[i][j];
            }
        }

        clear();
        int tmp = this->n;
        this->n = this->m;
        this->m = tmp;
        data = new T *[n];
        for(int i = 0;i<n;i++){ data[i] = new T[m]; }

        for(int i = 0;i< this->n;i++){
            for(int j = 0;j<this->m;j++){
                this->data[i][j] = copy[j][i];
            }
        }

    }
private:
    int m;

};

template <typename T>
class SquareMatrix : public Matrix<T> {
public:
    SquareMatrix(int n) : Matrix<T>(n,n) {}

    SquareMatrix(const Matrix<T> & other) : Matrix<T>(other.n,other.n) {
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->n; ++j) {
                this->data[i][j] = other.data[i][j];
            }
        }
    }

};

template <typename T>
class IdentityMatrix : public SquareMatrix<T> {
public:
    IdentityMatrix(int n) : SquareMatrix<T>(n) {
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->n; ++j) {
                if(i == j) this->data[i][j] = 1;
                else this->data[i][j] = 0;
            }
        }
    }


};

template <typename T>
class EliminationMatrix : public IdentityMatrix<T> {
public:
    EliminationMatrix(int i, int j, const SquareMatrix<T> & other) : IdentityMatrix<T>(other.n) {
        i--; j--;
        T x = 0;
        for (int k = 0; k < other.n; ++k) {
            if(k != j) x -= this->data[i][k] * other.data[k][j];
        }
        x = x / other.data[j][j];
        this->data[i][j] = x;
    }

};

template <typename T>
class PermutationMatrix : public IdentityMatrix<T> {
public:
    PermutationMatrix(int i, int j, const SquareMatrix<T> & other) : IdentityMatrix<T>(other.n) {
        i--; j--;
        for (int k = 0; k < other.n; ++k) {
            swap(this->data[i][k], this->data[j][k]);
        }
    }
};


template <typename T>
ostream &operator << (ostream &out, Matrix<T> &matrix){
    for(int i = 0;i<matrix.n;i++){
        for(int j = 0;j<matrix.m - 1;j++){
            if(matrix.data[i][j] == 0) out << 0.00 << " ";
            else out << matrix.data[i][j] << " ";
        }
        if(matrix.data[i][matrix.m - 1] == 0) out << 0.00 << endl;
        else out << matrix.data[i][matrix.m - 1] << endl;
    }

    return out;
}

template <typename T>
istream &operator >> (istream &in, Matrix<T> &matrix){
    for(int i = 0;i<matrix.n;i++){
        for(int j = 0;j<matrix.m;j++){
            in >> matrix.data[i][j];
        }
    }

    return in;
}
template <typename T>
int findLineMaxPivot(int column,int size, const SquareMatrix<T> & A){
    T max = 0;
    int index = column;
    for (int i = column; i < size; ++i) {
        if(abs(A.data[i][column]) > max){
            max = abs(A.data[i][column]);
            index = i;
        }
    }

    return index + 1;
}

template <typename T>
void printAugmentedMatrix(const SquareMatrix<T> & matrix1, const SquareMatrix<T> & matrix2, int size){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix1.data[i][j] << " ";
        }
        for (int j = 0; j < size - 1; ++j) {
            cout << matrix2.data[i][j] << " ";
        }
        cout << matrix2.data[i][size-1];
        cout << endl;
    }
}

int main(){
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    /*int n = 100, step = 0;
    SquareMatrix<double> A(n);
    A.random();
    Matrix<double> b(n, 1);
    b.random();*/

    int step = 0;
    int n;
    cout << "Enter the size of Matrix(n x n)"<< endl;
    cin >> n;
    cout << "Enter Matrix"<< endl;
    SquareMatrix<double> A(n);
    cin >> A;
    cout << "Enter b" << endl;
    Matrix<double> b(n,1);
    cin >> b;

#ifdef DETAILS
    cout << "step #0:\n";
    #endif
    cout << A << b;

#ifdef EXE_TIME
    ExecutionTime t;
#endif
    for (int i = 0; i < n-1; ++i) {
        int index = findLineMaxPivot(i,n,A);
        if(index - 1 != i){
            step++;
            PermutationMatrix<double> P(i+1, findLineMaxPivot(i,n,A), A);
            A = P * A;
            b = P * b;
#ifdef DETAILS
            cout << "step #"<<step<<": permutation"<<endl;
            cout << A << b;
#endif
        }
        for (int j = i+1; j < n; ++j) {
            if(A.data[j][i] != 0){
                step++;
                EliminationMatrix<double> E(j+1, i+1, A);
                A = E * A;
                b = E * b;
#ifdef DETAILS
                cout << "step #"<<step<<": elimination"<<endl;
                cout << A << b;
#endif
            }
        }
    }
#ifdef DETAILS
    cout << "Way back:\n";
#endif
    for (int i = n-1; i > 0; i--) {
        int index = findLineMaxPivot(i,n,A);
        if(index - 1 != i){
            step++;
            PermutationMatrix<double> P(i+1, findLineMaxPivot(i,n,A), A);
            A = P * A;
            b = P * b;
#ifdef DETAILS
            cout << "step #"<<step<<": permutation"<<endl;
            cout << A << b;
#endif
        }
        for (int j = i-1; j > -1; j--) {
            if(A.data[j][i] != 0){
                step++;
                EliminationMatrix<double> E(j+1, i+1, A);
                A = E * A;
                b = E * b;
#ifdef DETAILS
                cout << "step #"<<step<<": elimination"<<endl;
                cout << A << b;
#endif
            }
        }
    }



    for (int i = 0; i < n; ++i) {
        double div = A.data[i][i];
        b.data[i][0] = b.data[i][0] / div;
        A.data[i][i] = A.data[i][i] / div;
    }
#ifdef DETAILS
    cout << "Diagonal normalization:\n";
    cout << A << b;
#endif


    cout << "result:\n";
    cout << b;


    return 0;
}
