#include <stdio.h>

typedef struct {
    int x, y;
} point;
int main() {
    point p = {3, 5};
    printf("%d\n",p.x);
}