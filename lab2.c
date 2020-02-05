#include <stdio.h>
#include <string.h>
unsigned long interleaveBitwise(unsigned int i1, unsigned int i2);
unsigned long interleavePointer(unsigned int i1, unsigned int i2);
void printArray(unsigned char *arr, int len);
void reverseArray(unsigned char *arr);
void print_raw_bytes(char *start, unsigned int len);
unsigned long interleaveRecursion(unsigned int i1, unsigned int i2);
unsigned long ilr(unsigned long u, unsigned char* p1, unsigned char* p2, int i);
void count_ones(unsigned int n);
int main() {
	unsigned int i1 = 0x12345678;
	unsigned int i2 = 0xdeadbeef;
	printf("0x%x, 0x%x, 0x%lx\n", i1, i2, interleavePointer(i1,i2));
	printf("0x%x, 0x%x, 0x%lx\n", i1, i2, interleaveRecursion(i1,i2));
	unsigned int i = 0xc0de1234;
	print_raw_bytes((char *) &i, sizeof(i));
	
	count_ones(15);
	
	//printf(print_raw_bytes())
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
	// Cast to char array to access each individual byte (set of 2 hex chars = 1 byte);
	unsigned char *pi2 = (unsigned char *) &i2;
 	unsigned char *pi1 = (unsigned char *) &i1;
	
	// Initialize array, counters, and retval
	int arrLen = 8;
	unsigned char charArray[arrLen];
	unsigned long retval;
	int pos = 0;
	int i = 0;

	// Loop over each char Array adding it to a larger one
	while (pos < arrLen) {
		charArray[pos] = pi2[i];
		pos++;
		charArray[pos] = pi1[i];
		pos++;
		i++;
	}
	//printArray(charArray, arrLen);
	//reverseArray(charArray);
	//printArray(charArray, arrLen);

	// Convert char array representation back to unsigned long
	memcpy(&retval,charArray,sizeof(unsigned long));
	
	return retval;
}

// using recursion
unsigned long ilr(unsigned long u, unsigned char* p1, unsigned char* p2, int i) {
	if (i < 0) {
		return u;
	}
	u <<= 8;
	u |= p1[i];
	u <<= 8;
	u |= p2[i];
	return ilr(u, p1, p2, i-1);
	
}
unsigned long interleaveRecursion(unsigned int i1, unsigned int i2) {
	unsigned long u;
	unsigned char *pi1 = (unsigned char*) &i1;
	unsigned char *pi2 = (unsigned char*) &i2;
	return ilr(u, pi1, pi2, 4);
}

void printArray(unsigned char *arr, int len) {
	for(int i = 0; i < len; i++) {
		printf("%x", arr[i]);
	}
	printf("\n");
}

void reverseArray(unsigned char *arr) {
	int n = sizeof(arr)/sizeof(arr[0]);
	int end = n-1;
	int start = 0;
	unsigned char temp;
	while(start<end) {
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

void print_raw_bytes(char *start, unsigned int len) {
	// Delete preceding f's (sign bit) by casting to unsigned
	unsigned char *ustart = start;
	for (int i=0; i<len; i++) {
		printf("%p 0x%x\n", &ustart[i], ustart[i]);
	}
}

void count_ones(unsigned int n) {
	
	int ones_count = 0;
	for (int i=0; i<sizeof(n); i++) {
		if (n & 1 == 1) {
			ones_count++;
		}
		n >>= 1;
	}
	printf("ones count: %d", ones_count);
}