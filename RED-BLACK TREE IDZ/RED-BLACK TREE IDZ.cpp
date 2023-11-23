#include "Spisok.hpp"

#include <string>
struct TimeKey {
   short int h;
   short int m;
   short int s;
};
char compare(TimeKey k1, TimeKey k2) {
    if (k1.h > k2.h) return '>';
    else if (k1.h < k2.h) return '<';
    else {
        if (k1.m > k2.m) return '>';
        else if (k1.m < k2.m) return '<';
        else {
            if (k1.s > k2.s) return '>';
            else if (k1.s < k2.s) return '<';
            else return '=';
        }
    }
}
enum Color{BLACK,RED};

struct Node {
    TimeKey key;
    NodeList data; // номер строки
    Color NodeColor;
    Node* parentNode = nullptr;
    Node* leftNode   = nullptr;
    Node* rightNode  = nullptr;
   
};

class redBlackTree {
private:
    Node* root = new Node;
    Node* TNULL = new Node;

    void leftRotate(Node* x) {
        Node* y = new Node;
        y = x->rightNode;
        x->rightNode = y->leftNode;
        if (y->leftNode != TNULL) y->leftNode->parentNode = x;
        y->parentNode = x->parentNode;
        if (x->parentNode == TNULL) root = y;
        else if (x == x->parentNode->leftNode) x->parentNode->leftNode = y;
        else x->parentNode->rightNode = y;
        y->leftNode = x;
        x->parentNode = y;
    }

    void rightRotate(Node* x) {
        Node* y = new Node;
        y = x->leftNode;
        x->leftNode = y->rightNode;
        if (y->rightNode != TNULL) y->rightNode->parentNode = x;
        y->parentNode = x->parentNode;
        if (x->parentNode == TNULL) root = y;
        else if (x == x->parentNode->rightNode) x->parentNode->rightNode = y;
        else x->parentNode->leftNode = y;
        y->rightNode = x;
        x->parentNode = y;

    }

    void insertFix(Node* z) {
        Node* y = new Node;
        while (z->parentNode->NodeColor == RED) {
            if (z->parentNode == z->parentNode->parentNode->leftNode) {
                y = z->parentNode->parentNode->rightNode;
                if (y->NodeColor == RED) {
                    z->parentNode->NodeColor = BLACK;
                    y->NodeColor = BLACK;
                    z->parentNode->parentNode->NodeColor = RED;
                    z = z->parentNode->parentNode;
                }
                else {
                    if (z == z->parentNode->rightNode) {
                        z = z->parentNode;
                        leftRotate(z);
                    }
                    z->parentNode->NodeColor = BLACK;
                    z->parentNode->parentNode->NodeColor = RED;
                    rightRotate(z->parentNode->parentNode);
                }
            }


            else {
                y = z->parentNode->parentNode->leftNode;
                if (y->NodeColor == RED) {
                    z->parentNode->NodeColor = BLACK;
                    y->NodeColor = BLACK;
                    z->parentNode->parentNode->NodeColor = RED;
                    z = z->parentNode->parentNode;
                }
                else {
                    if (z == z->parentNode->leftNode) {
                        z = z->parentNode;
                        rightRotate(z);
                    }
                    z->parentNode->NodeColor = BLACK;
                    z->parentNode->parentNode->NodeColor = RED;
                    leftRotate(z->parentNode->parentNode);
                }

            }
            root->NodeColor = BLACK;
     }
    }
    void transplant(Node* x, Node* y) {
        if (x->parentNode == TNULL) root = y;
        else if (x == x->parentNode->leftNode) x->parentNode->leftNode = y;
        else x->parentNode->rightNode = y;
        y->parentNode = x->parentNode;
   }
    Node* TMinimum(Node* x) {
        while (x->leftNode != TNULL) {
            x = x->leftNode;
        }
        return x;
    }
    void delfix(Node* x) {
        Node* w = new Node;
        while (x != root && x->NodeColor == BLACK) {
            if (x == x->parentNode->leftNode) {
                w = x->parentNode->rightNode;
                if (w->NodeColor == RED) {
                    w->NodeColor = BLACK;
                    x->parentNode->NodeColor = RED;
                    leftRotate(x->parentNode);
                    w = x->parentNode->rightNode;
                }
                if (w->leftNode->NodeColor == BLACK && w->rightNode->NodeColor == BLACK) {
                    w->NodeColor = RED;
                    x = x->parentNode;
                }
                else {
                    if (w->rightNode->NodeColor == BLACK) {
                        w->leftNode->NodeColor = BLACK;
                        w->NodeColor = RED;
                        rightRotate(w);
                        w = x->parentNode->rightNode;
                    }
                    w->NodeColor = x->parentNode->NodeColor;
                    x->parentNode->NodeColor = BLACK;
                    w->rightNode->NodeColor = BLACK;
                    leftRotate(x->parentNode);
                    x = root;
                }
            }
            else {
                w = x->parentNode->leftNode;
                if (w->NodeColor == RED) {
                    w->NodeColor = BLACK;
                    x->parentNode->NodeColor = RED;
                    rightRotate(x->parentNode);
                    w = x->parentNode->leftNode;
                }
                if (w->rightNode->NodeColor == BLACK && w->leftNode->NodeColor == BLACK) {
                    w->NodeColor = RED;
                    x = x->parentNode;
                }
                else {
                    if (w->leftNode->NodeColor == BLACK) {
                        w->rightNode->NodeColor = BLACK;
                        w->NodeColor = RED;
                        leftRotate(w);
                        w = x->parentNode->leftNode;
                    }
                    w->NodeColor = x->parentNode->NodeColor;
                    x->parentNode->NodeColor = BLACK;
                    w->leftNode->NodeColor = BLACK;
                    rightRotate(x->parentNode);
                    x = root;
                }

            }
        }
        x->NodeColor = BLACK;
    }

