#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#ifndef PROMPTBUFFER_H
#include "Tools/PromptBuffer.h"
#endif

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "Tools/Debug.h"
#include "booleans.h"
#include "input.h"

// "input.h" macros for easy readability
#ifdef INPUT_H
// getchar input macro (assign input with getchar and returning the INPUT_STATUS)
#define GETCHAR_INPUT(input, default_status) check_input_status(input = getchar(), default_status)
#endif

// put string
#define putstr(str) printf("%s", str)

// END OF INPUT STRING
#define ENDINPUT            EOF
#define STRING_TERMINATOR   '\0'
#define END_FLAG            -8

#define WITH_END_SEQUENCE   TRUE
#define END_SEQ_SIZE        10

// temporary solution for standard_constants header include placement
#ifndef STANDARD_CONSTANTS_H
#define IN      1
#define OUT     0

#define TRUE    1
#define FALSE   0

#define END_OF_INDEX    -5    /* Unique value of the end of index */
#endif


#define STD_MAX_LINES   512
unsigned char* std_endSequence = "THE END";

// declare strcat for end sequence check
int strArrayCat(char from[], char to[], int toPosition, int parameter);

// end characters sequence check returns FALSE if end sequence fulfilled (and returns "i (last position)" if failed)
int endSeqCheck(unsigned char input, unsigned char tempEndStr[], unsigned char endSequence[])
{
    int i = 0;
    while (input == endSequence[i]) /* loop as long input is the same as end characters Sequence */
    {
        tempEndStr[i++] = input;    /* assign the temporary string in case endSeqCheck Fails */
        input = getchar();          /* get next input */

        // if the input becomes blank and end sequence reach null terminator '\0'
        if (blankCheck(input) && (!endSequence[i])) return TRUE;
    }
    tempEndStr[i++] = input;  /* if the loop fails assign the last input character to tempEndStr */
    tempEndStr[i] = '\0';
    return FALSE;
}

/* ========== INPUT OUTPUT ============ */



// Main Input function
int input_str(char str[], int size, unsigned char* endSequence)
{
    INPUT_STATUS status;
    int nbuffer, nchar, pos, i;
    nbuffer = nchar = pos = i = 0;
    unsigned char tempBuffer[END_SEQ_SIZE];
    unsigned char c;

    status.section.active = TRUE;
    if (!endSequence) endSequence = std_endSequence;

    // main loop
    while (++i)
    {

        // check the buffer if already been finished with buffer string terminator '\0'
        // and activate the input if it not activated yet
        if (!tempBuffer[nbuffer] && !status.section.active) status.section.active = TRUE;

        // main input
        c = (status.section.active) ? getchar() : tempBuffer[nbuffer++];


        // check the status
        status.UNION = check_input_status(c, status.section.active);

        // blank check
        (status.section.blank) ? nchar = 0 : nchar++;

        // End sequence (if the first character in word)
        if (status.section.active && c == endSequence[0] && nchar == 1)
        {
            status.section.exit = endSeqCheck(c, tempBuffer, endSequence);
            status.section.active = FALSE;
            nbuffer = 1;    /* set the nbuffer position to 1 because the first character already been taken before */
        }

        // ENDINPUT
        if (c == ENDINPUT)  status.section.exit = TRUE;

        // overflow Check
        if (CHECK_ARRAY_OVERFLOW(size, pos)) {
            printf("%s Input exceed the maximum size...  (FORCE EXIT INITIATED) [size: %d]\n", DEBUG_WARNING, size);
            status.section.exit = TRUE; 
            pos--; /* for the STRING TERMINATOR */        
        }
        

        printf("%4d| input: %3d  status: %s", i, c, binaryPrint_str(status.UNION, sizeof(INPUT_STATUS)));
        printf("  nchar: %d  pos: %d  ACTIVE: %d '%c'\n", nchar, pos, status.section.active, c);


        // exit
        if (status.section.exit) { str[pos] = STRING_TERMINATOR; break; }

        // assign the input
        str[pos++] = c;

    }
    // Clear the remaining buffered string if possible
    (c == '\n') ? 0 : clearBufferedText(0);
    return pos;


}

