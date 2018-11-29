#include <iostream>
#include <bitset>
//#include <emmintrin.h>
// #include <xmmintrin.h>
#include <immintrin.h>
#include <fstream>

using namespace std;

int const bitsSortedOn = 3;

void printBinaryArray(int *arr, int n) {
	for (int i=0; i<n; i++) {
		cout << bitset<32>(arr[i]) << endl;
	}
}

void printBucketArray(int *matrix, int n, int *freq, int bitsSortedOn) {
	int buckets = 1 << bitsSortedOn;
	for (int i = 0; i < buckets; i++) {
		int bucketOffset = i * n, j = 0;
		cout << "printing contents of bucket " << i << endl;
		while (j < freq[i]) {
			cout << "    " << hex << matrix[bucketOffset + j++] << endl;
		}
	}
	cout << endl;
}

void printHexArray(int *arr, int n) {
	for (int i=0; i<n; i++) {
		cout << hex << arr[i] << endl;
	}
}

void printArray(int *arr, int n) {
	for (int i=0; i<n; i++) {
		cout << arr[i] << endl;
	}
}

int radixSort(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int *freq = (int *) calloc(buckets, sizeof(int));
	int *tmp = (int *) malloc(sizeof(int) * size);
	int shift = 0;

	while (shift < 32) {
		for (int i=0; i<size; i++) { // count frequencies
			freq[(arr[i] >> shift) & bitMask]++; }
		for (int i=1; i<buckets; i++) { // sum frequencies
			freq[i] += freq[i-1]; }
		for (int i=size-1; i >= 0; i--) { // move nodes correct loc in tmp array
			int index = --freq[(arr[i] >> shift) & bitMask];
			tmp[index] = arr[i]; 
			// _mm_stream_si32(&tmp[index], arr[i]);
		}
		for (int i=0; i<buckets; i++) { // set frequencies to 0
			freq[i] = 0; }
		for (int i=0; i<size; i++) { // copy from tmp back to arr
			arr[i] = tmp[i]; }
		shift += bitsSortedOn;
	}

	free(tmp);
	free(freq);

	return 0;
}

// optimized standard radix sort without copy back
int radixSortWoCopyBack(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int *freq = (int *) calloc(buckets, sizeof(int));
	int *tmp = (int *) malloc(sizeof(int) * size);
	int shift = 0;
	bool exitedEarly = false;

	while (shift < 32) {
		for (int i=0; i<size; i++) { // count frequencies
			freq[(arr[i] >> shift) & bitMask]++; }
		for (int i=1; i<buckets; i++) { // sum frequencies
			freq[i] += freq[i-1]; }
		for (int i=size-1; i >= 0; i--) { // move nodes correct loc in tmp array
			tmp[--freq[(arr[i] >> shift) & bitMask]] = arr[i]; }
		for (int i=0; i<buckets; i++) { // set frequencies to 0
			freq[i] = 0; }

		shift += bitsSortedOn;
		if (!(shift < 32)) { exitedEarly = true; break; }

		for (int i=0; i<size; i++) { // count frequencies
			freq[(tmp[i] >> shift) & bitMask]++; }
		for (int i=1; i<buckets; i++) { // sum frequencies
			freq[i] += freq[i-1]; }
		for (int i=size-1; i >= 0; i--) { // move nodes to correct loc in arr
			arr[--freq[(tmp[i] >> shift) & bitMask]] = tmp[i]; }
		for (int i=0; i<buckets; i++) { // set frequencies to 0
			freq[i] = 0; }
		shift += bitsSortedOn;

	}
	if (exitedEarly) {
		for (int i=0; i<size; i++) {
			arr[i] = tmp[i];
		}
	}
	free(tmp); free(freq);

	return 0;
}

int radixSortWoCopyBack8Bit(int *arr, int size) {
	int freq[256] = {0};
	int *tmp = (int *) malloc(sizeof(int *) * size);

	// iteration 1
	for (int i=0; i<size; i++) { // count frequencies
		freq[((unsigned char *)(&arr[i]))[0]]++; }
	for (int i=1; i<256; i++) { // sum frequencies
		freq[i] += freq[i-1]; }
	for (int i=size-1; i >= 0; i--) { // move nodes correct loc in tmp array
		tmp[--freq[((unsigned char *)(&arr[i]))[0]]] = arr[i]; }
	for (int i=0; i<256; i++) { // set frequencies to 0
		freq[i] = 0; }

	// iteration 2
	for (int i=0; i<size; i++) {
		freq[((unsigned char *)(&tmp[i]))[1]]++; }
	for (int i=1; i<256; i++) {
		freq[i] += freq[i-1]; }
	for (int i=size-1; i >= 0; i--) {
		arr[--freq[((unsigned char *)(&tmp[i]))[1]]] = tmp[i]; }
	for (int i=0; i<256; i++) {
		freq[i] = 0; }

	// iteration 3
	for (int i=0; i<size; i++) { // count frequencies
		freq[((unsigned char *)(&arr[i]))[2]]++; }
	for (int i=1; i<256; i++) { // sum frequencies
		freq[i] += freq[i-1]; }
	for (int i=size-1; i >= 0; i--) { // move nodes correct loc in tmp array
		tmp[--freq[((unsigned char *)(&arr[i]))[2]]] = arr[i]; }
	for (int i=0; i<256; i++) { // set frequencies to 0
		freq[i] = 0; }

	for (int i=0; i<size; i++) {
		freq[((unsigned char *)(&tmp[i]))[3]]++; }
	for (int i=1; i<256; i++) {
		freq[i] += freq[i-1]; }
	for (int i=size-1; i >= 0; i--) {
		arr[--freq[((unsigned char *)(&tmp[i]))[3]]] = tmp[i]; }
	for (int i=0; i<256; i++) {
		freq[i] = 0; }

	free(tmp);
	return 0;
}

// Count all frequencies first, then move stuff around
int radixSortFreqFirst(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	// ceiling, works for values between 1-16 but kinda silly
	int const passes = 32.0/bitsSortedOn + 0.99; 
	int freq[passes][buckets];
	for (int i=0; i<passes; i++)
		for (int j=0; j<buckets; j++)
			freq[i][j] = 0;
	int *tmp = (int *) malloc(sizeof(int) * size);
	bool exitedEarly = false;
	int shifts[passes];
	shifts[0] = 0;
	for (int i = 1; i < passes; i++) {
		shifts[i] = shifts[i-1] + bitsSortedOn;
	}

	// Calculate frequencies for every pass at the same time
	for (int elem = 0; elem < size; elem++) {
		for (int pass = 0; pass < passes; pass++) { // loop unrolling if we know #passes
			// freq[pass][(arr[elem] >> (bitsSortedOn * pass)) & bitMask]
			freq[pass][(arr[elem] >> shifts[pass]) & bitMask]++;
		}
	}
	// Sum the frequencies
	for (int i=0; i<passes; i++)
		for (int j=1; j<buckets; j++)
			freq[i][j] += freq[i][j-1];

	int shift = 0; // don't use shift array as not in cache
	for (int pass = 0; pass < passes; pass++) {
		int *currFreq = freq[pass];
		for (int elem = size-1; elem >= 0; elem--) {
			int index = --currFreq[(arr[elem] >> shift) & bitMask];
			tmp[index] = arr[elem];
		}

		pass++;
		shift += bitsSortedOn;
		currFreq = freq[pass];
		if (!(pass < passes)) { exitedEarly = true; break; }

		for (int elem = size-1; elem >= 0; elem--) {
			int index = --currFreq[(tmp[elem] >> shift) & bitMask];
			arr[index] = tmp[elem];
		}
		shift += bitsSortedOn;
	}
	// move from tmp to arr if unequal number of passes
	if (exitedEarly) {
		for (int elem=0; elem<size; elem++) {
			arr[elem] = tmp[elem];
		}
	}
	free(tmp);
	return 0;
}

