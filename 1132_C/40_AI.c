#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義二元樹節點結構
typedef struct node_s {
    char data;
    struct node_s *right, *left;
} tree_t;

typedef tree_t *btree;

// --- 佇列的實作 (用於層序遍歷) ---
#define MAX_QUEUE_SIZE 100 // 假設樹的節點數不會超過100，根據題目輸入長度 <= 20，100足夠
typedef struct {
    btree items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, btree item) {
    if (q->rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = item;
}

btree dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    btree item = q->items[q->front];
    if (q->front == q->rear) { // Last element in queue
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}
// --- 佇列實作結束 ---

// 輔助函數：在中序遍歷字串中查找某個字元的位置
int findCharIndex(const char *str, int start, int end, char target_char) {
    for (int i = start; i <= end; i++) {
        if (str[i] == target_char) {
            return i;
        }
    }
    return -1; // 不會發生，因為 target_char 必然存在
}

// 根據前序和中序序列建構二元樹
btree buildTree_Pre_In(const char *preorder, int pre_start, int pre_end,
                       const char *inorder, int in_start, int in_end) {
    // 基本情況：遍歷範圍無效，返回 NULL
    if (pre_start > pre_end || in_start > in_end) {
        return NULL;
    }

    // 前序遍歷的第一個字元是根節點
    char root_data = preorder[pre_start];
    btree root = (btree)malloc(sizeof(tree_t));
    if (root == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    root->data = root_data;
    root->left = NULL;
    root->right = NULL;

    // 在中序遍歷中找到根節點的位置
    int root_idx_in_inorder = findCharIndex(inorder, in_start, in_end, root_data);

    // 計算左子樹的節點數量
    int left_subtree_size = root_idx_in_inorder - in_start;

    // 遞迴建構左子樹
    root->left = buildTree_Pre_In(preorder, pre_start + 1, pre_start + left_subtree_size,
                                  inorder, in_start, root_idx_in_inorder - 1);

    // 遞迴建構右子樹
    root->right = buildTree_Pre_In(preorder, pre_start + left_subtree_size + 1, pre_end,
                                   inorder, root_idx_in_inorder + 1, in_end);

    return root;
}

// 根據後序和中序序列建構二元樹
btree buildTree_Post_In(const char *postorder, int post_start, int post_end,
                        const char *inorder, int in_start, int in_end) {
    // 基本情況：遍歷範圍無效，返回 NULL
    if (post_start > post_end || in_start > in_end) {
        return NULL;
    }

    // 後序遍歷的最後一個字元是根節點
    char root_data = postorder[post_end];
    btree root = (btree)malloc(sizeof(tree_t));
    if (root == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    root->data = root_data;
    root->left = NULL;
    root->right = NULL;

    // 在中序遍歷中找到根節點的位置
    int root_idx_in_inorder = findCharIndex(inorder, in_start, in_end, root_data);

    // 計算左子樹的節點數量
    int left_subtree_size = root_idx_in_inorder - in_start;

    // 遞迴建構右子樹（因為後序遍歷是左->右->根，所以先處理右子樹的後序序列會比較順）
    root->right = buildTree_Post_In(postorder, post_start + left_subtree_size, post_end - 1,
                                    inorder, root_idx_in_inorder + 1, in_end);

    // 遞迴建構左子樹
    root->left = buildTree_Post_In(postorder, post_start, post_start + left_subtree_size - 1,
                                   inorder, in_start, root_idx_in_inorder - 1);

    return root;
}

// 層序遍歷並輸出樹的內容
void levelOrderTraversal(btree root) {
    if (root == NULL) {
        return;
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        btree current = dequeue(&q);
        printf("%c", current->data);

        if (current->left != NULL) {
            enqueue(&q, current->left);
        }
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }
    printf("\n"); // 輸出後換行
}

// 釋放樹的記憶體
void freeTree(btree root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char type1, type2;
    char str1[21], str2[21]; // 字串長度最大20 + 1 for null terminator
    int len;
    btree root = NULL;

    // 讀取輸入
    scanf(" %c", &type1); // 注意 ' ' 在 %c 前，用於吃掉換行符號
    scanf("%s", str1);
    scanf(" %c", &type2);
    scanf("%s", str2);

    len = strlen(str1); // 兩個字串長度應該相同

    // 根據輸入的遍歷類型建構樹
    if (type1 == 'P' && type2 == 'I') {
        root = buildTree_Pre_In(str1, 0, len - 1, str2, 0, len - 1);
    } else if (type1 == 'I' && type2 == 'P') {
        root = buildTree_Pre_In(str2, 0, len - 1, str1, 0, len - 1);
    } else if (type1 == 'O' && type2 == 'I') {
        root = buildTree_Post_In(str1, 0, len - 1, str2, 0, len - 1);
    } else if (type1 == 'I' && type2 == 'O') {
        root = buildTree_Post_In(str2, 0, len - 1, str1, 0, len - 1);
    } else {
        // 理論上不會發生，因為題目限定了輸入組合
        printf("Invalid input traversal types.\n");
        return 1;
    }

    // 輸出層序遍歷結果
    levelOrderTraversal(root);

    // 釋放記憶體
    freeTree(root);

    return 0;
}
