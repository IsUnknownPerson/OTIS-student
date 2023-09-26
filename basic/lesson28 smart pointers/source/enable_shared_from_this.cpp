#include <iostream>
#include <memory>
#include <vector>

struct SomeStruct : std::enable_shared_from_this<SomeStruct> {
    SomeStruct() {
        std::cout << "ctor" << std::endl;
    }
    ~SomeStruct() {
        std::cout << "dtor" << std::endl;
    }

    std::shared_ptr<SomeStruct> getPtr() {
        return shared_from_this();
    }
};

int main() {
    {
        auto ptr1 = std::shared_ptr<SomeStruct>{new SomeStruct{}};
        auto ptr2 = ptr1->getPtr();
        std::cout << "before scope end" << std::endl;
    }
    std::cout << "after scope" << std::endl;

    return 0;
}




struct Subscriber : public std::enable_shared_from_this<Subscriber> {
    using SubscriberPtr = std::shared_ptr<Subscriber>;

    Subscriber(int index)
        : m_index{index} {

    }

    SubscriberPtr getPtr() {
        return shared_from_this();
    }

    void notify() {
        std::cout << "[" << m_index << "] notify" << std::endl;
    }
private:
    int m_index;
};

struct Publisher {
    void subscribe(Subscriber& subscriber) {
        m_subscribers.emplace_back(subscriber.getPtr());
    }

    void makeNotification() {
        for (auto& s : m_subscribers)
            s->notify();
    }
private:
    std::vector<Subscriber::SubscriberPtr> m_subscribers;
};

int main() {

    Publisher publisher;
    Publisher publisher2;

    const int subsrCount = 5;
    for (int i = 0; i < subsrCount; ++i) {
        Subscriber subscr{i};
        publisher.subscribe(subscr);
        publisher2.subscribe(subscr);
    }

    publisher.makeNotification();
    publisher2.makeNotification();

    return 0;
}