#include "Header.h"

using namespace std;

int main()
{
    ifstream input("test.bmp");
    bmpHead header;
    input >> header.id[0] >> header.id[1] >> header.filesize >> header.reserved[0] >> header.reserved[1] >> header.headersize >> header.infoSize >> header.width >> header.depth >> header.biPlanes >> header.bits >> header.biCompression >> header.biSizeImage >> header.biXPelsPerMeter >> header.biYPelsPerMeter >> header.biClrUsed >> header.biClrImportant;
    pixelData** pix = new pixelData * [header.width];
    for (int i = 0; i < header.width; i++)
        for (int j = 0; j < header.depth; j++)
            input >> pix[i][j].redComponent >> pix[i][j].greenComponent >> pix[i][j].blueComponent;


}