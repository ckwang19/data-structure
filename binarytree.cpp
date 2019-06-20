#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

class TreeNode{
public:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int data;
    TreeNode(int d):leftchild(0),rightchild(0),parent(0),data(d){};
};
class BinaryTree{
public:
    TreeNode *root;         // 以root作為存取整棵樹的起點
    int numCount;
    int maxDepth;
    BinaryTree(TreeNode *node):root(node),numCount(0),maxDepth(0){};
    void Preorder(TreeNode *current);
    void Inorder(TreeNode *current);
    void Inorder(TreeNode *current, int depth);
    void Postorder(TreeNode *current);
    void Levelorder();
    void AddNode(TreeNode *current,std::vector<int> v);
    void InsertLevelorder(char data);
    void InsertBST(int key);
    TreeNode* SearchBST(int key);
    TreeNode* DeleteBST(int key);
    TreeNode* GetLastNode(TreeNode* root);
};

void BinaryTree::InsertLevelorder(char data){    

    std::queue<TreeNode*> q;
    TreeNode *current = root;
    
    while (current) {
        if (current->leftchild != NULL){               // current的leftchild沒有空位
            q.push(current->leftchild);                // 將其推進queue中
        }
        else{                                          // current的leftchild有空位
            TreeNode *new_node = new TreeNode(data);   // 建立新的node, 將字母放在這裡
            new_node->parent = current;
            current->leftchild = new_node;
            break;                         
        }
        if (current->rightchild != NULL) {             // current的rightchild沒有空位
            q.push(current->rightchild);               // 將其推進queue中
        }
        else{                                          // current的rightchild有空位
            TreeNode *new_node = new TreeNode(data);   // 建立新的node, 將字母放在這裡
            new_node->parent = current;                
            current->rightchild = new_node;
            break;
        }
        current = q.front();
        q.pop();
    }
}

void BinaryTree::Preorder(TreeNode *current){   //A B C 踩到的點就會先輸出，然後先左再右
    if (current) {                          // if current != NULL
        std::cout << current->data << " ";   // V
        Preorder(current->leftchild);       // L
        Preorder(current->rightchild);      // R
    }
}
void BinaryTree::Inorder(TreeNode *current){    //B A C 先左到底再回來，最後才是右
    if (current) {                          // if current != NULL
        Inorder(current->leftchild);        // L
        std::cout << current->data << " ";   // V
        Inorder(current->rightchild);       // R
    }
}

void BinaryTree::Inorder(TreeNode *current, int depth){    //B A C 先左到底再回來，最後才是右
    if (current) {                          // if current != NULL
        this->numCount++;
        depth++;
        Inorder(current->leftchild, depth);        // L
        Inorder(current->rightchild, depth);       // R
    }else {
        if(depth > this->maxDepth) this->maxDepth = depth;
    }
}

void BinaryTree::Postorder(TreeNode *current){  //B C A 先左再右，最後才回來
    if (current) {                         // if current != NULL
        Postorder(current->leftchild);     // L
        Postorder(current->rightchild);    // R
        std::cout << current->data << " ";  // V
    }
}
void BinaryTree::Levelorder(){  //A B C 由上往下，先左再右，同一個level的由左到右
    std::queue<TreeNode*> q;
    q.push(this->root);                     // 把root作為level-order traversal之起點，推進queue中
    while (!q.empty()){                     // 若queue不是空的, 表示還有node沒有visiting
        TreeNode *current = q.front();      // 取出先進入queue的node
        q.pop();                          
        std::cout << current->data << " ";   // 進行visiting
        if (current->leftchild != NULL){    // 若leftchild有資料, 將其推進queue
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL){   // 若rightchild有資料, 將其推進queue
            q.push(current->rightchild);
        }
    }
}

