#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 100

struct ReplacementRule {
    char word[MAX_WORD_LEN];
    char replacement[MAX_WORD_LEN];
};

int main() {
    // Open the file for reading
    FILE *file = fopen("1.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    struct ReplacementRule rules[MAX_RULES];
    int ruleCount = 0;

    // Read replacement rules
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '#' && sscanf(line, "#define %s %s", rules[ruleCount].word, rules[ruleCount].replacement) == 2) {
            ruleCount++;
            if (ruleCount >= MAX_RULES) {
                printf("Too many replacement rules. Increase MAX_RULES.\n");
                break;
            }
        } else {
            // Break when plain text starts
            break;
        }
    }

    // Rewind the file to read from the beginning
    fseek(file, 0, SEEK_SET);

    // Open a new file for writing
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(file);
        return 1;
    }

    // Read and substitute plain text
    while (fgets(line, sizeof(line), file) != NULL) {
        // Create a new buffer for the modified line
        char modifiedLine[MAX_LINE_LEN] = "";

        // Keep track of spaces
        char *pos = line;

        // Substitute words based on rules
        for (int i = 0; i < ruleCount; i++) {
            char *foundPos = strstr(pos, rules[i].word);
            while (foundPos != NULL) {
                // Copy the content before the found word
                strncat(modifiedLine, pos, foundPos - pos);

                // Append the replacement
                strcat(modifiedLine, rules[i].replacement);

                // Move to the end of the found word
                pos = foundPos + strlen(rules[i].word);

                // Find the next occurrence
                foundPos = strstr(pos, rules[i].word);
            }
        }

        // Append the remaining content
        strcat(modifiedLine, pos);

        // Write the modified line to the output file
        fputs(modifiedLine, outputFile);
    }

    // Close the files
    fclose(file);
    fclose(outputFile);

    return 0;
}
