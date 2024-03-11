#include <iostream>
#include <string>
#include <windows.h>

#define CURRENT_YEAR (__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + (__DATE__[10] - '0')

using namespace std;

class Item
{
private:
    string name;
    int amount;
    int purchase_year;
    int lifetime;
public:
    Item()
    {
        name = "не определено";
        amount = 0;
        purchase_year = CURRENT_YEAR;
        lifetime = 0;
    }

    Item(const string _name, const unsigned int _amount, const unsigned int _purchase_year, const unsigned int _lifetime)
    {
        if (!(_name.empty())) name = _name;
        if (_amount > 0) amount = _amount;
        if (_purchase_year <= CURRENT_YEAR) purchase_year = _purchase_year;
        if (_lifetime > 0) lifetime = _lifetime;
    }

    Item(const Item &src_object)
    {
        if (this != &src_object)
        {
            name = src_object.name;
            amount = src_object.amount;
            purchase_year = src_object.purchase_year;
            lifetime = src_object.lifetime;
        }
    }

    ~Item() { }

    string get_name() { return name; }

    int get_amount() { return amount; }

    int get_purchase_year() { return purchase_year; }

    int get_lifetime() { return lifetime; }

    bool set_name(const string settable_name)
    {
        bool successfully = false;

        if (!(settable_name.empty()))
        {
            name = settable_name;
            successfully = true;
        }

        return successfully;
    }

    bool set_amount(const unsigned int settable_amount)
    {
        bool successfully = false;

        if (settable_amount > 0)
        {
            amount = settable_amount;
            successfully = true;
        }

        return successfully;
    }

    bool set_purchase_year(const unsigned int settable_purchase_year)
    {
        bool successfully = false;

        if (settable_purchase_year <= CURRENT_YEAR)
        {
            purchase_year = settable_purchase_year;
            successfully = true;
        }

        return successfully;
    }

    bool set_lifetime(const unsigned int settable_lifetime)
    {
        bool successfully = false;

        if (settable_lifetime > 0)
        {
            lifetime = settable_lifetime;
            successfully = true;
        }

        return successfully;
    }

    void output()
    {
        cout << name << "            " << amount << "            " << purchase_year << "            " << lifetime << endl;
    }
};

class Element
{
private:
    Item* data;
public:
    Element* previous;

    Element()
    {
        data = nullptr;
        previous = nullptr;
    }

    Element(const Item &src_object)
    {
        previous = nullptr;
        data = new Item(src_object);
    }

    Element(const Element &src_object)
    {
        if (this != &src_object)
        {
            data = new Item(*src_object.data);
            previous = src_object.previous;
        }
    }

    ~Element()
    {
        if (data != nullptr) delete data;
    }

    Element& operator = (const Element &src_object)
    {
        if (this != &src_object)
        {
            if (this->data != nullptr) { delete data; }
            data = new Item(*src_object.data);
            previous = src_object.previous;
        }
        return *this;
    }

    string get_name() { return data->get_name(); }

    int get_amount() { return data->get_amount(); }

    int get_purchase_year() { return data->get_purchase_year(); }

    int get_lifetime() { return data->get_lifetime(); }

    bool set_name(const string settable_name) { return data->set_name(settable_name); }

    bool set_amount(const unsigned int settable_amount) { return data->set_amount(settable_amount); }

    bool set_purchase_yaer(const unsigned int settable_purchase_year) { return data->set_purchase_year(settable_purchase_year); }

    bool set_lifetime(const unsigned int settable_lifetime) { return data->set_lifetime(settable_lifetime); }

    void output() { data->output(); }
};

class LIFO
{
private:
    Element* head;
public:
    LIFO() { head = nullptr; }

    ~LIFO()
    {
        while (head != nullptr) { delete_Element(); };
    }

    Element* delete_Element()
    {
        Element* temp;
        temp = nullptr;

        if (head != nullptr)
        {
            temp = new Element(*head);
            head = head->previous;
        }

        return temp;
    }

    void add_Element(Element &src_object)
    {
        Element* temp = new Element(src_object);

        if (head == nullptr)
        {
            head = temp;
            head->previous = nullptr;
        }
        else
        {
            temp->previous = head;
            head = temp;
        }
    }

    Element* search_by_name(const string required_name)
    {
        Element* temp;
        temp = nullptr;

        LIFO object;

        while (head != nullptr)
        {
            if (head->get_name() == required_name)
            {
                temp = new Element(*head);
                break;
            }
            object.add_Element(*delete_Element());
        }

        while (object.head != nullptr) { add_Element(*object.delete_Element()); }

        return temp;
    }

    void sort_by_purchase_year()
    {
        LIFO first_object;
        LIFO second_object;

        while (head != nullptr)
        {
            Element* temp;
            temp = nullptr;

            while (head != nullptr)
            {
                if (temp == nullptr)
                {
                    temp = delete_Element();
                }
                else
                {
                    if (temp->get_purchase_year() > head->get_purchase_year())
                    {
                        first_object.add_Element(*delete_Element());
                    }
                    else
                    {
                        first_object.add_Element(*temp);

                        delete temp;
                        temp = nullptr;

                        temp = delete_Element();
                    }
                }
            }

            second_object.add_Element(*temp);

            while (first_object.head != nullptr)
            {
                add_Element(*first_object.delete_Element());
            }
        }

        while (second_object.head != nullptr)
        {
            add_Element(*second_object.delete_Element());
        }
    }

