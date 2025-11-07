#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagDNode {
    int data;
    struct tagDNode *Pre, *Next;
} DNode;

typedef struct tagDList {
    DNode *Head, *Tail;
} DList;

void CreateDList(DList *l) {
    l->Head = NULL;
    l->Tail = NULL;
}

DNode* CreateNode(int x) {
    DNode *n = (DNode*) malloc(sizeof(DNode));
    if(!n) exit(1);
    n->data = x;
    n->Pre = NULL;
    n->Next = NULL;
    return n;
}

void AddNode(DList *l) {
    char input[10];
    printf("Nhap danh sach (# de ngung nhap): ");
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "#") == 0) break;
        DNode *n = CreateNode(atoi(input));
        if (l->Head == NULL) {
            l->Head = n;
            l->Tail = l->Head;
        } else {
            l->Tail->Next = n;
            n->Pre = l->Tail;
            l->Tail = n;
        }
    }
}

int PowofNum(DList l, int x) {
    DNode *n = l.Head;
    long long powN = 1;
    while(n) {
        if (n->data > 0 && n->data % x == 0 && n->data % 2 == 0) powN *= n->data;
        n = n->Next;
    }
    return powN;
}

void SortList(DList *l) {
    
}

void FilterList(DList *l) {
    for (DNode *n = l->Head; n ; n = n->Next) {
        DNode *p = n->Next;
        while(p) {
            if (p->data == n->data) { // Check data(p) = data(n) ?
                DNode *temp = p;
                p = p->Next;

                // Check p la Head ?
                if (temp == l->Head) {
                    l->Head = temp->Next;
                } else {
                    temp->Pre->Next = temp->Next;
                }
                // Check p la Tail ?
                if (temp == l->Tail) {
                    l->Tail = temp->Pre;
                } else {
                    temp->Next->Pre = temp->Pre;
                }
                free(temp);
            } else p = p->Next;
        }
    }
}

void printList(DList l) {
    DNode *n = l.Head;
    while (n) {
        printf("%d ", n->data);
        n = n->Next;
    }
    printf("\n");
}

void printAddvsData(DList l) {
    DNode *n = l.Head;
    int count = 1;
    while (n) {
        printf("%3d | %15d | %10d\n", count, n, n->data);
        n = n->Next;
        count++;
    }
    printf("\n");
}

int main() {
    DList l;
    CreateDList(&l);
    while (1) {
        printf("\n-------- MENU --------\n\n");
        printf("1. Khoi tao danh sach.\n");
        printf("2. Kiem tra tinh nguyen to va xoa o vi tri K.\n");
        printf("3. Tinh tich cac so Chan, Duong chia het cho 5 (tru 0).\n");
        printf("4. Sap xep tang dan.\n");
        printf("5. Xoa cac phan tu trung nhau chi giu lai 1.\n");
        printf("6. In danh sach dia chi va gia tri.\n");
        printf("7. Hien thi Fibonaci.\n");
        printf("0. Thoat.\n");
        printf("\nChoice: ");
        int opt; 
        scanf("%d", &opt);    
        switch(opt) {
            case 1: 
                AddNode(&l);
                printList(l);
                break;
            case 2:
                break;
            case 3:
                if (PowofNum(l, 5) > 1) printf("Tich cua cac so chan, duong chia het cho 5: %d\n",  PowofNum(l, 5));
                else printf("Khong co so nao thoa man!!\n");
                break;
            case 4:
                break;
            case 5: 
                FilterList(&l); 
                printf("Thanh cong!\n");
                break;
            case 6:
                printf("---- Danh sach phan tu ----\n");
                printf("%3s | %15s | %10s\n", "STT", "Address", "Data");
                printAddvsData(l); 
                break;
            case 7: break;
            case 0: printf("Dang thoat ...."); return 0;
            default: printf("Lua chon khong hop le!!");
        }
    }
}