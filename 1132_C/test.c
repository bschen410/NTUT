#include <stdio.h>
#include <stdlib.h> // 包含 malloc 和 free
#include <string.h> // 包含 memcpy (如果需要複製陣列)

// 定義二元樹節點結構
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 輔助函數：在中序遍歷陣列中查找某個值的位置
// 這裡為了簡化，每次查找都遍歷，效率較低。
// 實際應用中，可以考慮使用哈希表 (hash map) 或傳入索引範圍來優化。
int find_root_in_inorder(int *inorder, int start, int end, int root_val) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == root_val) {
            return i;
        }
    }
    return -1; // 不可能發生，因為 root_val 必然在中序遍歷中
}

// 主函數：從前序遍歷和中序遍歷陣列建構二元樹
TreeNode* buildTree(int* preorder, int pre_start, int pre_end,
                    int* inorder, int in_start, int in_end) {
    // 基本情況：如果遍歷範圍為空，則返回 NULL
    if (pre_start > pre_end || in_start > in_end) {
        return NULL;
    }

    // 前序遍歷的第一個元素是根節點
    int root_val = preorder[pre_start];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    root->val = root_val;
    root->left = NULL;
    root->right = NULL;

    // 在中序遍歷中找到根節點的位置
    int root_idx_in_inorder = find_root_in_inorder(inorder, in_start, in_end, root_val);

    // 計算左子樹的節點數量
    int left_subtree_size = root_idx_in_inorder - in_start;

    // 遞迴建構左子樹
    // 前序遍歷的左子樹：從 pre_start + 1 開始，長度為 left_subtree_size
    // 中序遍歷的左子樹：從 in_start 開始，到 root_idx_in_inorder - 1 結束
    root->left = buildTree(preorder, pre_start + 1, pre_start + left_subtree_size,
                           inorder, in_start, root_idx_in_inorder - 1);

    // 遞迴建構右子樹
    // 前序遍歷的右子樹：從 pre_start + left_subtree_size + 1 開始，到 pre_end 結束
    // 中序遍歷的右子樹：從 root_idx_in_inorder + 1 開始，到 in_end 結束
    root->right = buildTree(preorder, pre_start + left_subtree_size + 1, pre_end,
                            inorder, root_idx_in_inorder + 1, in_end);

    return root;
}

// 輔助函數：中序遍歷並印出節點值，用於驗證
void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

// 輔助函數：釋放樹的記憶體
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 主函數：測試
int main() {
    // 範例 1
    int preorder1[] = {3, 9, 20, 15, 7};
    int inorder1[] = {9, 3, 15, 20, 7};
    int n1 = sizeof(preorder1) / sizeof(preorder1[0]);

    printf("--- 範例 1 ---\n");
    TreeNode* root1 = buildTree(preorder1, 0, n1 - 1, inorder1, 0, n1 - 1);
    printf("建構樹 1 的中序遍歷結果: ");
    inorderTraversal(root1); // 應該是 9 3 15 20 7
    printf("\n");
    freeTree(root1); // 釋放記憶體

    // 範例 2
    int preorder2[] = {1, 2, 3, 4, 5, 6, 7};
    int inorder2[] = {3, 2, 4, 1, 6, 5, 7};
    int n2 = sizeof(preorder2) / sizeof(preorder2[0]);

    printf("--- 範例 2 ---\n");
    TreeNode* root2 = buildTree(preorder2, 0, n2 - 1, inorder2, 0, n2 - 1);
    printf("建構樹 2 的中序遍歷結果: ");
    inorderTraversal(root2); // 應該是 3 2 4 1 6 5 7
    printf("\n");
    freeTree(root2); // 釋放記憶體

    // 只有一個節點的樹
    int preorder3[] = {10};
    int inorder3[] = {10};
    int n3 = sizeof(preorder3) / sizeof(preorder3[0]);

    printf("--- 範例 3 ---\n");
    TreeNode* root3 = buildTree(preorder3, 0, n3 - 1, inorder3, 0, n3 - 1);
    printf("建構樹 3 的中序遍歷結果: ");
    inorderTraversal(root3); // 應該是 10
    printf("\n");
    freeTree(root3); // 釋放記憶體

    // 空樹
    printf("--- 範例 4 (空樹) ---\n");
    TreeNode* root4 = buildTree(NULL, 0, -1, NULL, 0, -1); // 傳入空陣列，範圍設為無效
    printf("建構樹 4 的中序遍歷結果: ");
    inorderTraversal(root4); // 應該是空輸出
    printf("\n");
    // 不需要 freeTree(root4) 因為它會是 NULL

    return 0;
}