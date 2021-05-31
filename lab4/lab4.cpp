#include "Header.h"

using namespace std;

int main()
{
    ifstream input("input.bmp", ios::binary);
    bmpHead header;
    input.read((char*)&header.id, sizeof(int8_t) * 2);
    input.read((char*)&header.filesize, sizeof(int32_t));
    input.read((char*)&header.reserved, sizeof(int16_t)*2);
    input.read((char*)&header.headersize, sizeof(int32_t));
    input.read((char*)&header.infosize, sizeof(int32_t));
    input.read((char*)&header.width, sizeof(int32_t));
    input.read((char*)&header.depth, sizeof(int32_t));
    input.read((char*)&header.biPlanes, sizeof(int16_t));
    input.read((char*)&header.bits, sizeof(int16_t));
    input.read((char*)&header.biCompression, sizeof(int32_t));
    input.read((char*)&header.biSizeImage, sizeof(int32_t));
    input.read((char*)&header.biXPelsPerMeter, sizeof(int32_t));
    input.read((char*)&header.biYPelsPerMeter, sizeof(int32_t));
    input.read((char*)&header.biClrUsed, sizeof(int32_t));
    input.read((char*)&header.biClrImportant, sizeof(int32_t));
    //input.read((char*)&header, sizeof(bmpHead));

    int help = 4 - (header.width * 3 % 4);
    uint8_t help1 = 0;
    pixelData** pix = new pixelData * [header.width];
    for (int i = 0; i < header.width; i++)
        pix[i] = new pixelData[header.depth];
    for (int i = 0; i < header.depth; i++)
    {
        for (int j = 0; j < header.width; j++)
        {
            input.read((char*)&pix[i][j].redComponent, sizeof(int8_t));
            input.read((char*)&pix[i][j].greenComponent, sizeof(int8_t));
            input.read((char*)&pix[i][j].blueComponent, sizeof(int8_t));
        }
        for (int i = 0; i < help; i++)
            input.read((char*)&help1, sizeof(int8_t));
    }

    int n;
    cin >> n;
    header.width *= n;
    header.depth *= n;
    help = 4 - (header.width * 3 % 4);
    if (help == 4) help = 0;

    header.biSizeImage = header.width * header.depth * 3;
    header.filesize = header.biSizeImage + header.headersize;

    ofstream output("output.bmp", ios::binary);
    output.write((char*)&header.id, sizeof(int8_t) * 2);
    output.write((char*)&header.filesize, sizeof(int32_t));
    output.write((char*)&header.reserved, sizeof(int16_t) * 2);
    output.write((char*)&header.headersize, sizeof(int32_t));
    output.write((char*)&header.infosize, sizeof(int32_t));
    output.write((char*)&header.width, sizeof(int32_t));
    output.write((char*)&header.depth, sizeof(int32_t));
    output.write((char*)&header.biPlanes, sizeof(int16_t));
    output.write((char*)&header.bits, sizeof(int16_t));
    output.write((char*)&header.biCompression, sizeof(int32_t));
    output.write((char*)&header.biSizeImage, sizeof(int32_t));
    output.write((char*)&header.biXPelsPerMeter, sizeof(int32_t));
    output.write((char*)&header.biYPelsPerMeter, sizeof(int32_t));
    output.write((char*)&header.biClrUsed, sizeof(int32_t));
    output.write((char*)&header.biClrImportant, sizeof(int32_t));
    //output.write((char*)&header, sizeof(bmpHead));

    for (int i = 0; i < header.depth; i++)
    {
        for (int j = 0; j < header.width; j++)
        {
            output.write((char*)&pix[i / n][j / n].redComponent, sizeof(int8_t));
            output.write((char*)&pix[i / n][j / n].greenComponent, sizeof(int8_t));
            output.write((char*)&pix[i / n][j / n].blueComponent, sizeof(int8_t));
        }
        for (int i = 0; i < help; i++)
            output.write((char*)&help1, sizeof(int8_t));
    }
    cout << "Done";
}