void BinaryTree::AddNode(TreeNode *current,std::vector<int> v){
    int index = 0;
    std::queue<TreeNode*> q;
    q.push(this->root);                     // 把root作為level-order traversal之起點，推進queue中
    while (!q.empty()){                     // 若queue不是空的, 表示還有node沒有visiting
        TreeNode *current = q.front();      // 取出先進入queue的node
        q.pop();                          
        std::cout << current->data << " ";   // 進行visiting
        if (current->leftchild != NULL){    // 若leftchild有資料, 將其推進queue
            q.push(current->leftchild);
        }else{
            if (!v.empty()){
                TreeNode *temp = new TreeNode(v[0]); 
                current->leftchild = temp;
                q.push(temp);
                v.erase(v.begin());
            }
        }
        if (current->rightchild != NULL){   // 若rightchild有資料, 將其推進queue
            q.push(current->rightchild);
        }else{
            if (!v.empty()){
                TreeNode *temp = new TreeNode(v[0]); 
                current->rightchild = temp;
                q.push(temp);
                v.erase(v.begin());
            }
        }
    }
    std::cout << "\n";
}

TreeNode* BinaryTree::SearchBST(int key){
    TreeNode *current_node = root;
    while(current_node){
        if(current_node->data == key) return current_node;
        else if(current_node->data > key) current_node = current_node->leftchild;
        else current_node = current_node->rightchild;
    }
    return nullptr;
}

