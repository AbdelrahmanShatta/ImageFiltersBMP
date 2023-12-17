// Last Modification Date:	19/10/2023
// Author:	Abdelrahman ashraf 

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <bits/stdc++.h>

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char part1[SIZE / 2][SIZE / 2];
unsigned char part2[SIZE / 2][SIZE / 2];
unsigned char part3[SIZE / 2][SIZE / 2];
unsigned char part4[SIZE / 2][SIZE / 2];

void loadImage(); // defines  the funciton explained and coded below
void saveImage();

void black_white();

void vflip();

void edges();

void hflip();

void shrink(float quarter);

void invert();

void crop(int x, int y, int l, int w);

void lighter();

void darker();

void shuffle(int input[]);

void loadImage2();

void enlarge(int quad);

void rotate(int rotation);

void merge();

void blur();

void rightskew(float theta);

void upskew(float theta);

int main() {
    loadImage(); // loads the images
    char user_choice;

    while (true) { // itereates over various filters untill the user saves/exists
        cout
                << "Please select a filter to apply or 0 to exit:\n1-    Black & White Filter\n2-    Invert Filter\n3-    Merge Filter\n4-    Flip Image\n5-    Darken and Lighten Image\n6-    Rotate Image\n7-    Detect Image Edges\n8-    Enlarge Image\n9-    Shrink Image\na-    Mirror 1/2 Image\nb-    Shuffle Image\nc-    Blur Image\nd-    Crop Image\ne-    Skew Image Right\nf-    Skew Image Up\ns-    Save the image to a file\n0-    Exit"
                << endl;
        cin >> user_choice;

        if (user_choice == 's') // exits and saves the image
            break;
        if (user_choice == '0') // exists wihout saving the image
            return 0;

        if (isdigit(user_choice)) {                                         // checks if the user inputed a char digit
            user_choice = int(user_choice - '0'); // coverts the char to int

            switch (user_choice) // uses the switch function to use different filters given the choice of the user
            {
                case 1:
                    black_white();
                    cout << "Done------------------" << endl;
                    break;
                case 2:
                    invert();
                    cout << "Done------------------" << endl;
                    break;
                case 3:
                    loadImage2();
                    merge();
                    cout << "Done------------------" << endl;
                    break;
                case 4:
                    char in;
                    cout << "Flip (h)orizontally or (v)ertically ?" << endl;
                    cin >> in;
                    if (in == 'v') {
                        vflip();
                    } else {
                        hflip();
                    }
                    cout << "Done------------------" << endl;
                    break;
                case 5:
                    char letter;
                    cout << "Do you want to (d)arken or (l)ighten?" << endl;
                    cin >> letter;
                    if (letter == 'd') {
                        darker();
                    } else {
                        lighter();
                    }
                    cout << "Done------------------" << endl;
                    break;
                case 6:
                    int rotation;
                    cout << "Rotate (90), (180),(270) or (360) degrees?" << endl;
                    cin >> rotation;
                    rotate(rotation);
                    break;
                case 7:
                    edges();
                    break;
                case 8:
                    cout << "Which quarter to enlarge 1, 2, 3 or 4?" << endl;
                    int quad;
                    cin >> quad;
                    enlarge(quad);
                    break;
                case 9:
                    cout << "Shrink to (0.5), (0.   ) or (0.25)?" << endl;
                    float quarter;
                    cin >> quarter;
                    shrink(quarter);
                    break;
            }
        }
        //_________________________________________
        if (user_choice == 'a') {
            cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << endl;
            char userinput;
            cin >> userinput;
            if (userinput == 'l') {
                for (int i = 0; i < SIZE; i++) // left half
                {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][SIZE - j - 1] = image[i][j];
                    }
                }
            } else if (userinput == 'r') {
                for (int i = 0; i < SIZE; i++) // right half
                {
                    for (int j = 0; j < SIZE / 2; j++) {
                        image[i][j] = image[i][SIZE - j - 1];
                    }
                }
            } else if (userinput == 'u') {
                for (int i = 0; i < SIZE / 2; i++) // upper half
                {
                    for (int j = 0; j < SIZE; j++) {
                        image[SIZE - i - 1][j] = image[i][j];
                    }
                }
            } else if (userinput == 'd') {
                for (int i = 0; i < SIZE / 2; i++) // lower half
                {
                    for (int j = 0; j < SIZE; j++) {
                        image[i][j] = image[SIZE - i - 1][j];
                    }
                }
            }
        } else if (user_choice == 'b') {
            int a, b, c, d;
            cout << "New order of quarters ?" << endl;
            cin >> a >> b >> c >> d;
            int input[] = {a, b, c, d};
            shuffle(input);
        } else if (user_choice == 'c') {
            blur();
        } else if (user_choice == 'd') {
            int x, y, l, w;
            cout << "Please enter x y l w " << endl;
            cin >> x >> y >> l >> w;
            crop(x, y, l, w);
        } else if (user_choice == 'e') {
            float theta;
            cout << "Please enter degree to skew right" << endl;
            cin >> theta;
            rightskew(theta);
        } else if (user_choice == 'f') {
            float theta;
            cout << "Please enter degree to skew up" << endl;
            cin >> theta;
            upskew(theta);
        }
    }

    saveImage();
    cout << "Done------------------" << endl;
    return 0;
}

