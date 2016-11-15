#include "Noise.h"

Noise::Noise(int seed){

	std::srand(seed);
	this->_FBM = FBM();
}

	
	for(int row = 0; row < NOISE_SIZE; ++row)

  	for(int row = 0; row < NOISE_SIZE; ++row){
		for(int col = 0; col < NOISE_SIZE; ++col){

			float rand1 = ((float) std::rand()) / ((float) RAND_MAX);
			float rand2 = ((float) std::rand()) / ((float) RAND_MAX);

			float x = cos(2 * M_PI * rand1);
			float y = sin(2 * M_PI * rand1);

		}
	}

	return gradients;
}


	for(int row = 0; row < NOISE_SIZE; ++row)
	
	float frequency = 1.0f / period;	
	for(int row = 0; row < NOISE_SIZE; ++row){
		for(int col = 0; col < NOISE_SIZE; ++col){

			int L = (col / period) * period;
			int R = (L + period) % NOISE_SIZE;

			int T = (row / period) * period;
			int B = (T + period) % NOISE_SIZE;

			float dx = fabs((col - L) * frequency);
			float dy = fabs((row - T) * frequency);



		
			float fadeX = fade(dx);
			float fadeY = fade(dy);

			float st = lerp(s, t, fadeX);
			float uv = lerp(u, v, fadeX);
			float noise = lerp(st, uv, fadeY);
			noise *= sqrt(2.0f);

			if(noise < 0.0f) noise = 0.0f;
		}
	}

	return perlinNoise;
}


	for(int row = 0; row < NOISE_SIZE; ++row)


	for(int octave = 0; octave < OCTAVES; octave++){

		
		for(int row = 0; row < NOISE_SIZE; ++row){
			for(int col = 0; col < NOISE_SIZE; ++col){

			}
		}

		free(perlin);
	}

	free(gradient);

	return FBM;
}


float Noise::lerp(float x, float y, float weight){

	return y * weight + x * (1.0f - weight);
}

float Noise::fade(float t){

	float t3 = t * t * t;
	return (6 * t * t * t3) - (15 * t * t3) + (10 * t3);
}
