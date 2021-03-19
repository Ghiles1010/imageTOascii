#include <opencv2/opencv.hpp>
#include<iostream>
#include <map>
#include<string>
#include<fstream>
#include <vector>
#include<stdlib.h>
#include "main.h"


// Characters ordered by number of black pixels
std::map<float, std::vector<char>> bToC =
{
    {0.f, {' ', }},
    {0.133333f, {'.', /*'`',*/ }},
    {0.155556f, {'-', }},
    {0.177778f, {/*'\'', */','/*, '_',*/ }},
    {0.266667f, {':', /*'=', '^', */}},
    {0.311111f, {/*'"', */'+',/* '/', '\\',*/ }},
    {0.333333f, {'~', }},
    {0.355556f, {';',/* '|', */}},
    {0.4f, {'(', /*')', '<', '>', */}},
    {0.444444f, {'%'/*, '?', 'c', 's', '{', '}',*/ }},
    {0.488889f, {/*'!', 'I', '[', ']', 'i', 't', 'v',*/ 'x',/* 'z',*/ }},
    {0.511111f, {'1'/*, 'r', */}},
    {0.533333f, {'*'/*, 'a', 'e', 'l', 'o', */}},
    {0.555556f, {'n', 'u', }},
    {0.577778f, {'T', /*'f', 'w', */}},
    {0.6f, {'3',/* '7',*/ }},
    {0.622222f, {'J', /*'j', 'y',*/ }},
    {0.644444f, {'5', }},
    {0.666667f, {'$',/* '2', '6', '9', 'C', 'L', 'Y', 'm',*/ }},
    {0.688889f, {'S', }},
    {0.711111f, {'4',/* 'g', 'k', 'p', 'q', */}},
    {0.733333f, {'F', 'P',/* 'b', 'd', 'h',*/ }},
    {0.755556f, {'G', 'O', 'V', 'X', }},
    {0.777778f, {'E', 'Z', }},
    {0.8f, {'8', 'A', 'U', }},
    {0.844444f, {'D', 'H', 'K', 'W', }},
    {0.888889f, {/*'&',*/ '@',/* 'R', */}},
    {0.911111f, {'B', 'Q', }},
    {0.933333f, {'#', }},
    {1.f, {'0', 'M', 'N', }},
};

// calculate luminosity
float luminance(float R, float G, float B){
        return (0.2126 * R + 0.7152 * G + 0.0722 * B);
}

// Averagaes colors
float avgPxL(float arr[]) {

    float s = 0;

        for (int j = 0; j < 8; j++) {

            s = s + arr[j];
        }
    
    return (s / 64);
}

// Find appropriate Char to use
char find_char(float avg) {

    for (std::map<float, std::vector<char>>::iterator it=bToC.begin(); it!=bToC.end(); it++) {

        if (it->first >= avg) {

            return(it->second[0]);
        }
    }

 
}



void draw(cv::Mat image) {

    //std::ofstream outfile;

    //outfile.open("ascii_img.txt");
    int height = image.rows, width = image.cols;
    float avg_lum = 0;

    int a, b, size = 2;
    char c;

    
    for (int b_x = 0; b_x <= height - size; b_x = b_x + size) {

        for (int b_y = 0; b_y <= width - size; b_y = b_y + size) {


            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {

                    a = x + b_x;
                    b = y + b_y;

                    cv::Vec3b color = image.at <cv::Vec3b> (a, b);

                    avg_lum += luminance(color[2], color[1], color[0]);

                }
            }

            avg_lum = avg_lum / (size * size);

            // We devide by 255 to get a value between 0 and 1
            c = find_char(avg_lum / 255); 
            //outfile << c;
            std::cout << c;


        }




        std::cout << "\n";
        //outfile << "\n";

    }

    //outfile.close();
}


int main()
{

    const int FPS = 20;

    cv::Mat frame;
    cv::VideoCapture vid(0);

    if (!vid.isOpened()) {

        return -1;
    }

    while (vid.read(frame)) {


        draw(frame);
        system("cls");

    }
    

    return 0;
}