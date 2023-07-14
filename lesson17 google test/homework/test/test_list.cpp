#include "../vector/mvector.cpp"

#include <gtest/gtest.h>


TEST(mVector, Empty) {
    mVector<int> v;

    ASSERT_EQ(v.size(), 0);
    //ASSERT_TRUE(v.empty());
}

TEST(mVector, PushBackSize) {
    const size_t count = 10;
    mVector<int> v;

    for (size_t i = 0; i < count; ++i) {
        v.push_back(i);
    }

    ASSERT_EQ(v.size(), count);
    //ASSERT_FALSE(v.empty());
}

TEST(mVector, PushBackValue) {
    const size_t count = 10;
    mVector<size_t> v;

    for (size_t i = 0; i < count; ++i) {
        //        if (i == 5)
        //            v.push_back(i+1);
        //        else
        v.push_back(i);
    }

    for (size_t i = 0; i < count; ++i) {
        ASSERT_EQ(v[i], i);
    }
}


TEST(mVector, errase) {

    mVector<int> v;

    for(int i=0; i<10; ++i){
        v.push_back(i);
    }

    v.erase(6);
    v.erase(4);
    v.erase(2);

    //0 1 3 5 7 8 9
    ASSERT_EQ(v.size(), 7);
    ASSERT_EQ(v[0], 0);  ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[2], 3);  ASSERT_EQ(v[3], 5);
    ASSERT_EQ(v[4], 7);  ASSERT_EQ(v[5], 8);
    ASSERT_EQ(v[6], 9);
}

TEST(mVector, push_front) {
    const size_t count = 10;
    mVector<size_t> v;

    for (size_t i = 0; i < count; ++i) {
        v.push_back(i);
    }

    v.push_front(66);

    ASSERT_EQ(v[0], 66);
}

TEST(mVector, insert_in_middle) {
    mVector<size_t> v{11, 22, 44, 55};

    v.insert(v.size()/2, 33);

    ASSERT_EQ(v[v.size()/2], 33);
}

TEST(mVector, errase_first) {
    mVector<size_t> v{11, 22, 44, 55};

    v.erase(0);

    ASSERT_EQ(v.size(), 3); ASSERT_EQ(v[0], 22);
    ASSERT_EQ(v[1], 44);    ASSERT_EQ(v[2], 55);
}

TEST(mVector, errase_last) {
    mVector<size_t> v{11, 22, 44, 55};

    v.erase(3);

    ASSERT_EQ(v.size(), 3); ASSERT_EQ(v[0], 11);
    ASSERT_EQ(v[1], 22);    ASSERT_EQ(v[2], 44);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
