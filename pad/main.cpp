#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;


//use struct to store orb data
struct Orb
{
    int xCoor;
    int yCoor;
    int xLocation;
    int yLocation;
    string color;
};

void getOrbData(Orb* orbs, int* orbCount)
{
    //for the string of colors, we should prioritize orbs w/ highest damage
    //ie red starter priority #1, heart and dark orbs #6 because they don't do damage in tutorial
    string colors[] = {"r","b","g","d","l","h"};

    //for now coordinates of the orb will be x(1~3),y(1~3)
    int xCoor = 1;
    int yCoor = 1;

    //for now orbs will be random
    //we will identify color of orbs later
    srand(time(NULL));

    for (int i=0; i<9; i++)
    {
        //orb coordinates (1,1) (1,2) ... (3,2) (3,3)
        orbs[i].xCoor = xCoor;
        orbs[i].yCoor = yCoor;
        orbs[i].xLocation = xCoor;
        orbs[i].yLocation = yCoor;
        //random color of orb
        int colorNumber = rand() % 6;
        orbs[i].color = colors[colorNumber];
        //getting specific orb count here
        orbCount[colorNumber] = orbCount[colorNumber] + 1;


        if (yCoor != 3)
        {
            yCoor ++;
        } else
        {
            xCoor ++;
            yCoor = 1;
        }
    }
}

void resetOrbCount(int* orbCount)
{
    for (int i=0; i<6; i++)
    {
        orbCount[i] = 0;
    }
}

int findOrbsToMatch(int* orbCount)
{
    for (int i=0; i<6; i++)
    {
        if (orbCount[i] >= 3)
        {
            return i;
        }
    }

    return -1;
}


//patterns with center orb

void pattern1(Orb* orbs, Orb* matchingOrbs)
{
    // x x o
    // o x o
    // o o o
    cout << "pattern1" << endl;
    //sp = starting point
    //tp = turning point
    //ep = ending point
    int spx = -1;
    int spy = -1;
    int tpx1 = -1;
    int tpy1 = -1;
    int epx = 2;
    int epy = 2;
    //find turning point orb
    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
        {
            //this is turning point 1
            tpx1 = matchingOrbs[i].xCoor;
            tpy1 = matchingOrbs[i].yCoor;

            break;
        }

    }

    //now find starting point
    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
        {
            //vertically next to each other
            if (tpx1 == matchingOrbs[i].xCoor)
            {
                spx = tpx1;
                spy = 4 - (matchingOrbs[i].yCoor);
            } else //horizontally next to each other
            {
                spy = tpy1;
                spx = 4 - (matchingOrbs[i].xCoor);
            }

        }
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changed" << endl;
}



void pattern2(Orb* orbs, Orb* matchingOrbs)
{
    // o x o
    // x x o
    // o o o
    cout << "pattern 2" << endl;

    int spx = -1;
    int spy = -1;
    int tpx1 = 2;
    int tpy1 = 2;
    int epx = -1;
    int epy = -1;

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].yCoor != 2)
        {
            epx = matchingOrbs[i].xCoor;
            epy = matchingOrbs[i].yCoor;
        }

        if (matchingOrbs[i].xCoor != 2)
        {
            spx = 4 - matchingOrbs[i].xCoor;
            spy = matchingOrbs[i].yCoor;
        }
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changed" << endl;
}

void pattern3(Orb* orbs, Orb* matchingOrbs)
{
    // o x o
    // o x o
    // x o o
    cout << "pattern 3" << endl;

    int spx = -1;
    int spy = -1;
    int epx = -1;
    int epy = -1;

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
        {
            epx = matchingOrbs[i].xCoor;
            epy = matchingOrbs[i].yCoor;
        }
    }

    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
        {
            int xDifference = abs(matchingOrbs[i].xCoor-epx);
            int yDifference = abs(matchingOrbs[i].yCoor-epy);

            if (xDifference == 2)
            {
                spx = 4 - matchingOrbs[i].xCoor;
                spy = matchingOrbs[i].yCoor;
            }

            if (yDifference == 2)
            {
                spy = 4 - matchingOrbs[i].yCoor;
                spx = matchingOrbs[i].xCoor;
            }
        }
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changed" << endl;
}

