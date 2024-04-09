#include <gtest/gtest.h>
#include <glib.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"

TEST(HashtableTests, Initialization)
{
    GHashTable* hashtable;
    hashtable = create(); //create hashtable
    ASSERT_NE(hashtable, nullptr); // creation success
};

TEST(HashtableTests, InsertAndLookup) {
    GHashTable* hashtable;
    hashtable = create();
    insert(hashtable, "test_func", (ForthFunction) int_stack_dup);

    ForthFunction func = lookup(hashtable, "test_func");

    ASSERT_NE(func, nullptr); //ensure its found
    ASSERT_EQ(func, (ForthFunction) int_stack_dup); 
}

TEST(HashtableTests, AddAllFunctions) {
    GHashTable* hashtable;
    hashtable = create();
    add_all_functions(hashtable);

    // lookup each function and ensure they are all found
    ASSERT_NE(lookup(hashtable, "dup"), nullptr);
    ASSERT_NE(lookup(hashtable, "2dup"), nullptr);
    ASSERT_NE(lookup(hashtable, "swap"), nullptr);
    ASSERT_NE(lookup(hashtable, "+"), nullptr);
    ASSERT_NE(lookup(hashtable, "-"), nullptr);
    ASSERT_NE(lookup(hashtable, "*"), nullptr);
    ASSERT_NE(lookup(hashtable, "/"), nullptr);
    ASSERT_NE(lookup(hashtable, "."), nullptr);
    ASSERT_NE(lookup(hashtable, "drop"), nullptr);
    ASSERT_NE(lookup(hashtable, "2drop"), nullptr);
    ASSERT_NE(lookup(hashtable, "over"), nullptr);
    ASSERT_NE(lookup(hashtable, "2over"), nullptr);
}

TEST(HashtableTests, Delete)
{ 
    GHashTable* hashtable;
    hashtable = create();
    destroy(hashtable);
    ASSERT_EQ(hashtable, nullptr);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}