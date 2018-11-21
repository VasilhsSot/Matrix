/* 
 * File:   main.cpp
 * Author: panos
 *
 * Created on May 31, 2015, 10:50 PM
 */

#include <iostream>
#include <stdexcept>
using namespace std;

// ROWS X COLS

class Matrix {
private:
    char name;
    int rows;
    int cols;
    double ** data;
public:
    char getName() const {
        return name;
    }

    void setName(char name) {
        this->name = name;
    }


    void destroy() {
        if (data != NULL) {
            for (int i = 0; i < rows; i++) {
                delete [] data[i];
            }
            delete [] data;
        }
    }

    void build(int newrows, int newcols) {
        if (cols != newcols || rows != newrows || data == NULL) {
            destroy();
            data = new double*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = 0;
                }
            }
        }
        cols = newcols;
        rows = newrows;
    }

    //  -----------------------   Constructors   ------------------------
    Matrix(char name, int rows, int cols) : name(name), rows(rows), cols(cols), data(NULL) {
        build(rows, cols);
        cout << "A new matrix has been created with dimensions " << rows << "x" << cols << endl;
    }
    Matrix(char name, int d) : name(name),rows(d), cols(d), data(NULL) {
        cout << "A new matrix has been created with dimensions " << cols << "x" << rows << endl;
        build(d, d);
    }
    Matrix(char name, int d, double value) : name(name),rows(d), cols(d), data(NULL) {
        cout << "A new matrix has been created with dimensions " << cols << "x" << rows << endl;
        build(d, d);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = value;
            }
        }
    }

    //------CopyConstactor
    // this MxN
    // copy OxP
    Matrix(const Matrix &copy) : name(copy.name), rows(copy.rows), cols(copy.cols), data(NULL) {
        // 1. theoro oti an M<> O  H N <>P tote error
        //        if (cols != copy.cols || rows != copy.rows) {
        //            exit(0);
        //        }

        // 2. antigrafo apo copy se this, prosarmozontas ton pinaka
        cout << "A new matrix has been created via cc-tor with dimensions " << rows << "x" << cols << endl;
        build(copy.rows, copy.cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                data[i][j] = copy.data[i][j];
        }
    }

    //  -----------------------   Destructor   ------------------------
    ~Matrix() {
        cout << "A matrix has been destroyed with dimensions " << cols << "x" << rows << endl;
        destroy();
    }

    //  ---------------------   Assignment operator ------------------------
    // Assignment operator: A = B
    //      this einai &A
    //      mat einai B
    Matrix & operator=(const Matrix & mat) {
        if (cols != mat.cols || rows != mat.rows) {
            build(rows, cols);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                data[i][j] = mat.data[i][j];
        }

        return *this;
    }
    
    //  ---------------------   bracket operator ------------------------
    double * operator[](int column) {
        return &data[0][column];
    }
    
    // ----------------------------------------------------------------------
    //                          Arithmetic operators 
    // ----------------------------------------------------------------------
    // C = ... A+B                                                  operator +
    //      this einai &A
    //      mat einai B
    Matrix operator+(const Matrix & mat) {
        if (cols == mat.cols && rows == mat.rows) {
            Matrix temp(name, rows, cols);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    temp.data[i][j] = data[i][j] + mat.data[i][j];
            }
            return temp;
        } else {
            throw std::invalid_argument("received negative value");
        }
    }

    // C = ... A-B                                                  operator -
    //      this einai &A
    //      mat einai B
    Matrix operator-(const Matrix & mat) {
        if (cols == mat.cols && rows == mat.rows) {
            Matrix temp(name, rows, cols);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    temp.data[i][j] = data[i][j] - mat.data[i][j];
            }
            return temp;
        } else {
            throw std::invalid_argument("received negative value");
        }
    }
    
    Matrix operator+() {
        Matrix temp(name, rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                temp.data[i][j] = data[i][j];
        }
        return temp;
    }
    
    Matrix operator-() {
        Matrix temp(name, rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                temp.data[i][j] = -data[i][j];
        }
        return temp;
    }
    
    Matrix operator~() {
        Matrix temp(name, cols, rows);

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++)
                temp.data[i][j] = data[j][i];
        }
        return temp;
    }

    //                                                              operator *
    // C = ... matrix * double
    // A[3][4] * 2
    Matrix operator*(double plus) {
        Matrix temp(name, rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.data[i][j] = data[i][j] * plus;
            }
        }
        return temp;
    }
    
    // C = ... double * matrix
    friend Matrix operator*(double lhs, const Matrix & rhs);
    
    //                                                              operator /
    // Matrix/double
    Matrix operator/(double div) {
        Matrix temp(name, rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.data[i][j] = data[i][j] / div;
            }
        }
        return temp;
    }

    // A+=B                                                         operator+=
    //      this einai &A
    //      mat einai B
    Matrix & operator+=(const Matrix & mat) {
        if (cols == mat.cols && rows == mat.rows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    data[i][j] += mat.data[i][j];
            }
        } else {
            throw std::invalid_argument("received negative value");
        }

        return *this;
    }

    // A-=B                                                         operator-=
    //      this einai &A
    //      mat einai B
    Matrix & operator-=(const Matrix & mat) {
        if (cols == mat.cols && rows == mat.rows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    data[i][j] -= mat.data[i][j];
            }
        } else {
            throw std::invalid_argument("received negative value");
        }

        return *this;
    }
    
    // Matrix * Matrix                                              operator*
    Matrix operator*(const Matrix & mat) {
        // C = A*B = this [rows][n] * mat[n][cols]
        int result_rows = this->rows;
        int result_cols = mat.cols;
        int common_dimension = this->cols;
        
        Matrix temp(name, result_rows, result_cols);
        
        if (this->cols != mat.rows) {
             throw std::invalid_argument("invalid matrix dimensions");
        } else {
            for (int i = 0; i < result_rows; i++) {
                for (int j = 0; j < result_cols; j++) {
                    temp[i][j] = 0;
                    for (int k = 0; k < common_dimension; k++) {
                        temp[i][j] += data[i][k] * mat.data[k][j];
                    }
                }
            }
        }

        return temp;
    }
    
    // ----------------------------------------------------------------------
    //                          Logical operators 
    //         == != >= <= > < 
    // ----------------------------------------------------------------------
   
    //                                                              operator==
    bool operator==(const Matrix & rmat) const {
        if (cols == rmat.cols && rows == rmat.rows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (data[i][j] != rmat.data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        } else {
            return false;
        }
    }
    
    //                                                              operator!=
    bool operator!=(const Matrix & rmat) const {
        return !((*this) == rmat);
//        if (cols == rmat.cols && rows == rmat.rows) {
//            for (int i = 0; i < rows; i++) {
//                for (int j = 0; j < cols; j++) {
//                    if (data[i][j] != rmat.data[i][j]) {
//                        return true;
//                    }
//                }
//            }
//            return false;
//        } else {
//            return true;
//        }
    }

    // ----------------------------------------------------------------------
    //                          stream operators 
    //         << >> 
    // ----------------------------------------------------------------------
    
    friend ostream & operator<<(ostream & out, const Matrix & rhs);
    friend istream & operator>>(istream & in, const Matrix & rhs);
};


 // double* Matrix
    // 2*A[3][4] 
