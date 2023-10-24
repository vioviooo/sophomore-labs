#include <stdbool.h>
#include <math.h>
#include <stdio.h>


typedef struct {
    double x;
    double y;
} Point;

// Function to check if there are overlapping points in the array with tolerance
bool is_overlap(Point points[], int n, double tolerance) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double x_diff = fabs(points[i].x - points[j].x);
            double y_diff = fabs(points[i].y - points[j].y);
            
            if (x_diff <= tolerance && y_diff <= tolerance) {
                return false; // Found an overlapping point
            }
        }
    }
    return true; // No overlapping points found
}

int main() {
    Point coord1 = {-3.5, -2.5};
    Point coord2 = {-3.5, -6.5};
    Point coord3 = {0.5, -6.5};
    Point coord4 = {0.5, -6.5};
    
    Point points[] = {coord1, coord2, coord3, coord4};
    int n = sizeof(points) / sizeof(points[0]);
    
    double tolerance = 1e-6; // Adjust the tolerance based on your requirements
    
    if (is_overlap(points, n, tolerance)) {
        printf("No overlapping points found.\n");
    } else {
        printf("Overlapping points detected.\n");
    }
    
    return 0;
}
