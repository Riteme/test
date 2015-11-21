// AC

#include <cstring>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// hash������ȡģֵ��10..07ϵ��������һ�� +20%
#define MOD 1000007
// ״̬�������ֵ
#define MAXN 1030302

// ��ʾ������
struct Result {
    Result() : value(0), count(0) {}
    Result(int _v, int _c) : value(_v), count(_c) {}

    int value;
    int count; // ���ڼ����ж��ٸ���ʽ��ֵ��value

    bool operator==(const int lhs) const { return value == lhs; }
};  // struct Result

// �����ֶ�ʵ�ֵ��������ػ���POJ��STL�����˶�... +50%
template <typename T>
struct Node {
    T value;
    Node *next;
};  // struct Node

typedef unsigned hash_t;
typedef Node<Result> NodeType;

static NodeType *hb[MOD]; // ɢ�б�
static NodeType memory[MAXN + 1]; // �Ż��������ܽ���������ڴ���䵽�����Ŀռ��ϣ�����cache miss +25%
static int n = 1; // ����ʹ�ù����ڴ�

static int a1, a2, a3, a4, a5;

NodeType *list_allocate();// �����ڴ棬��ʵ������memory���ó�һ��Ԫ��...
void list_push(NodeType **node, int v); // ��ָ���ڵ��ǰ������µĽڵ㣬��ΪNULL�����滻
NodeType *list_find(NodeType *node, int v); // ���ҽڵ�

void increase(int v);
int count(int v);

inline hash_t h(int v) {
    return (v >= 0 ? v : -v) % MOD;
}

inline int compute(int x1, int x2, int x3) {
    return a1 * x1 * x1 * x1 + a2 * x2 * x2 * x2 + a3 * x3 * x3 * x3;
}

inline int compute(int x4, int x5) {
    return -(a4 * x4 * x4 * x4 + a5 * x5 * x5 * x5);
}

inline NodeType *list_allocate() { return &memory[n++]; }

void list_push(NodeType **node, int v) {
    if (node == NULL) {
        // *node = new NodeType();
        *node = list_allocate();
        (*node)->value.value = v;
        (*node)->value.count = 1;
        (*node)->next = NULL;
    } else {
        NodeType *origin = *node;

        // *node = new NodeType();
        *node = list_allocate();
        (*node)->value.value = v;
        (*node)->value.count = 1;
        (*node)->next = origin;
    }
}

NodeType *list_find(NodeType *node, int v) {
    while (node != NULL) {
        if (node->value.value == v)
            break;
        else
            node = node->next;
    }  // while

    return node;
}

/*inline*/ void increase(int v) {
    hash_t u = h(v);
    NodeType *iter = list_find(hb[u], v);

    if (iter == NULL)
        list_push(&hb[u], v);
    else
        iter->value.count++;
}

/*inline*/ int count(int v) {
    hash_t u = h(v);

    NodeType *iter = list_find(hb[u], v);
    if (iter == NULL)
        return 0;
    else
        return iter->value.count;
}

int main(/*int argc, char *argv[]*/) {
    scanf("%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5);

    memset(hb, NULL, sizeof(hb));

    // for (int x1 = -50; x1 <= 50; x1++)
    //     if (x1 != 0)
    //         for (int x2 = -50; x2 <= 50; x2++)
    //             if (x2 != 0)
    //                 for (int x3 = -50; x3 <= 50; x3++)
    //                     if (x3 != 0) increase(compute(x1, x2, x3));
    // �ֶ��Ż���ʹѭ�������գ�����cache miss +50%
    for (int x1 = 1; x1 <= 50; x1++)
        for (int x2 = 1; x2 <= 50; x2++)
            for (int x3 = 1; x3 <= 50; x3++) {
                increase(compute(x1, x2, x3));
                increase(compute(x1, x2, -x3));
                increase(compute(x1, -x2, x3));
                increase(compute(-x1, x2, x3));
                increase(compute(x1, -x2, -x3));
                increase(compute(-x1, x2, -x3));
                increase(compute(-x1, -x2, x3));
                increase(compute(-x1, -x2, -x3));
            }

    // int cnt = 0;
    // for (int x1 = -50; x1 <= 50; x1++)
    //     if (x1 != 0)
    //         for (int x2 = -50; x2 <= 50; x2++)
    //             if (x2 != 0) cnt += count(compute(x1, x2));
    // �Ż�ͬ��
    int cnt = 0;
    for (int x1 = 1; x1 <= 50; x1++)
        for (int x2 = 1; x2 <= 50; x2++) {
            cnt += count(compute(x1, x2));
            cnt += count(compute(x1, -x2));
            cnt += count(compute(-x1, x2));
            cnt += count(compute(-x1, -x2));
        }

    printf("%d", cnt);

    return 0;
}  // function main