Matrix operator*(double lhs, const Matrix & rhs) {
    Matrix temp(rhs.name, rhs.rows, rhs.cols);
    
    for (int i = 0; i < rhs.rows; i++ ) {
        for (int j = 0; j < rhs.cols; j++) {
            temp.data[i][j] = rhs.data[i][j] * lhs;
        }
    }
    return temp;
}

ostream & operator<<(ostream& out, const Matrix & rhs) {
    
    out << "Matrix " << rhs.name << " " << rhs.rows << "x" << rhs.cols << ":" << endl; 
    for (int i=0;i<rhs.rows;i++) {
        for (int j=0;j<rhs.cols;j++) {
            cout << rhs.data[i][j] << "\t";
        }
        cout << endl;
    }
    
    return out;
}

istream & operator>>(istream& in, const Matrix & rhs) {
    for (int i=0;i<rhs.rows;i++) {
        for (int j=0;j<rhs.cols;j++) {
            cout << rhs.name << "[" << i << "][" << j << "]=? ";
            in >> rhs.data[i][j];
        }
    }
    
    return in;
}

int main(int argc, char** argv) {

    //
    //    int data[m][n][k];
    //
    //    int *** d = new int**[m];
    //    for (int i = 0; i < m; i++) {
    //        d[i] = new int*[n];
    //        for (int j = 0; j < 15; j++) {
    //            d[i][j] = new int[15];
    //        }
    //    }
    
    //    for (int i = 0; i < 5; i++) {
    //        for (int j = 0; j < 10; j++) {
    //            for (int k = 0; k < 15; k++) {
    //                data[i][j][k] = 0;
    //            }
    //        }
    //    }
    //

//
    Matrix A('A', 3, 3);
    Matrix B('B', 3, 3);
    cout << " -------------------------- BEFORE: " << endl;
    cout << A << endl;
    cout << B << endl;
    cout << " -------------------------- "<< endl;;
    
    B[0][0] = 10;
    B[0][1] = 20;
    B[0][2] = 30;
    
    A = A+3*B+B*5+(-B);
    
    Matrix C = 3*A+(-B) + (~A)*10;
    C.setName('C');
    cout << C << endl;
            
    cout << " -------------------------- "<< endl;;
    cout << A << endl;
    cout << ~A << endl;
    cout << A+(~A) << endl;
    cout << B << endl;
    
    Matrix m('M', 2, 2);
    cin >> m;
    cout << m;
    m = m*m;
    cout <<" M*M is: " << endl;
    cout << m;
    
//    Matrix B(5);
//    Matrix C(5, 5);
//    //    Matrix D(3, 5, 7.0);  // TODO

//    A += B;
//

    return 0;
}

