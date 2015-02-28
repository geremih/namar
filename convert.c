#include "includes.h"

int integer_mask = 0b11;
int integer_tag = 0b00;
int integer_shift= 2;

int boolean_mask = 0b1111111;
int boolean_tag  = 0b0011111;
int boolean_shift = 7;

int nil_mask = 0b11111111;
int nil_tag = 0b00101111;
int nil_shift = 8;

#define L_IS(type) \
        int l_is_ ## type(int i){                               \
                return (type ## _mask & i) == type ## _tag;     \
        }

L_IS(nil);
L_IS(integer);
L_IS(boolean);

int h_l_nil(){
        return nil_tag;
}

int h_l_boolean(int i){
        i = !!i;
        return (i<<boolean_shift) | boolean_tag;
};


int h_l_integer(int i){
        return (i << integer_shift) | integer_tag;
};


int l_h_integer(int i){
        if(!l_is_integer(i)){
                die("Argument is not a l_int");
                return -1;
        }
        return i >> integer_shift;
}