int radixSortFreqFirst8Bit(int *arr, int size) {
	int const buckets = 256;
	int freq[4][256] = {0};
	int *tmp = (int *) malloc(sizeof(int) * size);

	// Calculate frequencies for every pass at the same time
	for (int elem = 0; elem < size; elem++) {
		freq[0][((unsigned char *)(&arr[elem]))[0]]++;
		freq[1][((unsigned char *)(&arr[elem]))[1]]++;
		freq[2][((unsigned char *)(&arr[elem]))[2]]++;
		freq[3][((unsigned char *)(&arr[elem]))[3]]++;
	}
	// Is it better to use 4 loops? one for each column
	// Still constant time since size is fixed
	for (int j=1; j<256; j++) {
		freq[0][j] += freq[0][j-1];
		freq[1][j] += freq[1][j-1];
		freq[2][j] += freq[2][j-1];
		freq[3][j] += freq[3][j-1];
	}

	// Iteration 1
	for (int elem = size-1; elem >= 0; elem--) {
		int index = --freq[0][((unsigned char *)(&arr[elem]))[0]];
		tmp[index] = arr[elem];
	}

	// Iteration 2
	for (int elem = size-1; elem >= 0; elem--) {
		int index = --freq[1][((unsigned char *)(&tmp[elem]))[1]];
		arr[index] = tmp[elem];
	}

	// Iteration 3
	for (int elem = size-1; elem >= 0; elem--) {
		int index = --freq[2][((unsigned char *)(&arr[elem]))[2]];
		tmp[index] = arr[elem];
	}

	// Iteration 4
	for (int elem = size-1; elem >= 0; elem--) {
		int index = --freq[3][((unsigned char *)(&tmp[elem]))[3]];
		arr[index] = tmp[elem];
	}

	free(tmp);
	return 0;
}


/*
 * Idea from algorithm 1 in article
 * Allocate buckets for each possible value for the sorted in bits
 */
int radixSortWoCountingFreq(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	// int *freq = (int *) calloc(buckets, sizeof(int));
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);
	// int *freq = (int *) calloc(buckets, sizeof(int));
	int freq[buckets];
	for (int i = 0; i < buckets; i++) {
		freq[i] = 0;
	}
	int shift = 0;
	while (shift < 32) {
		for (int i=0; i < size; i++) {
			long bucket = (arr[i] >> shift) & bitMask;
			tmp[freq[bucket] + size * bucket] = arr[i];
			freq[bucket]++;
		}
		// Go through each bucket and copy all its content back to arr
		int elem = size-1;
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			while (freq[bucket] != 0) {
				arr[elem--] = tmp[bucket*size + --freq[bucket]];
			}
		}
		shift += bitsSortedOn;
	}

	free(tmp);
	// free(freq);
	return 0;
}

int **radixSortWoCountingFreqPointerArray(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int freq[buckets];
	for (int i=0; i<buckets; i++) freq[i] = 0;
	// can't use new since buckets and size aren't known and compile time
	int **tmp = (int **) malloc(sizeof(int *) * buckets);
	for (int i=0; i<buckets; i++)
		tmp[i] = (int *) malloc(sizeof(int) * size);
	int shift = 0;
	while (shift < 32) {
		for (int i=0; i < size; i++) {
			long bucket = (arr[i] >> shift) & bitMask;
			tmp[bucket][freq[bucket]] = arr[i];
			freq[bucket]++;
		}
		// Go through each bucket and copy all its content back to arr
		int elem = size-1;
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			while (freq[bucket] != 0) {
				arr[elem--] = tmp[bucket][--freq[bucket]];
			}
		}
		shift += bitsSortedOn;
	}
	/*
	for (int i=0; i<buckets; i++)
		free(tmp[i]);
	free(tmp);
	*/
	return tmp;
}

/*
 * using the idea of having the last iterations done at the same time
 */
int radixSortWoCountingFreqCombinedLastIt(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	// int *freq = (int *) calloc(buckets, sizeof(int));
	int freq[buckets];
	for (int i=0; i<buckets; i++) freq[i] = 0;
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);
	int shift = 0;
	int regularSortedBits = 32 - bitsSortedOn - bitsSortedOn;

	while (shift < regularSortedBits) {
		for (int i=0; i < size; i++) {
			long bucket = (arr[i] >> shift) & bitMask;
			tmp[freq[bucket] + size * bucket] = arr[i];
			freq[bucket]++;
		}
		// Go through each bucket and copy all its content back to arr
		int elem = size-1;
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			while (freq[bucket] != 0) {
				arr[elem--] = tmp[bucket*size + --freq[bucket]];
			}
		}
		shift += bitsSortedOn;
	}
	// create freq2 sorted on using shift2 = shift+bitsSortedOn
	// int *lastFreq = (int *) calloc(buckets, sizeof(int));
	int lastFreq[buckets];
	for (int i=0; i<buckets; i++) lastFreq[i] = 0;
	int lastShift = shift + bitsSortedOn;
	for (int i=0; i < size; i++) {
		long bucket = (arr[i] >> shift) & bitMask;
		tmp[freq[bucket] + size * bucket] = arr[i];
		freq[bucket]++;
		lastFreq[(arr[i] >> lastShift) & bitMask]++;
	}
	for (int i=1; i<buckets; i++)
		lastFreq[i] += lastFreq[i-1];
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		// cout << bucket << endl;
		long bucketOffset = bucket * size;
		while (freq[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freq[bucket]];
			int index = --lastFreq[(currElem >> lastShift) & bitMask];
			arr[index] = currElem;
		}
	}

	free(tmp);
	// free(freq); free(lastFreq);
	return 0;
}

int radixSortWoCountingFreqCopyBackArr(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int *freqTmp = (int *) calloc(buckets, sizeof(int));
	int *freqArr = (int *) calloc(buckets, sizeof(int));
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);
	bool exitedEarly = false;
	int shiftTmp = 0;
	int shiftArr = bitsSortedOn;
	while (shiftTmp < 32) {
		for (int i=0; i < size; i++) {
			long bucket = (arr[i] >> shiftTmp) & bitMask;
			tmp[freqTmp[bucket] + size * bucket] = arr[i];
			freqTmp[bucket]++;
			freqArr[(arr[i] >> shiftArr) & bitMask]++;
		}
		if (!(shiftArr <= 32)) {
			exitedEarly = true;
			break;
		}
		// Go through each bucket and copy all its content back to arr
		for (int i = 1; i < buckets; i++) {
			freqArr[i] += freqArr[i-1];
		}
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			long bucketOffset = bucket * size;
			while (freqTmp[bucket] != 0) {
				int currElem = tmp[bucketOffset + --freqTmp[bucket]];
				int index = --freqArr[(currElem >> shiftArr) & bitMask];
				arr[index] = currElem;
			}
		}
		for (int i = 0; i < buckets; i++) {
			freqArr[i] = 0;
		}
		shiftTmp += bitsSortedOn + bitsSortedOn;
		shiftArr += bitsSortedOn + bitsSortedOn;
	}

	int elem = size-1;
	if (exitedEarly) {
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			long bucketOffset = bucket * size;
			while (freqTmp[bucket] != 0) {
				arr[elem--] = tmp[bucketOffset + --freqTmp[bucket]];
			}
		}
	}

	free(tmp); 
	free(freqArr); free(freqTmp);
	return 0;
}

