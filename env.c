#include "env.h"
#include<stdlib.h>
#include<stdio.h>
struct env* add_env(struct env* env){
        struct env* new_env = malloc(sizeof(struct env));
        new_env->table = NULL;
        new_env->previous = env;
        return new_env;
}

struct env* remove_env(struct env* env){
        if(env == NULL){
                return env;
        }
        struct env *old_env = env->previous;
        struct env_entry *entry, *tmp;
        HASH_ITER(hh, env->table, entry, tmp) {
                HASH_DEL(env->table, entry);
                free(entry->symbol);
                free(entry);
        }
        free(env);
        return old_env;
}

void add_env_symbol(struct env* env, char* symbol, int stack_index){
        struct env_entry* entry;
        HASH_FIND_STR(env->table, symbol, entry);
        if(entry){
                entry->stack_index = stack_index;
        }
        else{
                entry = malloc(sizeof(struct env_entry));
                entry->symbol = strdup(symbol);
                entry->stack_index = stack_index;
                HASH_ADD_KEYPTR( hh, env->table, entry->symbol, strlen(entry->symbol), entry);
        }

}

int find_env_stack_index(struct env* env, char* symbol){
        //Go up the environments
        struct env_entry* entry = NULL;
        struct env* temp_env = env;
        while(temp_env != NULL){
                HASH_FIND_STR(env->table, symbol, entry);
                if(entry)
                        break;
                temp_env = env->previous;
        }
        if(!entry)
                die("Undefined symbol");
        
        return entry->stack_index;
}

/* int main(){ */
/*         struct env *env = malloc(sizeof(struct env)); */
/*         env->table = NULL; */
/*         env->previous = NULL; */
/*         add_env_symbol(env, "a", 1); */
/*         printf("%d\n", find_env_stack_index(env, "a")); */
/*         add_env_symbol(env, "a", 12); */
        
/*         printf("%d\n", find_env_stack_index(env, "a")); */
/*         env = add_env(env); */
/*         add_env_symbol(env, "a", 13); */
/*         printf("%d\n", find_env_stack_index(env, "a")); */
/*         env = remove_env(env); */
/*         printf("%d\n", find_env_stack_index(env, "a")); */
/*         remove_env(env); */
/* } */