    void output()
    {
        if (head != nullptr)
        {
            LIFO temp;

            while (head != nullptr) { temp.add_Element(*delete_Element()); }

            cout << "Наименование   " << "Количество   " << "Год приобретения   " << "Срок службы   " << endl;

            while (temp.head != nullptr)
            {
                add_Element(*temp.delete_Element());
                head->output();
            }
        }
        else
        {
            cout << "[Ошибка]: стек пуст." << endl;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Item A("Компьютер", 10, 2020, 20);
    Element _A(A);
    
    Item B("Принтер", 2, 2015, 30);
    Element _B(B);

    Item C("Сервер", 1, 1999, 25);
    Element _C(C);

    Item D("Ноутбук", 4, 2014, 10);
    Element _D(D);

    Item E("Планшет", 2, 2014, 10);
    Element _E(E);

    Item F("Коммутатор", 2, 1999, 25);
    Element _F(F);

    Item G("Роутер", 1, 2015, 10);
    Element _G(G);

    LIFO Stack;

    Stack.add_Element(_A);
    Stack.add_Element(_B);
    Stack.add_Element(_C);
    Stack.add_Element(_D);
    Stack.add_Element(_E);
    Stack.add_Element(_F);
    Stack.add_Element(_G);

    Stack.output();

    int cmd = 0;

    do
    {
        cout << "Меню взаимодействия:" << endl;
        cout << "1. Вывести на экран все записи." << endl;
        cout << "2. Найти запись по наименованию." << endl;
        cout << "3. Отсортировать записи по году приобретения." << endl;
        cout << "4. Вывести записи предметов, подлежащих списанию в заданный год." << endl;
        cout << "5. Вывести 5 записей самых долгосрочных предметов." << endl;
        cout << "6. Добавить запись." << endl;
        cout << "7. Удалить запись." << endl;
        cout << "0. Завершить работу программы." << endl;
        cout << "Номер команды: ";

        cin >> cmd;

        cout << endl;

        while (cmd < 0 || cmd > 7)
        {
            cout << "[Ошибка]: введено недопустимое значение команды, повторите попытку: ";

            cin >> cmd;

            cout << endl;
        }

        switch (cmd)
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                Stack.output();
                break;
            }
            case 2:
            {
                cout << "Введите искомое наименование: ";

                string required_name = "";

                cin >> required_name;

                while (required_name.empty())
                {
                    cout << "[Ошибка]: некорректно задано искомое наименование, повторите попытку: ";

                    cin >> required_name;
                }

                Element* temp;
                temp = Stack.search_by_name(required_name);

                if (temp != nullptr)
                {
                    cout << "Запись с наименованием \"" << required_name << "\":" << endl;

                    temp->output();
                }
                else
                {
                    cout << "[Ошибка]: запись с наименованием \"" << required_name << "\" не найдена." << endl;
                }

                break;
            }
            case 3:
            {
                Stack.sort_by_purchase_year();

                break;
            }
            case 4:
            {
                // TODO: Вывести записи предметов, подлежащих списанию в заданный год

                break;
            }
            case 5:
            {
                // TODO: Вывести 5 записей самых долгосрочных предметов

                break;
            }
            case 6:
            {
                cout << "Добавление записи:" << endl;

                string name = "";
                cout << "Введите наименование: ";
                cin >> name;

                while (name.empty())
                {
                    cout << "[Ошибка]: некорректно задано наименование, повторите попытку: ";

                    cin >> name;
                }

                int amount = 0;
                cout << "Введите количество: ";
                cin >> amount;

                while (amount <= 0)
                {
                    cout << "[Ошибка]: некорректно задано количество, повторите попытку: ";

                    cin >> amount;
                }

                int purchase_year = CURRENT_YEAR;
                cout << "Введите год приобретения: ";
                cin >> purchase_year;

                while (purchase_year > CURRENT_YEAR)
                {
                    cout << "[Ошибка]: некорректно задан год приобретения, повторите попытку: ";

                    cin >> purchase_year;
                }

                int lifetime = 0;
                cout << "Введите срок службы (в годах): ";
                cin >> lifetime;

                while (lifetime <= 0)
                {
                    cout << "[Ошибка]: некорректно задан срок службы, повторите попытку: ";

                    cin >> lifetime;
                }

                Item Temp(name, amount, purchase_year, lifetime);

                Element _Temp(Temp);

                Stack.add_Element(_Temp);

                break;
            }
            case 7:
            {
                cout << "Удалиние записи:" << endl;

                string name = "";
                cout << "Введите наименование: ";
                cin >> name;

                while (name.empty())
                {
                    cout << "[Ошибка]: некорректно задано наименование, повторите попытку: ";

                    cin >> name;
                }

                Stack.search_by_name(name);

                // TODO: Удаление элемента стека по наименованию

                break;
            }

        }
    } while (cmd != 0);

    return 0;
}
