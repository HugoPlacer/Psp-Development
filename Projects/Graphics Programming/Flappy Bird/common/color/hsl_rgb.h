struct RGB
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct HSL
{
	int H;
	float S;
	float L;
};

float HueToRGB(float v1, float v2, float vH);

struct RGB HSLToRGB(struct HSL hsl);