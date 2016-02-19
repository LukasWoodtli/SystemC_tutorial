#ifndef _STACK_IF_H__
#define _STACK_IF_H__

#include <systemc>

class stack_write_if : public virtual sc_interface
{
public:
    virtual bool nb_write(char) = 0;
    virtual void reset() = 0;
};


class stack_read_if : virtual public sc_interface
{
public:
    virtual bool nb_read(char&) = 0;
};

#endif /* _STACK_IF_H__ */