void pattern4(Orb* orbs, Orb* matchingOrbs)
{
    // x o o
    // o x o
    // o o x

    cout << "pattern 4" << endl;

    int spx = 1;
    int spy = 2;
    int tpx1 = 1;
    int tpy1 = -1;
    int tpx2 = 3;
    int tpy2 = -1;
    int epx = 3;
    int epy = -1;

    //starting at (1,2), going up or down, going across, and then going up or down

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor == 1 && matchingOrbs[i].yCoor == 1)
        {
            tpy1 = 1;
            tpy2 = 1;
            epy = 3;
            break;
        }
        //if not on corner(1,1)
        else if (matchingOrbs[i].xCoor == 1 && matchingOrbs[i].yCoor == 3)
        {
            tpy1 = 3;
            tpy2 = 3;
            epy = 1;
            break;
        }
    }

    //passing points
    int ppx1 = 2;
    int ppy1 = tpy1;
    int ppx2 = 3;
    int ppy2 = 2;

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int tp2 = tpy2 + (tpx2 - 1) * 3 - 1;
    int pp2 = ppy2 + (ppx2 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[pp1].color;
    orbs[pp1].color = orbs[tp2].color;
    orbs[tp2].color = orbs[pp2].color;
    orbs[pp2].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;


}

void pattern5(Orb* orbs, Orb* matchingOrbs)
{
    // x o o
    // o x o
    // x o o

    cout << "pattern 5" << endl;

    int spx = -1;
    int spy = -1;
    int epx = 2;
    int epy = 2;

    int totalx = 0;
    int totaly = 0;
    for (int i=0; i<3; i++)
    {
        totalx = totalx + matchingOrbs[i].xCoor;
        totaly = totaly + matchingOrbs[i].yCoor;
    }

    if (totalx == 6 && totaly == 4)
    {
        spx = 2;
        spy = 1;
    }

    if (totalx == 4 && totaly == 6)
    {
        spx = 1;
        spy = 2;
    }

    if (totalx == 8 && totaly == 6)
    {
        spx = 3;
        spy = 2;
    }

    if (totalx == 6 && totaly == 8)
    {
        spx = 2;
        spy = 3;
    }

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}


