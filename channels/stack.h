//
//  stack.h
//  SystemCTutorial
//
//  Created by Lukas Woodtli on 16.02.16.
//
//

#ifndef stack_h
#define stack_h

#include <systemc>

#include <iostream>

#include "stack_if.h"

using namespace std;

class stack : public sc_module,
              public stack_write_if,
              public stack_read_if
{
private:
    char data[20];
    int top;
    
public:
    stack(sc_module_name nm) : sc_module(nm), top(0)
    {
    }
    
    bool nb_write(char c)
    {
        if (top < 20)
        {
            data[top++] = c;
            return true;
        }
        return false;
    }
    
    void reset()
    {
        top = 0;
    }
    
    bool nb_read(char& c)
    {
        if (top > 0)
        {
            c = data[--top];
            return true;
        }
        return false;
    }
    
    void register_port(sc_port_base& port, const char* if_type_name)
    {
        cout << "binding: " << port.name() << " to interface " << if_type_name << endl;
    }
};


#endif /* stack_h */
