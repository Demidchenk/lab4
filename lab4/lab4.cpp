#include "Header.h"

using namespace std;

int main()
{
    ifstream input("test.bmp", ios::binary);
    bmpHead header;
    input.read((char*)&header, sizeof(bmpHead));
    //input >> header.id[0] >> header.id[1] >> header.filesize >> header.reserved[0] >> header.reserved[1] >> header.headersize >> header.infoSize >> header.width >> header.depth >> header.biPlanes >> header.bits >> header.biCompression >> header.biSizeImage >> header.biXPelsPerMeter >> header.biYPelsPerMeter >> header.biClrUsed >> header.biClrImportant;
    pixelData** pix = new pixelData * [header.width];
    for (int i = 0; i < header.width; i++)
        for (int j = 0; j < header.depth; j++)
            input >> pix[i][j].redComponent >> pix[i][j].greenComponent >> pix[i][j].blueComponent;

    int n;
    cin >> n;
    ofstream output("output.bmp", ios::binary);
    output << header.id[0] << header.id[1] << header.filesize << header.reserved[0] << header.reserved[1] << header.headersize << header.infoSize << header.width * n << header.depth * n << header.biPlanes << header.bits << header.biCompression << header.biSizeImage << header.biXPelsPerMeter << header.biYPelsPerMeter << header.biClrUsed << header.biClrImportant;

    for (int i = 0; i < header.width * n; i++)
        for (int j = 0; j < header.depth * n; j++)
            output << pix[i / n][j / n].redComponent << pix[i / n][j / n].greenComponent << pix[i / n][j / n].blueComponent;
    cout << "Done";
}