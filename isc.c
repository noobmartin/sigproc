#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void computeAutoCorrelation(int* input, const int input_length, int* autocorrelation){
	int* conjugate = malloc(input_length*sizeof(int));

	// Compute the conjugate.
	int i = 0;
	for(i = 0; i < input_length; i++){
		conjugate[i] = -1*input[i];
	}

  // Compute the auto-correlation
	unsigned int autocorrelation_length = 2*(input_length - 1) + 1;
  int j = 0;
  for(i = 0; i < autocorrelation_length; i++){
    autocorrelation[i] = 0;
    for(j = 0; j < input_length; j++){
      if((j-i) >= 0){
			  autocorrelation[i] += input[j]*conjugate[j-i];
      }
    }
  }

	free(conjugate);
}

void computeISR(int* input, const int input_length, const int code_length, float* ISR){
	unsigned int i = 0;
	for(i = 1; i < input_length; i++){
		*ISR += input[i]*input[i];
	}
	*ISR *=2;
	*ISR /= (code_length*code_length);
	printf("ISR: %f\n", *ISR);
	printf("ISR: %f dB\n", 10*log10(*ISR));
}

int main(void){
	int code_length = 0;
	printf("Select the length of the Barker code: ");
	scanf("%i", &code_length);
	
	int* code = malloc(code_length*sizeof(int));
	printf("Input the Barker code, one digit at a time and press enter for each:\n");

	int j = 0;
	for(j = 0; j < code_length; j++){
		scanf("%i", &code[j]);
	}

	float ISR = 0.0f;
	int autocorrelation[2*(code_length-1) + 1];
	computeAutoCorrelation(code, code_length, autocorrelation);
	computeISR(autocorrelation, 2*(code_length-1) + 1, code_length, &ISR);

	free(code);
}
