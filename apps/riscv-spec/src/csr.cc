// define of legal instructions
#include <iostream>
#include <string>
#include <cassert>


#include "ila++.h"

#include "helpers.hpp"

using namespace ila;

#include "encoding.hpp"

unsigned legalMatch [52] = {0x63,0x1063,0x4063,0x5063,0x6063,0x7063,0x67,0x6f,0x37,0x17,0x13,0x1013,0x2013,0x3013,0x4013,0x5013,0x40005013,0x6013,0x7013,0x33,0x40000033,0x1033,0x2033,0x3033,0x4033,0x5033,0x40005033,0x6033,0x7033,0x3,0x1003,0x2003,0x4003,0x5003,0x23,0x1023,0x2023,0xf,0x100f,0x73,0x100073,0x200073,0x10200073,0x30200073,0x12000073,0x10500073,0x1073,0x2073,0x3073,0x5073,0x6073,0x7073}; 
unsigned legalMask  [52] = {0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x7f,0x7f,0x7f,0x707f,0xfc00707f,0x707f,0x707f,0x707f,0xfc00707f,0xfc00707f,0x707f,0x707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xfe007fff,0xffffffff,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f}; 
unsigned prevList   [52] = {0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x7f,0x7f,0x7f,0x707f,0xfc00707f,0x707f,0x707f,0x707f,0xfc00707f,0xfc00707f,0x707f,0x707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0xfe00707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xfe007fff,0xffffffff,0x707f,0x707f,0x707f,0x707f,0x707f,0x707f}; 

                        // sstatus, stvec,  sie,sscratch,sepc,scause,  stval,  sip, satp,  
unsigned legalCSRAddr[] = [0x100, 0x105, 0x104, , 0x140, 0x141, 0x142, 0x143, 0x144, 0x180,  
             //mcpuid , mimpid,mhartid,mstatus,mtvec,mtdel,mie, mtimecmp
                0xF00, 0xF01, 0xF10, 0x300, 0x301, 0x302, 0x304, 0x321,
             //mscratch,mepc,mcause, mbadaddr,mip, mtohost,mfromhost
                0x340, 0x341, 0x342, 0x343, 0x344, 0x780, 0x781];
unsigned NondetCSRAddr[];
unsigned ROCSR[];
std::vector<range> CSRNotModeled;