void loadImage() {
    char imageFileName[100]; // Gets the gray scale of the  image

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // loads the image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void loadImage2() {
    char imageFileName[100]; // gets the gray scale of anohter image if needed for multipile image operations

    cout << "Enter the 2nd image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp"); // loads the 2nd image if needed for multipile image operations
    readGSBMP(imageFileName, image2);
}

//________________________________________
void saveImage() { // addes .bmp to the image extentsion and saves the image
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________

void
black_white() { // takes the average of image pixel intensity overall and uses it as a threshold, anythng below the average is pure black and everything above average is pure white
    int avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }

    avg = avg / (256 * 256);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

//_________________________________________
void vflip() { // fips the image around its vertical axis by reversing the pixel array

    reverse(begin(image), end(image));
}

void hflip() { // fips the image around its horizontal  axis by reversing each array in the 2d array

    for (int i = 0; i < SIZE; i++) {
        reverse(begin(image[i]), end(image[i]));
    }
}

//_________________________________________
void invert() { // inverts the pixel colour by subtracting it from pure white (255)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = abs(255 - image[i][j]);
        }
    }
}

//_________________________________________
void darker() { // darknes the pixel intensity by half(50%)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j] / 2);
        }
    }
}

void lighter() { // increases the pixel intensity by half(50%)
    int avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] += (255 - image[i][j]) * 0.5;
        }
    }
}

//_________________________________________
void merge() { // merges two images together by taking the average pixel intensity of each image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

//_________________________________________
void rotate(int rotation) { // rotates the image by 90, 180, 270 or 360 in clockwise direction
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }
    if (rotation == 360) {
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[j][(SIZE - 1) - i] = image2[i][j];
        }
    }
    if (rotation == 90) {
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[j][(SIZE - 1) - i] = image2[i][j];
        }
    }
    if (rotation == 180) {
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[j][(SIZE - 1) - i] = image2[i][j];
        }
    }
    if (rotation == 270) {
        return;
    }
}

//_________________________________________
void edges() {
    int avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }

    avg = avg / (256 * 256);

    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            image2[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }

    int x = 40;

    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if ((image2[i - 1][j] - image2[i][j]) > x || (image2[i][j - 1] - image2[i][j]) > x ||
                (image2[i + 1][j] - image2[i][j]) > x || (image2[i][j + 1] - image2[i][j]) > x ||
                (image2[i + 1][j + 1] - image2[i][j]) > x || (image2[i - 1][j - 1] - image2[i][j]) > x) {
                image[i][j] = 13;
            }
        }
    }
}