    void recDel(Node* x) {
        if (x != TNULL) {
            if (x->rightNode)   recDel(x->rightNode);
            if (x->leftNode)    recDel(x->leftNode);
            if (x == x->parentNode->leftNode) x->parentNode->leftNode = TNULL;
            if (x == x->parentNode->rightNode) x->parentNode->rightNode = TNULL;
            ClearNodeList(x->data);
            delete x;
        }
    }
   
public:
    redBlackTree() {
        TNULL = new Node;
        TNULL->NodeColor = BLACK;
        TNULL->leftNode = nullptr;
        TNULL->rightNode = nullptr;
        root = TNULL;
    }
    
    void insert(TimeKey k, int data) {
        bool flag = 1;
        Node* x = root;
        Node* y = TNULL;
        Node* tmp = new Node;
        AddInEnd(tmp->data , data);
        tmp->key = k;
        tmp->NodeColor = RED;
        tmp->leftNode = TNULL;
        tmp->rightNode = TNULL;
       
        while (x != TNULL) {
            y = x;
            if (compare(tmp->key, x->key) == '=') { AddInEnd(x->data, data); flag = 0; x = TNULL; }
            else {
                if (compare(tmp->key, x->key) == '<') x = x->leftNode;
                else x = x->rightNode;
            }
        }
        if (flag == 1) {
            tmp->parentNode = y;
            if (y == TNULL) {
                tmp->NodeColor = BLACK;
                root = tmp;
            }
            else if (compare(tmp->key, y->key) == '<')  y->leftNode = tmp;
            else y->rightNode = tmp;

            insertFix(tmp);
            root->NodeColor = BLACK;
        }
    }

    void del(Node* z) {
        Node* x = new Node;
        Node* y = new Node;
       
            y = z;
            Color y_original = y->NodeColor;
            if (z->leftNode == TNULL) {
                x = z->rightNode;
                transplant(z, z->rightNode);
            }
            else if (z->rightNode == TNULL) {
                x = z->leftNode;
                transplant(z, z->leftNode);
            }
            else {
                y = TMinimum(z->rightNode);
                y_original = y->NodeColor;
                x = y->rightNode;
                if (y->parentNode == z) {
                    x->parentNode = y;
                }
                else {
                    transplant(y, y->rightNode);
                    y->rightNode = z->rightNode;
                    y->rightNode->parentNode = y;
                }
                transplant(z, y);
                y->leftNode = z->leftNode;
                y->leftNode->parentNode = y;
                y->NodeColor = z->NodeColor;

            };
            ClearNodeList(z->data);
            delete z;
            if (y_original == BLACK) delfix(x);
        }
    



