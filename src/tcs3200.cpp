/*  CPP FILE - TCS3200 library
 *  TCS3200 color sensor library
 *  author: Panjkrc
 *  date: 12/14/2019
 *  url: https://github.com/Panjkrc/TCS3200_library
 */

#include "Arduino.h"
#include "tcs3200.h"

tcs3200::tcs3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t output)
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(output, INPUT);

	_S0 = S0;
	_S1 = S1;
	_S2 = S2;
	_S3 = S3;
	_output = output;
}

int tcs3200::colorRead(char color, int scaling)
{

	switch (scaling)
	{
	case 0:
		digitalWrite(_S0, LOW); // Set scaling to 0%(scaling is turned OFF)
		digitalWrite(_S1, LOW);
		break;

	case 2:
		digitalWrite(_S0, LOW); // Set scaling to 2%
		digitalWrite(_S1, HIGH);
		break;

	case 20: // Set scaling to 20%
		digitalWrite(_S0, HIGH);
		digitalWrite(_S1, LOW);
		break;

	case 100: // Set scaling to 100%
		digitalWrite(_S0, HIGH);
		digitalWrite(_S1, HIGH);
		break;

	default: // Set default scaling (default scaling is 20%)
		digitalWrite(_S0, HIGH);
		digitalWrite(_S1, LOW);
		break;
	}

	switch (color)
	{
	case 'r': // Setting red filtered photodiodes to be read
		digitalWrite(_S2, LOW);
		digitalWrite(_S3, LOW);
		break;

	case 'b': // Setting blue filtered photodiodes to be read
		digitalWrite(_S2, LOW);
		digitalWrite(_S3, HIGH);
		break;

	case 'c': // Setting clear photodiodes(no filters on diodes) to be read
		digitalWrite(_S2, HIGH);
		digitalWrite(_S3, LOW);
		break;

	case 'g': // Setting green filtered photodiodes to be read
		digitalWrite(_S2, HIGH);
		digitalWrite(_S3, HIGH);
		break;

	default:
		digitalWrite(_S2, HIGH);
		digitalWrite(_S3, LOW);
		break;
	}

	unsigned long duration;

	duration = pulseIn(_output, LOW);
	
	if (duration != 0)
	{
		return 1000 / duration; // Reads and returns the frequency of selected color
	}
	else
	{
		return 0;
	}
}

String tcs3200::closestColor(int distinctRGB[][3], String distinctColors[], int num_of_colors)
{
	String colorReturn = "NA"; // return "NA" if no declared color matches color sensor is reading
	int index = closestColorIndex(distinctRGB, num_of_colors);
	return (index == -1 ? colorReturn : distinctColors[index]);
}

int tcs3200::closestColor(int distinctRGB[][3], int distinctColors[], int num_of_colors)
{
	int colorReturn = -1; // return "-1" if no declared color matches color sensor is reading
	int index = closestColorIndex(distinctRGB, num_of_colors);
	return (index == -1 ? colorReturn : distinctColors[index]);
}

int tcs3200::closestColorIndex(int distinctRGB[][3], int num_of_colors)
{
	int index = -1; // return -1 if no declared color matches color sensor is reading
	int biggestDifference = 765;
	int r, g, b;

	r = colorRead('r');
	g = colorRead('g');
	b = colorRead('b');

	for (int i = 0; i < num_of_colors; i++)
	{
		int difference = sqrt(pow(r - distinctRGB[i][0], 2) + pow(g - distinctRGB[i][1], 2) + pow(b - distinctRGB[i][2], 2));
		if (difference < biggestDifference)
		{
			index = i;
			biggestDifference = difference;
		}
	}
	return index;
}

int tcs3200::colorMax()
{

	int r, g, b;

	r = colorRead('r');
	g = colorRead('g');
	b = colorRead('b');

	if ((r > g) && (r > b))
		return 0; // Returns 0 if 'red' is the color with highest value

	if ((g > r) && (g > b))
		return 1; // Returns 1 if 'green' is the color with highest value

	if ((b > r) && (b > g))
		return 2; // Returns 2 if 'blue' is the color with highest value

	if (r == g && r == b)
		return 3; // Returns 3 if all of the colors have the same value

	else
		return 4; // Returns 4 if none of the statments above are fulfilled
}

int tcs3200::colorMin()
{

	int r, g, b;

	r = colorRead('r');
	g = colorRead('g');
	b = colorRead('b');

	if ((r < g) && (r < b))
		return 0; // Returns 0 if 'red' is the color with lowest value

	if ((g < r) && (g < b))
		return 1; // Returns 1 if 'green' is the color with lowest value

	if ((b < r) && (b < g))
		return 2; // Returns 2 if 'blue' is the color with lowest value

	if (r == g && r == b)
		return 3; // Returns 3 if all of the colors have the same value

	else
		return 4; // Returns 4 if none of the statments above are fulfilled
}
