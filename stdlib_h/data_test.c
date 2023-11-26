#include "test.h"
#include "lib/data.h"

// LIST OF TESTS
/*
 * checksum()
 * checksum_byte()
 * checksum_word()
 * checksum_dword()
 * checksum_qword()
*/

/*
 * data_obfuscator()
 * data_deobfuscator()
*/

testbool checksum_test(void);
testbool dataObfuscation_test(void);

char* globalptr = NULL;

int main(int argc, char* argv[]) {

    testbool result1 = checksum_test();
    return 0;
}

char str[] = "l";

testbool checksum_test() {
    char* ptr = str[0];
    int a = 100;
    

}