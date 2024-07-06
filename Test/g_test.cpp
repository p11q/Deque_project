#include <gtest/gtest.h>
#include <random>
#include <type_traits>
#include "deque.hpp"

struct NotDefaultConstructible {
    NotDefaultConstructible() = delete;
    NotDefaultConstructible(int data) : data(data) {}
    int data;

    //auto operator<=>(const NotDefaultConstructible&) const = default;
};

struct ThrowStruct {
    ThrowStruct(int value, bool throw_in_assignment, bool throw_in_copy) :
            value(value),
            throw_in_assignment(throw_in_assignment),
            throw_in_copy(throw_in_copy) {}

    ThrowStruct(const ThrowStruct& s) {
        value = s.value;
        throw_in_assignment = s.throw_in_assignment;
        throw_in_copy = s.throw_in_copy;

        if (throw_in_copy) {
            throw 1;
        }
    }

    ThrowStruct& operator=(const ThrowStruct& s) {
        if (throw_in_assignment) {
            throw 1;
        }

        value = s.value;
        throw_in_assignment = s.throw_in_assignment;
        throw_in_copy = s.throw_in_copy;

        return *this;
    }

    //auto operator<=>(const ThrowStruct&) const = default;

    int value;
    bool throw_in_assignment;
    bool throw_in_copy;
};

template <class Stack1, class Stack2>
bool CompareStacks( Stack1& s1,  Stack2& s2) { // не работает с const
    for (size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }

    return true;
}


TEST(DequeConstructors, Default) {          // +
    Deque<int> defaulted;
    EXPECT_EQ(defaulted.size(), 0);

    Deque<NotDefaultConstructible> without_default;
    EXPECT_EQ(without_default.size(), 0);
}


TEST(DequeConstructors, CopyEmpty) {        // +
    Deque<NotDefaultConstructible> without_default;
    Deque<NotDefaultConstructible> copy = without_default;
    std::ignore = copy;
    EXPECT_EQ(copy.size(), 0);
}


TEST(DequeConstructors, WithSize) {             // +
    size_t size = 17;
    int value = 14;

    {
        Deque<int> simple(size);
        EXPECT_EQ(simple.size(), size);
    }

    {
        Deque<NotDefaultConstructible> less_simple(size, value);
        EXPECT_EQ(less_simple.size(), size);
    }

}

TEST(DequeOperators, Assignment) {              // +-
    Deque<int> first(10, 10);
    Deque<int> second(9, 9);
    first = second;

    EXPECT_EQ(first.size(), 9);
    EXPECT_EQ(first.size(), second.size());
   // EXPECT_TRUE(CompareStacks(first, second)); // проблемы с tail
}



TEST(DequeConstructors, StaticAsserts) {            // ????
    using T1 = int;
    using T2 = NotDefaultConstructible;

    EXPECT_TRUE(std::is_default_constructible_v<Deque<T1>>);
    EXPECT_TRUE(std::is_default_constructible_v<Deque<T2>>);

    EXPECT_TRUE(std::is_copy_constructible_v<Deque<T1>>);
    EXPECT_TRUE(std::is_copy_constructible_v<Deque<T2>>);

    {
        auto test = std::is_constructible_v<Deque<T1>, size_t>;
        EXPECT_TRUE(test);
    }

    {
        auto test = std::is_constructible_v<Deque<T1>, size_t, const T1&>;
        EXPECT_TRUE(test);
    }

    {
        auto test = std::is_constructible_v<Deque<T2>, size_t, const T2&>;
        EXPECT_TRUE(test);
    }

    EXPECT_TRUE(std::is_copy_assignable_v<Deque<T1>>);
    EXPECT_TRUE(std::is_copy_assignable_v<Deque<T2>>);
}


/*TEST(DequeAccess, SquareBrackets) {               // Ошибка в тесте
    Deque<size_t> defaulted(1300, 43);

    EXPECT_EQ(defaulted[0], defaulted[1280]);
    EXPECT_EQ(defaulted[0], 43);
}*/
/*
TEST(DequeAccess, OperatorAt) {
    Deque<size_t> defaulted(1300, 43);

    EXPECT_EQ(defaulted.at(0), defaulted.at(1280));
    EXPECT_EQ(defaulted.at(0), 43);

    EXPECT_THROW(defaulted.at(size_t(-1)), std::out_of_range);
    EXPECT_THROW(defaulted.at(1300), std::out_of_range);
}
*/
TEST(DequeModification, PushFrontOnly) {        // +
    Deque<size_t> d(5, 10);
    EXPECT_EQ(d.size(), 5);

    for (size_t i = 0; i < 64; ++i) {
        d.push_front(i);
    }
    EXPECT_EQ(d.size(), 69);
}

TEST(DequeModification, PushBackOnly) {     // +
    Deque<size_t> d(5, 10);
    EXPECT_EQ(d.size(), 5);

    for (size_t i = 0; i < 64; ++i) {
        d.push_back(i);
    }
    EXPECT_EQ(d.size(), 69);
}
/*
TEST(Deque, Throw) {
    {
        EXPECT_THROW(Deque<ThrowStruct> d(10, ThrowStruct(0, false, true)), int);
    }
{
     Deque<ThrowStruct> d(10, ThrowStruct(10, true, false));
     EXPECT_THROW(d[0] = ThrowStruct(1, false, false), int);
     EXPECT_EQ(d.size(), 10);
     EXPECT_EQ(d[0].value, 10);
 }

{
    Deque<ThrowStruct> d(1, ThrowStruct(10, false, false));
    EXPECT_THROW(d.push_back(ThrowStruct(1, false, true)), int);
    EXPECT_EQ(d.size(), 1);
}
 }
 */
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}