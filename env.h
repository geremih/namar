#include"uthash.h"
#include "utils.h"
struct env_entry{
        char* symbol;
        int stack_index;
        UT_hash_handle hh;
};
struct env{
        struct env_entry* table;
        struct env* previous;
};

struct env* add_env(struct env*);
struct env* remove_env(struct env*);
int find_env_stack_index(struct env* env, char* symbol);
void add_env_symbol(struct env* env, char* symbol, int stack_index);
