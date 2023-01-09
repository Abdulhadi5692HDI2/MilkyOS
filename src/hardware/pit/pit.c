#include "pit.h"
#include "../../drivers/IO/osio.h"
#include "../../tty.h"
#include "../../libc/libc.h"

int tick = 0;
char dtick;

void pit_callback() {
    for (tick = 0;;tick++) {
        itoa(tick, dtick, 10);
        scrprint(dtick);
    }
}