int inputLine(unsigned char text[], int size, int lineLimit)
{
    if (!lineLimit) lineLimit = STD_MAX_LINES;  /* if line limit is undefined */
    int cur_line = 1;

    unsigned char c;
    INPUT_STATUS status;

    printf("%4d ", cur_line);
    for (int i = 0; TRUE ; i++)
    {
        
        // main input
        c = getchar();

        // add line number
        if ( status.section.newline ) { printf("%4d ", ++cur_line); }

        
        // Limit of line
        if (lineLimit == 0) ;
        else if ((cur_line >= lineLimit)){
            printf("\nMaximum number of lines reached... %d\n", c);
            text[i] = STRING_TERMINATOR;
            break;
        }

        // INPUT
        if (i < size - 1) { text[i] = c; }
        else 
        {
            text[i] = STRING_TERMINATOR; /* NULL TERMINATOR */
            printf("\nCharacters exceed the maximum size...\n"); 
            clearBufferedText(0);
            break;
        }

        // End of File (because the value of EOF is -1) and after preprocessed / buffered by OS (the actual value is 26)
        if ((c == ENDINPUT) || (c == 26)) { text[i] = STRING_TERMINATOR; break; }   
    }

}

int output(char text[], int size)
{
    for (int i = 0; (text[i] != STRING_TERMINATOR) && (i < size) ; i++) { printf("%c", text[i]); }
    putchar('\n');
}

int outputLine(char text[], int size)
{
    int line = 1;
    printf("%4d ", line); line++;
    for (int i = 0; (text[i] != STRING_TERMINATOR) && (i < size) ; i++)
    {
        printf("%c", text[i]);
        if (text[i] == '\n') {printf("%3d ", line); line++;}
    }
}

int outputValue(char text[], int size)
{
    for (int i = 0; (i < size) || (size == 0) ; )
    {
        printf("%d ", text[i]);
        if (text[i] == STRING_TERMINATOR) break;
        else if (!(++i % 40)) putchar('\n');
    }
    putchar('\n');
}

/* parameter
 * 0 - print the value
 * 1 - print the character
 */
int forced_strOutput(register unsigned char text[], register int size, int parameter) 
{ 
    // print the value
    if (parameter == 0) 
        for (register int i = 0; i < size; i++) printf("%d ", text[i]);

    // print the character
    else if (parameter == 1)
        for (register int i = 0 ; i < size; i++) printf("%c", text[i]);
    
    putchar('\n');
}

// Getline function - Input the string every newline return the position of string terminator '\0'
int getline_s(char str[], int size)
{
    int i = 0;
    // main loop
    for (char c ; i < size ; i++)
    {
        str[i] = c = getchar();

        if      (c == '\n')     { str[++i] = STRING_TERMINATOR; return i; }
        else if (c == ENDINPUT) { str[i]   = END_FLAG;          return i; }
    }

    // overflow check
    if (i >= size) {
        str[--i] = STRING_TERMINATOR;
        printf("%s Array maximum size exceeded\n", warning(__FILE__, FUNC, LINE));
        return 0;
    }
    return i;
}

int wordOutput(char text[], int firstCharPosition, int endCharPosition)
{
    int i = firstCharPosition;
    if (endCharPosition <= 0)
        while ((text[i] != ' ') && (text[i] != '\n') && (text[i] != '\t') && (text[i] != '\0') && (text[i] != STRING_TERMINATOR))
            putchar(text[i++]);
    
    else while ( i <= endCharPosition ) putchar(text[i++]);
}

/* ============ COPY ============ */
/* full string copy return the position of null terminator '\0' */
int fullStrCopy(char from[], char to[])
{
    int i;
    for (i = 0; (to[i] = from[i]); i++) ;
    return i;
}

/* string cat parameter:
 * 0 - return the position of null terminator '\0' of to string array 
 * 1 - return the total increment Value excluding null terminator '\0'
 */
int strArrayCat(char from[], char to[], int toPosition, int parameter)
{
    int i;
    for (i = 0; to[toPosition] = from[i]; i++, toPosition++) ;
    if      (parameter == 0) return toPosition;
    else if (parameter == 1) return i - 1;
}


