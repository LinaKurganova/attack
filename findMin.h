#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include <unistd.h>
#pragma once

// создание случайного информативного множества размера k из чисел [0, n)
int* makeSet(const int n, const int k){
    int* res = (int*)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++){
        int num;
        while (elem(num = generate_random_number(n), res, i));
        res[i] = num;
    }
    qsort(res, k, sizeof (int), (int(*) (const void *, const void *)) comp);
    return res;
}

// сложение двух векторов одинаковой размерности в поле по модулю два
int* sumInField(const int* left, int* right, const int size){
    int* res = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        res[i] = (left[i] + right[i]) % 2;
    return res;
}

// подсчет веса вектора
int weight(const int* vector, const int size){
    int res = 0;
    for (int i = 0; i < size; i++){
        res += vector[i];
    }
    return res;
}

// прямой[ и обратный] проход гаусса на множестве set
int** gauss(int** g, const int* set, const int set_size, const int k, const int n, int reverse){
    int** ans = matrixCopy(g, k, n);
    int now = 0;
    for (int i = 0; i < set_size; i++){
        int col = set[i];
        int j = now;
        while (j < k && ans[j][col] != 1)
            j++;
        if (j == k){
            continue;
        }
        if (j != now){
            int* tmp = ans[now];
            ans[now] = sumInField(ans[now], ans[j], n);
            free(tmp);
        } 
        for (int j = (reverse == 1) ? 0 : now + 1; j < k; j++){
            if (ans[j][col] != 0 && now != j){
                int* tmp = ans[j];
                ans[j] = sumInField(ans[now], ans[j], n);
                free(tmp);
            }
        }
        now++;
    }
    return ans;
}

// подбор случайного кодового слова из кода
int* sample(int** g, const int k, const int n){
    int set_size;
    while ((set_size = generate_random_number(k)) == 0);
    int* set = makeSet(k, set_size);
    int* res = (int*)malloc(sizeof(int) * n);
    for (int j = 0; j < n; j++){
        int num = 0;
        for (int i = 0; i < set_size; i++){
            num += g[set[i]][j];
        }
        res[j] = num % 2;
    }
    free(set);
    return res;
}

// нахождение кодового слова минимального веса в коде
int* findMinWeight(int** g, const int k, const int n, const int t){
    int set_i = 0;
    int max_size = 10;
    int** sets = (int**)malloc(sizeof(int*) * max_size);
    while (1){
        int** f;
        int* set;
        while (1) {
            if (!elem2d(set = makeSet(n, k), sets, set_i, k))
                break;
            free(set);
        }
        sets = putInSets(sets, set, &set_i, &max_size);
        f = gauss(g, set, k, k, n, 1);
        int x_i = 0;
        int** xs = (int**)malloc(sizeof(int*) * k);
        for (int i = 0; i < k; i++) {
            if (weight(f[i], n) <= t) {
                xs[x_i++] = f[i];
            }
        }
        if (x_i > 0) {
            int num = generate_random_number(x_i);
            int* res = vectorCopy(xs[num], n);
            free(xs);
            arrayFree(f, k);
            arrayFree(sets, set_i);
            return res;
        }
        free(xs);
        arrayFree(f, k);
    }
}