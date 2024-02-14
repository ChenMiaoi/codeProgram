#include "os.h"
#include "riscv.h"

int spin_lock(void) {
    w_mstatus(r_mstatus() & ~MSTATUS_MIE);
    return 0;
}

int spin_unlock(void) {
    w_mstatus(r_mstatus() | MSTATUS_MIE);
    return 0;
}