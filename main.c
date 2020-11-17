#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int file;

int randomint() {
  int *j;
  int k = read(file, j, sizeof(j));
  return *j;
}

int main() {
  file = open("/dev/random", O_RDONLY);
  if (file==-1) {
    printf("Error #: %d\tError: %s\n", errno, strerror(errno));
    return 0;
  }
  int array[10];
  int i;
  for (i=0; i<5; i++) {
    array[i] = randomint();
  }
  printf("Generating Random Numbers:\n");
  for (i=0; i<10; i++) {
    printf("array[%d]: %d\n", i, array[i]);
  }
  printf("\nWriting numbers to file...\n");
  int file2 = open("randfile.txt", O_CREAT | O_WRONLY, 0664);
  int writ = write(file2, array, sizeof(array));
  if (writ==-1) {
    printf("Error #: %d\tError: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("\nReading numbers from file...\n");
  int array2[10];
  int file3 = open("randfile.txt", O_RDONLY);
  int rea = read(file3, array2, sizeof(array2));
  if (rea==-1) {
    printf("Error #: %d\tError: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("\nVerification that written values were the same:\n");
  for (i=0; i<10; i++) {
    printf("array2[%d]: %d\n", i, array2[i]);
  }
  return 0;
}
