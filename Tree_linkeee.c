#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Trie 节点定义
typedef struct TrieNode {
    struct TrieNode *children[26];  // 26个指针，指向子节点
    char *phoneNumber;              // 存储电话号码的指针
    int isEndOfWord;                // 标记是否是单词的结尾
} TrieNode;

// 创建新节点
TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    
    // 初始化所有子节点指针为 NULL
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    
    newNode->phoneNumber = NULL;
    newNode->isEndOfWord = 0;
    
    return newNode;
}

// 将字符串转换为小写
void toLowerString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// 插入联系人
void insertContact(TrieNode *root, const char *name, const char *phone) {
    TrieNode *current = root;
    
    // 复制名字并转为小写
    char *lowerName = strdup(name);
    toLowerString(lowerName);
    
    // 遍历名字的每个字符
    for (int i = 0; lowerName[i] != '\0'; i++) {
        char c = lowerName[i];
        
        // 只处理小写字母
        if (c < 'a' || c > 'z') {
            printf("错误：名字只能包含字母！\n");
            free(lowerName);
            return;
        }
        
        int index = c - 'a';  // 计算索引：'a'->0, 'b'->1, ..., 'z'->25
        
        // 如果当前字母对应的子节点不存在，创建它
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        
        // 移动到子节点
        current = current->children[index];
    }
    
    // 标记单词结束，并存储电话号码
    current->isEndOfWord = 1;
    
    // 如果已有电话号码，先释放
    if (current->phoneNumber != NULL) {
        free(current->phoneNumber);
    }
    
    // 分配内存并复制电话号码
    current->phoneNumber = (char*)malloc(strlen(phone) + 1);
    if (current->phoneNumber == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    strcpy(current->phoneNumber, phone);
    
    free(lowerName);
    
    printf("联系人 '%s' 已添加，电话: %s\n", name, phone);
}

// 搜索联系人
char* searchContact(TrieNode *root, const char *name) {
    TrieNode *current = root;
    
    // 复制名字并转为小写
    char *lowerName = strdup(name);
    toLowerString(lowerName);
    
    // 遍历名字的每个字符
    for (int i = 0; lowerName[i] != '\0'; i++) {
        char c = lowerName[i];
        
        if (c < 'a' || c > 'z') {
            free(lowerName);
            return NULL;
        }
        
        int index = c - 'a';
        
        // 如果路径不存在，返回 NULL
        if (current->children[index] == NULL) {
            free(lowerName);
            return NULL;
        }
        
        current = current->children[index];
    }
    
    free(lowerName);
    
    // 如果找到了名字的结尾，返回电话号码
    if (current != NULL && current->isEndOfWord) {
        return current->phoneNumber;
    }
    
    return NULL;
}

// 辅助函数：打印所有联系人
void printAllContactsHelper(TrieNode *node, char *prefix, int depth) {
    if (node == NULL) return;
    
    // 如果当前节点是一个联系人的结尾，打印它
    if (node->isEndOfWord) {
        prefix[depth] = '\0';  // 结束字符串
        printf("  %s: %s\n", prefix, node->phoneNumber);
    }
    
    // 递归遍历所有子节点
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            prefix[depth] = 'a' + i;  // 添加当前字母到前缀
            printAllContactsHelper(node->children[i], prefix, depth + 1);
        }
    }
}

// 打印所有联系人
void printAllContacts(TrieNode *root) {
    if (root == NULL) {
        printf("电话簿为空！\n");
        return;
    }
    
    printf("=== 所有联系人 ===\n");
    char buffer[100];  // 存储当前名字
    printAllContactsHelper(root, buffer, 0);
    printf("==================\n");
}

// 前缀搜索：查找所有以指定前缀开头的联系人
void searchByPrefixHelper(TrieNode *node, char *prefix, int depth, int *count) {
    if (node == NULL) return;
    
    // 如果当前节点是一个联系人的结尾，打印它
    if (node->isEndOfWord) {
        prefix[depth] = '\0';  // 结束字符串
        printf("  %d. %s: %s\n", ++(*count), prefix, node->phoneNumber);
    }
    
    // 递归遍历所有子节点
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            prefix[depth] = 'a' + i;  // 添加当前字母到前缀
            searchByPrefixHelper(node->children[i], prefix, depth + 1, count);
        }
    }
}

