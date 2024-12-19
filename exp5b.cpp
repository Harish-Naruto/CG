#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

class KochCurve {
public:
    // Function to draw the Koch curve recursively
    void drawKochCurve(int x1, int y1, int x2, int y2, int iteration) {
        if (iteration == 0) {
            // Draw the line when no more iterations are left
            line(x1, y1, x2, y2);
        } else {
            // Calculate the points to divide the line into 3 equal parts
            long dx = x2 - x1;
            long dy = y2 - y1;

            // Divide the line into three parts
            int x3 = x1 + dx / 3;
            int y3 = y1 + dy / 3;

            int x4 = x1 + 2 * dx / 3;
            int y4 = y1 + 2 * dy / 3;

            // Calculate the peak of the equilateral triangle
            // Use long to prevent potential overflow in calculation
            long x5 = x3 + (x4 - x3) / 2 - (long)((y4 - y3) * sqrt(3.0) / 2);
            long y5 = y3 + (y4 - y3) / 2 + (long)((x4 - x3) * sqrt(3.0) / 2);

            // Recursively draw the smaller Koch curves
            drawKochCurve(x1, y1, x3, y3, iteration - 1);       // First segment
            drawKochCurve(x3, y3, x5, y5, iteration - 1);       // Triangle peak
            drawKochCurve(x5, y5, x4, y4, iteration - 1);       // Third segment
            drawKochCurve(x4, y4, x2, y2, iteration - 1);       // Final segment
        }
    }

    // Function to draw the full Koch snowflake (starting with an equilateral triangle)
    void drawKochSnowflake(int x1, int y1, int x2, int y2, int iteration) {
        // First side of the triangle
        drawKochCurve(x1, y1, x2, y2, iteration);

        // Second side of the triangle
        int x3 = (x1 + x2) / 2 + (int)((y1 - y2) * sqrt(3.0) / 2);
        int y3 = (y1 + y2) / 2 - (int)((x2 - x1) * sqrt(3.0) / 2);
        drawKochCurve(x2, y2, x3, y3, iteration);

        // Third side of the triangle
        drawKochCurve(x3, y3, x1, y1, iteration);
    }

    // Function to calculate the bounding box for the triangle to center it
    void centerKochSnowflake(int &x1, int &y1, int &x2, int &y2, int &x3, int &y3) {
        // Adjust starting points to center the Koch snowflake in the screen
        int screenWidth = getmaxx();
        int screenHeight = getmaxy();

        // Calculate the center of the screen
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;

        // Adjust the side length and calculate the coordinates of the triangle
        int sideLength = 300; // You can adjust this value based on your desired size

        // Bottom left point
        x1 = centerX - sideLength / 2;
        y1 = centerY + (int)(sideLength * sqrt(3.0) / 6);

        // Bottom right point
        x2 = centerX + sideLength / 2;
        y2 = y1;

        // Top point
        x3 = centerX;
        y3 = centerY - (int)(sideLength * sqrt(3.0) / 3);
    }
};

void main() {
    int gd = DETECT, gm;
    
    // Initialize graphics
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    
    // Check for graphics initialization error
    int errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        return;
    }

    int x1, y1, x2, y2, x3, y3;
    int iterations;

    // Create object of KochCurve class
    KochCurve k;

    // Calculate the coordinates to center the Koch snowflake
    k.centerKochSnowflake(x1, y1, x2, y2, x3, y3);

    // Prompt for iterations
    clrscr();  // Clear screen before input
    cout << "Enter the number of iterations for Koch Curve (0-5): ";
    cin >> iterations;

    // Validate input
    if (iterations < 0) iterations = 0;
    if (iterations > 5) iterations = 5;

    // Set drawing color
    setcolor(WHITE);

    // Draw the Koch snowflake fractal
    k.drawKochSnowflake(x1, y1, x2, y2, iterations);

    // Wait for user input before closing the graphics window
    getch();
    
    // Close graphics
    closegraph();
}