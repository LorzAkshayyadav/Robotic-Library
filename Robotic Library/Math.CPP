#include <iostream>
#include <cmath>
#include "Matrix.h"
using namespace std;
MatrixUtils::MatrixUtils() {
                
}

// General matrix methods
void MatrixUtils::print_matrix(float* mat, int r, int c) { 
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout<<(mat[c * i + j]);
            cout<<("\t");
        }
        cout<<endl;
    }
    cout<<endl;
}

void MatrixUtils::copy_matrix(float* mat, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat[c * i + j];
        }
    }
}

void MatrixUtils::identity(float* mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                mat[n * i + j] = 1;
            }
            else {
                mat[n * i + j] = 0;
            }
        }
    }
}

void MatrixUtils::zero(float* mat, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mat[c * i + j] = 0;
        }
    }
}

void MatrixUtils::transpose(float* mat, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[r * j + i] = mat[c * i + j];
        }
    }
}

float MatrixUtils::trace(float* mat, int r) {
    float sum = 0;
    for (int i = 0; i < r; i++) {
        sum += mat[r * i + i]; 
    }
    return sum;
}

int MatrixUtils::inverse(float* A, int n) {
    int pivrow = 0;
    int k, i, j; 
    int pivrows[6];
    float tmp;

    for (k = 0; k < n; k++) {
        tmp = 0;
        for (i = k; i < n; i++) {
            if (abs(A[i * n + k]) >= tmp) {
                tmp = abs(A[i * n + k]);
                pivrow = i;
            }
        }

        if (A[pivrow * n + k] == 0.0f) {
//            Serial.println("Inversion failed due to singular matrix");
            return 0;
        }

        if (pivrow != k) {
            for (j = 0; j < n; j++) {
                tmp = A[k * n + j];
                A[k * n + j] = A[pivrow * n + j];
                A[pivrow * n + j] = tmp;
            }
        }
        pivrows[k] = pivrow; 

        tmp = 1.0f / A[k * n + k];  
        A[k * n + k] = 1.0f;

        for (j = 0; j < n; j++) {
            A[k * n + j] = A[k * n + j] * tmp;
        }

        for (i = 0; i < n; i++) {
            if (i != k) {
                tmp = A[i * n + k];
                A[i * n + k] = 0.0f;
                for (j = 0; j < n; j++) {
                    A[i * n + j] = A[i * n + j] - A[k * n + j] * tmp;
                }
            }
        }
    }

    for (k = n - 1; k >= 0; k--) {
        if (pivrows[k] != k) {
            for (i = 0; i < n; i++) {
                tmp = A[i * n + k];
                A[i * n + k] = A[i * n + pivrows[k]];
                A[i * n + pivrows[k]] = tmp;
            }
        }
    }
    return 1;
}


// Transformation matrix methods
void MatrixUtils::get_rot_mat(float* mat, float* rot_mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rot_mat[3 * i + j] = mat[4 * i + j];
        }
    }
}

void MatrixUtils::get_pos_vec(float* mat, float* pos_vec) {
    for (int i = 0; i < 3; i++) {
        pos_vec[i] = mat[4 * i + 3];
    }
}

void MatrixUtils::create_trn_mat(float* rot_mat, float* pos_vec, float* trn_mat) {
    zero((float*)trn_mat, 4, 4);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            trn_mat[4 * i + j] = rot_mat[3 * i + j];
        }
        trn_mat[4 * i + 3] = pos_vec[i];
    }
    trn_mat[4 * 3 + 3] = 1;
}

void MatrixUtils::trn_mat_inverse(float* mat, float* result) {
    float rot_mat[3][3];
    float pos_vec[3];
    float rot_mat_t[3][3];
    float pos_vec_result[3];

    get_rot_mat((float*)mat, (float*)rot_mat);
    get_pos_vec((float*)mat, pos_vec);
    transpose((float*)rot_mat, 3, 3, (float*)rot_mat_t);
    mul_vector((float*)rot_mat_t, pos_vec, 3, 3, pos_vec_result);
    pos_vec_result[0] = -pos_vec_result[0];
    pos_vec_result[1] = -pos_vec_result[1];
    pos_vec_result[2] = -pos_vec_result[2];
    create_trn_mat((float*)rot_mat_t, pos_vec_result, (float*)result);
}

void MatrixUtils::adjoint(float* mat, float* result) {
  
}

void MatrixUtils::exp3(float* mat, float* result) {
   
}

void MatrixUtils::exp6(float* mat, float* result) {
  
}

void MatrixUtils::log3(float* mat, float* result) {
   
}

void MatrixUtils::log6(float* mat, float* result) {
  
}

// Vector methods
float MatrixUtils::norm(float* vec) {
    return sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2)); 
}

float MatrixUtils::get_angle(float* vec) {
    return norm(vec);
}

// Matrix operators
void MatrixUtils::add_scalar(float* mat, float s, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat[c * i + j] + s;
        }
    }
}

void MatrixUtils::sub_scalar(float* mat, float s, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat[c * i + j] - s;
        }
    }
}

void MatrixUtils::mul_scalar(float* mat, float s, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat[c * i + j] * s;
        }
    }
}

void MatrixUtils::div_scalar(float* mat, float s, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat[c * i + j] / s;
        }
    }
}

void MatrixUtils::add_matrix(float* mat1, float* mat2, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat1[c * i + j] + mat2[c * i + j];
        }
    }
}

void MatrixUtils::sub_matrix(float* mat1, float* mat2, int r, int c, float* result) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[c * i + j] = mat1[c * i + j] - mat2[c * i + j];
        }
    }
}

void MatrixUtils::mul_matrix(float* mat1, float* mat2, int r1, int c1, int r2, int c2, float* result) {
    for (int i = 0; i < r1; i++) {
        for(int j = 0; j < c2; j++) {
            result[c2 * i + j] = 0;
            for (int k = 0; k < c1; k++) {
                result[c2 * i + j] = result[c2 * i + j] + mat1[c1 * i + k] * mat2[c2 * k + j];
            }
        }
    }
}

void MatrixUtils::mul_vector(float* mat, float* vec, int r, int c, float* result) {
    for (int i = 0; i < c; i++) {
        result[i] = 0;
    }
    
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            result[i] = result[i] + (vec[j] * mat[c * i + j]);
        }
    }
}