// 前缀搜索
void searchByPrefix(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    
    // 复制前缀并转为小写
    char *lowerPrefix = strdup(prefix);
    toLowerString(lowerPrefix);
    
    // 先导航到前缀的最后一个节点
    for (int i = 0; lowerPrefix[i] != '\0'; i++) {
        char c = lowerPrefix[i];
        
        if (c < 'a' || c > 'z') {
            printf("前缀只能包含字母！\n");
            free(lowerPrefix);
            return;
        }
        
        int index = c - 'a';
        
        if (current->children[index] == NULL) {
            printf("没有找到以 '%s' 开头的联系人\n", prefix);
            free(lowerPrefix);
            return;
        }
        
        current = current->children[index];
    }
    
    printf("=== 以 '%s' 开头的联系人 ===\n", prefix);
    
    // 从当前节点开始，递归查找所有联系人
    char buffer[100];
    strcpy(buffer, lowerPrefix);  // 复制前缀到缓冲区
    int startDepth = strlen(lowerPrefix);
    int count = 0;
    
    searchByPrefixHelper(current, buffer, startDepth, &count);
    
    if (count == 0) {
        printf("  没有找到联系人\n");
    }
    
    printf("============================\n");
    
    free(lowerPrefix);
}

// 检查节点是否有子节点
int hasChildren(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            return 1;
        }
    }
    return 0;
}

// 删除联系人
int deleteContactHelper(TrieNode *node, const char *name, int depth) {
    if (node == NULL) {
        return 0;
    }
    
    // 如果到了名字的末尾
    if (depth == strlen(name)) {
        // 如果这个节点标记为单词结尾
        if (node->isEndOfWord) {
            node->isEndOfWord = 0;  // 取消标记
            
            // 释放电话号码内存
            if (node->phoneNumber != NULL) {
                free(node->phoneNumber);
                node->phoneNumber = NULL;
            }
            
            // 如果这个节点没有子节点，它可以被删除
            if (!hasChildren(node)) {
                return 1;  // 返回1表示可以删除这个节点
            }
            
            return 0;  // 返回0表示不能删除这个节点
        }
        
        return 0;  // 不是单词结尾，不需要删除
    }
    
    // 递归处理下一个字符
    char c = name[depth];
    int index = c - 'a';
    
    // 如果下一个字符对应的路径不存在，这个联系人不存在
    if (node->children[index] == NULL) {
        return 0;
    }
    
    // 递归删除
    int shouldDeleteChild = deleteContactHelper(node->children[index], name, depth + 1);
    
    // 如果子节点应该被删除
    if (shouldDeleteChild) {
        free(node->children[index]);  // 释放子节点内存
        node->children[index] = NULL;  // 将指针设为NULL
        
        // 如果当前节点不是单词结尾且没有其他子节点，它也可以被删除
        if (!node->isEndOfWord && !hasChildren(node)) {
            return 1;  // 返回1表示可以删除这个节点
        }
    }
    
    return 0;  // 返回0表示不能删除这个节点
}

// 删除联系人（对外接口）
void deleteContact(TrieNode *root, const char *name) {
    // 复制名字并转为小写
    char *lowerName = strdup(name);
    toLowerString(lowerName);
    
    // 先检查联系人是否存在
    if (searchContact(root, lowerName) == NULL) {
        printf("联系人 '%s' 不存在，无法删除\n", name);
        free(lowerName);
        return;
    }
    
    // 执行删除
    deleteContactHelper(root, lowerName, 0);
    
    printf("联系人 '%s' 已删除\n", name);
    
    free(lowerName);
}

// 释放 Trie 树内存
void freeTrie(TrieNode *node) {
    if (node == NULL) return;
    
    // 递归释放所有子节点
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            freeTrie(node->children[i]);
        }
    }
    
    // 释放电话号码内存
    if (node->phoneNumber != NULL) {
        free(node->phoneNumber);
    }
    
    // 释放节点本身
    free(node);
}

// 显示内存使用情况（估算）
void showMemoryUsage(TrieNode *node, int *nodeCount) {
    if (node == NULL) return;
    
    (*nodeCount)++;
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            showMemoryUsage(node->children[i], nodeCount);
        }
    }
}

// 打印菜单
void printMenu() {
    printf("\n=== 电话号码簿管理系统 ===\n");
    printf("1. 添加联系人\n");
    printf("2. 查找联系人\n");
    printf("3. 删除联系人\n");
    printf("4. 显示所有联系人\n");
    printf("5. 前缀搜索\n");
    printf("6. 显示内存使用情况\n");
    printf("7. 退出\n");
    printf("==========================\n");
    printf("请选择操作 (1-7): ");
}

