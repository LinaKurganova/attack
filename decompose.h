#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "utils.h"
#include "findMin.h"
#include <math.h>
#pragma once

// удаляет нулевые столбцы в матрице
int** deleteColumns(int** code, int* set, const int set_size, const int k, const int n){
    for (int i = 0; i < k; i++){
        int* new = (int*)malloc(sizeof(int) * (n - set_size));
        int new_i = 0;
        for (int j = 0; j < n; j++) {
            if (!elem(j, set, set_size))
                new[new_i++] = code[i][j];
        }
        free(code[i]);
        code[i] = new;
    }
    return code;
}

// нахождение supp(x)
int* findSupp(int* x, const int size){
    int* set = (int*)malloc(sizeof(int) * size);
    int j = 0;
    for (int i = 0; i < size; i++){
        if (x[i] == 1){
            set[j++] = i;
        }
    }
    return (int*)realloc(set, j * sizeof(int));
}

// составление укороченного кода
int** makeShortenCode(int **g, int* supp, const int r, const int m){
    int n = power(2, m);
    int k = findK(m, r);
    int t = power(2, m - r);
    int** shorted = gauss(g, supp, t, k, n, 0);
    shorted = deleteColumns(shorted, supp, t, k, n);
    return shorted;
}

// разделение кода на неперсекающиеся множества координат
int** decompose(int** g, int* supp, const int supp_size, const int r, const int m, const int amount){
    int n = power(2, m) - power(2, m - r);
    int k = findK(m, r);
    int t = power(2, m - 2 * r + 1) * (power(2, r) - 1);
    int** c = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        c[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            c[i][j] = 0;
    }

    int sets_i = 0, max_size = amount + 1;
    int** sets = (int**)malloc(sizeof(int*) * max_size);
    for (int l = 0; l < amount; l++){
        int* min;
        while (1) {
            min = sample(g, k, n);
            if (weight(min, n) <= t && !elem2d(min, sets, sets_i, n)){
                break;
            }
            free(min);
        }
        sets = putInSets(sets, min, &sets_i, &max_size);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (min[i] == 1 && min[j] == 1 && i != j){
                    c[i][j]++;
                }
            }
        }
    }
    arrayFree(sets, sets_i);

    int v_i = 0;
    int** v = (int**)malloc(sizeof(int*) * (power(2, r) - 1));
    for (int e = 0; e < power(2, r) - 1; e++){
        int x_i = 0;
        int* x = (int*)malloc(sizeof(int) * power(2, m - r));
        int* max_rows = maxInRows(c, n, n);
        x[x_i++] = argmax(max_rows, n);
        for (int j = 0; j < n; j++){
            c[x[0]][j] = -100000;
        }
        free(max_rows);
        while (x_i < power(2, m - r)) {
            int* sum = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++){
                sum[i] = 0;
                for (int j = 0; j < x_i; j++){
                    sum[i] += c[i][x[j]];
                }
            }
            int new_num = argmax(sum, n);
            free(sum);
            for (int j = 0; j < n; j++){
                c[new_num][j] = -100000;
            }
            x[x_i++] = new_num;
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < power(2, m - r); j++){
                c[i][x[j]] = -100000;
            }
        }
        v[v_i++] = x;
    }
    for (int v_i = 0; v_i < power(2, r) - 1; v_i++){
        for (int i = 0; i < power(2, m - r); i++){
            int j = 0;
            while (j < power(2, m - r) && supp[j++] <= v[v_i][i]);
            v[v_i][i] += j - 1;
        }
    }

    arrayFree(c, n);
    return v;
}
