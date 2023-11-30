#include <iostream>
#include <locale.h>

using namespace std;

struct Node {
    int value;
    Node* next;
};

class LinkedList {
public:
    bool add_element(int value); //добавление элемента
    bool delete_element(int value); //удаление элемента по значению
    bool find_element(int value); //поиск элемента по значению
    bool insert(int value, int position); //добавление элемента по значению и позиции
    void print_list();

    LinkedList(int value);
    LinkedList();
    ~LinkedList();
private:
    Node* first;
    Node* last;
};

LinkedList::LinkedList() {
    first = nullptr;
    last = nullptr;
}

LinkedList::LinkedList(int value) {
    Node* nd = new Node{ value };
    first = nd;
    last = nd;
    last->next = nullptr;
}

bool LinkedList::add_element(int value) {
    Node* nd = new Node{ value, nullptr };
    if (last == nullptr) {
        first = nd;
        last = nd;
        return true;
    }
    last->next = nd;
    last = nd;
    return true;
}

bool LinkedList::find_element(int value) {
    if (last != nullptr) {
        Node* current = first;

        while (current != nullptr) {
            if (current->value == value) return true;
            current = current->next;
        }
    }
    return false;
}

bool LinkedList::insert(int value, int position) {
    if (last != nullptr) {
        Node* current = first;
        size_t i = 0;
        while (current != nullptr) {
            if (i == position - 1) { //current - текущий элемент, стоит перед добавляемым т.е. указывает на него
                Node* nd = new Node{ value, current->next };//current -> next - следующий элемент после текущего т.е. на это место добавляем элемент 
                current->next = nd; //добавили элемент после current
                return true;
            }
            current = current->next;
            ++i;
        }
    }
    return false;
}

bool LinkedList::delete_element(int value) {
    if (last != nullptr) {
        Node* current = first;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->value == value) {
                if (current == first) {
                    first = first->next;
                    delete current;
                    current = first;
                    continue;
                }
                else if (current == last) {
                    last = previous;
                    last->next = nullptr;
                    delete current;
                    break;
                }
                previous->next = current->next;
                delete current;
                current = previous->next;
                continue;
                //break;
            }
            previous = current;
            current = current->next;
            //previous = current;
            //current->next;
        }
        return true;
    }
    return false;
}

LinkedList::~LinkedList() {
    if (last != nullptr) {
        Node* current = first;

        while (current != nullptr) {
            Node* nd = new Node{ 0, current->next };
            delete current;

            current = nd;
        }
    }
}

void LinkedList::print_list() {
    Node* current = first;
    while (current != nullptr) {
        cout << current->value << ' ';
        current = current->next;
    }
    cout << "\n\n";
    return;
}

int main() {
    int a, b, c, d, n;
    setlocale(LC_ALL, "Russian");

    LinkedList LIST;
    cout << "Введите длину списка: ";
    cin >> n;
    cout << endl;
    for (int i = 0; i < n; ++i) {
        LIST.add_element(i);
    }
    cout << "Начальный список: ";
    LIST.print_list();
    cout << endl;

    cout << "Введите элемент, который хотите найти: ";
    cin >> c;
    cout << endl;
    if (LIST.find_element(c) == 1) {
        cout << "Элемент " << c << " найден" << endl;
    }
    else {
        cout << "Элемент " << c << " не найден" << endl;
    }

    cout << "Введите в строчку номер, на который хотите поставить элемент, и сам элемент: ";
    cin >> a >> b;
    cout << endl;
    LIST.insert(b, a);
    LIST.print_list();
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Введите элемент, который хотите удалить: ";
        cin >> d;
        cout << endl;
        LIST.delete_element(d);
        LIST.print_list();
        cout << endl;
    }
    return 0;
}