// 演示函数：展示 Trie 的工作原理
void demonstrateTrieStructure() {
    printf("\n=== Trie 结构演示 ===\n");
    
    // 创建根节点
    TrieNode* root = createNode();
    printf("1. 创建根节点\n");
    printf("   根节点地址: %p\n", (void*)root);
    printf("   根节点的 children 数组有 26 个指针元素\n");
    printf("   初始时所有指针都是 NULL\n\n");
    
    // 插入 "alice"
    printf("2. 插入联系人 'alice' -> '123-456-7890'\n");
    insertContact(root, "alice", "123-456-7890");
    
    // 显示一些内存地址
    printf("\n   内存地址说明:\n");
    printf("   - 根节点地址: %p\n", (void*)root);
    
    if (root->children[0] != NULL) {  // 'a' 的索引是 0
        TrieNode* nodeA = root->children[0];
        printf("   - 节点 'a' 地址: %p\n", (void*)nodeA);
        
        if (nodeA->children[11] != NULL) {  // 'l' 的索引是 11
            TrieNode* nodeL = nodeA->children[11];
            printf("   - 节点 'l' 地址: %p\n", (void*)nodeL);
        }
    }
    
    printf("\n3. 再插入联系人 'bob' -> '555-123-4567'\n");
    insertContact(root, "bob", "555-123-4567");
    
    printf("\n4. 搜索演示:\n");
    printf("   搜索 'alice': ");
    char* result = searchContact(root, "alice");
    if (result) {
        printf("找到，电话: %s\n", result);
    } else {
        printf("未找到\n");
    }
    
    printf("   搜索 'bob': ");
    result = searchContact(root, "bob");
    if (result) {
        printf("找到，电话: %s\n", result);
    } else {
        printf("未找到\n");
    }
    
    printf("   搜索 'charlie': ");
    result = searchContact(root, "charlie");
    if (result) {
        printf("找到，电话: %s\n", result);
    } else {
        printf("未找到\n");
    }
    
    // 显示所有联系人
    printf("\n5. 所有联系人:\n");
    printAllContacts(root);
    
    // 前缀搜索演示
    printf("\n6. 前缀搜索演示:\n");
    printf("   搜索以 'a' 开头的联系人:\n");
    searchByPrefix(root, "a");
    
    // 清理内存
    freeTrie(root);
    printf("\n演示结束，已释放内存\n");
}

int main() {
    TrieNode *phonebook = createNode();
    int choice;
    char name[100];
    char phone[20];
    
    // 预先声明可能用到的变量
    char *foundPhone = NULL;
    
    while (1) {
        printMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("输入错误！\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1: {
                printf("请输入联系人名字: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                
                printf("请输入电话号码: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = '\0';
                
                insertContact(phonebook, name, phone);
                break;
            }
                
            case 2: {
                printf("请输入要查找的联系人名字: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                
                foundPhone = searchContact(phonebook, name);
                if (foundPhone != NULL) {
                    printf("找到联系人 '%s': %s\n", name, foundPhone);
                } else {
                    printf("联系人 '%s' 不存在\n", name);
                }
                break;
            }
                
            case 3: {
                printf("请输入要删除的联系人名字: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                
                deleteContact(phonebook, name);
                break;
            }
                
            case 4: {
                printAllContacts(phonebook);
                break;
            }
                
            case 5: {
                printf("请输入前缀: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                
                searchByPrefix(phonebook, name);
                break;
            }
                
            case 6: {
                int nodeCount = 0;
                showMemoryUsage(phonebook, &nodeCount);
                
                size_t nodeSize = sizeof(TrieNode);
                size_t totalMemory = nodeCount * nodeSize;
                
                printf("当前 Trie 树有 %d 个节点\n", nodeCount);
                printf("每个节点大小: %zu 字节\n", nodeSize);
                printf("总内存使用: %zu 字节 (约 %.2f KB)\n", 
                       totalMemory, totalMemory / 1024.0);
                break;
            }
                
            case 7: {
                printf("感谢使用，正在释放内存...\n");
                freeTrie(phonebook);
                printf("程序退出\n");
                return 0;
            }
                
            default: {
                printf("无效选择，请重试\n");
                break;
            }
        }
    }
    
    return 0;
}