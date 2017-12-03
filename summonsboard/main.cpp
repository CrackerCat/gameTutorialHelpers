#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

HWND gameWindow;

void tap(int x, int y)
{
    SetForegroundWindow(gameWindow);
    Sleep(200);

    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
void doubleTap(int x, int y)
{
    SetForegroundWindow(gameWindow);
    Sleep(200);

    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}

void holdDown(int x, int y)
{
    SetForegroundWindow(gameWindow);
    Sleep(200);

    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    Sleep(100);
}

void release(int x, int y)
{
    SetForegroundWindow(gameWindow);
    Sleep(200);

    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
    Sleep(100);
}

void moveFinger(int x, int y, int fingerCommand)
{
    SetForegroundWindow(gameWindow);
    Sleep(200);

    POINT ptFinger;
    RECT windowPosition;

    GetWindowRect(gameWindow, &windowPosition);

    int finalX = (windowPosition.left + x) + rand() % 3;
    int finalY = (windowPosition.top + y) + rand() % 3;

    GetCursorPos(&ptFinger);

    int mX = ptFinger.x;
    int mY = ptFinger.y;

    while (mX != finalX || mY != finalY)
    {
        GetCursorPos(&ptFinger);

        mX = ptFinger.x;
        mY = ptFinger.y;
        int dy = 0;
        int dx = 0;
        if (finalX > mX)
        {
            if (mX != finalX)
                dx = 1 + rand() % 5;
        } else
        {
            if(mX != finalX)
                dx = -1 - rand() % 5;
        }

        if (finalY > mY)
        {
            if (mY != finalY)
                dy = 1 + rand() % 5;
        } else
        {
            if (mY != finalY)
                dy = -1 - rand() % 5;
        }

        SetCursorPos(mX + (dx), mY + (dy));

        SetForegroundWindow(gameWindow);
        Sleep(10);
    }

    if (fingerCommand == 1)
        tap(finalX, finalY);
    else if (fingerCommand == 2)
        doubleTap(finalX, finalY);
    else if (fingerCommand == 3)
        holdDown(finalX, finalY);
    else if (fingerCommand == 4)
        release(finalX, finalY);

}

bool isYellow(int x, int y)
{
    SetForegroundWindow(gameWindow);
    RECT windowPosition;

    GetWindowRect(gameWindow, &windowPosition);

    int finalX = (windowPosition.left + x);
    int finalY = (windowPosition.top + y);

    bool result = false;

    COLORREF color;
    HDC hDC;

    //get device context for the screen
    hDC = GetDC(NULL);
    if(hDC == NULL)
    {
        return 3;
    }

    //retrieve color
    color = GetPixel(hDC, finalX, finalY);
    if (color == CLR_INVALID)
        return 1;

    //release device context again
    ReleaseDC(GetDesktopWindow(), hDC);

    if(GetRValue(color) > 200 && GetGValue(color) > 150 && GetBValue(color) < 50)
        result = true;

    Sleep(10);

    return result;
}

bool isGreen(int x, int y)
{
    SetForegroundWindow(gameWindow);
    RECT windowPosition;

    GetWindowRect(gameWindow, &windowPosition);

    int finalX = (windowPosition.left + x);
    int finalY = (windowPosition.top + y);

    bool result = false;

    COLORREF color;
    HDC hDC;

    //get device context for the screen
    hDC = GetDC(NULL);
    if(hDC == NULL)
    {
        return 3;
    }

    //retrieve color
    color = GetPixel(hDC, finalX, finalY);
    if (color == CLR_INVALID)
        return 1;

    //release device context again
    ReleaseDC(GetDesktopWindow(), hDC);

    if(GetRValue(color) == 98 && GetGValue(color) == 162 && GetBValue(color) == 86)
        result = true;

    Sleep(10);

    return result;
}

bool tileOccupied(int x, int y)
{
    SetForegroundWindow(gameWindow);
    RECT windowPosition;

    GetWindowRect(gameWindow, &windowPosition);

    int finalX = (windowPosition.left + x);
    int finalY = (windowPosition.top + y);

    bool result = true;

    COLORREF color;
    HDC hDC;

    //get device context for the screen
    hDC = GetDC(NULL);
    if(hDC == NULL)
    {
        return 3;
    }

    //retrieve color
    color = GetPixel(hDC, finalX, finalY);
    if (color == CLR_INVALID)
        return 1;

    //release device context again
    ReleaseDC(GetDesktopWindow(), hDC);

    if(GetRValue(color) == 0 && GetGValue(color) == 0 && GetBValue(color) == 0)
        result = false;

    Sleep(10);

    return result;
}

int main()
{
    srand(time(NULL));
    POINT ptFinger;
    RECT windowPosition;

    gameWindow = FindWindow(NULL, TEXT("Andy"));

    if (gameWindow == NULL)
    {
        cout << "Couldn't find window." << endl;
        system("pause");
        return 0;
    }

    SetForegroundWindow(gameWindow);

    Sleep(5000);

    GetWindowRect(gameWindow,&windowPosition);

    GetCursorPos(&ptFinger);

    cout << "Ok" << endl;

    bool running = true;

    while (running)
    {
        bool agree = false;
        while (!agree)
        {
            if (isGreen(270,480))
            {
                moveFinger(300, 480, 1);
                Sleep(2000);
                moveFinger(320, 440, 1);
                cout << "Agreed to terms" << endl;
                agree = true;
            }

            Sleep(500);
        }

        //start screen
        bool start = false;
        while (!start)
        {
            if (isYellow(265, 465))
            {
                moveFinger(265, 465, 1);
                cout << "Application starting" << endl;
                start = true;
            }

            Sleep(500);
        }

        // "choose right/left hand"
        bool handChosen = false;
        while (!handChosen)
        {
            if (isGreen(277, 450))
            {
                moveFinger(277, 450, 1);
                cout << "Chosen hand" << endl;
                handChosen = true;
            }
            Sleep(1000);
        }

        bool introductionDone = false;
        int instructionCount = 0;
        while (!introductionDone)
        {
            if (isGreen(200, 400))
            {
                moveFinger(200, 400, 1);
                instructionCount ++;
            }
            Sleep(1000);

            if (instructionCount == 4)
            {
                cout << "Done with instructions" << endl;
                introductionDone = true;
            }

        }

        bool monsterChosen = false;
        while (!monsterChosen)
        {
            if (isGreen(360, 666))
            {
                moveFinger(360, 666, 1);
                Sleep(1000);
                moveFinger(290, 420, 1);
                Sleep (3000);
                cout << "Monster Chosen" << endl;
                monsterChosen = true;
            }
        }

        bool fightingInstructionsDone = false;
        int fightingInstructionsCount = 0;
        while (!fightingInstructionsDone)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructionsCount ++;
                Sleep(1000);
            }

            if (fightingInstructionsCount == 9)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructionsDone = true;
            }
        }

        bool moveMonster = false;
        //4
        while (!moveMonster)
        {
            Sleep(2000);
            moveFinger(400,300,3);
            moveFinger(290,300,4);
            cout << "Monster moved" << endl;
            moveMonster = true;
        }

        bool fightingInstructions2Done = false;
        int fightingInstructions2Count = 0;

        while (!fightingInstructions2Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions2Count ++;
                Sleep(1000);
            }

            if (fightingInstructions2Count == 4)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions2Done = true;
            }
        }

        bool moveMonster2 = false;
        while (!moveMonster2)
        {
            Sleep(2000);
            moveFinger(400, 200, 3);
            moveFinger(170, 200, 4);
            cout << "Monster moved" << endl;
            moveMonster2 = true;
        }

        //7 to double

        bool fightingInstructions3Done = false;
        int fightingInstructions3Count = 0;

        while (!fightingInstructions3Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions3Count ++;
                Sleep(1000);
            }

            if (fightingInstructions3Count == 7)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions3Done = true;
            }
        }

        bool monsterAttacked = false;
        while (!monsterAttacked)
        {
            if (isYellow(290, 300))
            {
                moveFinger(290,300,2);
                cout << "Monster attacked" << endl;
                monsterAttacked = true;
            }
        }

        bool fightingInstructions4Done = false;
        int fightingInstructions4Count = 0;

        while (!fightingInstructions4Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions4Count ++;
                Sleep(1000);
            }

            if (fightingInstructions4Count == 4)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions4Done = true;
            }
        }

        bool moveMonster3 = false;

        while (!moveMonster3)
        {
            Sleep(1500);
            moveFinger(170, 200, 3);
            moveFinger(170, 300, 4);
            cout << "Monster moved" << endl;
            moveMonster3 = true;
        }

        bool fightingInstructions5Done = false;

        while (!fightingInstructions5Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions5Done = true;
            }

            Sleep(500);
        }

        bool moveMonster4 = false;

        while(!moveMonster4)
        {
            Sleep(1000);
            moveFinger(400, 200, 3);
            moveFinger(60, 200, 4);
            moveMonster4 = true;
        }

        bool instruction2Done = false;
        int instruction2DoneCount = 0;

        while (!instruction2Done)
        {
            if(isGreen(200,440))
            {
                moveFinger(200, 440, 1);
                instruction2DoneCount ++;
                Sleep(500);
            }

            if (instruction2DoneCount == 2)
                instruction2Done = true;
        }

        //click anywhere
        Sleep(4000);
        moveFinger(200, 440, 1);
        cout << "Monster Dropped" << endl;

        bool instruction3Done = false;
        //ok button

        while (!instruction3Done)
        {
            if(isGreen(200,630))
            {
                moveFinger(200, 630, 1);
                cout << "End Battle 1" << endl;
                instruction3Done = true;
            }
        }

        bool instruction4Done = false;
        int instruction4DoneCount = 0;

        while (!instruction4Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction4DoneCount ++;
                Sleep(500);
            }

            if (instruction4DoneCount == 2)
                instruction4Done = true;
        }

        //monster tab
        Sleep(1000);
        moveFinger(400, 220, 1);
        Sleep(1000);
        moveFinger(200, 220, 1);
        Sleep(1000);

        bool instruction5Done = false;
        int instruction5DoneCount = 0;

        while (!instruction5Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction5DoneCount ++;
                Sleep(500);
            }

            if (instruction5DoneCount == 2)
                instruction5Done = true;
        }

        Sleep(500);
        moveFinger(310, 150, 1);

        bool instruction6Done = false;

        while (!instruction6Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction6Done = true;
            }
            Sleep(500);
        }

        bool arrowClicked = false;
        while (!arrowClicked)
        {
            if (isYellow(150, 380))
            {
                moveFinger(150,300,1);
                cout << "Monster selected" << endl;
                arrowClicked = true;
            }

            Sleep(500);
        }

        bool instruction7Done = false;
        int instruction7DoneCount = 0;

        while (!instruction7Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction7DoneCount ++;
                Sleep(500);
            }

            if (instruction7DoneCount == 4)
                instruction7Done = true;
        }

        bool arrowClicked2 = false;
        while (!arrowClicked2)
        {
            if (isYellow(360, 670))
            {
                moveFinger(420,680,1);
                cout << "Back to Menu" << endl;
                arrowClicked2 = true;
            }

            Sleep(500);
        }

        bool instruction8Done = false;

        while (!instruction8Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction8Done = true;
            }
            Sleep(500);
        }

        Sleep(500);
        //Home tab 400,150
        moveFinger(400,150,1);

        Sleep(500);
        moveFinger(200, 320, 1);
        Sleep(1000);
        moveFinger(200, 320, 1);
        Sleep(1000);
        moveFinger(300,440,1);
        cout << "Dungeon entered" << endl;

        bool fightingInstructions6Done = false;
        int fightingInstructions6Count = 0;

        while (!fightingInstructions6Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions6Count ++;
                Sleep(1000);
            }

            if (fightingInstructions6Count == 3)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions6Done = true;
            }
        }

        Sleep(1000);
        moveFinger(60,640,1);
        cout << "Skill Selected" << endl;

        bool fightingInstructions7Done = false;
        int fightingInstructions7Count = 0;

        while (!fightingInstructions7Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions7Count ++;
                Sleep(1000);
            }

            if (fightingInstructions7Count == 3)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions7Done = true;
            }
        }

        Sleep(1000);
        moveFinger(400, 640, 1);
        cout << "Activate Skill" << endl;

        bool fightingInstructions8Done = false;
        int fightingInstructions8Count = 0;

        while (!fightingInstructions8Done)
        {
            if (isGreen(200, 550))
            {
                moveFinger(200, 550, 1);
                fightingInstructions8Count ++;
                Sleep(1000);
            }

            if (fightingInstructions8Count == 6)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions8Done = true;
            }
        }

        //first move in fighting
        Sleep(500);
        moveFinger(400,200,3);
        moveFinger(170,200,4);

        //two situations: the boss monster attacks or moves forward
        Sleep(5000);

        if (tileOccupied(230,355))
        {
            moveFinger(170,200,2);
        } else
        {
            moveFinger(400,300,3);
            moveFinger(300,300,4);
        }

        //keep on double tapping until done with fight
        bool fightingInstructions9Done = false;
        int fightingInstructions9Count = 0;

        while (!fightingInstructions9Done)
        {
            if (isGreen(200, 440))
            {
                moveFinger(200, 440, 1);
                fightingInstructions9Count ++;
                Sleep(1000);
            } else if (!isGreen(200,440))
            {
                moveFinger(170,200,2);
                Sleep(3000);
            }

            if (fightingInstructions9Count == 3)
            {
                cout << "Done with fighting instructions" << endl;
                fightingInstructions9Done = true;
            }
        }

        Sleep(5000);
        moveFinger(200, 440, 1);
        cout << "Monster dropped" << endl;

        bool instruction9Done = false;
        //ok button

        while (!instruction9Done)
        {
            if(isGreen(200,630))
            {
                moveFinger(200, 630, 1);
                cout << "End Battle 2" << endl;
                instruction9Done = true;
            }
        }

        bool instruction10Done = false;
        int instruction10DoneCount = 0;

        while (!instruction10Done)
        {
            if(isGreen(200,400))
            {
                moveFinger(200, 400, 1);
                instruction10DoneCount ++;
                Sleep(500);
            }

            if (instruction10DoneCount == 2)
                instruction10Done = true;
        }

        Sleep(1000);
        moveFinger(420, 360,1);

        Sleep(1000);
        moveFinger(100,530,1);

        bool roll = false;

        while (!roll)
        {
            if (isYellow(140,320))
            {
                cout << "Is yellow" << endl;
                moveFinger(140,320,3);
                moveFinger(330,320,3);
                moveFinger(240,500,4);

                cout << "Rolled" << endl;

                roll = true;
            }
            Sleep(1000);
        }

        do {
            string reply = "";
            cout << "Keep? y or n" << endl;
            cin >> reply;

            if (reply == "y")
            {
                running = false;
                break;
            }
            if (reply == "n")
            {
                //go back to home to clear data
                moveFinger(230, 720, 1);

                Sleep(2000);
                //Hold the app icon
                moveFinger(370,145,3);
                Sleep(3000);

                moveFinger(340,30,4);

                Sleep(1000);

                moveFinger(340,270,1);
                Sleep(500);
                moveFinger(300,400,1);

                moveFinger(230,720,1);
                Sleep(1500);
                moveFinger(230,720,1);

                moveFinger(370,145,1);

                break;
            }
        } while (true);


    }

    return 0;
}