//patterns without center orb
void pattern6(Orb* orbs, Orb* matchingOrbs)
{
    // x o x
    // x o o
    // o o o

    cout << "pattern 6" << endl;

    int spx = -1;
    int spy = -1;
    int tpx1 = 2;
    int tpy1 = 2;
    int epx = -1;
    int epy = -1;

    int totalx = 0;
    int totaly = 0;

    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
        {
            spx = matchingOrbs[i].xCoor;
            spy = matchingOrbs[i].yCoor;
        } else
        {
            totalx += matchingOrbs[i].xCoor;
            totaly += matchingOrbs[i].yCoor;
        }
    }

    if (totalx == 4 && totaly == 2)
    {
        epx = 2;
        epy = 1;
    }

    if (totalx == 2 && totaly == 4)
    {
        epx = 1;
        epy = 2;
    }

    if (totalx == 6 && totaly == 4)
    {
        epx = 3;
        epy = 2;
    }

    if (totalx == 4 && totaly == 6)
    {
        epx = 2;
        epy = 3;
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern7(Orb* orbs, Orb* matchingOrbs)
{
    // x o o
    // x o x
    // o o o

    cout << "pattern 7" << endl;

    int spx = -1;
    int spy = -1;
    int tpx1 = -1;
    int tpy1 = -1;
    int epx = 2;
    int epy = 2;

    bool verticalOrbs = false;

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
        {
            spx = matchingOrbs[i].xCoor;
            spy = matchingOrbs[i].yCoor;
        } else
        {
            if (matchingOrbs[i].xCoor == 2)
            {
                verticalOrbs = true;
            }
        }
    }

    if (verticalOrbs)
    {
        tpx1 = spx;
        tpy1 = 2;
    } else
    {
        tpx1 = 2;
        tpy1 = spx;
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;

}

void pattern8(Orb* orbs, Orb* matchingOrbs)
{
    // x o o
    // x o o
    // o o x

    cout << "pattern 8" << endl;

    int spx = -1;
    int spy = -1;
    int epx = -1;
    int epy = -1;

    int markerx = -1;
    int markery = -1;

    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
        {
            markerx = matchingOrbs[i].xCoor;
            markery = matchingOrbs[i].yCoor;
            break;
        }
    }

    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == markerx) ^ (matchingOrbs[i].yCoor == markery))
        {
            if (matchingOrbs[i].xCoor == markerx)
            {
                epx = markerx;
                epy = 4 - matchingOrbs[i].yCoor;
            } else
            {
                epx = 4 - matchingOrbs[i].xCoor;
                epy = markery;
            }
        } else if (matchingOrbs[i].xCoor != markerx && matchingOrbs[i].yCoor != markery) //this will have to be the last orb
        {
            spx = matchingOrbs[i].xCoor;
            spy = matchingOrbs[i].yCoor;
        }
    }

    int ppx1 = (spx + epx) / 2;
    int ppy1 = (spy + epy) / 2;

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[pp1].color;
    orbs[pp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern9(Orb* orbs, Orb* matchingOrbs)
{
    // o o o
    // x o x
    // o x o

    cout << "pattern 9" << endl;

    int spx = -1;
    int spy = -1;
    int epx = 2;
    int epy = 2;

    for (int i=0; i<3; i++)
    {
        //compare each orb and see if their coordinate matches
        if (matchingOrbs[i%3].yCoor == matchingOrbs[(i+1)%3].yCoor)
        {
            spx = 2;
            break;
        }
        if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor)
        {
            spy = 2;
            break;
        }
    }

    for (int i=0; i<3; i++)
    {
        if (spx == matchingOrbs[i].xCoor)
        {
            spy = matchingOrbs[i].yCoor;
        }
        if (spy == matchingOrbs[i].yCoor)
        {
            spx = matchingOrbs[i].xCoor;
        }
    }

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern10(Orb* orbs, Orb* matchingOrbs)
{
    // o x o
    // x o o
    // o o x

    cout << "pattern 10" << endl;

    int spx = 2;
    int spy = 2;
    int tpx1 = 2;
    int tpy1 = -1;
    int tpx2 = -1;
    int tpy2 = -1;
    int epx = -1;
    int epy = -1;

    //go from center, up or down, left or right, and then up or down
    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
        {
            epx = matchingOrbs[i].xCoor;
            epy = matchingOrbs[i].yCoor;
        } else if (matchingOrbs[i].xCoor == 2)
        {
            tpy1 = matchingOrbs[i].yCoor;
        } else
        {
           tpx2 = 4 - matchingOrbs[i].xCoor;
        }
    }

    tpy2 = tpy1;

    int ppx1 = tpx2;
    int ppy1 = 2;

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int tp2 = tpy2 + (tpx2 - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[tp2].color;
    orbs[tp2].color = orbs[pp1].color;
    orbs[pp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern11(Orb* orbs, Orb* matchingOrbs)
{
    // x o x
    // o o o
    // x o o

    cout << "pattern 11" << endl;

    int spx = -1;
    int spy = -1;
    int tpx1 = -1;
    int tpy1 = -1;
    int epx = -1;
    int epy = -1;

    int ppx1 = 2;
    int ppy1 = 2;

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor || matchingOrbs[i%3].yCoor == matchingOrbs[(i+1)%3].yCoor)
        {
            //grab the left over orb
            spx = matchingOrbs[(i+2)%3].xCoor;
            spy = matchingOrbs[(i+2)%3].yCoor;
            if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor)
            {
                epx = matchingOrbs[i%3].xCoor;
                epy = 2;
                tpx1 = spx;
                tpy1 = 2;
            } else
            {
                epx = 2;
                epy = matchingOrbs[i%3].yCoor;
                tpx1 = 2;
                tpy1 = spx;
            }
            break;
        }
    }

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[tp1].color;
    orbs[tp1].color = orbs[pp1].color;
    orbs[pp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern12(Orb* orbs, Orb* matchingOrbs)
{
    // x x o
    // x o o
    // o o o

    cout << "pattern 12" << endl;

    int spx = -1;
    int spy = 2;
    int tpx1 = -1;
    int tpy1 = 2;
    int epx = -1;
    int epy = -1;


    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].yCoor == 2)
        {
            spx = matchingOrbs[i].xCoor;
            tpx1 = 4 - spx;
        }
        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
        {
            epy = matchingOrbs[i].yCoor;
            epx = 4 - matchingOrbs[i].xCoor;
        }
    }

    int ppx1 = 2;
    int ppy1 = 2;

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int tp1 = tpy1 + (tpx1 - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[pp1].color;
    orbs[pp1].color = orbs[tp1].color;
    orbs[tp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern13(Orb* orbs, Orb* matchingOrbs)
{
    // x o o
    // x o o
    // o x o

    cout << "pattern 13" << endl;

    int spx = -1;
    int spy = -1;
    int epx = -1;
    int epy = -1;

    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor || matchingOrbs[i%3].yCoor == matchingOrbs[(i+1)%3].yCoor)
        {
            spx = matchingOrbs[(i+2)%3].xCoor;
            spy = matchingOrbs[(i+2)%3].yCoor;

            if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor)
            {
                epx = matchingOrbs[i%3].xCoor;
                epy = spy;
            } else
            {
                epx = spx;
                epy = matchingOrbs[i%3].yCoor;
            }
        }
    }

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;
}

