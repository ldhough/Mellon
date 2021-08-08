#ifndef HASHCAT_FN_DATA_H
#define HASHCAT_FN_DATA_H

/*
 * Hashcat functions can take multiple types of
 * arguments - to make it easier to store and 
 * call the correct function dynamically, possible
 * arguments have been consilidated into this struct
 */

struct Hashcat_Fn_Data {
    char X;
    unsigned int N;
    unsigned int M;
    // Unused rn
    unsigned int I;
};

#endif /* HASHCAT_FN_DATA_H */