    void inOrderTravers(Node* root,std::ofstream* f) {
        if (root!=TNULL) {
           
            inOrderTravers(root->rightNode, f);
            fPrint(root->data, f);
            inOrderTravers(root->leftNode, f);
        }
    }
    void allDel() {
        if (root->rightNode) recDel(root->rightNode);
        if(root->leftNode) recDel(root->leftNode);
        root = TNULL;
    }
  

    void printBT(const std::string& prefix, Node* node, bool isLeft)
    {
        if (node != TNULL)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "|--" : "'--");

    
            print(node->data); std::cout << '(' << node->NodeColor << ')' << std::endl;
            
            printBT(prefix + (isLeft ? "|   " : "    "), node->rightNode, true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->leftNode, false);
        }
    }
    Node* GetRoot() {
        return root;
    }
   
    Node* search(TimeKey k) {
        Node* current = root;
        while (current != TNULL && compare(current->key,k)!='=') {
 
            if (compare(current->key, k) == '<') current = current->rightNode;
            else current = current->leftNode;
        }
        
        if (current != TNULL) { return current; }
        else return 0;
    }
};



int main()
{
    std::string error1 = "Файл не найден/Не удалось найти файл";
    std::string error2 = "Неверный формат времени";
    std::string error3 = "Неверный диапазон часов/минут/секунд ";


    setlocale(LC_ALL, "RUS");
    int LineCount = 0;
    std::string s;
    



    
    std::ifstream file;
    redBlackTree tree;
    TimeKey k;

    NodeList listStrok;
 

    file.open("TEST2.txt");
    if (!file) {
        std::cout << error1 <<"\n";
    }
    else std::cout << "Открыт!"<<"\n";
    while (!file.eof()) {

        LineCount++;
        std::getline(file, s);
        if (s.size() != 8) std::cout << error2 << std::endl;
        else {
            if (isdigit(s[0]) && isdigit(s[1]) && isdigit(s[3]) && isdigit(s[4]) && isdigit(s[6]) && isdigit(s[7])) {
                k.h = (s[0] - '0') * 10 + (s[1] - '0');
                k.m = (s[3] - '0') * 10 + (s[4] - '0');
                k.s = (s[6] - '0') * 10 + (s[7] - '0');
                if (k.h < 24 && k.m < 60 && k.s < 60) {
                    tree.insert(k, LineCount);
                    AddInEnd(listStrok, LineCount);
                }

            }
            else std::cout << error2 << std::endl;
        }

    }
    std::cout << "Красно-черное дерево"<<std::endl;
    tree.printBT("", tree.GetRoot(), false);

    std::cout << std::endl << "1 - поиск элемента" << std::endl << "2 - Удаление элемента" << std::endl << "3 - Освобождение памяти" <<
 std::endl << ("Введите номер операции:"); 
    int a;
    std::cin >> a;
    TimeKey kCin;
    switch (a) {
    case 1:
        std::cout << "Введите ключ(Час,Минута,секунда):";
        std::cin >> kCin.h >> kCin.m >> kCin.s;
   
        if (!(kCin.h < 24 && kCin.m < 60 && kCin.s < 60)) std::cout << error3 << std::endl;
        else {
            if (tree.search(kCin) != 0) print( tree.search(kCin)->data);
            else std::cout << "Элемент не найден";
        }
        break;
    case 2:

        std::cout << "Введите ключ(Час,Минута,секунда):";
        std::cin >> kCin.h >> kCin.m >> kCin.s;

        if (!(kCin.h < 24 && kCin.m < 60 && kCin.s < 60)) std::cout << error3 << std::endl;
        else {
            if (tree.search(kCin) != 0) {
                if (size(tree.search(kCin)->data) > 1) {
                    std::cout << " Введите номер строки("; print(tree.search(kCin)->data); std::cout << ')' << std::endl;
                    int Nomer;
                    std::cin >> Nomer;
                    deleteNomer(tree.search(kCin)->data, Nomer);
                }
                if(size(tree.search(kCin)->data) <= 1) tree.del(tree.search(kCin));
            }
            else std::cout << "Элемент не найден";
        }
        break;

    case 3:
        tree.allDel();
        break;
    }


    std::cout<<"\n";
 
    tree.allDel();
    tree.insert(k, 134);

   tree.printBT("", tree.GetRoot(), false);
   

   std::ofstream* fout = new std::ofstream("out.txt");
   tree.inOrderTravers(tree.GetRoot(), fout);

   fout->close();
   file.close();
   
}

