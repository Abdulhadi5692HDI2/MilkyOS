#include "keyboard.h"
#include "../../kernel.h"
#include "../IO/osio.h"

void chkscancode(uint8_t scancode1) {
    switch (scancode1)
    {
    case 0x0:
        break;
    case 0x1:
        break;
    case 0x2:
        scrprint("1");
        break;
    case 0x3:
        scrprint("2");
        break;
    case 0x4:
        scrprint("3");
        break;
    case 0x5:
        scrprint("4");
        break;
    case 0x6:
        scrprint("5");
        break;
    case 0x7:
        scrprint("6");
        break;
    case 0x8:
        scrprint("7");
        break;
    case 0x9:
        scrprint("8");
        break;
    case 0xA:
        scrprint("9");
        break;
    case 0x0B:
        scrprint("0");
        break;
    case 0x0C:
        scrprint("-");
        break;
    case 0x0D:
        scrprint("=");
        break;
    case 0x0E:
        scrprint("BACKSPACE");
        break;
    case 0x0F:
        scrprint("TAB");
        break;
    case 0x10:
        scrprint("Q");
        break;
    case 0x11:
        scrprint("W");
        break;
    case 0x12:
        scrprint("E");
        break;
    case 0x13:
        scrprint("R");
        break;
    case 0x14:
        scrprint("T");
        break;
    case 0x15:
        scrprint("Y");
        break;
    case 0x16:
        scrprint("U");
        break;
    case 0x17:
        scrprint("I");
        break;
    case 0x18:
        scrprint("O");
        break;
    case 0x19:
        scrprint("P");
        break;
    case 0x1A:
        scrprint("[");
        break;
    case 0x1B:
        scrprint("]");
        break;
    case 0x1C:
        scrprint("ENTER");
        break;
    case 0x1D:
        scrprint("LCTRL");
        break;
    case 0x1E:
        scrprint("A");
        break;
    case 0x1F:
        scrprint("S");
        break;
    case 0x20:
        scrprint("D");
        break;
    case 0x21:
        scrprint("F");
        break;
    case 0x22:
        scrprint("G");
        break;
    case 0x23:
        scrprint("H");
        break;
    case 0x24:
        scrprint("J");
        break;
    case 0x25:
        scrprint("K");
        break;
    case 0x26:
        scrprint("L");
        break;
    case 0x27:
        scrprint(";");
        break;
    case 0x28:
        scrprint("'");
        break;
    case 0x29:
        scrprint("`");
        break;
    case 0x2A:
        scrprint("LSHIFT");
        break;
    case 0x2B:
        scrprint("\\");
        break;
    case 0x2C:
        scrprint("Z");
        break;
    case 0x2D:
        scrprint("X");
        break;
    case 0x2E:
        scrprint("C");
        break;
    case 0x2F:
        scrprint("V");
        break;
    case 0x30:
        scrprint("B");
        break;
    case 0x31:
        scrprint("N");
        break;
    case 0x32:
        scrprint("M");
        break;
    case 0x33:
        scrprint(",");
        break;
    case 0x34:
        scrprint(".");
        break;
    case 0x35:
        scrprint("/");
        break;
    case 0x36:
        scrprint("RSHIFT");
        break;
    case 0x39:
        scrprint("SPACE");
        break;
    case 0x82:
        break;
    case 0x83:
        break;
    case 0x84:
        break;
    case 0x85:
        break;
    case 0x86:
        break;
    case 0x87:
        break;
    case 0x88:
        break;
    case 0x89:
        break;
    case 0x8A:
        break;
    case 0x8B:
        break;
    default:
        break;
    }

}


void keyboardCallback() {
    // store the key that was just pressed in a variable
    uint8_t pressedkey = inb(0x60);
    // chkscancode(pressedkey); will convert that scancode
    chkscancode(pressedkey);
    //scrprint("\n");
}
void kernelInitKeyboard() {
    scrprint(" Initalized keyboard driver successfully!\n");
}
void initKeyboard() {
    keyboardCallback();
}