namespace Awkernel {
    extern "C" {
        unsigned char inb (unsigned short int __port);
        void outb (unsigned int __value, unsigned short int __port);
    }
    unsigned char inb (unsigned short int __port)
    {
        unsigned char _v;
        __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
        return _v;
    }
    void outb (unsigned int __value, unsigned short int __port)
    {
        __asm__ __volatile__ ("outb %b0,%w1": :"a" (__value), "Nd" (__port));
    }
}