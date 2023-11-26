
/* ======= Fundamental Functions ======= */

STD_AVAILABLE int strlen_h(register const unsigned char *str);
STD_AVAILABLE int strcmp_h(register const unsigned char *str, register const unsigned char *str2);

int cfind(reg const char* str, reg const char c);
int cfind_s(reg const char* str, reg unsigned int len, reg const char c);

int getline(reg unsigned char* str);
DEFCON_ALPHA int getline_s(reg unsigned char* str, unsigned int size);

TEMP int getch_line(reg char* str, reg uint16_t mode, const char extraInput[], const char output);
TEMP int getch_line_s(char* str, uint16_t size, register uint16_t mode, const char extraInput[], const char output);
