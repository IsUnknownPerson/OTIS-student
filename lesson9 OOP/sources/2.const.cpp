#include <cstddef>
#include <string>
#include <iostream>

class Foo {
public:
    void changePointers() {
        // Меняем значения указателей.
        // Ок т.к. и указатели data и immutableData - неконстантные поля
        ptr = nullptr;
        ptrToConstData = nullptr;
        // Ошибки компиляции, т.к. указатели объявлены как константные
        // constPtrToConstData = nullptr;
        // constPtrToData = nullptr;
    }

    void changePointers() const {
        // Не можем в const методе менять не-mutable поля
        // ptr = nullptr;
        // ptrToConstData = nullptr;
        // Ошибки компиляции, т.к. указатели объявлены как константные
        // constPtrToConstData = nullptr; Ошибка компиляции, т.к. указатель константный
        // constPtrToData = nullptr;
    }

    void changeValues() {
        // Меняем значения в памяти по указателям
        // Ок т.к. данные по ptr, constPtrToData неконстантны
        *ptr = '!';
        *constPtrToData = '!';
        // Ошибки, т.к данные по указателям объявлены как константные
        // *ptrToConstData = '!'; ошибка
        //* constPtrToConstData = '!';
    }

    void changeValues() const{
        // Меняем значения в памяти по указателям
        // Ок т.к. данные по ptr, constPtrToData неконстантны. Константность метода
        // на этот факт никак не влияет...
        *ptr = '!';
        *constPtrToData = '!';
        // Ошибки, т.к данные по указателям объявлены как константные
        // *ptrToConstData = '!'; ошибка
        //* constPtrToConstData = '!';
    }
private:
    // Область памяти, на которую изначально указывают все члены-указатели
    char symbol = ' ';
    char* ptr = &symbol;
    const char* ptrToConstData = &symbol;
    char* const constPtrToData = &symbol;
    const char* const constPtrToConstData = &symbol;
};

void useFoo(Foo) {}


//---------------------------------------------


class String {
public:
    String(const char* cString): data{cString} { }
    std::size_t length() const {
        return data.size();
    }
private:
    std::string data;
};

void foo(const String& s) {
    std::cout << "string length " << s.length() << std::endl;
}

void base() {
    const String s("Hello!");
    foo(s); //ok
}

namespace text {
    class Surface{};

    class Text {
    public:
        void render(Surface& target) const {}

        void set(const std::string& text) {
            this->text = text;
        }
        std::string get() const {
            return text;
        }
    private:
        std::string text;
    };
//возможная реализация
    void show(const Text& text, Surface& s) {
        if (text.get().empty()) {
            Text tmp; tmp.set("<none>"); tmp.render(s);
        } else {
            text.render(s);
        }
    }
}


int main() {
    base();

//-------------

    Foo foo;
    // для вызова константных перегрузок методов. Не самый изящный, но наглядный подход
    const Foo& cfoo = foo;
    foo.changeValues();
    cfoo.changeValues();

    foo.changePointers();
    cfoo.changePointers();
}
