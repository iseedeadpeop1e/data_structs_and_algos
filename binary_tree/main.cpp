#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data): data(data), left(nullptr), right(nullptr) {}
    
    int getData() {
        return data;
    }
};

class BinaryTree {
private:
    TreeNode* root;
    
    TreeNode* recursiveInsert(TreeNode* treeNode, int data) {
        if (treeNode == nullptr) {
            return new TreeNode(data); // Если дерево пустое
        }

        if (data < treeNode->data) {
            treeNode->left = recursiveInsert(treeNode->left, data);
        }
        else if (data > treeNode->data) {
            treeNode->right = recursiveInsert(treeNode->right,data);
        }
        return treeNode; // Дубликаты не вставляем, просто возвращаем значение
    }


    TreeNode* recursiveDelete(TreeNode *treeNode, int data) {
        if (treeNode == nullptr) {
            return nullptr; // Не нашлии значение, 
        }

        if (data < treeNode->data){
            treeNode->left = recursiveDelete(treeNode->left, data);
        }

        else if (data > treeNode->data) {
            treeNode->right = recursiveDelete(treeNode->right, data);
        }
        else {  // нашли нужное data 
            if (treeNode->left == nullptr && treeNode->right == nullptr) {  // Первый случай, удаляемый узел не имеет потомков
                delete treeNode;
                return nullptr;
            }
            else if (treeNode->left == nullptr) {    // Второй случай, потомок один, в данном случае правый
                TreeNode* tempTreeNode = treeNode->right;
                delete treeNode;
                return tempTreeNode;
            }
            else if (treeNode->right == nullptr) {  // Есть только левый потомок
                TreeNode* tempTreeNode = treeNode->left;
                delete treeNode;
                return tempTreeNode;
            }
            else {  // третий случай, есть оба потомка
                TreeNode* nextNode = treeNode->right;
                while (nextNode && nextNode->left) { // ищем следующий узел
                    nextNode = nextNode->left;
                }
                treeNode->data = nextNode->data; // Заменяем данные на данные следующего узла
                treeNode->right = recursiveDelete(treeNode->right, nextNode->data); // и удаляем следующий узел
            }
        }
        return treeNode;
    } 

    bool recursiveSearch(const TreeNode* treeNode, int data) const {
        if (treeNode == nullptr) {
            return false;
        }
        if (data == treeNode->data) {
            return true;
        }
        if (data > treeNode->data) {
            return recursiveSearch(treeNode->right, data);
        }
        else {
            return recursiveSearch(treeNode->left, data);
        }
    }

    void recursiveGetInOrder (TreeNode *treeNode, vector<int>& list) const {
        if (treeNode == nullptr) {
            return;
        }
        recursiveGetInOrder(treeNode->left, list); // Сначала обойдем все левое поддерево от корня
        list.push_back(treeNode->data); // Затем добавим значение самого корня
        recursiveGetInOrder(treeNode->right, list); // И обойдем правое поддерево
    }

    void recursiveGetInRevesedOrded (TreeNode *treeNode, vector<int>& list) const {
        if(treeNode == nullptr) {
            return;
        }
        recursiveGetInRevesedOrded(treeNode->right, list);  // Логика та же, только меняем порядок обхода на обратный
        list.push_back(treeNode->data);
        recursiveGetInRevesedOrded(treeNode->left, list);
    }

    void recursiveSelfDestroy(TreeNode* treeNode) {
        if (treeNode != nullptr) {
            recursiveSelfDestroy(treeNode->left); //Начинаем удаление с листьев, рекурсивно доходим до них
            recursiveSelfDestroy(treeNode->right);
            delete treeNode;
        } 
    }

    TreeNode* recursiveSelfCopy(TreeNode* treeNode) {
        
        if (treeNode == nullptr) {
            return nullptr;
        }

        TreeNode* newTreeNode = new TreeNode(treeNode->data);
        newTreeNode->left = recursiveSelfCopy(treeNode->left );
        newTreeNode->right = recursiveSelfCopy(treeNode->right);
        return newTreeNode;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        recursiveSelfDestroy(root);
    }

    // конструктор копирования
    BinaryTree(const BinaryTree& other) {
        root = recursiveSelfCopy(other.root);
    }

    // присваивание
    BinaryTree& operator=(BinaryTree other) {
        swap(root, other.root);
        return *this;
    }

    void insert(int data ) {
        root = recursiveInsert(root, data);
    } 

    void remove(int data) {
        root = recursiveDelete(root, data);
    }

    bool search(int data) {
        bool found = recursiveSearch(root, data);
        return found;
    }

    vector<int> getInOrder() const {
        vector<int> result;
        recursiveGetInOrder(root, result);
        return result;
    }

    vector<int> getInReversedOrder() const {
        vector<int> result;
        recursiveGetInRevesedOrded(root, result);
        return result;
    }
};


int main() {
    BinaryTree binary_tree;
    
    binary_tree.insert(8);
    binary_tree.insert(3);
    binary_tree.insert(10);
    binary_tree.insert(1);
    binary_tree.insert(6);
    binary_tree.insert(14);
    binary_tree.insert(4);
    binary_tree.insert(7);

    cout << "Found 6: " << binary_tree.search(6) << "\n";

    // по возрастанию
    auto inOrder = binary_tree.getInOrder();
    cout << "In Order: ";
    for (int data : inOrder){
        cout << data << " ";
    } 
    cout << "\n";

    // по убыванию
    auto inReversedOrder = binary_tree.getInReversedOrder();
    cout << "In Reversed Order: ";
    for (int data : inReversedOrder){
        cout << data << " ";
    } 
    cout << "\n";

    // удаление
    binary_tree.remove(6);

    // копирование
    BinaryTree binary_tree_copied = binary_tree;
    binary_tree_copied.insert(2);
    cout << "Copied tree (removed 6, inserted 2):\n";
    for (int data : binary_tree_copied.getInOrder()) cout << data << " ";
}