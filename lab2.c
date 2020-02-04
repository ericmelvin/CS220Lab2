#include <stdio.h>

unsigned long interleaveBitwise(unsigned int i1, unsigned int i2);
unsigned long interleavePointer(unsigned int i1, unsigned int i2);
int main() {
	unsigned int i1 = 0x12345678;
	unsigned int i2 = 0xdeadbeef;
	printf("0x%x, 0x%x, 0x%x\n", i1, i2, interleavePointer(i1,i2));
	
	
	return 0;
}

unsigned long interleaveBitwise(unsigned int i1, unsigned int i2) {
	unsigned long result;

	
	//i1 = i1>>24;
	
	i1 = i1<<24;
	printf("%x\n", i1);

	// Get first two bytes of i1
	// Append to char array
	// Get first two bytes of i2
	// Append to char array
	char charArray[16];
	unsigned int temp1;
	unsigned int temp2;
	int rshiftamt = 24;
	int lshiftamt = 0;
	for (int i=0; i<16; i++) {
		temp1 = i1;
		temp2 = i2;
		temp1 = i1<<lshiftamt;
		temp2 = i2<<lshiftamt;
		temp1 = i1>>rshiftamt;
		temp2 = i2>>rshiftamt;
		
		rshiftamt -= 8;
		lshiftamt += 8;
		charArray[i] = temp1;
		i++;
		charArray[i] = temp2;
	}
}

// using pointers
unsigned long interleavePointer(unsigned int i1, unsigned int i2) {
	unsigned char *pi2 = (char *) &i2;
 	unsigned char *pi1 = (char *) &i1;
	for (int i=0; i<4; i++) {
		printf("%x\n", pi1[i]);
		printf("%x\n", pi2[i]);
		
	}
	
}

