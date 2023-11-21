#include <set>
#include <iostream>


struct NodeSp {
    int ch;
    NodeSp* next = NULL;
    NodeSp* prev = NULL;
};

struct NodeList {

    NodeSp* head = NULL;
};

//Добавление в конец для intersection
void AddInEnd(NodeList& list, int chs) {

    NodeSp* tmp = new NodeSp;
    tmp->ch = chs;

    if (list.head == NULL) {
        list.head = tmp;
        list.head->next = list.head;
        list.head->prev = list.head;
    }

    else {
        NodeSp* current = list.head;
        while (current->next != list.head) {
            current = current->next;

        }
        current->next = tmp;
        tmp->next = list.head;
        tmp->prev = current;
        list.head->prev = tmp;



    }

}



// Удалить перед каждым заданным K-ым  
void del(NodeList& list, int K) {
    NodeSp* current = list.head;
    if (list.head != NULL)
    {
        while (current->next != list.head)
        {
            if (current->next->ch == K) {
                if (current == list.head) {
                    NodeSp* tmp = new NodeSp;
                    tmp = list.head;
                    list.head->prev->next = list.head->next;
                    list.head->next->prev = list.head->prev;
                    list.head = list.head->next;
                    current = current->next;
                    delete tmp;
                }
                else {
                    NodeSp* tmp = new NodeSp;
                    tmp = current;
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    current = current->next;
                    delete tmp;
                }

            }
            else current = current->next;
        }
    }
}

bool Poisk(NodeList& list, int ch) {
    bool s = 0;
    NodeSp* current = list.head;
    if (list.head != NULL) {
        while (current->next != list.head) {
            if (current->ch == ch) s = 1;
            current = current->next;
        }
        if (current->ch == ch) s = 1;
    }
    return s;

}

void ClearNodeList(NodeList& list) {
    if (list.head != NULL) {
        NodeSp* current = list.head->next;
        while (current->next != list.head) {
            NodeSp* tmp = current;
            current = current->next;
            delete tmp;
        }
        delete list.head;
        list.head = NULL;
    }
}

void print(NodeList& list) {
    NodeSp* current = list.head;
    if (list.head == NULL) std::cout << "Список пуст";
    else {
        std::cout << list.head->ch << " ";
        while (current->next != list.head) {
            current = current->next;
            std::cout << current->ch << " ";
        }
        std::cout << std::endl;
    }
}



/*
int main()
{
    setlocale(LC_ALL, "Russian");
    NodeList list1;
    NodeList list2;
    NodeList list3;
    int n1, n2, v1;

    std::cout << "Введите количество элементов: ";
    std::cin >> n1;
    if (n1 < 1) {
        std::cout << "Невверно введено кол-во элементов" << std::endl;
    }
    else {
        for (int i = 0; i < n1; i++)
        {
            std::cin >> v1;
            AddInEnd(list1, v1);
        }
    }
    int p;
    std::cout << "Проверка существования числа P в списке. P = " << std::endl;
    std::cin >> p;
    std::cout << Poisk(list1, p) << std::endl;

    std::cout << "Список1: "; print(list1); std::cout << std::endl;

    std::cout << "Введите количество элементов: ";
    std::cin >> n2;
    if (n2 < 1) {
        std::cout << "Невверно введено кол-во элементов" << std::endl;
    }
    else {
        for (int i = 0; i < n2; i++)
        {
            std::cin >> v1;
            AddInEnd(list2, v1);
        }
    }

    std::cout << "Список2: "; print(list2); std::cout << std::endl;
    list3 = intersection(list1, list2);
    std::cout << "Элементы пересечения списков: "; print(list3);
    std::cout << "Удаление перед каждым вхождением заданного K. K =";
    int K;
    std::cin >> K;
    del(list3, K);
    std::cout << "Полученный список: "; print(list3);
}
*/