#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

	
typedef struct _word{
	char str[30];
	int num;
}word;

void charComp(char var, int *count);
void print(char *file, int array[], int arr2[], word arr3[], word arr4[], word arr5[], int j);
void lengthFinder(char x, int *i, int *count);
void stringParser(char x, int *i, int *j, word *counts);
void sort(word *alpha, word *nums, int i);

int main(int argc, char *argv[]){
FILE *fPtr, *oPtr;
int charCount[27];
int lengthCount[30];
word *counts, *alpha, *nums;
char x, prev;
int i, j, sum = 0;
char *string;
fPtr  = fopen(argv[1], "r");
for(i = 0; i <= 26; i++)
	charCount[i] = 0;
for(i = 0; i <= 29; i++)
	lengthCount[i] = 0;

if(fPtr == NULL){
	printf("File: %s not found\n", argv[1]);
	exit(1);
}
i = 0;
while((x = fgetc(fPtr)) != EOF){
	charComp(x, charCount);
	lengthFinder(x, &i, lengthCount);
	}
lengthCount[i-1]++;
for(i = 0; i <= 29; i++){
	sum += lengthCount[i];
}
counts = malloc( sum * sizeof(word));
alpha = malloc( sum * sizeof(word));
nums = malloc( sum * sizeof(word));
for(i = 0; i< sum; i++){
	counts[i].str[0] = ' ';
	counts[i].num = 0;
}
rewind(fPtr);
i = 0;
j = 0;
while((x = fgetc(fPtr)) != EOF){
	stringParser(x, &i, &j, counts);
	j++;
	prev = x;
	}
if(isalpha(prev) && x == EOF){
	counts[i].num++;
}
if(counts[i].str[0] == ' '){
i--;
} else {
	for(j=0; j< i; j++){
		if(strcmp(counts[j].str, counts[i].str) == 0 && counts[i].num ==0){
			counts[j].num++;
			i--;
		} else if( strcmp(counts[j].str, counts[i].str) == 0 && counts[i].num ==1){
			i--;
			counts[j].num++;
		}
	}

}
for(j=0; j<=i; j++){
alpha[j] = counts[j];
nums[j] = counts[j];
}

sort(alpha, nums, i+1);
print(argv[2], charCount, lengthCount, counts, alpha, nums, i);	

fclose(fPtr);
return 0;
}

void sort(word *alpha, word *nums, int i){
int j, k;
word temp;
for(j = 0; j < i; j++)
    for(k = 0; k < i-1; k++)
      if(strcmp(alpha[k].str, alpha[k+1].str) > 0) {
        temp = alpha[k+1];
        alpha[k+1] = alpha[k];
        alpha[k] = temp;
      }
for(j=0; j<=i; j++){
nums[j] = alpha[j];
}
for(j = 0; j < i; j++)
    for(k = 0; k < i-1; k++)
      if(nums[k].num > nums[k+1].num) {
        temp = nums[k+1];
        nums[k+1] = nums[k];
        nums[k] = temp;
      }
}

void stringParser(char x, int *i, int *j, word *counts){
	int k, l, r;
	r = *i;
	if(isalpha(x) || x== '\''){
		counts[*i].str[*j] = toupper(x);
	} else {
		counts[*i].str[*j] = '\0';
		 for(k=0; k <= *i; k++){
			if((strcmp(counts[k].str, counts[*i].str)==0) && counts[*i].str[0] != '\0'){
				counts[k].num++;
				break;
			}
		} 
		if((*i == k || strcmp(counts[k].str, counts[*i].str)!=0) && counts[*i].str[0] != '\0'){
			(*i)++;
		}
	if(*i == r){
		counts[*i].str[0] = ' ';
		for(l = 1; l < 30; l++)
		counts[*i].str[l] = '\0';
		}
	*j=-1;
	
	}
}

void lengthFinder(char x, int *i, int *count){
	if(isalpha(x) || x== '\'' )
		(*i)++;
	else {
		count[*i-1]++;
		*i = 0;
	}
}

