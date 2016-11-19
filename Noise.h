#include <algorithm>

class Noise {
	
public:

	Noise(int seed){

		srand(seed);
		//offsetP();
		randomP();
	}

	float FBM(float x, float y){

		float result = 0.0f;
		float frequency = 1.0f;
		float amplitude = 0.50f;

		for(int octave = 0; octave < OCTAVES; octave++){

			result += Perlin(x * frequency, y * frequency, pow(2, octave)) * amplitude;
			frequency *= LACUNARITY;
			amplitude *= 0.50f;
		}
		
		return result;
	}

	float Perlin(float x, float y, int period){

		int integers[2 * 2];
		float fractions[2 * 2];

		integers[0] = floor(x);
		integers[1] = floor(y);
		integers[2] = ((integers[0] + 1) % period) & 0xff;
		integers[3] = ((integers[1] + 1) % period) & 0xff;

		fractions[0] = x - integers[0];
		fractions[1] = y - integers[1];
		fractions[2] = fractions[0] - 1.0f;
		fractions[3] = fractions[1] - 1.0f;

		integers[0] = (integers[0] % period) & 0xff;
		integers[1] = (integers[1] % period) & 0xff;

		float s = fade(fractions[0]);
		float t = fade(fractions[1]);

		float TL = grad(P[integers[0] + P[integers[1]]], fractions[0], fractions[1]);
		float BL = grad(P[integers[0] + P[integers[3]]], fractions[0], fractions[3]);

		float TR = grad(P[integers[2] + P[integers[1]]], fractions[2], fractions[1]);
		float BR = grad(P[integers[2] + P[integers[3]]], fractions[2], fractions[3]);

		float LERP_Y1 = lerp(TL, BL, t);
		float LERP_Y2 = lerp(TR, BR, t);
		float noise = lerp(LERP_Y1, LERP_Y2, s) / 1.51115f;

		return (noise + 1.0f) * 0.5f;
	}

	int floor(float x){

		return (x > 0) ? ((int) x) : ((int) (x - 1));
	}

	float fade(float t){

		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	float grad(int hash, float x, float y){

		int h = hash & 7;
		float u = h < 4 ? x : y;
		float v = h < 4 ? y : x;
		return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
	}

	float lerp(float x, float y, float ratio){

		return x + (ratio * (y - x));
	}

private:

	void offsetP(){

		int random = std::rand() % 256;
		for(int i = 0; i < 256; i++){

			P[i] = (P[i] + random) % 256;
		}
	}

	void randomP(){

		std::vector<unsigned int> temp;
		for(unsigned int i = 0; i < 256; i++) temp.push_back(i);
	
		for(unsigned int i = 0; i < 256; i++){

			int random = std::rand() % (256 - i);
			P[i]		= temp[random];
			P[i + 256]	= temp[random];
			temp.erase(std::remove(temp.begin(), temp.end(), temp[random]), temp.end());
		}
	}

	float HIGHEST = 0.0f;
	float LOWEST = 1.0f;

	unsigned char P[512] = {

		151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
		140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
  		247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
  		 57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
  		 74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
  		 60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
  		 65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
  		200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
  		 52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
  		207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
  		119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
  		129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
  		218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
  		 81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
  		184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
  		222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,

		151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
		140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
  		247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
  		 57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
  		 74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
  		 60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
  		 65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
  		200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
  		 52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
  		207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
  		119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
  		129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
  		218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
  		 81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
  		184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
  		222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,
	};
};