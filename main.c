#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

// Authors:
//    Kris Santiso
//    Diego Arturo Contreras
//    Antia Vazquez

#define DOTEST 0
#define DOEX2 1
#define DOEX4 0

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
    for (int i=0;i<10;i++){
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

void insert_heap(pheap h, int x){
    if (h->last >= SZ-1) {
        printf("Cannot insert, heap is already full\n");
    } else{
        h->last = h->last +1;
        h->vector [h->last] = x;
        PercolateUp (h,h->last);
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

int check_min(const pheap h){
    if (h->last == -1){
        printf("Heap is empty\n");
        return -1;
    } else {
        return h->vector[0];
    }
}

void create_heap(pheap h, int a[], int n){
    init_heap(h);
    h->last=n-1;
    for (int i=0; i<n ;i++){
        h->vector[i]=a[i];
    }
    for (int i=n/2 -1;i>=0;i--){
        PercolateDown(h,i);
    }
}

void heap_sort (int a[],int n){
    pheap h=malloc(sizeof(struct heap));
    create_heap (h,a,n);
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
    int x=0;
    descending_init(a,n);
    printf("Initial array:\n");
    print_array(a,n);
    create_heap(h,a,n);
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
    //free(h);

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
            x = t / n; y = t / n; z = t / n;
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

double iterate_algorithms () {
    double t1 = 0, t2 = 0;
    return t2 - t1;;
}

void ex2_partA (int n) {
    int iterated = 0;
    double t1 = 0, t2 = 0, t;
    t1 = microsegundos();
    for (int z = 0; z < n; z++) {}
    t2 = microsegundos();
    t = (t2 - t1);
    if (t < 500) {
        t = iterate_algorithms(n);
        iterated = 1;
    }
    print_algorithms(n, t, iterated, 0);
}

void ex2 () {
    pheap h = malloc(sizeof(struct heap));
    print_headlines(2, 'a');
    for (int n = 125; n <= 16000; n = n*2) {

    }
    print_headlines(2, 'b');
    for (int n = 125; n <= 16000; n = n*2) {

    }
    free(h);
}

void ex4 () {
    print_headlines(4, 'a');
    print_headlines(4, 'b');
    print_headlines(4, 'c');
}

int main() {
    init_seed();
    if (DOTEST != 0) {
        test();
    }
    if (DOEX2 != 0) {
        ex2();
    }
    if (DOEX4 != 0) {
        ex4();
    }
    return 0;
}
