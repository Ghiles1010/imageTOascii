#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include <map>
#include<string>
#include<fstream>
#include <vector>


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


float luminance(float R, float G, float B){
        return (0.2126 * R + 0.7152 * G + 0.0722 * B);
}

float avgPxL(float arr[]) {

    float s = 0;

        for (int j = 0; j < 8; j++) {

            s = s + arr[j];
        }
    
    return (s / 64);
}

char find_char(float avg) {

    for (std::map<float, std::vector<char>>::iterator it=bToC.begin(); it!=bToC.end(); it++) {

        if (it->first >= avg) {

            return(it->second[0]);
        }
    }

 
}

int main()
{
    std::string input;
    sf::Image image;

    std::ofstream outfile;
    
    outfile.open("ascii_img.txt");

   
    image.loadFromFile("mm.jpg");
    sf::Vector2u vect = image.getSize();

    int width =vect.x;
    int height = vect.y;
    float avg_lum=0;
    sf::Color color;
    char c;
    int a, b;
    int size;

    

    do {

        std::cout << "Enter the size of the bloc of pixels (>0 and <10): ";
        std::cin >> size;

    } while ((size < 0) || (size > 10));

    
    
   
    for (int b_x = 0; b_x < height - size; b_x = b_x + size) {

        for (int b_y = 0; b_y < width -size; b_y = b_y + size) {


            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {

                    a = x + b_x;
                    b = y + b_y;

                    color = image.getPixel(b, a);
                    avg_lum += luminance(color.r, color.g, color.b);

                }
            }

            avg_lum = avg_lum / (size*size);
            c = find_char(1 - (avg_lum / 255)); //on divise par 255 pour avoir une valeur entre 0 et 1
            outfile << c;
                  
            
        }


        

            
        outfile << "\n";
            
    }

        
       

    
       


    outfile.close();

    std::cout << "Done";


    
    
    
    return 0;
}