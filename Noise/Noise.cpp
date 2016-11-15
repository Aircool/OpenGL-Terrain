#include "Noise.h"

Noise::Noise(int seed){

	std::srand(seed);
	this->_FBM = FBM();
}

vec3** Noise::Gradient(){
	
	vec3** gradients = new vec3*[NOISE_SIZE];
	for(int row = 0; row < NOISE_SIZE; ++row)
		gradients[row] = new vec3[NOISE_SIZE];

  	for(int row = 0; row < NOISE_SIZE; ++row){
		for(int col = 0; col < NOISE_SIZE; ++col){

			float rand1 = ((float) std::rand()) / ((float) RAND_MAX);
			float rand2 = ((float) std::rand()) / ((float) RAND_MAX);

			float x = cos(2 * M_PI * rand1);
			float y = sin(2 * M_PI * rand1);

			gradients[row][col] = vec3(x, y, 0.0f);
		}
	}

	return gradients;
}

vec3** Noise::Perlin(vec3** gradients, int period){

	vec3** perlinNoise = new vec3*[NOISE_SIZE];
	for(int row = 0; row < NOISE_SIZE; ++row)
		perlinNoise[row] = new vec3[NOISE_SIZE];
	
	float frequency = 1.0f / period;	
	for(int row = 0; row < NOISE_SIZE; ++row){
		for(int col = 0; col < NOISE_SIZE; ++col){

			int L = (col / period) * period;
			int R = (L + period) % NOISE_SIZE;

			int T = (row / period) * period;
			int B = (T + period) % NOISE_SIZE;

			float dx = fabs((col - L) * frequency);
			float dy = fabs((row - T) * frequency);

			vec3 a(dx, -dy, 0);
			vec3 b(dx - 1, -dy, 0);
			vec3 c(dx - 1, 1 - dy, 0);
			vec3 d(dx, 1 - dy, 0); 

			vec3 TL = gradients[T][L];
			vec3 TR = gradients[T][R];
			vec3 BL = gradients[B][L];
			vec3 BR = gradients[B][R];

			float s = dot(TL, a);
			float t = dot(TR, b);
			float u = dot(BL, d);
			float v = dot(BR, c);
		
			float fadeX = fade(dx);
			float fadeY = fade(dy);

			float st = lerp(s, t, fadeX);
			float uv = lerp(u, v, fadeX);
			float noise = lerp(st, uv, fadeY);
			noise *= sqrt(2.0f);

			if(noise < 0.0f) noise = 0.0f;
			perlinNoise[row][col] = vec3(noise, noise, noise);
		}
	}

	return perlinNoise;
}

vec3** Noise::FBM(){

	vec3** FBM = new vec3*[NOISE_SIZE];
	for(int row = 0; row < NOISE_SIZE; ++row)
		FBM[row] = new vec3[NOISE_SIZE];

	vec3** gradient = Gradient();

	for(int octave = 0; octave < OCTAVES; octave++){

		vec3** perlin = Perlin(gradient, NOISE_SIZE / pow(2, OCTAVES - octave));
		
		for(int row = 0; row < NOISE_SIZE; ++row){
			for(int col = 0; col < NOISE_SIZE; ++col){

				FBM[row][col] += perlin[row][col] * ((float) pow(AMPLITUDE, octave + 1));
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