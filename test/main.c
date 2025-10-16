#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main()
{

    /*------------------------------------------------------------------------*/
    {
        uint64_t result = 0;
        uint64_t expect = 3542168307;
        uint8_t input = 1;
        uint8_t * p = &input;
        asm("mov    %1   , %%rbx    \n"
            "movq   $10  , %%rax \n"
            "crc32b (%%rbx), %%rax \n"
            "crc32b (%%rbx), %%rax \n"
            "movq   %%rax, %0    \n"

            : "=r" (result)
            : "r"  (p)
            :"rax","rbx"
            );

        char fmt[] = "[%s] CRC32 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    exit(0);
    /*------------------------------------------------------------------------*/
    {
        uint64_t result = 0;
        uint64_t expect = 3542168307;
        uint64_t input = 1;
        uint64_t * p = &input;
        asm("movq   %1   , %%rbx    \n"
            "movq   $10  , %%rax \n"
            "crc32q  (%%rbx), %%rax \n"
            "crc32q  (%%rbx), %%rax \n"
            "movq   %%rax, %0    \n"

            : "=r" (result)
            : "r"  (p)
            :"rax","rbx"
            );

        char fmt[] = "[%s] CRC32 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }

    /*------------------------------------------------------------------------*/
    {
        uint64_t result = 0;
        uint64_t expect = 3542168307;
        asm("movq   $1   , %0    \n"
            "movq   $10  , %%rax \n"
            "crc32  %0   , %%rax \n"
            "crc32  %0   , %%rax \n"
            "movq   %%rax, %0    \n"

            : "=r" (result)
            :
            :"rax"
            );

        char fmt[] = "[%s] CRC32 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    /*------------------------------------------------------------------------*/
    {
        uint64_t input  = 100500;
        uint64_t result = 0;
        uint64_t expect = 100500;
        asm ("movq   %1, %%xmm0     \n"
             "pextrq $0, %%xmm0, %0 \n"

             :"=r" (result)
             :"r"  (input)
             :"xmm0", "%0", "%1"
             );
        char fmt[] = "[%s] PEXTRQ 0x0 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    /*------------------------------------------------------------------------*/
    {
        uint64_t input  = 100500;
        uint64_t result = 0;
        uint64_t expect = 100500;
        asm ("movq   %1, %%xmm0     \n"
             "pslldq $8, %%xmm0     \n"
             "pextrq $1, %%xmm0, %0 \n"

             :"=r" (result)
             :"r"  (input)
             :"xmm0", "%0", "%1"
             );
        char fmt[] = "[%s] PEXTRQ 0x1 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    /*------------------------------------------------------------------------*/
    {
        uint64_t input  = 100500;
        uint64_t result = 0;
        uint64_t expect = 100500;

        asm ("movq   %1    , %%rax         \n"
             "pinsrq $0    , %%rax, %%xmm0 \n"
             "movq   %%xmm0, %0            \n"

             :"=r" (result)
             :"r"  (input)
             :"rax", "xmm0", "%0"
             );

        char fmt[] = "[%s] PINSRQ 0x0 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    /*------------------------------------------------------------------------*/
    {
        uint64_t input  = 100500;
        uint64_t result = 0;
        uint64_t expect = 100500;

        asm ("movq   %1, %%rax          \n"
             "pinsrq $1, %%rax , %%xmm0 \n"
             "pextrq $1, %%xmm0, %0     \n"

             :"=r" (result)
             :"r"  (input)
             :"rax", "xmm0", "%0"
             );
        char fmt[] = "[%s] PINSRQ 0x1 : EXPECT(%lld) RESULT(%lld)\n";
        printf(fmt,expect==result?"SUCCESS":"FAIL",expect,result);
        assert(expect == result);
    }
    return 0;
}
