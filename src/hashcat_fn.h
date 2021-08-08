#ifndef HASHCAT_FN_H
#define HASHCAT_FN_H

#include <string>
#include "hashcat_fn_data.h"

// File contains declarations for implementations of imitation hashcat functions

namespace Hashcat_Fn {
    
    void append_char(std::string&, Hashcat_Fn_Data);  // $X
    void prepend_char(std::string&, Hashcat_Fn_Data); // ^X
    void toggle_char(std::string&, Hashcat_Fn_Data);  // TN

}

// Represents a pointer to a "Hashcat Function"
typedef void (*hc_fn_ptr)(std::string &s, Hashcat_Fn_Data);

#endif /* HASHCAT_FN_H */
