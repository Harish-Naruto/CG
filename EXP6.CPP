#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>  // Required for toupper function

class Stack {
private:
    int arr[10];
    int top;

public:
    Stack() { 
        top = -1; 
    }

    int isEmpty() { 
        return top == -1; 
    }

    int isFull() { 
        return top == 9; 
    }

    void push(int x) {
        if (!isFull()) {
            arr[++top] = x;
            drawStack();
        } else {
            setcolor(RED);
            outtextxy(100, 400, "Stack Overflow!");
            delay(1000);
            setcolor(BLACK);
            outtextxy(100, 400, "Stack Overflow!");
        }
    }

    int pop() {
        if (!isEmpty()) {
            int x = arr[top--];
            drawStack();
            return x;
        } else {
            setcolor(RED);
            outtextxy(100, 400, "Stack Underflow!");
            delay(1000);
            setcolor(BLACK);
            outtextxy(100, 400, "Stack Underflow!");
            return -1;
        }
    }

    void drawStack() {
        // Clear previous drawing area
        setfillstyle(SOLID_FILL, BLACK);
        bar(400, 50, 600, 350);

        // Draw stack frame
        setcolor(WHITE);
        rectangle(400, 50, 600, 350);

        // Draw stack elements
        char str[10];
        for (int i = 0; i <= top; i++) {
            // Convert number to string manually
            sprintf(str, "%d", arr[i]);  // Using sprintf instead of itoa

            // Alternate colors for elements
            if (i % 2 == 0)
                setfillstyle(SOLID_FILL, BLUE);
            else
                setfillstyle(SOLID_FILL, GREEN);

            bar(410, 340 - i * 30, 590, 310 - i * 30);

            // Display element value
            setcolor(WHITE);
            outtextxy(480, 320 - i * 30, str);
        }
    }
};

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    if (graphresult() != grOk) {
        cout << "Graphics error: " << grapherrormsg(graphresult());
        getch();
        return;
    }

    Stack s;
    char choice;

    // Draw title and instructions
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(50, 20, "Stack Visualization");
    
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(50, 70, "Controls:");
    outtextxy(50, 90, "P - Push random number");
    outtextxy(50, 110, "O - Pop number");
    outtextxy(50, 130, "Q - Quit");

    // Initial stack drawing
    s.drawStack();

    while (1) {
        choice = getch();
        
        // Manual uppercase conversion instead of toupper
        if (choice >= 'a' && choice <= 'z') {
            choice = choice - 32;  // Convert to uppercase
        }
        
        switch (choice) {
            case 'P': {
                int val = random(100);
                s.push(val);
                break;
            }
            case 'O':
                s.pop();
                break;
            case 'Q':
                closegraph();
                exit(0);
        }
    }
}