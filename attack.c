#include "utils.h"
#include "findMin.h"
#include "decompose.h"
#include "generateBasis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    const int r = 2;
    const int m = 4;
    int n = power(2, m);
    const int k = findK(m, r);
    int t = power(2, m - r);
    int** g = read2dArray("data2.txt", k, n);
    print2dArray(g, k, n);
    printf("==================================\n");
    int** b = lessBasis(g, m, r);
    print2dArray(b, findK(m, r - 1), n);
    arrayFree(b, findK(m, r - 1));
    arrayFree(g, k);
    return 0;
}