#include <iostream>
#include <map>
#include <list>
#include <vector>

class Node // клас родитель
{
public:
    int a;
    char c;
    Node *left, *right; // указательна на левого и правого сына
    Node()              // шаблон по умолчани
    {
    }
    Node(Node *L, Node *R) // 2 конструктор по умолчани
    {
        left = L;
        right = R;
        a = L->a + R->a; // 2 сына сумма
    }
};

struct MyCompare
{
    bool operator()(Node *l, Node *r) const
    {
        return l->a < r->a;
    }
};

void print(Node *root, unsigned k = 0) // k отвечает за отступ чем глубже тем больше отступ
{
    if (root != NULL)
    {
        print(root->left, k + 3);
        for (unsigned i = 0; i < k; i++)
        {
            std::cout << "  ";
        }
        if (root->c)
        {
            std::cout << root->a << " (" << root->c << ")" << std::endl; // если буква есть то выводим
        }
        else
        {
            std::cout << root->a << std::endl; // если нет буквы то число
        }
        print(root->right, k + 3);
    }
}

std::vector<bool> code;
std::map<char, std::vector<bool>> table;
void BuildTable(Node *root) // пробежимся по дереву и сделаем таблицу соответсвий буквы и символа
{
    if (root->left != NULL)
    {
        code.push_back(0);
        BuildTable(root->left);
    }
    if (root->right != NULL)
    {
        code.push_back(1);
        BuildTable(root->right);
    }
    if (root->left == NULL && root->right == NULL)
    {
        table[root->c] = code;
    }
    code.pop_back();
}

int main()
{
    setlocale(LC_COLLATE, "");

    std::string orig_data = "it is my 1 zip programm!!!"; // исходная строка

    std::map<char, int> m;
    for (int i = 0; i < orig_data.length(); i++) // считаем кол-во вхождений
    {
        char c = orig_data[i];
        m[c]++;
    }
    // посмотрим что получилось, временно
    std::cout << "================================" << std::endl;
    std::cout << "Разложем на элементы и посчитаем" << std::endl;
    std::cout << "================================" << std::endl;
    std::map<char, int>::iterator ii;
    for (ii=m.begin(); ii != m.end(); ii++)
    {
        std::cout << ii->first << ":" << ii->second << std::endl;
    }
    std::cout << "================================" << std::endl;
    std::list<Node *> t;
    std::map<char, int>::iterator i;
    for (i = m.begin(); i != m.end(); i++) // добавляем первоночальные узлы
    {
        Node *p = new Node;
        p->c = i->first;
        p->a = i->second;
        t.push_back(p);
    }

    while (t.size() != 1) // строим дерево
    {
        t.sort(MyCompare()); // сортировка

        Node *SonL = t.front(); // сын
        t.pop_front();
        Node *SonR = t.front(); // сын
        t.pop_front();

        Node *parent = new Node(SonL, SonR); // отец
        t.push_back(parent);
    }

    Node *root = t.front(); // вершина дерева

    std::cout << "\tПосмотрим дерево:" << std::endl;
    std::cout << "================================" << std::endl;
    print(root); // выведим дерево временно
    
    std::cout << "================================" << std::endl;
    std::cout << "Превратим в 1 и 0:" << std::endl;
    std::cout << "================================" << std::endl;
    BuildTable(root);
    
    for (int i = 0; i < orig_data.length(); i++)
    {
        char c = orig_data[i];
        std::vector<bool> x = table[c];

        for (int n = 0; n < x.size(); n++)
        {
            std::cout << x[n];
        }
    }
    std::cout << std::endl;

    return 0;
}