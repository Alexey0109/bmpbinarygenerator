#include "bitmap_image.hpp"
#include <string.h>
#include <iostream>
#include <iomanip>
#define WIDTH 17
using namespace std;

void generate(string outputfile, string bitstream, int dwidth, int dheight)
{
	cout << "Image properties:" << endl;
	cout <<
		setw(WIDTH) << "#WIDTH" <<
		setw(WIDTH) << "#HEIGHT" <<
		setw(WIDTH) << "#BUFFER LENGTH" <<
		setw(WIDTH) << "#OUTPUT FILE" << endl;
		
	bitmap_image image(7 * dwidth, bitstream.length() / 7 * dheight);
	cout <<
		setw(WIDTH) << 7 * dwidth <<
		setw(WIDTH) << bitstream.length() / 7 * dheight <<
		setw(WIDTH) << bitstream.length() <<
		setw(WIDTH) << outputfile << endl;
	
	image.set_all_channels(255, 255, 255);
	int x = 0, y = 0;
	for(int i = 0; i < bitstream.length(); i ++)
	{
		if(bitstream[i] == ' ')
		{
			y += dheight;
			x = 0;
			continue;
		}
		if(bitstream[i] == '1')
			for(int a = y; a < y + dheight; a ++)
				for(int b = x; b < x + dwidth; b ++)
					image.set_pixel(b, a, jet_colormap[1025]);
		else
			for(int a = y; a < y + dheight; a ++)
				for(int b = x; b < x + dwidth; b ++)
					image.set_pixel(b, a, jet_colormap[2000]);
		x += dwidth;
		cout<<"#";
	}
	
	image.save_image(outputfile);
}

int main()
{
	int dw = 0, dh = 0;
	string bitstream, out;
	cout << "Enter bitstream to encode into BMP: ";
	getline(cin, bitstream);
	cout << "Enter filename: ";
	cin >> out;
	cout << "Enter dwidth, dheight: ";
	cin >> dw >> dh;
	generate(out, bitstream, dw, dh);
	return 0;
}
