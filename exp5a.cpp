#include <iostream.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

class HilbertCurve {
private:
    // Rotate/translate a point 90 degrees
    void rot(int n, int &x, int &y, int rx, int ry) {
        if (ry == 0) {
            if (rx == 1) {
                x = n - 1 - x;
                y = n - 1 - y;
            }
            
            // Swap x and y
            int t = x;
            x = y;
            y = t;
        }
    }

public:
    // Structure to hold points instead of vector and pair
    struct Point {
        int x, y;
    };

    // Generate Hilbert curve coordinates
    Point* generateCurve(int order, int &totalPoints, int scale = 1) {
        int n = 1 << order;  // 2^order
        totalPoints = n * n;
        
        // Dynamically allocate points
        Point* points = new Point[totalPoints];
        
        for (int d = 0; d < totalPoints; d++) {
            int x = d % n;
            int y = d / n;
            
            // Compute Hilbert curve coordinates
            int rx, ry, s = 1;
            int dx = 0, dy = 0;
            
            for (s = 1; s < n; s *= 2) {
                rx = 1 & (d >> 1);
                ry = 1 & (d ^ rx);
                
                rot(s, x, y, rx, ry);
                
                dx += s * rx;
                dy += s * ry;
            }
            
            // Store point
            points[d].x = dx * scale;
            points[d].y = dy * scale;
        }
        
        return points;
    }

    // Visualize Hilbert curve using line drawing
    void visualizeCurve(int order, int scale = 10) {
        // Initialize graphics
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
        
        // Check for graphics initialization error
        int errorcode = graphresult();
        if (errorcode != grOk) {
            cout << "Graphics error: " << grapherrormsg(errorcode) << endl;
            return;
        }

        // Generate Hilbert curve points
        int totalPoints;
        Point* points = generateCurve(order, totalPoints, scale);

        // Draw lines connecting Hilbert curve points
        for (int i = 1; i < totalPoints; ++i) {
            line(
                points[i-1].x,
                points[i-1].y,
                points[i].x,
                points[i].y
            );
        }

        // Free dynamically allocated memory
        delete[] points;

        // Wait for user input
        getch();
        closegraph();
    }
};

void main() {
    HilbertCurve hilbert;
    
    // Clear screen
    clrscr();

    // Demonstrate Hilbert Curve generation
    cout << "Generating Hilbert Curve Coordinates:" << endl;

    // Example of generating points for different orders
    for (int order = 1; order <= 4; ++order) {
        cout << "\nOrder " << order << " Hilbert Curve Points:" << endl;
        
        // Generate points
        int totalPoints;
        HilbertCurve::Point* points = hilbert.generateCurve(order, totalPoints);

        // Print points
        for (int i = 0; i < totalPoints; ++i) {
            cout << "(" << points[i].x << ", " << points[i].y << ") ";
        }
        cout << endl;

        // Free memory
        delete[] points;
    }

    // Visualize the curve
    cout << "\nPress any key to visualize Hilbert Curve..." << endl;
    getch();
    hilbert.visualizeCurve(4);
}