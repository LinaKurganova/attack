#include <stdio.h>
#include "utils.h"
#include "findMin.h"
#include "decompose.h"

//составление базиса кода меньшего порядка
int** lessBasis(int** g, const int m, const int r){
    int n = power(2, m);
    int k = findK(m, r);
    int t = power(2, m - r);
    int now = 0;
    int next_k = findK(m, r - 1);
    int** b = (int**)malloc(sizeof(int*) * next_k);
    while(now < next_k){
        int* x = findMinWeight(g, k, n, t);
        int* supp = findSupp(x, n);
        int** shortCode = makeShortenCode(g, supp, r, m);
        int** v = decompose(shortCode, supp, t, r, m, 20);
        for (int i = 0; i < power(2, r) - 1; i++){
            int* f = (int*)malloc(sizeof(int) * n);
            for (int j = 0; j < n; j++){
                if (elem(j, supp, t) || elem(j, v[i], t))
                    f[j] = 1;
                else
                    f[j] = 0;
            }
            if (now < next_k){
                b[now++] = f;
            } else {
                free(f);
            }
        }
        free(x);
        free(supp);
        arrayFree(shortCode, k);
        arrayFree(v, power(2, r) - 1);
    }
    return b;
}

// поиск перестановки для кода первого порядка
int* findPermute(int** g, int m){
    int n = power(2, m);
    int k = m + 1;
    int** a = (int**)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++){
        a[i] = sample(g, k, n);
    }
    print2dArray(a, m, n);
    int* all_nums = (int*)malloc(sizeof(int) * n);
    int now_num = 0;
    for (int j = 0; j < n; j++){
        int* vec = (int*)malloc(sizeof(int) * m);
        for (int i = 0; i < m; i++){
            vec[i] = a[i][j];
        }
        int num = bin2int(vec, m);
        free(vec);
        if (elem(num, all_nums, now_num)){
            free(all_nums);
            arrayFree(a, m);
            return NULL;
        }
        all_nums[now_num++] = num;
    }
    return all_nums;
}
