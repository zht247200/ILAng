#include "model_sha_class.hpp"

#include <iostream>
#include <time.h>

#define SHA_IDLE  0
#define SHA_READ  1
#define SHA_OP1   2
#define SHA_OP2   3
#define SHA_WRITE 4

BIT_VEC sha(BIT_VEC cppVar_14)
{
    return 0;
}

int main()
{
    BIT_VEC RD = 1;
    BIT_VEC WR = 2;

    BIT_VEC addr_start = 0xfe00;
    BIT_VEC addr_state = 0xfe01;
    BIT_VEC addr_rd    = 0xfe02;
    BIT_VEC addr_wr    = 0xfe04;
    BIT_VEC addr_len   = 0xfe06;

    BIT_VEC wraddr = 128;
    BIT_VEC rdaddr = 0;
    BIT_VEC len = 128;

	model_sha mod;

    mod.sha_state = SHA_IDLE;

    int cnt = 0;

    clock_t t;
    t = clock();

    for (int i = 0; i < 1000000; i++) {
        mod.update(WR, addr_rd, rdaddr);
        mod.update(WR, addr_wr, wraddr);
        mod.update(WR, addr_len, len);
        mod.update(WR, addr_start, 1);
        cnt += 4;
        do {
            mod.update(RD, addr_state, 0);
            cnt++;
        } while (mod.dataout != SHA_IDLE);
    }

    t = clock() - t;
    std::cout << "time: " << (double)t/CLOCKS_PER_SEC << std::endl;
    std::cout << "cycle: " << cnt << std::endl;

    return 0;
}