void charComp(char var, int *count){
switch(var){
		case 'a':
		case 'A':
			count[0]++;
			break;
		case 'b':
		case 'B':
			count[1]++;
			break;
		case 'c':
		case 'C':
			count[2]++;
			break;
		case 'd':
		case 'D':
			count[3]++;
			break;
		case 'e':
		case 'E':
			count[4]++;
			break;
		case 'f':
		case 'F':
			count[5]++;
			break;
		case 'g':
		case 'G':
			count[6]++;
			break;
		case 'h':
		case 'H':
			count[7]++;
			break;
		case 'i':
		case 'I':
			count[8]++;
			break;
		case 'j':
		case 'J':
			count[9]++;
			break;
		case 'k':
		case 'K':
			count[10]++;
			break;
		case 'l':
		case 'L':
			count[11]++;
			break;
		case 'm':
		case 'M':
			count[12]++;
			break;
		case 'n':
		case 'N':
			count[13]++;
			break;
		case 'o':
		case 'O':
			count[14]++;
			break;
		case 'p':
		case 'P':
			count[15]++;
			break;
		case 'q':
		case 'Q':
			count[16]++;
			break;
		case 'r':
		case 'R':
			count[17]++;
			break;
		case 's':
		case 'S':
			count[18]++;
			break;
		case 't':
		case 'T':
			count[19]++;
			break;
		case 'u':
		case 'U':
			count[20]++;
			break;
		case 'v':
		case 'V':
			count[21]++;
			break;
		case 'w':
		case 'W':
			count[22]++;
			break;
		case 'x':
		case 'X':
			count[23]++;
			break;
		case 'y':
		case 'Y':
			count[24]++;
			break;
		case 'z':
		case 'Z':
			count[25]++;
			break;
		default:
			count[26]++;
			break;
		}
}

void print(char *file, int array[], int arr2[], word arr3[], word arr4[], word arr5[], int j){
char base = 97;
FILE *ptr;
int i;
if(file == NULL){
	printf("Letter | Count\n");
	for(i = 0; i <= 25; i++)
		if(array[i] != 0)
			printf("%c -----|---- %d\n", base+i, array[i]); 
	//printf("Other -|---- %d\n", array[26]);
	printf("\n");
	printf("\n");
	
	printf("Length | Count\n");
	for(i = 0; i <= 8; i++)
		if(arr2[i] != 0)
			printf(" %d ----|---- %d\n", i+1, arr2[i]);
	for(i = 9; i <= 29; i++)
		if(arr2[i] != 0)
		printf("%d ----|---- %d\n", i+1, arr2[i]); 
	printf("\n");
	printf("\n");
	
	printf("Word counts:\n");
	printf("As encountered:\n");
	printf("             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		printf("%30s    |    %d\n", arr3[i].str , arr3[i].num);
	printf("\n");
	
	printf("Alphabetically ordered:\n");
	printf("             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		printf("%30s    |    %d\n", arr4[i].str , arr4[i].num);
	printf("\n");
	
	printf("Sorted by occurrence:\n");
	printf("             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		printf("%30s    |    %d\n", arr5[i].str , arr5[i].num);
	printf("\n");
} else {
	ptr = fopen(file, "w+");
	fprintf(ptr, "Letter | Count\n");
	for(i = 0; i <= 25; i++)
		if(array[i] != 0)
			fprintf(ptr, "%c ----|---- %d\n", base++, array[i]); 
	//fprintf(ptr, "Other -|---- %d\n", array[26]);
	fprintf(ptr, "\n");
	fprintf(ptr, "\n");
	
	fprintf(ptr, "Length | Count\n");
	for(i = 0; i <= 8; i++)
		if(arr2[i] != 0)
			fprintf(ptr, " %d ----|---- %d\n", i+1, arr2[i]); 
	for(i = 9; i <= 29; i++)
		if(arr2[i] != 0)
			fprintf(ptr, "%d ----|---- %d\n", i+1, arr2[i]);
	fprintf(ptr, "\n");
	fprintf(ptr, "\n");
	
	fprintf(ptr, "Word counts:\n");
	fprintf(ptr, "As encountered:\n");
	fprintf(ptr, "             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		fprintf(ptr, "%30s    |    %d\n", arr3[i].str , arr3[i].num);
	fprintf(ptr, "\n");
	
	fprintf(ptr, "Alphabetically ordered:\n");
	fprintf(ptr, "             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		fprintf(ptr, "%30s    |    %d\n", arr4[i].str , arr4[i].num);
	fprintf(ptr, "\n");
	
	fprintf(ptr, "Sorted by occurrence:\n");
	fprintf(ptr, "             Word                 |  Count\n");
	for(i = 0; i <= j; i++)
		fprintf(ptr, "%30s    |    %d\n", arr5[i].str , arr5[i].num);
	fprintf(ptr, "\n");
	
	fclose(ptr);
}	
}