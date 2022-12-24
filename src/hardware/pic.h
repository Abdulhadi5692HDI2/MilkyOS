#ifndef _PIC_H
#define _PIC_H

void PIC_sendEOI(unsigned char irq);
void PIC_remap(int offset1, int offset2);
#endif