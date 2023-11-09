#include <stdio.h>

#define N 15
#define M 13

// Function prototypes
void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);

int main()
{
   int picture_data[N][M];
   int *picture[N];

   // Set up the picture_data 2D array
   for (int i = 0; i < N; i++) {
       picture[i] = picture_data[i];
   }

   make_picture(picture, N, M);

   print_picture(picture, N, M);  // Print the picture

   return 0;
}

void make_picture(int **picture, int n, int m)
{
   // Your code to create the pattern here...

   reset_picture(picture, n, m);
   
   int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int tree_trunk[] = { 7, 7, 7, 7 };
   int tree_foliage[] = { 3, 3, 3, 3 };

   // Add code to create the pattern in the picture array

   // Frame
   for (int i = 0; i < 13; i++) {
      picture[0][i] = 1;
      picture[14][i] = 1;
   }
   for (int i = 1; i < 14; i++) {
      picture[i][0] = 1;
      picture[i][12] = 1;
   }

   // sun
   int sun_data[6][5] = { { 0, 6, 6, 6, 6 },
                          { 0, 0, 6, 6, 6 },
                          { 0, 0, 6, 6, 6 },
                          { 0, 6, 0, 0, 6 },
                          { 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0 } };

   for (int i = 1; i < 7; i++) {
      for (int j = 7; j < 12; j++) {
         picture[i][j] = sun_data[i - 1][j - 7];
      }
   }

   // tree

for (int i = 2; i < 7; i++) {
    for (int j = 3; j < 5; j++) {
        picture[i][j] = tree_foliage[0];
        if (i == 3 || i == 4) {
            picture[i][j - 1] =tree_foliage[0];
            picture[i][j + 1] =tree_foliage[0];
        }
    }
}

    for (int i = 6; i < 10; i++) {
        for (int j = 3; j < 5; j++) {
            picture[i][j] = tree_trunk[0];
        }
    }

   for (int j = 2; j < 6; j++) {
      picture[10][j] = tree_trunk[j - 2];
   }

    // border --
   for (int j = 1; j < 12; j++) {
      picture[7][j] = frame_w[0];
   }

   // border |
   for (int i = 1; i < 14; i++) {
      picture[i][6] = frame_h[0];
   }
}

void reset_picture(int **picture, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         picture[i][j] = 0;
      }
   }
}

void transform(int *buf, int **matr, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      matr[i] = buf + i * m;
   }
}

void print_picture(int **picture, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         printf("%d ", picture[i][j]);
      }
      printf("\n");
   }
}
