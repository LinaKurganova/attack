#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <math.h>
#pragma once

int comp(const int *i, const int *j){
    return *i - *j;
}

int** deleteFirst(int** g, const int size){
    free(g[0]);
    for (int i = 0; i < size - 1; i++){
        g[i] = g[i + 1];
    }
    return (int**)realloc(g, sizeof(int*) * (size - 1));
}

long long fact(const int n){
    if (n < 0)
        return -1;
    if (n < 2)
        return 1;
    return n * fact(n - 1);
}

int eqVector(int* vector1, int* vector2, const int size){
    for (int i = 0; i < size; i++){
        if (vector1[i] != vector2[i])
            return 0;
    }
    return 1;
}

int* vectorCopy(int* tmp, const int n){
    int* res = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        res[i] = tmp[i];
    }
    return res;
}

int** matrixCopy(int** from, const int k, const int n){
    int** to = (int**)malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++){
        to[i] = vectorCopy(from[i], n);
    }
    return to;
}

int elem(const int num, int* array, const int size){
    for (int i = 0; i < size; i++){
        if (num == array[i])
            return 1;
    }
    return 0;
}

int elem2d(int* seq, int** array, const int k, const int n){
    for (int i = 0; i < k; i++){
        if (eqVector(seq, array[i], n))
            return 1;
    }
    return 0;
}

int max(int a, int b){
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int* maxInRows(int** g, int k, int n){
    int* res = (int*)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++){
        res[i] = g[i][0];
        for (int j = 1; j < n; j++){
            res[i] = max(res[i], g[i][j]);
        }
    }
    return res;
}

int argmax(int* seq, const int size){
    int max = seq[0];
    int id = 0;
    for (int i = 1; i < size; i++){
        if (seq[i] > max){
            max = seq[i];
            id = i;
        }
    }
    return id;
}

int** putInSets(int** sets, int* set, int* i, int* max_size){
    sets[(*i)++] = set;
    if (*i == *max_size){
        *max_size *= 2;
        sets = (int**)realloc(sets, *max_size * sizeof(int*));
    }
    return sets;
}

int generate_random_number(int n) {
    unsigned char buffer[4];
    RAND_bytes(buffer, sizeof(buffer));
    int random_number = *((unsigned int*) buffer) % n;
    return random_number;
}

double power(const int num, const int degree){
    if (degree == 0){
        return 1;
    } else if (degree > 0)
        return power(num, degree - 1) * num;
    else
        return power(num, degree + 1) / num;
}

long long comb(const int n, const int k){
    return fact(n) / fact(k) / fact(n - k);
}

void printArray(const int* tmp, const int k){
    for (int i = 0; i < k; i++){
        printf("%d ", tmp[i]);
    }
    printf("\n");
}

void print2dArray(int** tmp, const int k, const int n){
    for (int i = 0; i < k; i++)
        printArray(tmp[i], n);
}

int* readArray(FILE* f, const int n){
    int* res = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        fscanf(f, "%d", &res[i]);
    }
    return res;
}

void arrayFree(int** tmp, const int n){
    for (int i = 0; i < n; i++){
        free(tmp[i]);
    }
    free(tmp);
}

int** read2dArray(const char* file_path, const int k, const int n){
    FILE* f = fopen(file_path, "r");
    int** res = (int **)malloc(sizeof(int*) * k);
    for(int i = 0; i < k; i++){
        res[i] = readArray(f, n);
    }
    fclose(f);
    return res;
}

int bin2int(int* vec, const int size){
    int num = 0;
    for (int i = 0; i < size; i++){
        num = num * 2 + vec[i];
    }
    return num;
}

int findK(const int m, const int r){
    int k = 0;
    for (int i = 0; i <= r; i++){
        k += comb(m, i);
    }
    return k;
}
