#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct tagSN {
    int data;
} SN;

typedef struct tagDNode {
    SN *value;
    struct tagDNode *Pre, *Next;
} DNode;

typedef struct tagDList {
    DNode *Head, *Tail;
    int size;
} DList;

void CreateDList(DList *l) {
    l->Head = NULL;
    l->Tail = NULL;
    l->size = 0;
}

DNode *CreateNode(int x) {
    SN *num = (SN*) malloc(sizeof(SN));
    num->data = x;
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (!n || !num) exit(1);
    n->value = num;
    n->Pre = NULL;
    n->Next = NULL;
    return n;
}

void AddNode(DList *l, FILE *f) {
    char input[20];
    while (fscanf(f, "%s", input) != EOF) {
        if (strcmp(input, "#") == 0) break;
        DNode *n = CreateNode(atoi(input));
        if (l->Head == NULL) {
            l->Head = n;
            l->Tail = l->Head;
        }
        else {
            l->Tail->Next = n;
            n->Pre = l->Tail;
            l->Tail = n;
        }
        l->size++;
    }
}

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

DNode *findLocation(DList l, int locate) {
    DNode *n = l.Head;
    int i = 1;
    while (n && i < locate) {
        n = n->Next;
        i++;
    }
    return n;
}

void DeleteNode(DList *l, DNode *n){
    if (n == l->Head)
        l->Head = n->Next;
    if (n == l->Tail)
        l->Tail = n->Pre;
    if (n->Pre)
        n->Pre->Next = n->Next;
    if (n->Next)
        n->Next->Pre = n->Pre;
}

void DeleteAtPosition(DList *l, int locate) {
    DNode *n = findLocation(*l, locate);
    if (!n) {
        printf("Vuot qua so luong phan tu List hoac List rong!!");
        return; 
    }
    if (isPrime(n->value->data)) {
        printf("Da xoa phan tu o vi tri %d co gia tri %d\n", locate, n->value->data);
        DeleteNode(l, n);
        free(n->value);
        free(n);
        l->size--;
    } else printf("Phan tu o vi tri %d khong phai so nguyen to!!\n", locate);
}

int PowofNum(DList l, int x) {
    DNode *n = l.Head;
    long long powN = 1;
    while (n) {
        if (n->value->data > 0 && n->value->data % x == 0 && n->value->data % 2 == 0)
            powN *= n->value->data;
        n = n->Next;
    }
    return powN;
}

void SortList(DList *l) {
    DNode *i = l->Head;
    if (!i) return;
    for (i; i != NULL; i = i->Next) {
        for (DNode *j = l->Tail; j != i; j = j->Pre) {
            if (j->value->data < j->Pre->value->data) {
                SN *temp = j->value;
                j->value = j->Pre->value;
                j->Pre->value = temp;
            }
        }
    }
}

void FilterList(DList *l) {
    for (DNode *n = l->Head; n; n = n->Next) {
        DNode *p = n->Next;
        while (p) {
            if (p->value->data == n->value->data) { // Check data(p) = data(n) ?
                DNode *temp = p;
                p = p->Next;
                // Check p la Head ?
                if (temp == l->Head) l->Head = temp->Next;
                // Check p la Tail ?
                if (temp == l->Tail) l->Tail = temp->Pre;
                if (temp->Pre) 
                    temp->Pre->Next = temp->Next;
                if (temp->Next)
                    temp->Next->Pre = temp->Pre;
                free(temp->value);
                free(temp);
                l->size--;
            }
            else p = p->Next;
        }
    }
}

void DeleteList(DList *l) {
    while (l->Head) {
        DNode *temp = l->Head;
        l->Head = l->Head->Next;
        if (temp->value) free(temp->value);
        free(temp);
    }
    l->Tail = NULL;
    l->size = 0;
}

void Fibonacci(DList l) {
    DNode *n = l.Head;
    int f1 = 1;   // fib[n-1]
    int f2 = 0;   // fib[n-2]
    int f  = 0;   // fib hiện tại
    int count = 0;
    while (n) {
        if (f == n->value->data) {
            count++;
            printf("%d ", n->value->data);
            n = n->Next;
        }
        else if (f > n->value->data) {
            n = n->Next;
        }
        else {
            f = f1 + f2; // tạo số tiếp theo
            f2 = f1;
            f1 = f;
        }
    }
    if (count == 0) printf("-- EMPTY --");
}

void printList(DList l) {
    DNode *n = l.Head;
    while (n) {
        printf("%d ", n->value->data);
        n = n->Next;
    }
    printf("\n");
}

void printAddvsData(DList l) {
    DNode *n = l.Head;
    int count = 1;
    while (n) {
        printf("%3d | %15d | %10d\n", count, n, n->value->data);
        n = n->Next;
        count++;
    }
    printf("\n");
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        printf("Khong mo duoc file input.txt");
        return 1;
    }
    DList l;
    
    for (int i = 0; i < 5; i++) {
        printf("\n---------------------------\n");
        printf("TESTCASE #%d", i + 1);
        printf("\n---------------------------\n");
        CreateDList(&l);
        // Nhập List
        AddNode(&l, f);
        printf("List vua nhap: "); printList(l);
        printf("\n");
        // Kiểm tra tính nguyên tố và xoá khỏi List
        DeleteAtPosition(&l, 5); printList(l);
        printf("\n");
        // Tính tích các số chẵn, dương chia hết cho 5 > 0
        if (PowofNum(l, 5) > 1) printf("Tich cua cac so chan, duong chia het cho 5: %d\n", PowofNum(l, 5));
        else printf("Khong co so nao thoa man chan, duong, chia het cho 5!!\n");
        printf("\n");
        // Sắp xếp tăng dần
        SortList(&l); 
        printf("List sau khi sap xep tang dan: "); printList(l);
        printf("\n");
        // Xoá các phần tử trùng nhau chỉ để lại 1 số
        FilterList(&l);
        printf("List sau khi loc: "); printList(l);
        printf("\n");
        // In danh sách dịa chỉ và giá trị
        printf("---- Danh sach phan tu ----\n");
        printf("%3s | %15s | %10s\n", "STT", "Address", "Data"); 
        printAddvsData(l);
        printf("\n");
        // In fibonaci
        printf("Day Fibonacci trong List: "); Fibonacci(l);
        printf("\n");
        DeleteList(&l);
    }
}
