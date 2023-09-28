#include <stdio.h>
#include <math.h>

enum convergence_status_codes {
    csc_okay,
    csc_error
};

enum convergence_status_codes third(double x, double eps, double* res) {
    if (fabs(x) - 1.0 >= eps) {
        return csc_error;
    }
    else {
        // enum convergence_status_codes check_status_code = csc_okay;
    
        double elem = 1.0, last = 1.0, curr = 2.0, next = 3.0;
        
        for (int n = 1; fabs(elem) > eps; n++) {
            elem *= 27.0 * x * x * n * n * n / (last * curr * next);
            *res += elem;
            last += 3.0;
            curr += 3.0;
            next += 3.0;
        }
        return csc_okay;
    }
}

int main() {
    double result = 1.0;
    double epsilon = 1e-6;
    enum convergence_status_codes status = third(0.5, epsilon, &result);

    if (status == csc_okay) {
        printf("Converged successfully. Result: %lf\n", result);
    }
    else if (status == csc_error) {
        printf("Convergence error.\n");
    }

    return 0;
}
