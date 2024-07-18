#ifndef DEQUE_HPP
#define DEQUE_HPP
template<typename T>
class Deque;

template<typename T>
class Node {
    friend class Deque<T>;
private:
    T m_val;
    Node* m_next;
    Node* m_prev;

public:
    Node()
        : m_val(0), m_next(nullptr), m_prev(nullptr) {};

    Node(T value, Node* next, Node* prev)
        : m_val(value), m_next(next), m_prev(prev) {};

    Node(T m_val) = delete;

    ~Node() = default;

};

template<typename T>
class Deque {
private:
    Node<T>* m_head;
    Node<T>* m_tail;
    size_t m_size;
public:
    using Node_t = Node<T>;

    Deque() :
        m_head(nullptr), m_tail(nullptr), m_size{ 0 }
    {}

    explicit Deque(size_t size) :
        m_size{ size } {

        auto* head_val = new Node_t{T{}, nullptr, nullptr};

        m_head = head_val;

        Node_t* it = m_head;
        for (int i = 0; i < m_size; i++) {

            auto* tmp = new Node_t{T{}, nullptr,nullptr};

            it->m_next = tmp;
            tmp->m_prev = it;
            it = it->m_next;
        }
        m_tail = it;
    }

    Deque(const size_t size, T value) :
    m_size(size) {

        auto* head_val = new Node_t{value, nullptr, nullptr};

        m_head = head_val;

        Node_t* it = m_head;
        for (int i = 0; i < m_size; i++) {

            auto* tmp = new Node_t{value, nullptr,nullptr};

            it->m_next = tmp;
            tmp->m_prev = it;
            it = it->m_next;
        }
        m_tail = it;
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    Deque& operator=(const Deque<T> dq_1) {
        // Выравнивание size
        if (dq_1.m_head == nullptr) {
            return *this;
        } else {
            if (dq_1.m_size > this->m_size) {
                for (int i = 0; i < (dq_1.m_size - this->m_size); i++) {
                    auto* tmp = new Node_t{};
                    tmp->m_prev = this->m_tail;
                    this->m_tail->m_next = tmp;
                    this->m_tail = tmp;
                }
            }
            if (dq_1.m_size < this->m_size) {
                for (int i = 0; i < (this->m_size - dq_1.m_size); i++) {
                    m_tail = m_tail->m_prev;  // не перевешивается tail
                    m_tail->m_next->m_prev = nullptr;
                    m_tail->m_next = nullptr;

                }
            }
            this->m_size = dq_1.m_size;
        }

        // Наполнение
        auto* it = new Node_t{};
        it = this->m_head;
        for(int j = 0; j < this->m_size; j++) {
            it->m_val = dq_1.m_head->m_val;
            it = it->m_next;
        }
        return *this;
    }
// Надо подумать
    Node_t* operator[] (const int index) {
        if (m_head == nullptr || index < 0 || index >= this->m_size) return nullptr;
        int i = 0;
        Node_t* tmp = m_head;
        while (i++ < index) {
            tmp = tmp->m_next;
        }
        return tmp;
    }

    Node_t* at(int index) const {
        return this[index];
    }

    void push_back(int value) {
        auto* tmp = new Node_t{};
        tmp->m_val = value;
        tmp->m_next = nullptr;
        tmp->m_prev = nullptr;

        if (m_head == nullptr) {
            m_head = tmp;
            m_tail = tmp;
        }
        else {
            Node_t* it = m_tail;
            tmp->m_prev = it;
            it->m_next = tmp;
            m_tail = tmp;
        }
        m_size++;
    }

    void push_front(int value) {
        auto* tmp = new Node_t{};
        tmp->m_val = value;
        tmp->m_next = nullptr;
        tmp->m_prev = nullptr;

        if (m_head == nullptr) {
            m_head = tmp;
            m_tail = tmp;
        }

        else {
            m_head->m_prev = tmp;
            tmp->m_next = m_head;
            m_head = tmp;
        }
        m_size++;
    }



    ~Deque() {
       auto* it = new Node_t{};
        it = m_head->m_next;
        while (it->m_next != nullptr) {
            it->m_prev->~Node();
            it = it->m_next;
        }
        it->~Node();
    }
};




#endif
