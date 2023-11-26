#ifndef PROMPTBUFFER_H
#define PROMPTBUFFER_H

#include <stdio.h>

#define CLR_INBUF while (getchar() != '\n')

int clearBufferedPrompt(char substitute, char falseReturnValue)
{
    char temp, text;
    int buffered = 0;
    // Because all input remain buffered before "enter / return" key pressed (ASCII = Newline '\n')
    while ((temp = getchar()) != '\n') {text = temp; buffered++;}

    return (buffered <= 1) && (text == substitute) ? text : falseReturnValue;
}

int clearBufferedPrompt2(char substitute1, char substitude2, char falseReturnValue)
{
    char temp, text;
    int buffered = 0;
    // Because all input remain buffered before "enter / return" key pressed (ASCII = Newline '\n')
    while ((temp = getchar()) != '\n') {text = temp; buffered++;}

    return (buffered <= 1) && ((text == substitute1) || (text == substitude2)) ? text : falseReturnValue;
}

int clearBufferedText(char falseReturnValue)
{
    char temp, text;
    int buffered = 0;
    // Because all input remain buffered before "enter / return" key pressed (ASCII = Newline '\n')
    while ((temp = getchar()) != '\n') {text = temp; ++buffered;}
    return (buffered == 1) ? text : falseReturnValue; 
}

#endif