void enlarge(int quad) {
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            image2[i][j] = image[i][j];
        }
    }

    // first quad
    if (quad == 1) {
        int x;
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                x = image2[i / 2][j / 2];
                image[i][j] = x;
                image[i + 1][j] = x;
                image[i][j + 1] = x;
                image[i + 1][j + 1] = x;
            }
        }
    }
        // second quad
    else if (quad == 2) {
        int x;
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                x = image2[i / 2][(j + SIZE) / 2];
                image[i][j] = x;
                image[i + 1][j] = x;
                image[i][j + 1] = x;
                image[i + 1][j + 1] = x;
            }
        }
    }
        // third quad
    else if (quad == 3) {
        int x;
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                x = image2[(i + SIZE) / 2][j / 2];
                image[i][j] = x;
                image[i + 1][j] = x;
                image[i][j + 1] = x;
                image[i + 1][j + 1] = x;
            }
        }
    }

        // fourth quad
    else if (quad == 4) {
        int x;
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                x = image2[(i + SIZE) / 2][(j + SIZE) / 2];
                image[i][j] = x;
                image[i + 1][j] = x;
                image[i][j + 1] = x;
                image[i + 1][j + 1] = x;
            }
        }
    }
}

void shrink(float quarter) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }
    float avg = 0;
    float scale = 1.0 / quarter;
    for (int i = 0; i < SIZE / int(scale); i++) {
        for (int j = 0; j < SIZE / int(scale); j++) {
            avg = 0;
            for (int k = 0; k < int(scale); k++) {
                for (int l = 0; l < int(scale); l++) {
                    avg += image2[i * int(scale) + k][j * int(scale) + l];
                }
            }
            avg = avg / float(int(scale) * int(scale));
            image[i][j] = avg;
        }
    }
}

void shuffle(int input[]) {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            part1[i][j] = image[i][j];
            part2[i][j] = image[i + SIZE / 2][j];
            part3[i][j] = image[i][j + SIZE / 2];
            part4[i][j] = image[i + SIZE / 2][j + SIZE / 2];
        }
    }
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            image[i + ((input[0] - 1) % 2) * SIZE / 2][j + ((input[0] - 1) / 2) * SIZE / 2] = part1[i][j];
            image[i + ((input[1] - 1) % 2) * SIZE / 2][j + ((input[1] - 1) / 2) * SIZE / 2] = part2[i][j];
            image[i + ((input[2] - 1) % 2) * SIZE / 2][j + ((input[2] - 1) / 2) * SIZE / 2] = part3[i][j];
            image[i + ((input[3] - 1) % 2) * SIZE / 2][j + ((input[3] - 1) / 2) * SIZE / 2] = part4[i][j];
        }
    }
}

void crop(int x, int y, int l, int w) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i >= x && i < x + l && j >= y && j < w + y) {
            } else {
                image[i][j] = 255;
            }
        }
    }
}

void rightskew(float theta) {

    theta = float(tan(theta * M_PI / 180.0));
    float s = theta * 256;
    float step = s / 256;
    float s_temp = s;
    char image2[SIZE + int(s)][SIZE + int(s)];

    // white
    for (int i = 0; i < SIZE + int(s); i++) {
        for (int j = 0; j < SIZE + int(s); j++) {
            image2[i][j] = 255;
        }
    }

    // white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = 255;
        }
    }

    // skew
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j + int(s)] = image[i][j];
        }
        s = s - step;
    }

    // shrink
    float v = ceil((256 + s_temp)) / 256;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // if(image2[i][j]!=255)
            image3[i][j] = image2[i][int(j * v)];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image3[i][j];
        }
    }
}

void upskew(float theta) {
    theta = tan(theta * M_PI / 180.0);
    float s = theta * 256;
    float step = s / 256;
    float so = s;
    char image2[SIZE + int(s)][SIZE + int(s)];

    // white
    for (int i = 0; i < SIZE + int(s); i++) {
        for (int j = 0; j < SIZE + int(s); j++) {
            image2[i][j] = 255;
        }
    }

    // white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = 255;
        }
    }

    // skew
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            image2[i + int(s)][j] = image[i][j];
        }
        s = s - step;
    }
    // shrink
    float v = ceil((256 + so)) / 256;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = image2[int(i * v)][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image3[i][j];
        }
    }
}

void blur() {   
    for (int k = 0; k < 8; k++) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = (image[i][j] * 4 + image[i][j + 1] * 2 + image[i][j - 1] * 2 + image[i + 1][j] * 2 +
                                image[i - 1][j] * 2 + image[i - 1][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1] +
                                image[i + 1][j + 1]) / 16;
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[i][j];
            }
        }
    }
}