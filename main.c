
// Authors:
//    Kris Santiso
//    Diego Arturo Contreras
//    Antia Vazquez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


#define DOTEST 0
#define DOEX2 1
#define DOEX4 0
//to reuse variables we also use this as the maximum number a node can be
#define iterations 10000

#define SZ 256000
struct heap {
    int last;
    int vector[SZ];
};
typedef struct heap * pheap;

double microsegundos () {
    struct timeval t;
    if (gettimeofday (&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void init_seed () {
    srand(time(NULL));
}

void ascending_init (int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descending_init (int v[], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = n-i;
}

void random_init (int v[], int n) {
    init_seed();
    int i, m = 2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void init_heap(pheap h){
    h->last = -1;
}

void print_heap (pheap h){
    for (int i=0; i<=h->last;i++){
        printf("%d ",h->vector[i]);
    }
    printf("\n");
}

void print_array (int v[],int n){
    for (int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

void swap (pheap h, int a, int b){
    int aux=h->vector[a];
    h->vector[a]=h->vector[b];
    h->vector[b]=aux;
}

void PercolateUp (pheap h, int i){
    while((i>0)&&(h->vector[(i-1)/2]>h->vector[(i)])){
        swap (h,(i-1)/2,i);
        i=(i-1)/2;
    }
}

int insert_heap(pheap h, int x){
    if (h->last >= SZ-1) {
        printf("Cannot insert, heap is already full\n");
        return 1;
    } else{
        h->last = h->last +1;
        h->vector [h->last] = x;
        PercolateUp (h,h->last);
        return 0;
    }
}

void PercolateDown(pheap h, int i){
    int j=i+1,left,right;
    while (j!=i){
        left= 2*i +1;
        right= 2*i +2;
        j = i;
        if((right<=h->last)&&(h->vector[right]<h->vector[i])){
            i=right;
        }
        if ((left<=h->last)&&(h->vector[left]<h->vector[i])){
            i=left;
        }
        swap (h,j,i);
    }
}

void remove_min(pheap h){
    if (h->last==-1){
        printf("Empty heap, cannot remove\n");
    } else{
        h->vector[0]=h->vector[h->last];
        h->last=h->last-1;
        if (h->last>=0){
            PercolateDown(h,0);
        }
    }
}

int check_min(pheap h){
    if (h->last == -1){
        printf("Heap is empty\n");
        return -1;
    } else {
        return h->vector[0];
    }
}

void create_heap(pheap* h, int const a[], int n){
    init_heap(*h);
    (*h)->last=n-1;
    for (int i=0; i<n ;i++){
        (*h)->vector[i]=a[i];
    }
    for (int i=n/2 -1;i>=0;i--){
        PercolateDown(*h,i);
    }
}

void heap_sort (int a[],int n){
    pheap h=malloc(sizeof(struct heap));
    create_heap (&h,a,n);
    printf("Heap array after create_heap: \t");
    print_heap(h);
    for (int i=0;i<n;i++){
        a[i]= check_min(h);
        remove_min(h);
    }
    free(h);
}

void test_functions(int a[],int n){
    pheap h=malloc(sizeof(struct heap));
    if (h==NULL){
        printf("Allocation error\n");
        return;
    }
    int x=0;
    descending_init(a,n);
    printf("Initial array:\n");
    print_array(a,n);
    create_heap(&h,a,n);
    printf("Created heap:\n");
    print_heap(h);
    printf("Minimum element: %d\n", check_min(h));
    printf("Inserting element %d:\n",x);
    insert_heap(h,x);
    print_heap(h);
    printf("Minimum element: %d\n", check_min(h));
    for (int i=0;i<n+1;i++){
        printf("Removing  minimum element %d:\n", check_min(h));
        remove_min(h);
        print_heap(h);
    }
    printf("\n");
    free(h);
}

void test_heapsort(int a[],void (*init)(int[],int),int n){
    init(a,n);
    printf("Original Array:\t");
    print_array(a,n);
    printf("Sorting...\n");
    heap_sort(a,n);
    printf("Sorted array:\t");
    print_array(a,n);
}

void test(){
    int n=10, t[n],a[n],d[n],r[n];
    test_functions(t,n);
    test_heapsort(a,ascending_init,n);
    test_heapsort(d,descending_init,n);
    test_heapsort(r,random_init,n);
}

void print_headlines(int ex, char part) {
    if (ex == 2 ) {
        if (part == 'a') {
            printf("Adding n nodes with insert_heap to an empty array\n");
        }
        else if (part == 'b') {}
        else {printf("ERROR\n");}
    } else if (ex == 4) {
        if (part == 'a') {}
        else if (part == 'b') {}
        else if (part == 'c') {}
        else {printf("ERROR\n");}
    } else {
        printf("ERROR\n");
    }
    printf("\tn\tTime\tunder.\ttight\tover.\n");
}

void print_algorithms (int n, double t, int iterated, int ex, char part) {
    double x, y, z;
    if (ex == 2) {
        if (part == 'a') {
            x = t / pow(n* (log(n)), 0.8); y = t / (n* (log(n))); z = t / pow(n* (log(n)), 1.2);
        } else if (part == 'b') {
            x = t / n; y = t / n; z = t / n;
        } else {x = 0; y = 0; z = 0;}
    } else if (ex == 4) {
        if (part == 'a') {
            x = t / n; y = t / n; z = t / n;
        } else if (part == 'b') {
            x = t / n; y = t / n; z = t / n;
        }  else if (part == 'c') {
            x = t / n; y = t / n; z = t / n;
        } else {x = 0; y = 0; z = 0;}
    } else {
        x = 0; y = 0; z = 0;
    }
    if (iterated == 1) {
        printf("%12d %20.3fms* %20.12f %20.12f %20.12f\n", n, t, x, y, z);
    } else {
        printf("%12d %20.3fms  %20.12f %20.12f %20.12f\n", n, t, x, y, z);
    }
}

int random_num (int max) {
    int i = rand() % (max + 1);
    return i;
}

double repeat_rand (int iter, int i) {
    double ta = 0, tb = 0;
    if (i == 0) { //it means we iterated iterations times
        ta = microsegundos();
        for (int k = 0; k < iterations; k++) {
            for (int z = 0; z < iter; z++) {
                random_num(iterations);
            }
        }
        tb = microsegundos();
    } else { //it means we didnt iterate
        ta = microsegundos();
        for (int z = 0; z < iter; z++) {
            random_num(iterations);
        }
        tb = microsegundos();
    }
    return tb - ta;
}

double repeat_init () {
    double ta = 0, tb = 0;
    pheap h = malloc(sizeof(struct heap));
    ta = microsegundos();
    for (int z = 0; z < iterations; z++) {
        init_heap(h);
    }
    tb = microsegundos();
    free(h);
    return tb - ta;
}

double repeat_rand_init (int iter) {
    double ta = 0, tb = 0;
    int arr[iter];
    ta = microsegundos();
    for (int z = 0; z < iterations; z++) {
        random_init(arr, iter);
    }
    tb = microsegundos();
    return tb - ta;
}

double repeat_asc_init (int iter) {
    double ta = 0, tb = 0;
    int arr[iter];
    ta = microsegundos();
    for (int k = 0; k < iterations; k++) {
        random_init(arr, iter);
        ascending_init(arr, iter);
    }
    tb = microsegundos();
    return tb - ta - repeat_rand_init(iter);
}

double repeat_desc_init (int iter) {
    double ta = 0, tb = 0;
    int arr[iter];
    ta = microsegundos();
    for (int k = 0; k < iterations; k++) {
        random_init(arr, iter);
        descending_init(arr, iter);
    }
    tb = microsegundos();
    return tb - ta - repeat_rand_init(iter);
}

double iterate_algorithms_2 (pheap h, int n, char part) {
    double t1 = 0, t2 = 0, t = 0;
    if (part == 'a') {
        t1 = microsegundos();
        for (int k = 0; k < iterations; k++) {
            init_heap(h);
            for (int z = 0; z < n; z++) {
                int i = random_num(iterations);
                insert_heap(h, i);
            }
        }
        t2 = microsegundos();
        t = t2 - t1 - repeat_rand(iterations, 1) - repeat_init();
    } else if (part == 'b') {
        int arr[n];
        t1 = microsegundos();
        for (int k = 0; k < iterations; k++) {
            random_init(arr, n);
            for (int z = 0; z < n; z++) {
                create_heap(&h, arr, n);
            }
        }
        t2 = microsegundos();
        t = t2 - t1 - repeat_rand_init(n);
    }
    return t;
}

double iterate_algorithms_4 (int arr[], int n, char part) {
    double t1 = 0, t2 = 0;
    if (part == 'a') {
        t1 = microsegundos();
        for (int k = 0; k < iterations; k++) {
            heap_sort(arr, n);
            ascending_init(arr, n);
        }
        return t2 - t1 - repeat_asc_init(n);
    } else if (part == 'b') {
        t1 = microsegundos();
        for (int k = 0; k < iterations; k++) {
            heap_sort(arr, n);
            descending_init(arr, n);
        }
        return t2 - t1 - repeat_desc_init(n);
    } else if (part == 'c') {
        t1 = microsegundos();
        for (int k = 0; k < iterations; k++) {
            heap_sort(arr, n);
            random_init(arr, n);
        }
        return t2 - t1 - repeat_rand_init(n);
    }
}

double iterate_algorithms (pheap h, int arr[], int n, int ex, char part) {
    double t = 0;
    if (ex == 2) {
        t = iterate_algorithms_2(h, n, part);
    } else if (ex == 4) {
        t = iterate_algorithms_4(arr, n, part);
    }
    return t / iterations;
}

double ex2_partA (pheap h, int iteration) {
    double t1 = 0, t2 = 0;
    t1 = microsegundos();
    for (int n = 0; n < iteration; n++) {
        int i = random_num(iterations);
        if ( insert_heap(h, i) == 1 ) {
            return -1;
        }
    }
    t2 = microsegundos();
    return (t2 - t1);
}

double ex2_partB (pheap h, int iteration) {
    double t1 = 0, t2 = 0;
    int arr[iteration];
    random_init(arr, iteration);
    t1 = microsegundos();
    for (int n = 0; n < iteration; n++) {
        create_heap(&h, arr, iteration);
    }
    t2 = microsegundos();
    return (t2 - t1);
}

double ex4_partA (int arr[], int iteration) {
    double t1 = 0, t2 = 0;
    t1 = microsegundos();
    heap_sort(arr, iteration);
    t2 = microsegundos();
    return (t2 - t1);
}

double ex4_partB (int arr[], int iteration) {
    double t1 = 0, t2 = 0;
    t1 = microsegundos();
    heap_sort(arr, iteration);
    t2 = microsegundos();
    return (t2 - t1);
}

double ex4_partC (int arr[], int iteration) {
    double t1 = 0, t2 = 0;
    t1 = microsegundos();
    heap_sort(arr, iteration);
    t2 = microsegundos();
    return (t2 - t1);
}

void run_algorithm (pheap h, int arr[], int iteration, int ex, char part) {
    int iterated = 0;
    double t = 0;
    if (ex == 2 && part == 'a') { t = ex2_partA(h, iteration); }
    if (ex == 2 && part == 'b') { t = ex2_partB(h, iteration); }
    if (ex == 4 && part == 'a') { t = ex4_partA(arr, iteration); }
    if (ex == 4 && part == 'b') { t = ex4_partB(arr, iteration); }
    if (ex == 4 && part == 'c') { t = ex4_partC(arr, iteration); }
    if (t < 500) {
        t = iterate_algorithms(h, arr, iteration, ex, part);
        iterated = 1;
    }
    print_algorithms(iteration, t, iterated, ex, part);
}

int main() {
    init_seed();
    if (DOTEST != 0) {
        test();
    }
    if ( DOEX2 != 0) {
        print_headlines(2, 'a');
        for (int n = 500; n <= 32000; n = n*2) {
            pheap h = malloc(sizeof(struct heap));
            init_heap(h);
            run_algorithm(h, NULL, n, 2, 'a');
            free(h);
        }
        print_headlines(2, 'b');
        for (int n = 500; n <= 32000; n = n*2) {
            pheap h = malloc(sizeof(struct heap));
            init_heap(h);
            run_algorithm(h, NULL, n, 2, 'b');

        }

    }
    if (DOEX4 != 0) {
        print_headlines(4, 'a');
        for (int n = 125; n <= 16000; n = n*2) {
            int arr[n];
            ascending_init(arr, n);
            run_algorithm(NULL, arr, n, 4, 'a');
        }
        print_headlines(4, 'b');
        for (int n = 125; n <= 16000; n = n*2) {
            int arr[n];
            descending_init(arr, n);
            run_algorithm(NULL, arr, n, 4, 'b');
        }
        print_headlines(4, 'c');
        for (int n = 125; n <= 16000; n = n*2) {
            int arr[n];
            random_init(arr, n);
            run_algorithm(NULL, arr, n, 4 , 'c');
        }
    }
    return 0;
}
