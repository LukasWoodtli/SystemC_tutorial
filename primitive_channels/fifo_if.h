#ifndef _FIFO_IF_H__
#define _FIFO_IF_H__

#include <systemc>

class fifo_out_if : public virtual sc_interface
{
public:
    virtual void write(char) = 0;
    virtual int num_free() const = 0;

protected:
    fifo_out_if() {}

private:
    fifo_out_if(fifo_out_if&); // disable copy
    fifo_out_if & operator= (const fifo_out_if&); // disable assignment
};


class fifo_in_if : virtual public sc_interface
{
public:
    virtual void read(char&) = 0;
    virtual char read() = 0;
    virtual int num_available() const = 0;

protected:
    fifo_in_if(){}

private:
    fifo_in_if(const fifo_in_if&);
    fifo_in_if& operator= (const fifo_in_if&);
};

#endif /* _FIFO_IF_H__ */
