#ifndef MAIN_SCREEN_OUTPUT
#define MAIN_SCREEN_OUTPUT

#include <stdio.h>
#include "Library/Standard_Constants.h"

// Graphics Buffer prototype
#define PIXEL_LENGTH    25  /* x length */
#define PIXEL_HEIGHT    20  /* y height */
#define PIXEL_STRENGTH  15  /* total strength value available per pixel */
#define LENGTH_MODIFIER 3   /* to take account the difference of space taken by newline '\n' and blank ' ' */

#define BLANK_STRENGTH  1

#define OUTPUT_SCALE    1.0 /* screen output scaling (n : 1) */
#define X_OUTPUT_SCALE  1.0 /* x (length) screen output scaling (n : 1) */
#define Y_OUTPUT_SCALE  1.0 /* y (length) screen output scaling (n : 1) */

#define DRAW_PIXEL(X, Y, Strength)  MAIN_GRAPHICS_BUFFER[Y][X] = Strength

#define WITH_COORD_VALUE    TRUE
char char_strength[20] = " .':;!|@&#";


int MAIN_GRAPHICS_BUFFER[PIXEL_HEIGHT][PIXEL_LENGTH * LENGTH_MODIFIER];

// output the buffer to the terminal
void main_Graphics_Buffer_Output(){
    int output = 0;
    char fin = 0;

    /* y coordinates (-1 for compensation of array index) */
    for (int y = (PIXEL_HEIGHT - 1); y >= 0 ; y--)
    {
        /* x coordinates */
        for (int x = 0; x < (PIXEL_LENGTH * LENGTH_MODIFIER); x++)
        {
            output = MAIN_GRAPHICS_BUFFER[y][x];
            putchar(char_strength[output]);
        }

        // newline for next y output
        // printf(" |%d", y);
        putchar('\n');
    }
    
}

void buffer_refresh() {
    for (int y = 0; y < PIXEL_HEIGHT; y++)
        for (int x = 0; x < (PIXEL_LENGTH * LENGTH_MODIFIER); x++)
            DRAW_PIXEL(x,y,BLANK_STRENGTH);
}

void drawCircle(float radius, float x_offset, float y_offset, int output_Strength) {
    float c_Equation;   /* (y*y) - (x*x) = r^2 */
    float x_pos, y_pos;
    float radius_sq = radius * radius;


    // radius = sqrt((y*y) - (x*x));

    // modify the graphics buffer
    for (int y = 0; y < PIXEL_HEIGHT; y++)
    {
        for (int x = 0; x < (PIXEL_LENGTH * LENGTH_MODIFIER); x++)
        {
            x_pos = powf((x - x_offset) / 2.5, 2);
            y_pos = powf((y - y_offset), 2);
            if ((x_pos + y_pos) <= radius_sq) 
                DRAW_PIXEL(x, y, output_Strength);
        }
        
    }
    


}

#include <windows.h>

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void cls( HANDLE hConsole )
{
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
}
#endif