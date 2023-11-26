
#include "test.h"
#include "lib/booleans.h"
#include <string.h>

#define SHOW 0

FILE* booleans_test_logfile = NULL;

/* LIST OF TESTS */
/* 
 * TRUE     - true  (1)
 * FALSE    - false (0)
 * BOOL_P   - bool positive (+)
 * BOOL_0   - bool neutral  (0)
 * BOOL_N   - bool negative (-)
 */
testbool boolconst_test(void);

/* 
 * buf  (-)
 * inv  (!)
 * or   (||)
 * nor  !(||)
 * and  (&&)
 * nand !(&&)
 * xor  ((!a && b) || ( a && !b))
 * xnor (( a && b) || (!a && !b))
*/
testbool logicalOperators_test(void);
    testbool _inputTest(char ninput, int (*logicOp)(int, int), unsigned char expectedResult_table[]);

/* 
 * boolfPrint()
 *  - boolPrint()
 * boolStr()
 */
testbool boolprint_test(void);


int main(int argc, char* argv[]) {
    booleans_test_logfile = testlogCreate(DEFAULT_LOGDIR);
    booleans_test_logfile = stdout;

    testbool result1 = boolconst_test(); 
    testlogWrite(booleans_test_logfile, result1, "{%s} standard boolean constants test", _testlocate(__FILE__, "boolconst_test", 0));
    
    testbool result2 = logicalOperators_test();
    testlogWrite(booleans_test_logfile, result2, "{%s} logical test result", _testlocate(NULL, "logicalOperators", 0));

    testbool result3 = boolprint_test();
    testlogWrite(booleans_test_logfile, result3, "{%s} boolprint test result", _testlocate(NULL, "boolPrint_test", 0));

    if (RETURN_TIME) return clock();
    else return testSummary(2, result1, result2);
}

// Boolean test
testbool boolconst_test(void) {
    if (!((TRUE == 1) && (FALSE == 0))) return TEST_FAILED;

    if (!((BOOL_P == 1) && (BOOL_0 == 0) && (BOOL_N == -1))) return TEST_FAILED;

    return TEST_SUCCESS;
}

// basic boolean algebra table lookup
/* 
 * a | b | result
 * 0   0    *
 * 1   0    *
 * 0   1    *
 * 1   1    *   
 */

#define MAX_BOOLINPUT   2
#define LOGICAL_BOOLEAN_OPERATORS 8

void* logicalBool_func[LOGICAL_BOOLEAN_OPERATORS] = { _buf, _inv, _or, _nor, _and, _nand, _xor, _xnor };
unsigned char logicOp_table[LOGICAL_BOOLEAN_OPERATORS][4] = {

//  | 0 | 1 | 0 | 1 |   a
//  | 0 | 0 | 1 | 1 |   b
    { 0 , 1 , 0 , 1 },  /* BUF (only a) */
    { 1 , 0 , 1 , 0 },  /* INV (only a) */

    { 0 , 1 , 1 , 1 },  /* OR  */
    { 1 , 0 , 0 , 0 },  /* NOR */

    { 0 , 0 , 0 , 1 },  /* AND  */
    { 1 , 1 , 1 , 0 },  /* NAND */

    { 0 , 1 , 1 , 0 },  /* XOR  */
    { 1 , 0 , 0 , 1 }   /* XNOR */
};


testbool booleans_test_result2[LOGICAL_BOOLEAN_OPERATORS] = { 0 };
testbool logicalOperators_test(void) {

    // function test
    for (int i = 0; i < LOGICAL_BOOLEAN_OPERATORS ; i++) {
        booleans_test_result2[i] = _inputTest(2, logicalBool_func[i], logicOp_table[i]);
    }
    return (testArrSummary(booleans_test_result2, 8));
}

testbool _inputTest(char ninput, int (*logicOp)(int, int), unsigned char expectedResult_table[]) {
    if(ninput > MAX_BOOLINPUT) {
        printf("Maximum ninput allowed currently: %d\n", MAX_BOOLINPUT);
        return TEST_INVALID;
    }

    int i = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int result = 0;

    for ( ; i < (1 << ninput) ; i++) {
        switch (ninput)
        {
        case 3: break;
        case 2: b = ((i >> 1) & 1);
        case 1: a = ((i >> 0) & 1);
        break;
        
        default: return TEST_INVALID;
        }

        result = (*logicOp)(a, b);

        logwrite(booleans_test_logfile, "a:%d b:%d  | %d (%d)", a, b, result, expectedResult_table[i]);
        if (result != expectedResult_table[i]) return TEST_FAILED;
    }
    return TEST_SUCCESS;
}


const char* __bstr[2] = {"FALSE", "TRUE"};

#define BOOLEANTEST_VALUE_SIZE  6
const int booleanTestValue[BOOLEANTEST_VALUE_SIZE] = {TRUE, FALSE, -3, 25, -1, 0};
const int booleanTestExpected[BOOLEANTEST_VALUE_SIZE] = {1, 0, 1, 1, 1, 0};

testbool booleans_test_result3[2][BOOLEANTEST_VALUE_SIZE] = { 0 };
testbool boolprint_test() {
    char buffer[0x40] = { 0 };
    int fileEndPos = 0;
    const char* tempfiledir = "test\\booleans_tempfile";

    FILE* tempfile = createTempFile(tempfiledir);    
    for (int i = 0; i < BOOLEANTEST_VALUE_SIZE; i++) {
        boolfPrint(tempfile, booleanTestValue[i]); fputc('\0', tempfile);
    }
    
    fseek(tempfile, 0, SEEK_END);
    fileEndPos = ftell(tempfile);

    fseek(tempfile, 0, SEEK_SET);
    fread(buffer, 1, fileEndPos, tempfile);

    // 1st test
    int i = 0;
    for (int n = 0; n < BOOLEANTEST_VALUE_SIZE; n++) {
        if(strcmp(&buffer[i], __bstr[booleanTestExpected[n]]) == 0)
            booleans_test_result3[0][n] = TEST_SUCCESS;
        else
            booleans_test_result3[0][n] = TEST_FAILED;

        logwrite(booleans_test_logfile, "%2d/%2d [%s] %s", i, fileEndPos, testStateStr[booleans_test_result3[0][n]], &buffer[i]);
        i += strlen(&buffer[i]) + 1;
    }
    deleteTempFile(&tempfile, tempfiledir);

    // 2nd test
    for (int n = 0; n < BOOLEANTEST_VALUE_SIZE; n++) {
        if (strcmp(__bstr[booleanTestExpected[n]], boolStr(booleanTestValue[n])) == 0)
            booleans_test_result3[1][n] = TEST_SUCCESS;
        else
            booleans_test_result3[1][n] = TEST_FAILED;
    }
    
    return testSummary(
        2,
        testArrSummary(booleans_test_result3[0], BOOLEANTEST_VALUE_SIZE),
        testArrSummary(booleans_test_result3[1], BOOLEANTEST_VALUE_SIZE)
    );
}
