#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#define uint unsigned int

int xor8(FILE* input_file) {
    int result = 0, byte;
    while ((byte = fgetc(input_file)) != EOF) {
        result ^= byte;
    }

    return result;
}

int xor32(FILE* inp) {
    int ans = 0;
    unsigned char buffer[4];

    while (fread(buffer, 4, 1, inp) == 1) {
        int num = 0;
        num = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
        ans ^= num;
    }

    return ans;
}

int mask(FILE* file, int mask) {
    unsigned char buff[4] = {0};
    int count = 0;
    while (fread(buff, sizeof(unsigned char), 4, file) == 4) {
        int tmp = *(int*)buff;
        if ((tmp & mask) == mask) {
            count++;
        }
    }

    return count;
}

#endif
