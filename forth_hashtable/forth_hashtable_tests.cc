#include <gtest/gtest.h>
#include <glib.h>
extern "C" {
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"
}

TEST(HashtableTests, Initialization)
{
    GHashTable* hashtable;
    hashtable = create(); //create hashtable
    ASSERT_NE(hashtable, nullptr); // creation success
}
/*
TEST(HashtableTests, Insert) {
    GHashTable* hashtable;
    hashtable = create();
    insert(hashtable, "test_func", (ForthFunction) int_stack_dup);

    // Check if the function was inserted successfully
    ForthFunction func = lookup(hashtable, "test_func");
    ASSERT_NE(func, nullptr); // Ensure it's found
}

TEST(HashtableTests, Lookup) {
    GHashTable* hashtable;
    hashtable = create();
    insert(hashtable, "test_func", (ForthFunction) int_stack_dup);

    ForthFunction func = lookup(hashtable, "test_func");

    ASSERT_EQ(func, (ForthFunction) int_stack_dup); 
}*/

TEST(HashtableTests, Delete)
{ 
    GHashTable* hashtable;
    hashtable = create();
    destroy(hashtable);
    hashtable = NULL; 
    ASSERT_EQ(hashtable, nullptr);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}