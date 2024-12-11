#include <stdio.h>
#include <stdlib.h>
#include "pbPlots.h"
#include "supportLib.h"

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RED  "\x1b[31m"
int count = 0;

float power(float a, int b) {
    float mul = 1;
    if (b > 0) {
        // for finding positive powers
        for (int i = 0; i < b; i++) {
            mul *= a;
        }
    } else if (b < 0) {
        // for finding negative powers
        for (int i = b; i < 0; i++) {
            mul /= a;
        }
    }
    return mul;
}

float mod(float a) {
    if (a < 0)
        return -1 * a;
    else
        return a;
}


void update(float a[], int n, int d) {
    if (d == 0)
        return;
    for (int i = n; i >= count; i--) {
        a[i] = a[i] * (i - count);
    }
    count++;
    update(a, n, d - 1);
}


void Ndiff(float a[], int n) {
    printf(ANSI_COLOR_CYAN "ENTER THE NUMBER OF TIMES YOU WANT TO DIFFERENTIATE THE FUNCTION: " ANSI_COLOR_RESET);
    int k;
    scanf("%d", &k);
    update(a, n, k);
    if (k > n) {
        printf("THE VALUE OF %dth DIFFERENTIAL IS ZERO\n", k);
        return;
    }
    printf("THE REQUIRED DIFFERENTIATED POLYNOMIAL IS: ");
    for (int i = k; i < n + 1; i++) {
        if (i == k)
            printf("(%.2f)*X^%d", a[i], i - k);
        else
            printf(" + (%.2f)*X^%d", a[i], i - k);
    }
    printf("\n");
    printf(ANSI_COLOR_CYAN "ENTER THE VALUE AT WHICH YOU WHAT TO FIND THE VALUE OF THE Nth DIFFERENTIAL = " ANSI_COLOR_RESET);
    float v;
    scanf("%f", &v);
    float sum = 0;
    for (int i = k; i < n + 1; i++) {
        sum += a[i] * power(v, (i - k));
    }
    printf("THE REQUIRED VALUE IS %f", sum);
}


float evaluate(float a[], int n, float m) {
    // it evaluates the function at a point m
    float sum = 0;
    for (int i = 0; i < n + 1; i++) {
        sum += a[i] * power(m, i);
    }
    return sum;
}


float d(float a[], int n, float m) {
    // differentiate the function at a point and returns the corresponding values
    float b[n + 1];
    for (int i = 0; i < n + 1; i++) {
        b[i] = a[i] * i;
    }
    float sum = 0;
    for (int i = 1; i < n + 1; i++) {
        sum += b[i] * power(m, i - 1);
    }
    return sum;
}


float roots(float a[], int n, float m, int count, int p) {
    // using newtons and raphsons method recursively we are aiming to find root of an given polynomial
    if (count == 0) {
        return 1729.1729;
    }
    // new root = guessed root - value of the function at the guessed root
    //                           (divided by)value of the differential function at the guessed root

    float val = evaluate(a, n, m);
    float diff = d(a, n, m);
    float c = val / diff;
     if (diff == 0)    return 1729.1729;
    // recursively calling the function until the c value is below tolerance value
    if (mod(val) <= power(10, -p))
        return m;
    return roots(a, n, (m - c), count - 1, p);
}


void diff(float a[], int n) {
    printf(ANSI_COLOR_CYAN "DIFFERETIATION:>\n" ANSI_COLOR_RESET);
    float point;
    float b[n + 1];
    printf("ENTER THE POINT FOR WHICH YOU WHAT TO FIND DIFFERENTIAL = ");
    scanf("%f", &point);
    for (int i = 0; i < n + 1; i++) {
        if (i == 0)
            continue;
        else {
            b[i] = a[i] * i;
        }
    }
    printf("\n");
    printf("THE REQUIRED DIFFERENTIATED POLYNOMIAL IS =");
    for (int i = 1; i < n + 1; i++) {
        if (i == 1)
            printf(" (%.2f)*X^%d", b[i], i - 1);
        else
            printf(" + (%.2f)*X^%d", b[i], i - 1);
    }
    float sum = 0;
    for (int i = 1; i < n + 1; i++) {
        sum += b[i] * power(point, i - 1);
    }
    printf("\nTHE REQUIRED DIFFERENTIAL IS = %f", sum);
    return;
}


