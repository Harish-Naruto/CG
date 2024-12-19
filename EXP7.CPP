#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

class Ball {
private:
    int x, y;      // Current position
    int maxX, maxY; // Screen boundaries
    int radius;    // Ball radius
    int color;     // Ball color

public:
    // Constructor
    Ball(int startX, int startY, int screenWidth, int screenHeight) {
        x = startX;
        y = startY;
        maxX = screenWidth;
        maxY = screenHeight;
        radius = 10;
        color = WHITE;
    }

    // Move ball based on direction
    void move(int dx, int dy) {
        // Calculate new position
        int newX = x + dx;
        int newY = y + dy;

        // Boundary checking for X
        if (newX >= radius && newX < maxX - radius) {
            x = newX;
        }

        // Boundary checking for Y
        if (newY >= radius && newY < maxY - radius) {
            y = newY;
        }
    }

    // Draw ball on screen
    void draw() {
        // Clear previous drawing
        cleardevice();

        // Set drawing color
        setcolor(color);

        // Draw ball as a circle
        circle(x, y, radius);

        // Draw boundary
        rectangle(0, 0, maxX, maxY);

        // Display current position
        char posText[50];
        sprintf(posText, "Position: X=%d, Y=%d", x, y);
        outtextxy(10, maxY - 20, posText);
    }

    // Get current X position
    int getX() { return x; }

    // Get current Y position
    int getY() { return y; }
};

int main() {
    int gdriver = DETECT, gmode, errorcode;

    // Initialize graphics
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    // Check for graphics initialization error
    errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        return 1;
    }

    // Get screen dimensions
    int width = getmaxx();
    int height = getmaxy();

    // Create ball in center of screen
    Ball ball(width/2, height/2, width, height);

    int ch;
    while ((ch = getch()) != 27) {  // ESC key to exit
        switch(ch) {
            case 72:  // Up arrow
                ball.move(0, -10);
                break;
            case 80:  // Down arrow
                ball.move(0, 10);
                break;
            case 75:  // Left arrow
                ball.move(-10, 0);
                break;
            case 77:  // Right arrow
                ball.move(10, 0);
                break;
        }

        // Redraw ball
        ball.draw();

        // Small delay to control game speed
        delay(50);
    }

    // Close graphics
    closegraph();

    return 0;
}