int radixSortWoCountingFreqCopyBackArr8Bit(int *arr, int size) {
	int const buckets = 256;
	int const bitMask = 255;
	int freqTmp[256] = {0};
	int freqArr[256] = {0};
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);

	// Iteration 1
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		tmp[freqTmp[bucket]++ + size * bucket] = arr[i];
		freqArr[((unsigned char *)(&arr[i]))[1]]++;
	}
	// Iteration 2
	for (int i = 1; i < buckets; i++) {
		freqArr[i] += freqArr[i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freqTmp[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freqTmp[bucket]];
			int index = --freqArr[((unsigned char *)(&currElem))[1]];
			arr[index] = currElem;
		}
	}
	for (int i = 0; i < buckets; i++) {
		freqArr[i] = 0;
	}
	// Iteration 3
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[2];
		tmp[freqTmp[bucket]++ + size * bucket] = arr[i];
		freqArr[((unsigned char *)(&arr[i]))[3]]++;
	}
	// Iteration 4
	for (int i = 1; i < buckets; i++) {
		freqArr[i] += freqArr[i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freqTmp[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freqTmp[bucket]];
			int index = --freqArr[((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp);
	return 0;
}

int radixSortWoCountingFreqCopyBackArr8BitWriteBuffer(int *arr, int size) {
	int const buckets = 256;
	int const bitMask = 255;
	int freqTmp[256] = {0};
	int freqArr[256] = {0};
	int writeBuffer[buckets][8];
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);

	// Iteration 1
	// use buffer here
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		int bufferIndex = freqTmp[bucket] & 7;
		writeBuffer[bucket][bufferIndex] = arr[i];
		freqTmp[bucket]++;
		if ((freqTmp[bucket] & 7) == 0) {
			long bucketOffset = size * bucket;
			int currFreq = freqTmp[bucket];
			tmp[bucketOffset + currFreq - 8] = writeBuffer[bucket][0];
			tmp[bucketOffset + currFreq - 7] = writeBuffer[bucket][1];
			tmp[bucketOffset + currFreq - 6] = writeBuffer[bucket][2];
			tmp[bucketOffset + currFreq - 5] = writeBuffer[bucket][3];
			tmp[bucketOffset + currFreq - 4] = writeBuffer[bucket][4];
			tmp[bucketOffset + currFreq - 3] = writeBuffer[bucket][5];
			tmp[bucketOffset + currFreq - 2] = writeBuffer[bucket][6];
			tmp[bucketOffset + currFreq - 1] = writeBuffer[bucket][7];
		}
		freqArr[((unsigned char *)(&arr[i]))[1]]++;
	}
	for (long i = 0; i < buckets; i++) {
		long bucketOffset = size * i;
		for (int j = (freqTmp[i] & 7)-1, k=1; j >= 0; j--,k++) {
			tmp[bucketOffset + freqTmp[i] - k] = writeBuffer[i][j];
		}
	}
	// Iteration 2
	for (int i = 1; i < buckets; i++) {
		freqArr[i] += freqArr[i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freqTmp[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freqTmp[bucket]];
			int index = --freqArr[((unsigned char *)(&currElem))[1]];
			arr[index] = currElem;
		}
	}
	for (int i = 0; i < buckets; i++) {
		freqArr[i] = 0;
	}
	// Iteration 3
	// use write buffer here
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[2];
		int bufferIndex = freqTmp[bucket] & 7;
		writeBuffer[bucket][bufferIndex] = arr[i];
		freqTmp[bucket]++;
		if ((freqTmp[bucket] & 7) == 0) {
			long bucketOffset = size * bucket;
			int currFreq = freqTmp[bucket];
			tmp[bucketOffset + currFreq - 8] = writeBuffer[bucket][0];
			tmp[bucketOffset + currFreq - 7] = writeBuffer[bucket][1];
			tmp[bucketOffset + currFreq - 6] = writeBuffer[bucket][2];
			tmp[bucketOffset + currFreq - 5] = writeBuffer[bucket][3];
			tmp[bucketOffset + currFreq - 4] = writeBuffer[bucket][4];
			tmp[bucketOffset + currFreq - 3] = writeBuffer[bucket][5];
			tmp[bucketOffset + currFreq - 2] = writeBuffer[bucket][6];
			tmp[bucketOffset + currFreq - 1] = writeBuffer[bucket][7];
		}
		freqArr[((unsigned char *)(&arr[i]))[3]]++;
	}
	for (long i = 0; i < buckets; i++) {
		long bucketOffset = size * i;
		for (int j = (freqTmp[i] & 7)-1, k=1; j >= 0; j--,k++) {
			tmp[bucketOffset + freqTmp[i] - k] = writeBuffer[i][j];
		}
	}
	// Iteration 4
	for (int i = 1; i < buckets; i++) {
		freqArr[i] += freqArr[i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freqTmp[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freqTmp[bucket]];
			int index = --freqArr[((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp);
	return 0;
}



/*
 * Version hardcoded for sorting for 8 bit by using unsigned char array
 * to access each byte and loop unrolling, about 10% faster
 */
int radixSortWoCountingFreq8Bit(int *arr, int size) {
	int const buckets = 1 << 8;
	int const bitMask = buckets-1;
	int freq[buckets] = {0};
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);

	// Iteration 1
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		tmp[freq[bucket] + size * bucket] = arr[i];
		freq[bucket]++;
	}
	// Go through each bucket and copy all its content back to arr
	int elem = size-1;
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freq[bucket] != 0) {
			arr[elem--] = tmp[bucketOffset + --freq[bucket]];
		}
	}
	// Iteration 2
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[1];
		tmp[freq[bucket] + size * bucket] = arr[i];
		freq[bucket]++;
	}
	// Go through each bucket and copy all its content back to arr
	elem = size-1;
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freq[bucket] != 0) {
			arr[elem--] = tmp[bucketOffset + --freq[bucket]];
		}
	}
	int lastIterationFreq[buckets] = {0};
	// Iteration 3 and 4 at same time
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[2];
		tmp[freq[bucket] + size * bucket] = arr[i];
		freq[bucket]++;
		lastIterationFreq[((unsigned char *)(&arr[i]))[3]]++;
	}
	for (int i=1; i<buckets;i++) {
		lastIterationFreq[i] += lastIterationFreq[i-1];
	}
	// Go through each bucket and copy all its content back to arr
	elem = size-1;
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		// cout << bucket << endl;
		long bucketOffset = bucket * size;
		while (freq[bucket] != 0) {
			int currElem = tmp[bucketOffset + --freq[bucket]];
			int index = --lastIterationFreq[((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp);
	return 0;
}

int radixSortWoCountingFreq8Bitv2(int *arr, int size) {
	int const buckets = 256;
	int const bitMask = 255;
	int freq[2][256] = {0};
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);

	// Iteration 1
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		tmp[freq[0][bucket]++ + size * bucket] = arr[i];
		freq[1][((unsigned char *)(&arr[i]))[1]]++;
	}
	// Iteration 2, sort back to arr
	for (int i = 1; i < 256; i++) {
		freq[1][i] += freq[1][i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freq[0][bucket] != 0) {
			int currElem = tmp[bucketOffset + --freq[0][bucket]];
			int index = --freq[1][((unsigned char *)(&currElem))[1]];
			arr[index] = currElem;
		}
	}
	for (int i = 0; i < 256; i++) {
		freq[1][i] = 0;
	}
	// Iteration 3
	for (int i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[2];
		tmp[freq[0][bucket]++ + size * bucket] = arr[i];
		freq[1][((unsigned char *)(&arr[i]))[3]]++;
	}
	// Iteration 4
	for (int i = 1; i < 256; i++) {
		freq[1][i] += freq[1][i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freq[0][bucket] != 0) {
			int currElem = tmp[bucketOffset + --freq[0][bucket]];
			int index = --freq[1][((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp);
	return 0;
}

int radixSortWoCountingFreqWBuffers(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int *freq = (int *) calloc(buckets, sizeof(int));
	int writeBuffer[buckets][8];
	// can't use new since buckets and size aren't known and compile time
	int *tmp = (int *) malloc(sizeof(int) * size * buckets);
	int shift = 0;
	while (shift < 32) {
		for (int i=0; i < size; i++) {
			long bucket = (arr[i] >> shift) & bitMask;
			// find correct loc in write buffer using last 3 bits of the freq count for the bucket
			int bufferIndex = freq[bucket] & 7;
			writeBuffer[bucket][bufferIndex] = arr[i];
			freq[bucket]++;
			// the write buffer is full, write it to tmp - use intel intrinsic operation?
			if ((freq[bucket] & 7) == 0) {
				long bucketOffset = size * bucket;
				int currFreq = freq[bucket];
				tmp[bucketOffset + currFreq - 8] = writeBuffer[bucket][0];
				tmp[bucketOffset + currFreq - 7] = writeBuffer[bucket][1];
				tmp[bucketOffset + currFreq - 6] = writeBuffer[bucket][2];
				tmp[bucketOffset + currFreq - 5] = writeBuffer[bucket][3];
				tmp[bucketOffset + currFreq - 4] = writeBuffer[bucket][4];
				tmp[bucketOffset + currFreq - 3] = writeBuffer[bucket][5];
				tmp[bucketOffset + currFreq - 2] = writeBuffer[bucket][6];
				tmp[bucketOffset + currFreq - 1] = writeBuffer[bucket][7];
			}
		}
		// move the remaining elements from write buffers to array
		for (long i = 0; i < buckets; i++) {
			long bucketOffset = size * i;
			for (int j = (freq[i] & 7)-1, k=1; j >= 0; j--,k++) {
				tmp[bucketOffset + freq[i] - k] = writeBuffer[i][j];
			}
		}
		// Go through each bucket and copy all its content back to arr
		int elem = size-1;
		for (long bucket=buckets-1; bucket>=0; bucket--) {
			while (freq[bucket] != 0) {
				arr[elem--] = tmp[bucket*size + --freq[bucket]];
			}
		}
		shift += bitsSortedOn;
	}

	free(tmp);
	free(freq);
	return 0;
}

/*
 * With two matrixes to sort back and forth between
*/
int radixSortWoCountingFreqW2Tmps(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int freq[2][buckets];
	for (int i=0; i<buckets; i++) freq[0][i] = 0;
	for (int i=0; i<buckets; i++) freq[1][i] = 0;
	// can't use new since buckets and size aren't known and compile time
	int *tmp1 = (int *) malloc(sizeof(int) * size * buckets);
	int *tmp2 = (int *) malloc(sizeof(int) * size * buckets);
	int shift = bitsSortedOn, lastUsedTmp = 1;
	// begin by sorting into tmp
	for (long i=0; i < size; i++) {
		long bucket = arr[i] & bitMask;
		tmp1[freq[0][bucket] + size * bucket] = arr[i];
		freq[0][bucket]++;
	}

	while (shift < 32) {
		// sorts from tmp1 into tmp2
		for (long bucket=0; bucket<buckets; bucket++) {
			long bucketOffset = bucket * size, j = 0;
			long elemsInBucket = freq[0][bucket];
		   	freq[0][bucket] = 0;
			while (j < elemsInBucket) {
				long elem = tmp1[bucketOffset + j++];
				tmp2[size * ((elem >> shift) & bitMask) + freq[1][(elem >> shift) & bitMask]++] = elem;
			}
		}
		shift += bitsSortedOn;
		if (!(shift < 32)) {
			lastUsedTmp = 2;
			break;
		}
		// sorts from tmp2 back into tmp1
		for (long bucket=0; bucket<buckets; bucket++) {
			long bucketOffset = bucket * size, j = 0;
		    long elemsInBucket = freq[1][bucket];
			freq[1][bucket] = 0;
			while (j < elemsInBucket) {
				long elem = tmp2[bucketOffset + j++];
				tmp1[size * ((elem >> shift) & bitMask) + freq[0][(elem >> shift) & bitMask]++] = elem;
			}
		}
		shift += bitsSortedOn;
	}
	shift -= bitsSortedOn;
	int *tmp = (lastUsedTmp == 1) ? tmp1 : tmp2;
	int freqBucket = (lastUsedTmp == 1) ? 0 : 1;
	// copy back into array
	for (long bucket=buckets-1, elem = size-1; bucket>=0; bucket--) {
		long bucketOffset = bucket*size;
		while (freq[freqBucket][bucket] != 0) {
			arr[elem--] = tmp[bucketOffset + --freq[freqBucket][bucket]];
		}
	}

	free(tmp1); free(tmp2);
	return 0;
}

// some issues for bitsSorted = 3,5,7
int radixSortWoCountingFreqW2TmpsCombinedIt(int *arr, int size, int bitsSortedOn) {
	int const buckets = 1 << bitsSortedOn;
	int const bitMask = buckets-1;
	int freq[3][buckets];
	for (int i=0; i<buckets; i++) freq[0][i] = 0;
	for (int i=0; i<buckets; i++) freq[1][i] = 0;
	for (int i=0; i<buckets; i++) freq[2][i] = 0;
	// can't use new since buckets and size aren't known and compile time
	int *tmp1 = (int *) malloc(sizeof(int) * size * buckets);
	int *tmp2 = (int *) malloc(sizeof(int) * size * buckets);
	int shift = bitsSortedOn, lastUsedTmp = 1;
	// begin by sorting into tmp
	for (long i=0; i < size; i++) {
		long bucket = arr[i] & bitMask;
		tmp1[freq[0][bucket] + size * bucket] = arr[i];
		freq[0][bucket]++;
	}
	int regularSortedBits = 32 - bitsSortedOn - bitsSortedOn;

	while (shift < regularSortedBits) {
		// sorts from tmp1 into tmp2
		for (long bucket=0; bucket<buckets; bucket++) {
			long bucketOffset = bucket * size, j = 0;
			long elemsInBucket = freq[0][bucket];
			freq[0][bucket] = 0;
			while (j < elemsInBucket) {
				long elem = tmp1[bucketOffset + j++];
				tmp2[size * ((elem >> shift) & bitMask) + freq[1][(elem >> shift) & bitMask]++] = elem;
			}
		}
		shift += bitsSortedOn;
		if (!(shift < regularSortedBits)) {
			lastUsedTmp = 2;
			break;
		}
		// sorts from tmp2 back into tmp1
		for (long bucket=0; bucket<buckets; bucket++) {
			long bucketOffset = bucket * size, j = 0;
		    long elemsInBucket = freq[1][bucket];
			freq[1][bucket] = 0;
			while (j < elemsInBucket) {
				long elem = tmp2[bucketOffset + j++];
				tmp1[size * ((elem >> shift) & bitMask) + freq[0][(elem >> shift) & bitMask]++] = elem;
			}
		}
		shift += bitsSortedOn;
	}
	int *currTmp, *lastTmp, currFreqs, lastFreqs;
	if (lastUsedTmp == 1) {
		currTmp = tmp1;
		lastTmp = tmp2;
		currFreqs = 0;
		lastFreqs = 1;
	} else {
		currTmp = tmp2;
		lastTmp = tmp1;
		currFreqs = 1;
		lastFreqs = 0;
	}
	int lastShift = shift + bitsSortedOn;
	for (long bucket=0; bucket<buckets; bucket++) {
		long bucketOffset = bucket * size, j = 0;
		long elemsInBucket = freq[currFreqs][bucket];
		while (j < elemsInBucket) {
			long elem = tmp2[bucketOffset + j++];
			long index = size * ((elem >> shift) & bitMask) + freq[lastFreqs][(elem >> shift) & bitMask]++;
			tmp1[index] = elem;
			freq[2][(elem >> lastShift) & bitMask]++;
		}
	}
	for (int i=1; i<buckets;i++) {
		freq[2][i] += freq[2][i-1];
	}
	int elem = size-1;
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		while (freq[lastFreqs][bucket] != 0) {
			int currElem = tmp1[bucketOffset + --freq[lastFreqs][bucket]];
			int index = --freq[2][(currElem >> lastShift) & bitMask];
			arr[index] = currElem;
		}
	}

	free(tmp1); free(tmp2);
	return 0;
}

int radixSortWoCountingFreqW2TmpsCombinedIt8Bit(int *arr, int size) {
	int const buckets = 256;
	int freq[3][256] = {0};
	// can't use new since buckets and size aren't known and compile time
	int *tmp1 = (int *) malloc(sizeof(int) * size * buckets);
	int *tmp2 = (int *) malloc(sizeof(int) * size * buckets);

	// begin by sorting into tmp
	for (long i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		tmp1[freq[0][bucket]++ + size * bucket] = arr[i];
	}

	// sorts from tmp1 into tmp2
	for (long bucket=0; bucket<buckets; bucket++) {
		long bucketOffset = bucket * size, j = 0;
		int elemsInBucket = freq[0][bucket];
		freq[0][bucket] = 0;
		while (j < elemsInBucket) {
			long elem = tmp1[bucketOffset + j++];
			long newBucket = ((unsigned char *)(&elem))[1];
			tmp2[size * newBucket + freq[1][newBucket]++] = elem;
		}
	}
	// sort from tmp1 into tm2 and count freqs for tmp1 to arr
	for (long bucket=0; bucket<buckets; bucket++) {
		long bucketOffset = bucket * size, j = 0;
		int elemsInBucket = freq[1][bucket];
		while (j < elemsInBucket) {
			long elem = tmp2[bucketOffset + j++];
			long newBucket = ((unsigned char *)(&elem))[2];
			long index = size * newBucket + freq[0][newBucket]++;
			tmp1[index] = elem;
			freq[2][((unsigned char *)(&elem))[3]]++;
		}
	}
	for (int i=1; i<buckets;i++) {
		freq[2][i] += freq[2][i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		int elemsInBucket = freq[0][bucket];
		while (elemsInBucket != 0) {
			int currElem = tmp1[bucketOffset + --elemsInBucket];
			int index = --freq[2][((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp1); free(tmp2);
	return 0;
}

int radixSortWoCountingFreqW2TmpsCombinedIt8BitWriteBuffer(int *arr, int size) {
	int const buckets = 256;
	int freq[3][256] = {0};
	int writeBuffer[256][8];
	// can't use new since buckets and size aren't known and compile time
	int *tmp1 = (int *) malloc(sizeof(int) * size * buckets);
	int *tmp2 = (int *) malloc(sizeof(int) * size * buckets);

	// begin by sorting into tmp
	for (long i=0; i < size; i++) {
		long bucket = ((unsigned char *)(&arr[i]))[0];
		int bufferIndex = freq[0][bucket] & 7;
		writeBuffer[bucket][bufferIndex] = arr[i];
		freq[0][bucket]++;
		if ((freq[0][bucket] & 7) == 0) {
			long bucketOffset = size * bucket;
			int currFreq = freq[0][bucket];
			tmp1[bucketOffset + currFreq - 8] = writeBuffer[bucket][0];
			tmp1[bucketOffset + currFreq - 7] = writeBuffer[bucket][1];
			tmp1[bucketOffset + currFreq - 6] = writeBuffer[bucket][2];
			tmp1[bucketOffset + currFreq - 5] = writeBuffer[bucket][3];
			tmp1[bucketOffset + currFreq - 4] = writeBuffer[bucket][4];
			tmp1[bucketOffset + currFreq - 3] = writeBuffer[bucket][5];
			tmp1[bucketOffset + currFreq - 2] = writeBuffer[bucket][6];
			tmp1[bucketOffset + currFreq - 1] = writeBuffer[bucket][7];
		}
	}
	for (long i = 0; i < buckets; i++) {
		long bucketOffset = size * i;
		for (int j = (freq[0][i] & 7)-1, k=1; j >= 0; j--,k++) {
			tmp1[bucketOffset + freq[0][i] - k] = writeBuffer[i][j];
		}
	}

	// sorts from tmp1 into tmp2
	for (long bucket=0; bucket<buckets; bucket++) {
		long bucketOffset = bucket * size, j = 0;
		int elemsInBucket = freq[0][bucket];
		freq[0][bucket] = 0;
		while (j < elemsInBucket) {
			long elem = tmp1[bucketOffset + j++];
			long newBucket = ((unsigned char *)(&elem))[1];
			int bufferIndex = freq[1][newBucket] & 7;
			writeBuffer[newBucket][bufferIndex] = elem;
			freq[1][newBucket]++;
			if ((freq[1][newBucket] & 7) == 0) {
				long bucketOffset = size * newBucket;
				int currFreq = freq[1][newBucket];
				tmp2[bucketOffset + currFreq - 8] = writeBuffer[newBucket][0];
				tmp2[bucketOffset + currFreq - 7] = writeBuffer[newBucket][1];
				tmp2[bucketOffset + currFreq - 6] = writeBuffer[newBucket][2];
				tmp2[bucketOffset + currFreq - 5] = writeBuffer[newBucket][3];
				tmp2[bucketOffset + currFreq - 4] = writeBuffer[newBucket][4];
				tmp2[bucketOffset + currFreq - 3] = writeBuffer[newBucket][5];
				tmp2[bucketOffset + currFreq - 2] = writeBuffer[newBucket][6];
				tmp2[bucketOffset + currFreq - 1] = writeBuffer[newBucket][7];
			}
		}
	}
	for (long i = 0; i < buckets; i++) {
		long bucketOffset = size * i;
		for (int j = (freq[1][i] & 7)-1, k=1; j >= 0; j--,k++) {
			tmp2[bucketOffset + freq[1][i] - k] = writeBuffer[i][j];
		}
	}
	// sort from tmp1 into tm2 and count freqs for tmp1 to arr
	for (long bucket=0; bucket<buckets; bucket++) {
		long bucketOffset = bucket * size, j = 0;
		int elemsInBucket = freq[1][bucket];
		while (j < elemsInBucket) {
			long elem = tmp2[bucketOffset + j++];
			long newBucket = ((unsigned char *)(&elem))[2];
			int bufferIndex = freq[0][newBucket] & 7;
			writeBuffer[newBucket][bufferIndex] = elem;
			freq[0][newBucket]++;
			freq[2][((unsigned char *)(&elem))[3]]++;
			if ((freq[0][newBucket] & 7) == 0) {
				long bucketOffset = size * newBucket;
				int currFreq = freq[0][newBucket];
				tmp1[bucketOffset + currFreq - 8] = writeBuffer[newBucket][0];
				tmp1[bucketOffset + currFreq - 7] = writeBuffer[newBucket][1];
				tmp1[bucketOffset + currFreq - 6] = writeBuffer[newBucket][2];
				tmp1[bucketOffset + currFreq - 5] = writeBuffer[newBucket][3];
				tmp1[bucketOffset + currFreq - 4] = writeBuffer[newBucket][4];
				tmp1[bucketOffset + currFreq - 3] = writeBuffer[newBucket][5];
				tmp1[bucketOffset + currFreq - 2] = writeBuffer[newBucket][6];
				tmp1[bucketOffset + currFreq - 1] = writeBuffer[newBucket][7];
			}
		}
	}
	for (long i = 0; i < buckets; i++) {
		long bucketOffset = size * i;
		for (int j = (freq[0][i] & 7)-1, k=1; j >= 0; j--,k++) {
			tmp1[bucketOffset + freq[0][i] - k] = writeBuffer[i][j];
		}
	}
	for (int i=1; i<buckets;i++) {
		freq[2][i] += freq[2][i-1];
	}
	for (long bucket=buckets-1; bucket>=0; bucket--) {
		long bucketOffset = bucket * size;
		int elemsInBucket = freq[0][bucket];
		while (elemsInBucket != 0) {
			int currElem = tmp1[bucketOffset + --elemsInBucket];
			int index = --freq[2][((unsigned char *)(&currElem))[3]];
			arr[index] = currElem;
		}
	}

	free(tmp1); free(tmp2);
	return 0;
}


int msdLsdRadixSort(int *arr, int size, int msdBits, int lsdBits) {
	int const msdBuckets = 1 << msdBits;
	int bitMask = msdBuckets-1;
	int *freq = (int *) calloc(msdBuckets, sizeof(int));
	int *tmp = (int *) malloc(sizeof(int) * size);
	// indexes of where each msdBuckets is placed, first one obv begins at 0
	int msdIndexes[msdBuckets+1]; msdIndexes[0] = 0; msdIndexes[msdBuckets] = size;
	int shift = 32 - msdBits;

	// TODO msd-sort
	for (int i=0; i<size; i++) { // count frequencies
		freq[(arr[i] >> shift) & bitMask]++; }
	for (int i=1; i<msdBuckets; i++) { // sum frequencies
		freq[i] += freq[i-1]; 
		msdIndexes[i] = freq[i-1];
	}
	for (int i=size-1; i >= 0; i--) { // move nodes correct loc in tmp array
		int index = --freq[(arr[i] >> shift) & bitMask];
		tmp[index] = arr[i]; 
	}
	for (int i=0; i<size; i++) { // copy from tmp back to arr
		arr[i] = tmp[i]; }

	// variables for sorting lsd sorting
	int const lsdBuckets = 1 << lsdBits;
	bitMask = lsdBuckets-1;
	free(freq); free(tmp);
	freq = (int *) calloc(lsdBuckets, sizeof(int));
	shift = 0;
	int *tmp1 = (int *) malloc(sizeof(int) * size);
	int *tmp2 = (int *) malloc(sizeof(int) * size);

	// TODO sort rest using lsd
	// go through each bucket and sort it in lsd fashion
	for (int bucket=0; bucket < msdBuckets; bucket++) {
		// cout << "sorting bucket " << bucket << endl;
		shift = 0;
		int remainingBits = 32 - msdBits;
		// start and end indexes of the elems in the bucket in arr
		int start = msdIndexes[bucket], end = msdIndexes[bucket+1]; 
		int elemts = end-start;
		bool exitedEarly = false;
		// don't sort if bucket contains less than one element
		if ((end-start) < 2) continue;
		// copy the elems of the bucket into tmp1
		for (int i = start, j = 0; i < end; i++,j++) { 
			tmp1[j] = arr[i];
		}

		// sort the bucket in lsd fashion by sorting between tmp1 and 2
		while (shift < remainingBits) {
			for (int i=0; i<elemts; i++) {
				freq[(tmp1[i] >> shift) & bitMask]++; }
			for (int i=1; i<lsdBuckets; i++) {
				freq[i] += freq[i-1]; }
			for (int i=elemts-1; i >= 0; i--) {
				tmp2[--freq[(tmp1[i] >> shift) & bitMask]] = tmp1[i]; }
			for (int i=0; i<lsdBuckets; i++) {
				freq[i] = 0; }

			shift += lsdBits;
			if (!(shift < remainingBits)) { exitedEarly = true; break; }

			for (int i=0; i<elemts; i++) { // count frequencies
				freq[(tmp2[i] >> shift) & bitMask]++; }
			for (int i=1; i<lsdBuckets; i++) { // sum frequencies
				freq[i] += freq[i-1]; }
			for (int i=elemts-1; i >= 0; i--) { // move nodes to correct loc in tmp1
				tmp1[--freq[(tmp2[i] >> shift) & bitMask]] = tmp2[i]; }
			for (int i=0; i<lsdBuckets; i++) { // set frequencies to 0
				freq[i] = 0; }
			shift += lsdBits;
	   	}
		// copy from the correct bucket depending on which was last sorted into
		tmp = (exitedEarly) ? tmp2 : tmp1;
		// copy back from tmp into the correct position of arr
		for (int i = start, j = 0; i < end; i++,j++) { 
			arr[i] = tmp[j]; }
	}
	free(tmp1); free(tmp2); free(freq);
	return 0;
}

bool isSorted(int *arr, int size) {
	for (int i=0, end = size-1; i<end; i++) {
		if (arr[i] > arr[i+1]) {
			return false;
		}
	}
	return true;
}

void testBitsSortedOn(int N, int reps) {
	int *array = new int[N];
	for (int i = 0; i<N; i++) {
		array[i] = rand();
	}
	int times[17] = {0}; // larger than 16 doesn't make really make sense
	for (int k=0; k<reps; k++) {
		for (int i=1; i<=16;i++) {
			for (int j = 0; j<N; j++) {
				array[j] = rand();
			}
			clock_t t = clock();
			radixSort(array, N, i);

			times[i] += clock() - t;
		}
	}
	for (int i = 1; i<17; i++) {
		cout << (times[i]/reps) << " when sorting on " << i << " bits" << endl;
	}
	delete[] array;
}

void initialTest();

void testing(int test, string fileEnding) {
	int start = 10000000;
	int inc   = 10000000;
	int end   = start *  10;
	ofstream results;
	string testFunc = "";
	switch(test) {
		case  1: testFunc = "01. radix sort";
			 	 break;
		case  2: testFunc = "02. radix sort wo copy back";
			 	 break;
		case  3: testFunc = "03. radix sort freqs first";
			 	 break;
		case  4: testFunc = "04. radix sort wo counting freqs";
			 	 break;
		case  5: testFunc = "05. radix sort wo counting freqs combined last iteration";
			 	 break;
		case  6: testFunc = "06. radix sort wo counting freqs copy back arr";
			 	 break;
		case  7: testFunc = "07. radix sort freq counting 8-bit hardcoded";
			 	 break;
		case  8: testFunc = "08. radix sort with write buffers";
			 	 break;
		case  9: testFunc = "09. radix sort freqs count with 2 tmps";
			 	 break;
		case 10: testFunc = "10. radix sort freqs count with 2 tmps combined iteration";
				 break;
		case 11: testFunc = "02.1. radix sort wo copy back 8-b";
				 break;
		default: cerr << "unrecognized test value: " << test << endl;
				 exit(1);
	}

	results.open("data/" + testFunc + " " + fileEnding + ".csv");
	results << "input,";
	for (int i=1; i<=16;i++) {
		results << i << " bit" << ((i == 1) ? "," : ((i == 16) ? "" : ","));
	}
	results << "\n";
	for (int k = start; k <= end; k+=inc) {
		results << k << ",";
		for (int i=1; i<=16;i++) {
			int *array = new int[k];
			srand(24); // use srand to make the arrays identical
			for (int j = 0; j<k; j++) {
				array[j] = rand();
			}
			// Test this function call
			clock_t t1 = clock();
			switch(test) {
				case 1: radixSort(array, k, i);
						break;
				case 2: radixSortWoCopyBack(array, k, i);
						break;
				case 3: radixSortFreqFirst(array, k, i);
						break;
				case 4: radixSortWoCountingFreq(array, k, i);
						break;
				case 5: radixSortWoCountingFreqCombinedLastIt(array, k, i);
						break;
				case 6: radixSortWoCountingFreqCopyBackArr(array, k, i);
						break;
				case 7: radixSortWoCountingFreq8Bitv2(array, k);
						break;
				case 8: radixSortWoCountingFreqWBuffers(array, k, i);
						break;
				case 9: radixSortWoCountingFreqW2Tmps(array, k, i);
						break;
				case 10: radixSortWoCountingFreqW2TmpsCombinedIt(array, k, i);
						 break;
				case 11: radixSortWoCopyBack8Bit(array, k);
						 break;
				default: cout << "this can't happen" << endl;
			}
			clock_t t2 = clock();
			results << (t2-t1) << ((i != 16) ? "," : "");

			delete[] array;
		}
		results << "\n";
	}
	results.close();
}

void testingMatrix8Bit(int test, string fileEnding) {
	int start = 10000000;
	int inc   = 10000000;
	int end   = start *  50;
	int repetitions = 3;
	ofstream results;
	string testFunc = "";

	results.open("data/matrix 8 bit " + fileEnding + ".csv");
	results << "input,";
	results << "wo counting freq,";
	results << "wo counting freq combined last it,";
	results << "wo counting freq copy back,";
	results << "wo counting write buffers,";
	results << "wo counting 2 tmps,";
	results << "wo counting 2 tmps combined last it";
	results << "\n";
	for (int k = start; k <= end; k+=inc) {
		results << k << ",";
		int *array = new int[k];
		for (int i=1; i<=6;i++) {
			long time = 0;
			for (int rep=0; rep<repetitions;rep++) {
				srand(24); // use srand to make the arrays identical
				for (int j = 0; j<k; j++) {
					array[j] = rand();
				}
				// Test this function call
				clock_t t1 = clock();
				switch(i) {
					case 1: radixSortWoCountingFreq(array, k, 8);
							break;
					case 2: radixSortWoCountingFreqCombinedLastIt(array, k, 8);
							break;
					case 3: radixSortWoCountingFreqCopyBackArr(array, k, 8);
							break;
					case 4: radixSortWoCountingFreqWBuffers(array, k, 8);
							break;
					case 5: radixSortWoCountingFreqW2Tmps(array, k, 8);
							break;
					case 6: radixSortWoCountingFreqW2TmpsCombinedIt(array, k, 8);
							break;
					default: cout << "this can't happen" << endl;
				}
				time += clock() - t1;
				clock_t t2 = clock();
			}
			results << (time / repetitions) << ((i != 6) ? "," : "");
		}
		results << "\n";
		delete[] array;
	}
	results.close();
}

void testingStandard8Bit(int test, string fileEnding) {
	int start = 10000000;
	int inc   = 10000000;
	int end   = start *  50;
	int repetitions = 3;
	ofstream results;
	string testFunc = "";

	results.open("data/standard 8 bit " + fileEnding + ".csv");
	results << "input,";
	results << "standard,";
	results << "copy back,";
	results << "freqs first";
	results << "\n";
	for (int k = start; k <= end; k+=inc) {
		results << k << ",";
		int *array = new int[k];
		for (int i=1; i<=3;i++) {
			long time = 0;
			for (int rep=0; rep<repetitions;rep++) {
				srand(24); // use srand to make the arrays identical
				for (int j = 0; j<k; j++) {
					array[j] = rand();
				}
				clock_t t = clock();
				switch(i) {
					case 1: radixSort(array, k, 8);
							break;
					case 2: radixSortWoCopyBack(array, k, 8);
							break;
					case 3: radixSortFreqFirst(array, k, 8);
							break;
					default: cout << "this can't happen" << endl;
				}
				time += clock() - t;
			}
			results << (time / repetitions) << ((i != 3) ? "," : "");
		}
		results << endl;
		delete[] array;
	}
	results.close();
}

void testing8BitHardcoded(int test, string fileEnding) {
	int start = 10000000;
	int inc   = 10000000;
	int end   = start *  50;
	int repetitions = 3;
	ofstream results;
	string testFunc = "";

	results.open("data/8 bit hardcoded" + fileEnding + ".csv");
	results << "input,";
	results << "wo copy back,";
	results << "freqs first,";
	results << "sort back arr,";
	results << "sort back arr write buffer,";
	results << "version 2,";
	results << "2 tmp combined iteration,";
	results << "2 tmp combined iteration write buffer";
	results << "\n";
	for (int k = start; k <= end; k+=inc) {
		results << k << ",";
		int *array = new int[k];
		for (int i=1; i<=7;i++) {
			long time = 0;
			for (int rep=0; rep<repetitions;rep++) {
				srand(24); // use srand to make the arrays identical
				for (int j = 0; j<k; j++) {
					array[j] = rand();
				}
				clock_t t = clock();
				switch(i) {
					case 1: radixSortWoCopyBack8Bit(array, k);
							break;
					case 2: radixSortFreqFirst8Bit(array, k);
							break;
					case 3: radixSortWoCountingFreqCopyBackArr8Bit(array, k);
							break;
					case 4: radixSortWoCountingFreqCopyBackArr8BitWriteBuffer(array, k);
							break;
					case 5: radixSortWoCountingFreq8Bitv2(array, k);
							break;
					case 6: radixSortWoCountingFreqW2TmpsCombinedIt8Bit(array, k);
							break;
					case 7: radixSortWoCountingFreqW2TmpsCombinedIt8BitWriteBuffer(array, k);
							break;
					default: cout << "this can't happen" << endl;
				}
				time += clock() - t;
			}
			results << (time / repetitions) << ((i != 7) ? "," : "");
		}
		results << endl;
		delete[] array;
	}
	results.close();
}

void testing8BitHardcoded2(int test, string fileEnding) {
	int start = 312999850;
	int inc = 10;
	int end = 313000050;
	int repetitions = 2;
	ofstream results;
	string testFunc = "";

	results.open("data/8 bit hardcoded anomalies" + fileEnding + ".csv");
	results << "input,";
	results << "sort back arr,";
	results << "2 tmp combined iteration";
	results << "\n";
	for (int k = start; k <= end; k= k+inc) {
		results << k << ",";
		int *array = new int[k];
		for (int i=1; i<=2;i++) {
			long time = 0;
			for (int rep=0; rep<repetitions;rep++) {
				srand(25); // use srand to make the arrays identical
				for (int j = 0; j<k; j++) {
					array[j] = rand();
				}
				clock_t t = clock();
				switch(i) {
					case 1: radixSortWoCountingFreqCopyBackArr8Bit(array, k);
							break;
					case 2: radixSortWoCountingFreqW2TmpsCombinedIt8Bit(array, k);
							break;
					default: cout << "this can't happen" << endl;
				}
				time += clock() - t;
			}
			results << (time / repetitions) << ((i != 2) ? "," : "");
		}
		cout << "test 1 done on " << k << " out of " << end << endl;
		results << endl;
		delete[] array;
	}
	results.close();
}

void testingStdSort(int test, string fileEnding) {
	int start = 20000000;
	int inc   = 20000000;
	int end = 1000000000;
	int repetitions = 3;
	ofstream results;
	string testFunc = "";

	results.open("data/std sort" + fileEnding + ".csv");
	results << "input,";
	results << "sort back arr,";
	results << "std sort";
	results << "\n";
	for (int k = start; k <= end; k+=inc) {
		results << k << ",";
		int *array = new int[k];
		for (int i=1; i<=2;i++) {
			long time = 0;
			for (int rep=0; rep<repetitions;rep++) {
				srand(24); // use srand to make the arrays identical
				for (int j = 0; j<k; j++) {
					array[j] = rand();
				}
				clock_t t = clock();
				switch(i) {
					case 1: radixSortWoCountingFreqCopyBackArr8Bit(array, k);
							break;
					case 2: sort(array, array+k);
							break;
					default: cout << "this can't happen" << endl;
				}
				time += clock() - t;
			}
			results << (time / repetitions) << ((i != 4) ? "," : "");
		}
		cout << "test 2 done on " << k << " out of " << end << endl;
		results << endl;
		delete[] array;
	}
	results.close();
}

void testingStdSortAlmostSorted(int test, string fileEnding) {
	int start = 0;
	int inc   = 1000;
	int end = 200000000;
	int repetitions = 2;
	ofstream results;
	string testFunc = "";

	results.open("data/standard sort almost sorted" + fileEnding + ".csv");
	results << "input,";
	results << "sort back arr,";
	results << "std sort";
	results << "\n";

	for (int k = start; k <= 150000; k+=inc) {
		results << k << ",";
		int *array = new int[end];
		int *array2 = new int[end];
		array[0] = 0;
		long timeRadix = 0;
		long timeStd = 0;
		for (int rep=0; rep<repetitions;rep++) {
			srand(24); // use srand to make the arrays identical
			for (int j = 1; j<end; j++) {
				array[j] = array[j-1] + 10;
			}
			for (int j = 0; j<k; j++) {
				array[rand() % end] = rand();
			}
			for (int j = 0; j<end; j++) {
				array2[j] = array[j];
			}
			clock_t t = clock();
			radixSortWoCountingFreqCopyBackArr8Bit(array, end);
			timeRadix += clock() - t;
			t = clock();
			sort(array2, array2+end);
			timeStd += clock() - t;
		}
		results << (timeRadix / repetitions) << "," << (timeStd / repetitions) << endl;
		delete[] array;
		delete[] array2;
		cout << "test 3 done on " << k << " out of " << end << endl;
	}
	results.close();
}

int main(int argc, char* argv[]) {
	if (argc != 1) {
		int test = atoi(argv[1]);
		string testName = "";
		if (argc == 3) {
			testName = argv[2];
		}
		if (test == 12) {
			testingStandard8Bit(test, testName);
		} else if (test == 13) {
			testingMatrix8Bit(test, testName);
		} else if (test == 14) {
			testing8BitHardcoded(test, testName);
		} else if (test == 15) {
			testing8BitHardcoded2(test, testName);
		} else if (test == 16) {
			testingStdSort(test, testName);
		} else if (test == 17) {
			testingStdSortAlmostSorted(test, testName);
		} else {
			testing(test, testName);
		}
	} else {
	}
}

void initialTest() {
	int start = 1 << 20;
	int end = (1 << 20) * 100;
	int inc = 10000000;
	// Test 1
	for (int i=1; i<=16;i++) {
		for (int k = start; k < end; k+=inc) {
			int *array = new int[k];
			srand(24); // use srand to make the arrays identical
			for (int j = 0; j<k; j++) {
				array[j] = rand();
			}
			// Test this function call
			radixSort(array, k, i);

			delete[] array;
		}
	}
	// Test 2
	for (int i=1; i<=16;i++) {
		for (int k = start; k < end; k+=inc) {
			int *array = new int[k];
			srand(24); // use srand to make the arrays identical
			for (int j = 0; j<k; j++) {
				array[j] = rand();
			}
			// Test this function call
			radixSortWoCopyBack(array, k, i);

			delete[] array;
		}
	}
	// Test 3
	for (int i=1; i<=16;i++) {
		for (int k = start; k < end; k+=inc) {
			int *array = new int[k];
			srand(24); // use srand to make the arrays identical
			for (int j = 0; j<k; j++) {
				array[j] = rand();
			}
			// Test this function call
			int **pointers = radixSortWoCountingFreqPointerArray(array, k, i);

			// finish test before this
			for (int j = 0, end = (1 << i); j < end; j++) {
				free(pointers[j]);
			}
			free(pointers);
			delete[] array;
		}
	}
}