void BinaryTree::InsertBST(int key){
    TreeNode *y = 0;        // 準新手爸媽
    TreeNode *x = 0;        // 哨兵
    TreeNode *insert_node = new TreeNode(key); 

    x = root;
    while (x != NULL) {                // 在while中, 以如同Search()的方式尋找適當的位置       
        y = x;                                
        if (insert_node->data < x->data){
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                  // 跳出迴圈後, x即為NULL
                                       // y即為insert_node的parent
    insert_node->parent = y;           // 將insert_node的parent pointer指向y

    if (y == NULL){                    // 下面一組if-else, 把insert_node接上BST
        this->root = insert_node;
    }
    else if (insert_node->data < y->data){
        y->leftchild = insert_node;
    }
    else{
        y->rightchild = insert_node;
    }
}

TreeNode* BinaryTree::GetLastNode(TreeNode* root){                         // if current != NULL
    TreeNode* current = root;
    while(current->rightchild){
        current = current->rightchild;
    }
    return current;
}

TreeNode* BinaryTree::DeleteBST(int key){
    TreeNode* targetNode = SearchBST(key);
    //std::cout << targetNode->data << std::endl;
    TreeNode* tempNode;
    if(targetNode){
        if(targetNode->parent){ //不是root
            // targetNode是那個分支的最後一個節點
            if(targetNode->leftchild == nullptr && targetNode->rightchild == nullptr){
                // target比父大，target在父的右邊，target右邊child = nullptr
                if(targetNode->data > targetNode->parent->data) targetNode->parent->rightchild = nullptr;
                // target比父小，target在父的左邊，target左邊child = nullptr
                else targetNode->parent->leftchild = nullptr;
            // 如果target的left & right node都不是0
            }else if(targetNode->leftchild != nullptr && targetNode->rightchild != nullptr){
                // target比父大，target在父的右邊，父指向target左邊child的頭，target左邊child的最右下的node指向target右邊child的頭
                if(targetNode->data > targetNode->parent->data) {
                    targetNode->parent->rightchild = targetNode->leftchild;
                    tempNode = GetLastNode(targetNode->leftchild);
                    tempNode->rightchild = targetNode->rightchild;
                } else{
                    targetNode->parent->leftchild = targetNode->leftchild;
                    tempNode = GetLastNode(targetNode->leftchild);
                    tempNode->rightchild = targetNode->rightchild;
                }
            // 其中一個node是0
            }else{
                if(targetNode->data > targetNode->parent->data) {
                    targetNode->parent->rightchild = targetNode->leftchild;
                } else{
                    targetNode->parent->leftchild = targetNode->leftchild;
                }
            }
            return root;
        // root
        }else{
            tempNode = GetLastNode(targetNode->leftchild);
            tempNode->parent->rightchild = nullptr;
            tempNode->leftchild = targetNode->leftchild;
            tempNode->rightchild = targetNode->rightchild;
            return tempNode;
        }
        cout << "end" << endl;
    }else{
        return root;
    }
}



void PathSumII(TreeNode* t, int current, int sum, vector<vector<int>> &ans, vector<int> &path){
    if (t == NULL || current + t -> data > sum) return;
    //確保加進ans的path一定都經過尾巴
    //if (t -> leftchild == NULL && t -> rightchild == NULL) {
        if (current + t -> data == sum) {
            cout << "1: " << t->data << endl;
            path.push_back(t -> data);
            ans.push_back(path);
            path.pop_back();
            return;
        }
    //}
    path.push_back(t -> data);
    PathSumII(t -> leftchild, current + t -> data, sum, ans, path);
    PathSumII(t -> rightchild, current + t -> data, sum, ans, path);
    path.pop_back();
    //讓中間的path也都能成為ans
    //vector<int> path2;
    //path2.clear();
    //PathSumII(t -> leftchild, 0, sum, ans, path2);
    //PathSumII(t -> rightchild, 0, sum, ans, path2);
};

void print2(vector<vector<int> > &ans){
    cout << endl;
    for (int i = 0; i < ans.size(); i++){
        for (int j = 0; j < ans[i].size(); j++){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

void LevelOrder(TreeNode* root){
    queue<TreeNode*> q;
    TreeNode *current = nullptr;
    q.push(root);
    while(!q.empty()){
        current = q.front();
        cout << current->data << endl;
        q.pop();
        if(current->leftchild){
            q.push(current->leftchild);
        }
        if(current->rightchild){
            q.push(current->rightchild);
        }
    }
}

void BinarySearchTreeInsert(TreeNode* root, int value){
    TreeNode *current = root;
    TreeNode *pre = nullptr;
    while(current){
        pre = current;
        if(current->data > value){
            current = current->leftchild;
        }else{
            current = current->rightchild;
        }
    }
    TreeNode *insertNode = new TreeNode(value);
    if(pre->data > value){
        pre->leftchild = insertNode;
    }else{
        pre->rightchild = insertNode;
    }
    insertNode->parent = pre;
}

bool ValidateBinarySearchTree(TreeNode* root, long max, long min){
    if(!root) return true;
    else if(root->data > max || root->data < min) return false;
    else if(root->leftchild || root->rightchild){
        if(root->leftchild){
            if(root->data < root->leftchild->data) return false;
        }
        if(root->rightchild){
            if(root->data > root->rightchild->data) return false;
        }
    }
    return ValidateBinarySearchTree(root->leftchild, root->data, min) && 
        ValidateBinarySearchTree(root->rightchild, max, root->data);
}

bool ValidBSTreeMain(TreeNode* root, long max, long min){
    if(root) return ValidateBinarySearchTree(root, max, min);
    else return false;
}

/*
bool PathSum0620(TreeNode* root, vector<vector<int>> &res, vector<int> path, 
    int target, int sum){
    if(!root) return false;
    if(sum > target) return false;
    if(sum == target){
        res.push_back(path);
        return true;
    }
    if(root->leftchild || root->rightchild){
        path.push_back(root->data);
        if(PathSum0620(root->leftchild, res, path, target, sum+root->data)) return true;
        if(PathSum0620(root->rightchild, res, path, target, sum+root->data)) return true;
        //path.pop_back();
    }
    return false;
}
*/
int main() {
    TreeNode *nodeA = new TreeNode(10);
    TreeNode *nodeB = new TreeNode(7);
    TreeNode *nodeC = new TreeNode(9);
    TreeNode *nodeD = new TreeNode(16);
    TreeNode *nodeE = new TreeNode(26);

    BinaryTree T(nodeA);
    nodeA->leftchild = nodeB;
    nodeB->rightchild = nodeC;
    nodeA->rightchild = nodeD;
    nodeD->rightchild = nodeE;
    vector<vector<int>> res;
    vector<int> temp;
    res.clear();
    temp.clear();

    //20190620
    //cout << PathSum0620(nodeA, res, temp, 26, 0) << endl;

    //PathSumII(nodeA, 0, 26, res, temp);
    //print2(res);

    
    //BinarySearchTreeInsert(nodeA, 1);
    //LevelOrder(nodeA);
    
    //cout << ValidBSTreeMain(nodeA, LONG_MAX, LONG_MIN) << endl;

    /*
    TreeNode *nodeA = new TreeNode(4);
    TreeNode *nodeB = new TreeNode(6);
    TreeNode *nodeC = new TreeNode(8);
    TreeNode *nodeD = new TreeNode(10);
    TreeNode *nodeE = new TreeNode(9);
    
    
    BinaryTree T(nodeC);
    nodeC->leftchild = nodeA;
    nodeA->parent = nodeC;
    nodeA->rightchild = nodeB;
    nodeB->parent = nodeA;
    nodeC->rightchild = nodeD;
    nodeD->parent = nodeC;
    nodeD->leftchild = nodeE;
    nodeE->parent = nodeD;
    TreeNode *nodeX = T.DeleteBST(10);
    int depth = 0;
    T.Inorder(nodeX, depth);
    cout << "depth: " << T.maxDepth << " nodecount: " << T.numCount << endl;
    */
    /*
    BinaryTree T(nodeA);
    //T.Inorder(nodeC);
    T.InsertBST(8);
    T.InsertBST(1000);
    T.InsertBST(2);
    T.InsertBST(513);
    T.Inorder(nodeA);
    T.DeleteBST(8);
    T.Inorder(nodeA);
    */
    /*
    TreeNode *nodeA = new TreeNode(4); 
    BinaryTree T(nodeA);
    std::vector<int> v;
    v.push_back(2);
    v.push_back(6);
    v.push_back(1);
    v.push_back(3);
    v.push_back(5);
    T.AddNode(T.root,v);
    //T.Preorder(T.root);
    //std::cout << std::endl;
    T.Inorder(T.root);
    std::cout << std::endl;
    //T.Postorder(T.root);
    //std::cout << std::endl;
    //T.Levelorder();
    //std::cout << std::endl; 
    */   
    return 0;
}


/*
#include <iostream>
#include <sstream>
#include <queue>


class BinaryTree;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    char data;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),data('x'){};
    TreeNode(char s):leftchild(0),rightchild(0),parent(0),data(s){};

    friend class BinaryTree;
};

class BinaryTree{
private:
    TreeNode *root;
public:
    BinaryTree():root(0){};
    BinaryTree(const char* str);

    void LevelorderConstruct(std::stringstream &ss);
    void InsertLevelorder(char data);

    TreeNode* leftmost(TreeNode *current);
    TreeNode* InorderSuccessor(TreeNode *current);
    void Inorder_by_parent();
    void Levelorder(TreeNode *current);
};

BinaryTree::BinaryTree(const char* str){
    std::stringstream  ss;
    ss << str;                     // magic!
    
    root = new TreeNode;           // allocate memory for root
    ss >> root->data;              // assign character to root
    
    LevelorderConstruct(ss);
}


void BinaryTree::Levelorder(TreeNode *current){
//Level-order是照著「level由小到大」的順序，由上而下，並在同一個level「由左至右」依序Visiting每個node。
//以下提供以迴圈配合Queue(佇列)實現level-order traversal之程式碼，其邏輯也非常直觀：
//當CurrentNode站在A時，先對A作Visiting，接著檢查是否有left child與right child，若不為NULL，
//則「依序」將child pointer 推(push)進queue中，又根據queue「先進先出」(first-in-first-out)的特性，
//先將B(left child)推入queue，再推入C(right child)，便能確保在下一層level時，是由左至右，先Visiting到B，
//才Visiting到C。
    std::queue<TreeNode*> q;
    q.push(this->root);                     // 把root作為level-order traversal之起點
                                            // 推進queue中
    while (!q.empty()){                     // 若queue不是空的, 表示還有node沒有visiting

        TreeNode *current = q.front();      // 取出先進入queue的node
        q.pop();                          
        std::cout << current->data << " ";   // 進行visiting

        if (current->leftchild != NULL){    // 若leftchild有資料, 將其推進queue
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL){   // 若rightchild有資料, 將其推進queue
            q.push(current->rightchild);
        }
    }
}

void BinaryTree::LevelorderConstruct(std::stringstream &ss){
    
    std::queue<TreeNode*> q;         // create a queue to handle level-roder rule
    TreeNode *current = root;        // point *current to root
    char data = 'x';                 // initializa data as 'x'
    
    while (ss >> data) {
        if (data >= 65 && data <= 90){                // 處理current的leftchild
            TreeNode *new_node = new TreeNode(data);  // call constructor TreeNode(char s)
            new_node->parent = current;
            current->leftchild = new_node;
            q.push(new_node);
        }
        if (!(ss >> data)){                           // 有可能char array含有奇數筆資料
            break;                                    // 所以在這裡結束迴圈
        }
        if (data >= 65 && data <= 90){                // 處理current的rightchild
            TreeNode *new_node = new TreeNode;        // call constructor TreeNode()
            new_node->parent = current;
            current->rightchild = new_node;
            new_node->data = data;                    // assign data to new_node
            q.push(new_node);
        }
        current = q.front();                          // 從queue中更新current
        q.pop();                                      // 更新queue
    }
}

void BinaryTree::InsertLevelorder(char data){    

    std::queue<TreeNode*> q;
    TreeNode *current = root;
    
    while (current) {
        if (current->leftchild != NULL){               // current的leftchild沒有空位
            q.push(current->leftchild);                // 將其推進queue中
        }
        else{                                          // current的leftchild有空位
            TreeNode *new_node = new TreeNode(data);   // 建立新的node, 將字母放在這裡
            new_node->parent = current;
            current->leftchild = new_node;
            break;                         
        }
        if (current->rightchild != NULL) {             // current的rightchild沒有空位
            q.push(current->rightchild);               // 將其推進queue中
        }
        else{                                          // current的rightchild有空位
            TreeNode *new_node = new TreeNode(data);   // 建立新的node, 將字母放在這裡
            new_node->parent = current;                
            current->rightchild = new_node;
            break;
        }
        current = q.front();
        q.pop();
    }
}
TreeNode* BinaryTree::leftmost(TreeNode *current){
    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}
TreeNode* BinaryTree::InorderSuccessor(TreeNode *current){
    if (current->rightchild != NULL){
        return leftmost(current->rightchild);
    }
    
    // 利用兩個pointer: successor與current做traversal 
    TreeNode *successor = current->parent;   
    while (successor != NULL && current == successor->rightchild) {
        current = successor;
        successor = successor->parent;
    }
    return successor;
}
void BinaryTree::Inorder_by_parent(){
    TreeNode *current = new TreeNode;
    current = leftmost(root);

    while(current){
        std::cout << current->data << " ";
        current = InorderSuccessor(current);
    }
}
int main() {
    const char *a = 'A B C D E F x x x G H x I';
    BinaryTree T(a);
    T.Inorder_by_parent();
    std::cout << std::endl;

    T.InsertLevelorder('K');
    T.InsertLevelorder('L');
    T.InsertLevelorder('M');
    T.InsertLevelorder('N');
    T.Inorder_by_parent();
    std::cout << std::endl;

    return 0;
}
*/