void integral(float a[], int n) {
    printf(ANSI_COLOR_CYAN "INTEGRATION :>\n" ANSI_COLOR_RESET);
    double lower, upper;
    printf("ENTER THE LOWER LIMIT = ");
    scanf("%lf", &lower);
    printf("ENTER THE UPPER LIMIT = ");
    scanf("%lf", &upper);
    float b[n + 1];
    printf("\n");
    printf("THE REQUIRED INTEGRAL POLYNOMIAL IS HERE = ");
    printf("c");
    for (int i = 0; i <= n; i++) {
        b[i] = a[i] / (i + 1);
        printf(" + (%.2f)*X^%d", b[i], i + 1);
    }
    printf("\n");
    float sumlow = 0;
    for (int l = 0; l <= n; l++) {
        sumlow += b[l] * (power(lower, l + 1));
    }
    float sumup = 0;
    for (int l = 0; l <= n; l++) {
        sumup += b[l] * (power(upper, l + 1));
    }
    printf("THE INTEGRATION OF THE POLYNOMIAL WITH THE UPPER AND LOWER BOUND AS %.3f AND %.3f == %.5f", upper, lower, sumup - sumlow);
    return;
}


int main() {
    char c;
    printf(ANSI_COLOR_CYAN "  ________________________\n");
    printf("  |...IC MINOR PROJECT...|\n");
    printf("  ________________________\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW " ----------------------------\n");
    printf(" |.....PRESS 1 FOR MENU.....|\n");
    printf(" |....PRESS 2 FOR ABOUT.....|\n");
    printf(" |..PRESS ANY KEY TO START..|\n");
    printf(" ----------------------------\n\n" ANSI_COLOR_RESET);
    printf("        " ANSI_COLOR_MAGENTA "|..PRESS..|  = " ANSI_COLOR_RESET);
    scanf("%c", &c);
    printf("\n");

    if (c == (char)49) {
        printf(ANSI_COLOR_YELLOW "****************************************\n");
        printf("#    AFTER INPUTING THE POLYNOMIAL:    #\n");
        printf("#______________________________________#\n");
        printf("#       PRESS 1 for INTEGRATION        #\n");
        printf("#     PRESS 2 for DIFFERENTIATION      #\n");
        printf("#  PRESS 3 for N'thPUL DIFFERENTIATION #\n");
        printf("#      PRESS 4 for finding a ROOT      #\n");
        printf("#     PRESS 5 for GRAPHPRINTING        #\n");
        printf("****************************************\n\n" ANSI_COLOR_RESET);
    }
    if (c == (char)50) {
        printf("\n" ANSI_COLOR_CYAN "NAME: KATHAN RAJENDRASINH ZULA\n");
        printf("ROLL NUMBER: B23CH1049\n");
        printf("BRANCH: CHEMICAL ENGINEERING \n");
        printf("BATCH: B1\n\n" ANSI_COLOR_RESET);
    }

    printf(ANSI_COLOR_CYAN "INPUT YOUR POLYNOMIAL HERE : \n" ANSI_COLOR_RESET);
    int n;
    printf(ANSI_COLOR_RED "ENTER THE DEGREE OF YOUR POLYNOMIAL = " ANSI_COLOR_RESET);
    scanf("%d", &n);
    float a[n + 1];
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf(ANSI_COLOR_CYAN"ENTER THE COEFFICIENT OF X^%d = ", i);
        scanf("%f", &a[i]);
    }
    printf("\n");
    printf("     " ANSI_COLOR_MAGENTA "|..PRESS..| = " ANSI_COLOR_RESET);
    int o;
    scanf("%d", &o);
    if (o == 1)
        integral(a, n);
    else if (o == 2)
        diff(a, n);
    else if (o == 3) {
        Ndiff(a, n);
    } else if (o == 4) {
        int k;
        printf(ANSI_COLOR_CYAN"ENTER THE GUESSED ROOT = ");
        scanf("%d", &k);
        printf(ANSI_COLOR_YELLOW"ENTER TOLERANCE LEVEL (10^-P) = ");
        float j;
        scanf("%f", &j);
        float y = roots(a, n, k, 1000, j);
        if (y != (float)1729.1729)
            printf("ROOT IS %f", y);
        else
            printf(ANSI_COLOR_RED"ROOTS DO NOT EXIST..!");
    } else if (o == 5) {
        printf(ANSI_COLOR_CYAN "GRAPH PRINTING:\n" ANSI_COLOR_RESET);
        double x[21];
        for (int i = 0; i <= 21; i++) {
            x[i] = i - 10;
        }
        double y[21];
        for (int i = 0; i <= 21; i++) {
            y[i] = evaluate(a, n, x[i]);
        }
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *error = (StringReference *)malloc(sizeof(size_t));
        DrawScatterPlot(imageRef, 1000, 1000, x, 21, y, 21, error);
        size_t length;
        double *pngData = ConvertToPNG(&length, imageRef->image);
        WriteToFile(pngData, length, "plot.png");
        printf("Graph image saved as plot.png\n");
    }

    return 0;
}
