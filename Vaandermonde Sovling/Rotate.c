#include <stddef.h>
#include <math.h>

void Tuple_Rotate (size_t length, double * tuple) {
	double c;
	double s;
	double alpha;
	for (int i = 1; i < (int) length; i++) {
		alpha = copysign(sqrt(tuple[0] * tuple[0] + tuple[i] * tuple[i]), tuple[0]);
		if (tuple[i] == 0) {
			c = 1; s = 0;
		} else {
			c = tuple[0] / alpha;
			s = - tuple[i] / alpha;
		}
		tuple[0] = c * tuple[0] - s * tuple[i];
		tuple[i] = s / c;
	}
}

void Tuple_Rotate_Back (size_t length, double * tuple) {
	double alpha;
	double c;
	double s;
	
	for (int i = (int) length - 2; i >= 0; i--) {
		alpha = tuple[0];
		c = sqrt(1 / (1 + tuple[i+1] * tuple[i+1]));
		
		// edge case when t is infinity
		if (c == 0) {
			s = copysign(1.0, tuple[i+1]);
		} else {
			s = c * tuple[i+1];
		}
		
		tuple[0] = c * alpha;
		tuple[i + 1] = - s * alpha;
	}
}