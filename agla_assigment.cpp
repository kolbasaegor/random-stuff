#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Matrix{
private:
    T **data;
    int n,m;
public:
    Matrix(int n, int m){
        this->n = n;
        this->m = m;
        data = new T *[n];
        for(int i = 0;i<n;i++){ data[i] = new T[m]; }
    }

    ~Matrix(){
        delete[] data;
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

    void printMatrix(){
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m - 1;j++){
                cout << this->data[i][j] << " ";
            }
            cout << this->data[i][this->m - 1] << endl;
        }
    }

    void inputMatrix(){
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                cin >> this->data[i][j];
            }
        }
    }

    Matrix & operator = (const Matrix &other){
        delete[] this->data;
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

    Matrix operator + (const Matrix &other){
        Matrix sum(this->n, this->m);
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                sum.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }

        return sum;
    }

    Matrix operator - (const Matrix &other){
        Matrix dif(this->n, this->m);
        for(int i = 0;i<this->n;i++){
            for(int j = 0;j<this->m;j++){
                dif.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }

        return dif;
    }

    Matrix operator * (const Matrix &other){
        Matrix product(this->n, other.m);
        for(int i = 0; i < this->n; i++)
            for(int j = 0; j < other.m; j++)
            {
                product.data[i][j] = 0;
                for(int k = 0; k < this->m; k++)
                    product.data[i][j] += this->data[i][k] * other.data[k][j];
            }

        return product;
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

        delete[] data;
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

        delete[] copy;
    }

};


int main(){
    int n,m;

    cin >> n >> m;
    Matrix<double> a(n,m);
    a.inputMatrix();

    cin >> n >> m;
    Matrix<double> b(n,m);
    b.inputMatrix();

    cin >> n >> m;
    Matrix<double> c(n,m);
    c.inputMatrix();

    if(a.getN() == b.getN() && a.getM() == b.getM()){
        Matrix<double> d = a + b;
        d.printMatrix();
        Matrix<double> e = b - a;
        e.printMatrix();
    } else {
        cout << "Error: the dimensional problem occurred" << endl;
        cout << "Error: the dimensional problem occurred" << endl;
    }

    if(c.getM() == a.getN()){
        Matrix<double> f = c*a;
        f.printMatrix();
    } else {
        cout << "Error: the dimensional problem occurred" << endl;
    }

    a.transpose();
    Matrix<double> g = a;
    g.printMatrix();




    return 0;
}