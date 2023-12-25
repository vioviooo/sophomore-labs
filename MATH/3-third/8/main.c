#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure to represent a term in a polynomial
typedef struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
} Term;

// Structure to represent a polynomial
typedef struct Polynomial {
    Term* head;
} Polynomial;

// Function to initialize an empty polynomial
Polynomial* initializePolynomial() {
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    poly->head = NULL;
    return poly;
}

// Function to insert a term into a polynomial
void insertTerm(Polynomial* poly, int coefficient, int exponent) {
    Term* newTerm = (Term*)malloc(sizeof(Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = poly->head;
    poly->head = newTerm;
}

// Function to print a polynomial
void printPolynomial(Polynomial* poly) {
    Term* current = poly->head;
    while (current != NULL) {
        printf("%+dx^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

// Function to evaluate a polynomial at a given value
int evaluatePolynomial(Polynomial* poly, int x) {
    int result = 0;
    Term* current = poly->head;
    while (current != NULL) {
        result += current->coefficient * (int)pow(x, current->exponent);
        current = current->next;
    }
    return result;
}

// Function to perform polynomial addition
Polynomial* addPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial* result = initializePolynomial();
    Term* current1 = poly1->head;
    Term* current2 = poly2->head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            insertTerm(result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            insertTerm(result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        } else {
            // Add coefficients when exponents are equal
            insertTerm(result, current1->coefficient + current2->coefficient, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // Add remaining terms from both polynomials
    while (current1 != NULL) {
        insertTerm(result, current1->coefficient, current1->exponent);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        insertTerm(result, current2->coefficient, current2->exponent);
        current2 = current2->next;
    }

    return result;
}

// Function to perform polynomial subtraction
Polynomial* subtractPolynomials(Polynomial* poly1, Polynomial* poly2) {
    // Negate coefficients of poly2 and add
    Polynomial* negPoly2 = initializePolynomial();
    Term* current = poly2->head;
    while (current != NULL) {
        insertTerm(negPoly2, -(current->coefficient), current->exponent);
        current = current->next;
    }

    Polynomial* result = addPolynomials(poly1, negPoly2);
    free(negPoly2);

    return result;
}

// Function to perform polynomial multiplication
Polynomial* multiplyPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial* result = initializePolynomial();
    Term* current1 = poly1->head;
    while (current1 != NULL) {
        Term* current2 = poly2->head;
        while (current2 != NULL) {
            int coeff = current1->coefficient * current2->coefficient;
            int exp = current1->exponent + current2->exponent;
            insertTerm(result, coeff, exp);
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return result;
}

// Function to perform polynomial division
Polynomial* dividePolynomials(Polynomial* poly1, Polynomial* poly2) {
    // TODO: Implement polynomial division
    return NULL;
}

// Function to perform polynomial modulo
Polynomial* modPolynomials(Polynomial* poly1, Polynomial* poly2) {
    // TODO: Implement polynomial modulo
    return NULL;
}

// Function to find the derivative of a polynomial
Polynomial* differentiatePolynomial(Polynomial* poly) {
    Polynomial* result = initializePolynomial();
    Term* current = poly->head;
    while (current != NULL) {
        if (current->exponent > 0) {
            int coeff = current->coefficient * current->exponent;
            int exp = current->exponent - 1;
            insertTerm(result, coeff, exp);
        }
        current = current->next;
    }
    return result;
}

// Function to perform polynomial composition
Polynomial* composePolynomials(Polynomial* poly1, Polynomial* poly2) {
    // TODO: Implement polynomial composition
    return NULL;
}

// Function to free memory allocated for a polynomial
void freePolynomial(Polynomial* poly) {
    Term* current = poly->head;
    while (current != NULL) {
        Term* temp = current;
        current = current->next;
        free(temp);
    }
    free(poly);
}

Term* parseTerm(char* termStr) {
    Term* term = (Term*)malloc(sizeof(Term));
    term->coefficient = 0;
    term->exponent = 0;

    // Parse the coefficient
    sscanf(termStr, "%dx", &(term->coefficient));

    // Check if there is an exponent
    char* exponentPtr = strchr(termStr, '^');
    if (exponentPtr != NULL) {
        sscanf(exponentPtr + 1, "%d", &(term->exponent));
    }

    return term;
}

// Function to parse a polynomial from a string
Polynomial* parsePolynomial(char* polyStr) {
    Polynomial* poly = initializePolynomial();

    char* termStr = strtok(polyStr, "+-");
    while (termStr != NULL) {
        // Determine the sign of the term
        int sign = 1;
        if (polyStr[0] == '-') {
            sign = -1;
        }

        // Parse the term and insert it into the polynomial
        Term* term = parseTerm(termStr);
        term->coefficient *= sign;
        insertTerm(poly, term->coefficient, term->exponent);
        free(term);

        // Move to the next term
        termStr = strtok(NULL, "+-");
    }

    return poly;
}

int main() {
    // Initialize the accumulator (sum) polynomial
    Polynomial* accumulator = initializePolynomial();

    // Process instructions from the file
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* instruction = strtok(line, " \t\n");
        if (instruction == NULL || instruction[0] == '%') {
            // Skip comments
            continue;
        }

        if (strcmp(instruction, "Add") == 0) {
            // Addition instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            accumulator = addPolynomials(poly1, poly2);
            printPolynomial(accumulator);
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else if (strcmp(instruction, "Sub") == 0) {
            // Subtraction instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            accumulator = subtractPolynomials(poly1, poly2);
            printPolynomial(accumulator);
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else if (strcmp(instruction, "Mult") == 0) {
            // Multiplication instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            accumulator = multiplyPolynomials(poly1, poly2);
            printPolynomial(accumulator);
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else if (strcmp(instruction, "Div") == 0) {
            // Division instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            // TODO: Call dividePolynomials function
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else if (strcmp(instruction, "Mod") == 0) {
            // Modulo instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            // TODO: Call modPolynomials function
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else if (strcmp(instruction, "Eval") == 0) {
            // Evaluation instruction
            char* value_str = strtok(NULL, ";");
            int value = atoi(value_str);
            int result = evaluatePolynomial(accumulator, value);
            printf("Result: %d\n", result);
        } else if (strcmp(instruction, "Diff") == 0) {
            // Differentiation instruction
            accumulator = differentiatePolynomial(accumulator);
            printPolynomial(accumulator);
        } else if (strcmp(instruction, "Cmps") == 0) {
            // Composition instruction
            char* poly1_str = strtok(NULL, ",");
            char* poly2_str = strtok(NULL, ";");
            Polynomial* poly1 = parsePolynomial(poly1_str);
            Polynomial* poly2 = parsePolynomial(poly2_str);
            // TODO: Call composePolynomials function
            freePolynomial(poly1);
            freePolynomial(poly2);
        } else {
            printf("Unknown instruction: %s\n", instruction);
        }
    }

    // Free memory
    freePolynomial(accumulator);
    fclose(file);

    return 0;
}