void pattern14(Orb* orbs, Orb* matchingOrbs)
{
    // x o x
    // o o o
    // o x o

    cout << "pattern 14" << endl;

    int spx = -1;
    int spy = -1;
    int epx = -1;
    int epy = -1;

    for (int i=0; i<3; i++)
    {
        if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
        {
            spx = matchingOrbs[i].xCoor;
            spy = matchingOrbs[i].yCoor;

            if (spx == 2)
            {
                epx = 2;
                epy = 4 - spy;
            } else if (spy == 2)
            {
                epy = 2;
                epx = 4 - epx;
            }

            break;
        }
    }

    int ppx1 = 2;
    int ppy1 = 2;

    //we have all the information needed to move orbs

    //all the coordinates into array places
    int sp = spy + (spx - 1) * 3 - 1;
    int pp1 = ppy1 + (ppx1 - 1) * 3 - 1;
    int ep = epy + (epx - 1) * 3 - 1;

    string grabOrbColor = orbs[sp].color;
    orbs[sp].color = orbs[pp1].color;
    orbs[pp1].color = orbs[ep].color;
    orbs[ep].color = grabOrbColor;

    cout << "changing" << endl;

}

void moveScr(Orb* orbs, int orbToMatch)
{
    //first find which pattern
    string colors[] = {"r","b","g","d","l","h"};
    string colorToMatch = colors[orbToMatch];

    //array of three to find orbs to match
    Orb* matchingOrbs = new Orb[3];
    //limiter at 3
    int limiter = 0;
    for (int i=0; i<9; i++)
    {
        if (orbs[i].color == colorToMatch)
        {
            matchingOrbs[limiter] = orbs[i];
            limiter ++;
        }

        if (limiter == 3)
        {
            break;
        }
    }

    int orb1 = -1;
    int orb2 = -1;
    int orb3 = -1;
    int center = 0;

    //see if center orb is matching
    for (int i=0; i<3; i++)
    {
        if (matchingOrbs[i].xCoor == 2 && matchingOrbs[i].yCoor == 2)
        {
            orb1 = i;
            center = 1;
            break;
        }
    }

    //one of the matching orbs is center
    //now see if another orb is adjacent(not on corner)
    if (center == 1)
    {
        for (int i=0; i<3; i++)
        {
            //^ is an 'exclusive or' statement
            if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
            {
                orb2 = i;
                break;
            }
        }

        //if there is an adjacent orb
        if (orb2 != -1)
        {
            int orb2xCoor = matchingOrbs[orb2].xCoor;
            int orb2yCoor = matchingOrbs[orb2].yCoor;

            //find orb3 coordinates
            // 0 + 1 + 2 = 3
            orb3 = 3 - orb1 - orb2;

            int orb3xCoor = matchingOrbs[orb3].xCoor;
            int orb3yCoor = matchingOrbs[orb3].yCoor;

            //now find pattern

            int xDifference = abs(orb2xCoor - orb3xCoor);
            int yDifference = abs(orb2yCoor - orb3yCoor);

            int sumDifferences = xDifference + yDifference;

            if (sumDifferences == 1)
            {
                pattern1(orbs,matchingOrbs);
            }

            if (xDifference == 1 && yDifference == 1)
            {
                pattern2(orbs,matchingOrbs);
            }

            if (sumDifferences == 3)
            {
                pattern3(orbs,matchingOrbs);
            }
        } else
        {
            //no adjacent = corner + corner
            //find if on opposite corners or not
            int cornerNW_SE = 0;
            for (int i=0; i<3; i++)
            {
                if (matchingOrbs[i].xCoor == matchingOrbs[i].yCoor)
                {
                    cornerNW_SE ++ ;
                }
            }

            if (cornerNW_SE % 2 == 1)
            {
                pattern4(orbs,matchingOrbs);
            } else if (cornerNW_SE % 2 == 0)
            {
                pattern5(orbs,matchingOrbs);
            }
        }
    }

    //done with cases with center orb
    //now onto all other cases
    if (center == 0)
    {
        //find if all corners
        int adjacentOrb = -1;
        for (int i=0; i<3; i++)
        {
            if ((matchingOrbs[i].xCoor == 2) ^ (matchingOrbs[i].yCoor == 2))
            {
                adjacentOrb = i;
                break;
            }
        }
        //if all orbs are on corner
        if (adjacentOrb == -1)
        {
            pattern11(orbs,matchingOrbs);
        } else
        {
            //find if next orb is on opposite side
            int oppositeOrb = -1;
            int oppositeOrbx = -1;
            int oppositeOrby = -1;
            int adjacentOrbx = matchingOrbs[adjacentOrb].xCoor;
            int adjacentOrby = matchingOrbs[adjacentOrb].yCoor;

            if (adjacentOrbx == 2)
            {
                oppositeOrbx = adjacentOrbx;
                oppositeOrby = 4 - adjacentOrby;
            } else if (adjacentOrby == 2)
            {
                oppositeOrbx = 4 - adjacentOrbx;
                oppositeOrby = adjacentOrby;
            }

            //now see if there is an orb on other side
            for (int i=0; i<3; i++)
            {
                if ((matchingOrbs[i].xCoor == oppositeOrbx) && (matchingOrbs[i].yCoor == oppositeOrby))
                {
                    oppositeOrb = i;
                    break;
                }
            }

            //there is an orb on opposite side
            // o o o
            // x o x
            // o o o
            if (oppositeOrb != -1)
            {
                //0 + 1 + 2 = 3
                int finalOrb = 3 - oppositeOrb - adjacentOrb;
                if ((matchingOrbs[finalOrb].xCoor == 2) ^ (matchingOrbs[finalOrb].yCoor == 2))
                {
                    pattern9(orbs,matchingOrbs);
                } else
                {
                    pattern7(orbs,matchingOrbs);
                }
            } else //now find if there is an orb next to adjacent orb
            {
                int adjacentOrbNotCenter = -1;
                char notCenterAxis = 'z';
                if (adjacentOrbx == 2)
                {
                    adjacentOrbNotCenter = adjacentOrby;
                    notCenterAxis = 'y';
                } else
                {
                    adjacentOrbNotCenter = adjacentOrbx;
                    notCenterAxis = 'x';
                }

                int adjacentAdjacentOrb = -1;
                int adjacentAdjacentOrbx = -1;
                int adjacentAdjacentOrby = -1;

                for (int i=0; i<3; i++)
                {
                    if (notCenterAxis == 'y')
                    {
                        if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor == adjacentOrbNotCenter)
                        {
                            adjacentAdjacentOrb = i;
                            adjacentAdjacentOrbx = matchingOrbs[i].xCoor;
                            adjacentAdjacentOrby = matchingOrbs[i].yCoor;
                            break;
                        }
                    } else
                    {
                        if (matchingOrbs[i].xCoor == adjacentOrbNotCenter && matchingOrbs[i].yCoor != 2)
                        {
                            adjacentAdjacentOrb = i;
                            adjacentAdjacentOrbx = matchingOrbs[i].xCoor;
                            adjacentAdjacentOrby = matchingOrbs[i].yCoor;
                            break;
                        }
                    }
                }

                //find final orb if there is an adjacent orb next to the first selected orb
                if (adjacentAdjacentOrb != -1)
                {
                    //0 + 1 + 2 = 3
                    int finalOrb = 3 - adjacentOrb - adjacentAdjacentOrb;
                    int finalOrbx = matchingOrbs[finalOrb].xCoor;
                    int finalOrby = matchingOrbs[finalOrb].yCoor;
                    int xDiff = abs(finalOrbx - adjacentAdjacentOrbx);
                    int yDiff = abs(finalOrby - adjacentAdjacentOrby);
                    int totalDiff = xDiff + yDiff;
                    if (totalDiff == 1)
                    {
                        pattern12(orbs,matchingOrbs);
                    }else if (totalDiff == 2)
                    {
                        pattern6(orbs,matchingOrbs);
                    }else if (totalDiff == 3)
                    {
                        pattern13(orbs,matchingOrbs);
                    }else if (totalDiff == 4)
                    {
                        pattern8(orbs,matchingOrbs);
                    }

                } else //now see if the other orbs are both in the furthest corner
                {
                    int furthestCount = 0;
                    for (int i=0; i<3; i++)
                    {
                       if (matchingOrbs[i].xCoor != 2 && matchingOrbs[i].yCoor != 2)
                       {
                           furthestCount ++;
                       }
                    }
                    if (furthestCount == 0)
                    {
                        pattern9(orbs,matchingOrbs);
                    } else if (furthestCount == 1)
                    {
                        int sameRow = 0;
                        for (int i=0; i<3; i++)
                        {
                            if (matchingOrbs[i%3].xCoor == matchingOrbs[(i+1)%3].xCoor || matchingOrbs[i%3].yCoor == matchingOrbs[(i+1)%3].yCoor)
                            {
                                sameRow ++;
                            }
                        }
                        if (sameRow == 0)
                        {
                            pattern10(orbs,matchingOrbs);
                        } else if (sameRow == 1)
                        {
                            pattern13(orbs,matchingOrbs);
                        }
                    } else if (furthestCount == 2)
                    {
                        pattern14(orbs,matchingOrbs);
                    }
                }
            }
        }
    }

    delete [] matchingOrbs;
}

void printScr(Orb* orbs)
{
    cout << orbs[0].color << orbs[1].color << orbs[2].color << endl;
    cout << orbs[3].color << orbs[4].color << orbs[5].color << endl;
    cout << orbs[6].color << orbs[7].color << orbs[8].color << endl;
}

int main()
{
    Orb* orbs = new Orb[9];
    int orbCount[] = {0,0,0,0,0,0};

    int orbToMatch = -1;
    while (orbToMatch == -1)
    {
        getOrbData(orbs,orbCount);
        orbToMatch = findOrbsToMatch(orbCount);
        resetOrbCount(orbCount);
    }

    printScr(orbs);

    moveScr(orbs,orbToMatch);

    printScr(orbs);

    delete [] orbs;

    return 0;
}