/* ================ ARRAY CHECKER ================= */

int specificCharCheck(char str[], char character, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] == character) printf("Found in index no: %d\n", i);
        if (str[i] == STRING_TERMINATOR) break;
    }
    
}

// Removes multiple blank and replace with single ' ' (ASCII: 32) in an character array
int blankNormalize(char str[], int size)
{
    int state = IN;
    int tempPos, blanks, i;
    tempPos = blanks = i = 0;
    char blankBool = 0;
   
   // temporary solution for early blanks bug
   while ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\t')) printf("%s early blank in: %d\n", "{similiarWords.h/wordCheck}", i++);

    // main loop
    for ( ; (size > 0) ? (i < size) : 1 ; i++)
    {
        if (str[i] == STRING_TERMINATOR) {str[tempPos] = STRING_TERMINATOR; break;} /* null terminator */
        
        blankBool = (str[i] == ' ') || (str[i] == '\n');

        if (blankBool)         {state = OUT; blanks++; }
        else if (state == OUT) { str[tempPos++] = ' '; state = IN; blanks = 0;} /* first thing to do when blankBool becomes false */

        if      (state == IN)  {str[tempPos++] = str[i];}
        else if (state == OUT) {str[tempPos] = str[i] = 0;}
    }

}


/* ========= CHARACTERS ARRAY INDEXING ============ */

int wordIndex(char text[], int index[], int indexSize)
{
    int character, n;
    character = n = 0;

    // Check the index Size
    if (indexSize <= 0) {printf("Please input the index Size properly...\n");}
    else {

        // Clean the index
        for (int i = 0; i < indexSize; i++) {index[i] = 0;}

        // assign the location of each first character per words to "index"
        for (int i = 0; text[i] != STRING_TERMINATOR; i++)
        {
            if (n >= indexSize) {printf("WARNING: Index Size not Sufficient!!!\n"); return 0;}

            character++;
            if ((text[i] == ' ') || (text[i] == '\t') || (text[i] == '\n')) { character = 0; }
            else if (character == 1) { index[n++] = i;}
        }
        
        // when the string ends
        index[n] = END_OF_INDEX;
        return n;
    }
}

/* ============ SECONDARY ARRAY ============ */
/* Collector of word returning end position of particular word
 * $ secPos  - indicates of the end position of secondary array (typically '\0')
 * $ endFlag - indicates of end character of particular word
 * $ divider - is character used for dividing words in secondary words collection
*/
int wordsCollector(char main[], char secondary[], int mainPos, int secPos, int endFlag, char divider, int secSize)
{
    char secEnd = secondary[secPos];
    (secPos != 0) ? (secondary[secPos++] = divider) : 0;
    (secSize == 0) ? (secSize = INT_MAX) : 0;


    // Non-Alphabet !(a~z) and Non-digits !(0~9) will be indicator of end of particular word
    if (endFlag == 400)
    {
        char lcharBool, ucharBool, dcharBool;
        while (secPos < secSize)
        {
            lcharBool = ((main[mainPos] >= 'a') && (main[mainPos] <= 'z'));
            ucharBool = ((main[mainPos] >= 'A') && (main[mainPos] <= 'Z'));
            dcharBool = ((main[mainPos] >= '0') && (main[mainPos] <= '9'));
            endFlag = !((lcharBool) || (ucharBool) || (dcharBool));

            if (endFlag) { secondary[secPos] = secEnd; return mainPos;}
            else {secondary[secPos++] = main[mainPos++];}
        }
        printf("Warning: Secondary array exceed maximum size!!\nPlease increase the size of the array..\n");
        return 0;
    }

    // main Loop
    while (secPos < secSize)
    {
        if (main[mainPos] == endFlag) { secondary[secPos] = secEnd; return mainPos;}
        else {secondary[secPos++] = main[mainPos++];}

    }
    printf("Warning: Secondary array exceed maximum size!!\nPlease increase the size of the array..\n");
    return 0;   
}

#endif

// EnD FLAG