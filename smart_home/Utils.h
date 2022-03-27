#ifndef UTILS_H
#define UTILS_H

#define SET_BIT(port_no,pin_no)  port_no|=(1<<pin_no)
#define CLEAR_BIT(port_no,pin_no)  port_no&=~(1<<pin_no)
#define TOGGLE_BIT(port_no,pin_no) port_no^=(1<<pin_no)
#define GET_BIT(port_no,pin_no)   (port_no)>>((pin_no)&0x01)


#define SetBit(Var,BitNum) (Var|=(1<<BitNum))
#define ClrBit(Var,BitNum) (Var&=~(1<<BitNum))
#define TogBit(Var,BitNum) (Var^=(1<<BitNum))
#define GetBit(Var,BitNum) ((Var>>BitNum)&1)


#endif
