#include <iostream>
#include <windows.h>
#include <winable.h>
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
        holdDown(finalX, finalY);
    else if (fingerCommand == 3)
        release(finalX, finalY);

}

//doesnt work on the andy module
void pressKey(WORD key)
{
    Sleep(500);

    INPUT *keyClick;
    keyClick = new INPUT;
    keyClick -> ki.wVk = key;
    keyClick->type = INPUT_KEYBOARD;
    keyClick->ki.dwFlags = 0;
    keyClick->ki.time = 0;
    keyClick->ki.wScan = 0;
    keyClick->ki.dwExtraInfo = 0;

    SendInput(1,keyClick,sizeof(INPUT));

    Sleep(100);

    keyClick->ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1,keyClick,sizeof(INPUT));
}

bool isWhite(int x, int y)
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

    if(GetRValue(color)  == GetGValue(color) && GetRValue(color) == GetBValue(color) && GetRValue(color) >= 125)
        result = true;

    Sleep(10);

    return result;
}

bool isBlack(int x, int y)
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

    if(GetRValue(color)  == GetGValue(color) && GetRValue(color) == GetBValue(color) && GetRValue(color) < 125)
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

    if(GetRValue(color) > 80 && GetRValue(color) < 140 && GetGValue(color) > 160 && GetGValue(color) < 200 && GetBValue(color) < 50)
        result = true;

    Sleep(10);

    return result;
}

bool isRed(int x, int y)
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

    if(GetRValue(color) > 200 && GetGValue(color) < 100 && GetBValue(color) < 100)
        result = true;

    Sleep(10);

    return result;
}

bool isBlue(int x, int y)
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

    if(GetRValue(color) < 50 && GetGValue(color) > 150 && GetBValue(color) > 200)
        result = true;

    Sleep(10);

    return result;
}

bool isBlue2(int x, int y)
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

    if(GetRValue(color) < 50 && GetGValue(color) < 100 && GetBValue(color) > 200)
        result = true;

    Sleep(10);

    return result;
}

bool gameFinished(int x, int y)
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

    if(GetRValue(color) > 200 && GetGValue(color) > 100 && GetGValue(color) < 200 && GetBValue(color) < 50)
        result = true;

    Sleep(10);

    return result;
}

bool findGuide(int x, int y)
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

    if(GetRValue(color) == 254 && GetGValue(color) == 223 && GetBValue(color) == 203)
        result = true;

    Sleep(10);

    return result;
}

int main()
{
    //if black @ 300 300 click 200 400

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

    //Wait here for the game to load and prepare for botting
    // aka movie time
    Sleep(5000);

    GetWindowRect(gameWindow,&windowPosition);

    GetCursorPos(&ptFinger);

    cout << "Ok" << endl;

    bool running = true;

    while (running)
    {
        bool dataDownload = false;
        while (!dataDownload)
        {
            if (isBlack(300,300))
            {
                moveFinger(200,400,1);
                cout << "Download started. Please wait..." << endl;
                dataDownload = true;
            }

            Sleep(500);
        }

        Sleep (30000);

        bool startScreen = false;
        while (!startScreen)
        {
            if (isWhite(50,50))
            {
                Sleep(2000);
                moveFinger(200,400,1);
                cout << "Download complete! Let's get started" << endl;
                startScreen = true;
            }

            Sleep(1000);
        }

        //agree to terms

        Sleep(3000);
        moveFinger(300,500,1);

        //type in name
        Sleep(2000);
        moveFinger(300,500,1);
        Sleep(2000);

        //have to get pop up keyboard because presskey() doesn't work
        //it works on normal word documents
        //"hiro"
        moveFinger(250,600,1);
        Sleep(100);
        moveFinger(320,550,1);
        Sleep(100);
        moveFinger(170,550,1);
        Sleep(100);
        moveFinger(360,550,1);

        //ok button for entering name
        moveFinger(200,300,1);

        Sleep(3000);
        //word bubble
        moveFinger(200,300,1);
        Sleep(1500);
        //confirm
        moveFinger(170,400,1);
        //long load
        Sleep(5000);

        //word bubble
        moveFinger(190,400,1);
        Sleep(3000);
        moveFinger(170,400,1);

        //click banner on bottom to start success mode
        bool banner = false;
        while (!banner)
        {
            if (isGreen(80,640))
            {
                moveFinger(200,650,1);
                cout << "Success mode started" << endl;
                banner = true;
            }

            Sleep(1000);
        }

        //word bubble after long load
        bool intro1 = false;
        int intro1c = 0;
        while (!intro1)
        {
            if (findGuide(370,450))
            {
                Sleep(1700);
                moveFinger(200,500,1);
                intro1c ++;
            }

            if (intro1c == 5)
                intro1 = true;

            Sleep(1000);
        }

        Sleep(1000);

        //click on success mode
        moveFinger(200,300,1);

        //3 times
        bool intro2 = false;
        while (!intro2)
        {
            if(findGuide(370,350))
            {
                for (int i=0; i<3; i++)
                {
                    Sleep(2500);
                    moveFinger(200,300,1);
                }
                intro2 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);

        //confirm entry form
        moveFinger(200,580,1);
        cout << "Entry form submitted" << endl;


        bool intro3 = false;
        int intro3c = 0;
        while (!intro3)
        {
            if(findGuide(370,500))
            {
                Sleep(2500);
                moveFinger(200,580,1);
                intro3c ++;
            }

            //there is one spot where the guide is not there
            //but you have to click
            if (intro3c == 1)
            {
                Sleep(1500);
                moveFinger(200,580,1);
                intro3c++;
            }

            if (intro3c == 6)
                intro3 = true;

            Sleep(1000);
        }

        Sleep(1000);
        moveFinger(300,650,1);
        cout << "Rolling..." << endl;

        bool endRoll = false;
        while (!endRoll)
        {
            if (isRed(180,670))
            {
                moveFinger(250,670,1);
                cout << "Rolled SUBARU" << endl;
                endRoll = true;
            }

            Sleep(1000);
            moveFinger(250,540,1);
        }

        //confirm roll result
        Sleep(1000);
        moveFinger(250,540,1);

        bool intro4 = false;
        while (!intro4)
        {
            if(findGuide(370,500))
            {
                for(int i=0; i<3; i++)
                {
                    Sleep(2000);
                    moveFinger(250,540,1);
                }
                intro4 = true;
            }

            Sleep(1000);
        }

        //confirm deck
        Sleep(1000);
        moveFinger(250,540,1);
        cout << "Deck confirmed" << endl;

        bool intro5 = false;
        while (!intro5)
        {
            if(findGuide(370,350))
            {
                for(int i=0; i<8; i++)
                {
                    Sleep(2500);
                    moveFinger(250,540,1);
                }
                intro5 = true;
            }

            Sleep(1000);
        }

        //start story
        Sleep(1500);
        moveFinger(250,570,1);
        cout << "Story started" << endl;

        Sleep(4000);

        bool faster = false;
        while (!faster)
        {
            if(findGuide(380,350))
            {
                moveFinger(220,670,1);
                faster = true;
            }

            Sleep(1000);
        }

        Sleep(3000);
        bool practice = false;
        while(!practice)
        {
            if (isBlue(150,460))
            {
                moveFinger(220,470,1);
                practice = true;
            }

            Sleep(1000);
        }

        Sleep(3000);

        //batting practice
        moveFinger(50,600,1);
        Sleep(500);
        moveFinger(50,550,1);
        cout << "Batting practice finished" << endl;

        Sleep(4000);

        //status up
        bool statusWindow = false;
        while (!statusWindow)
        {
            if (isRed(400,450))
            {
                moveFinger(400,450,1);
                cout << "Increasing status..." << endl;
                statusWindow = true;
            }

            Sleep(1000);
        }

        Sleep(5000);
        //one instruction
        moveFinger(400,450,1);

        Sleep(1000);
        //up button
        moveFinger(130,400,1);

        Sleep(1000);
        //confirm status upgrade
        moveFinger(370,660,1);
        cout << "Status upgraded" << endl;

        //one instruction
        Sleep(4000);
        moveFinger(370,660,1);

        //rest
        Sleep(2000);
        moveFinger(60,480,1);
        cout << "Resting..." << endl;

        Sleep(1000);

        bool noPractice = false;
        while (!noPractice)
        {
            if (isBlue2(100,320))
            {
                moveFinger(100,310,1);
                cout << "NO PRACTICING" << endl;
                noPractice = true;
            }

            Sleep(1000);
        }

        Sleep(1000);

        bool intro6 = false;

        while (!intro6)
        {
            if(findGuide(370,350))
            {
                Sleep(2000);
                moveFinger(60,310,1);
                Sleep(2000);
                moveFinger(100,500,1);
                intro6 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);
        //confirm finish
        moveFinger(200,650,1);
        Sleep(500);
        moveFinger(300,380,1);
        cout << "Story finished" << endl;

        Sleep(5000);

        //exit screen
        moveFinger(420,65,1);

        Sleep(1000);
        bool intro7 = false;

        while (!intro7)
        {
            if(findGuide(370,350))
            {
                Sleep(2000);
                moveFinger(420,65,1);
                Sleep(2000);
                moveFinger(330,300,1);
                intro7 = true;
            }

            Sleep(1000);
        }

        Sleep(2000);
        moveFinger(150,650,1);
        cout << "Adding player..." << endl;

        Sleep(1000);
        moveFinger(200,270,1);

        bool intro8 = false;
        while (!intro8)
        {
            if(findGuide(370,130))
            {
                Sleep(2000);
                moveFinger(200,270,1);
                Sleep(2500);
                moveFinger(180,270,1);
                intro8 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);
        //drag
        cout << "Dragging player..." << endl;
        moveFinger(150,270,2);
        Sleep(200);
        moveFinger(150,670,3);

        Sleep(2500);

        //one instruction
        moveFinger(150,550,1);
        Sleep(1000);
        moveFinger(150,370,1);
        cout << "Selected new player" << endl;
        Sleep(500);
        //go back
        moveFinger(50,240,1);

        Sleep(2000);
        //one instruction
        moveFinger(50,240,1);

        bool intro9 = false;
        while (!intro9)
        {
            if(findGuide(370,130))
            {
                Sleep(1500);
                moveFinger(50,240,1);
                Sleep(2500);
                moveFinger(50,200,1);
                intro9 = true;
            }

            Sleep(1000);
        }

        Sleep(500);

        //go back
        moveFinger(50,50,1);


        //*******LOGIN BONUS MUST CHANGE EVERY DAY*********//
        Sleep(4000);
        moveFinger(230,620,1);
        cout << "Login bonus" << endl;

        Sleep(2000);

        bool intro10 = false;
        while (!intro10)
        {
            if(findGuide(370,450))
            {
                for(int i=0; i<5; i++)
                {
                    Sleep(2500);
                    moveFinger(230,500,1);
                }
                intro10 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);
        moveFinger(280,390,1);
        cout << "Hear stadium details" << endl;

        Sleep(2000);
        //one instruction
        moveFinger(280,400,1);
        Sleep(500);
        moveFinger(400,570,1);

        Sleep(2000);
        //one instruction
        moveFinger(370,550,1);
        Sleep(500);
        moveFinger(250,300,1);
        cout << "Enter Stadium mode" << endl;

        bool intro11 = false;
        while (!intro11)
        {
            if(findGuide(370,440))
            {
                for(int i=0; i<5; i++)
                {
                    Sleep(2500);
                    moveFinger(250,310,1);
                }
                intro11 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);
        moveFinger(250,300,1);
        cout << "Play game" << endl;

        Sleep(1000);
        bool intro12 = false;
        while (!intro12)
        {
            if(findGuide(370,100))
            {
                for(int i=0; i<2; i++)
                {
                    Sleep(2500);
                    moveFinger(250,310,1);
                }
                intro12 = true;
            }

            Sleep(1000);
        }

        Sleep(500);
        //choose center opponent
        moveFinger(250,350,1);
        Sleep(1000);

//4
        while (!findGuide(370,350))
            Sleep(500);

        //click 4 times
        //popups occur all over the place
        for (int i=0; i<4; i++)
        {
            Sleep(2500);
            moveFinger(250,350,1);
        }

        Sleep(1500);
        //smiley faces
        moveFinger(350,620,1);

        while(!findGuide(370,350))
            Sleep(1000);

        Sleep(2000);
        cout << "Extra click" << endl;
        moveFinger(350,610,1);
        Sleep(2000);
        //next button
        moveFinger(370,620,1);

        Sleep(2500);
        //one instruction
        moveFinger(300,500,1);

        Sleep(1000);
        //Choose items to bring
        moveFinger(90,200,1);
        Sleep(500);
        moveFinger(150,200,1);

        Sleep(1000);
        moveFinger(200,550,1);
        cout << "Start game" << endl;

        Sleep(3000);

        bool gameOver = false;
        while (!gameOver)
        {
            if(gameFinished(365,490))
                gameOver = true;

            //this is where the selection for throwing straights is
            moveFinger(220,420,1);
            Sleep(2500);
        }

        cout << "Game over" << endl;

        moveFinger(370,560,1);

        Sleep(1000);
        bool intro13 = false;
        while (!intro13)
        {
            if(findGuide(370,300))
            {
                for(int i=0; i<3; i++)
                {
                    Sleep(2500);
                    moveFinger(300,500,1);
                }
                intro13 = true;
            }

            Sleep(1000);
        }

        Sleep(2000);
        moveFinger(300,450,1);
        cout << "View rankings" << endl;

        Sleep(1000);
        bool intro14 = false;
        while (!intro14)
        {
            if(findGuide(370,450))
            {
                for(int i=0; i<6; i++)
                {
                    Sleep(2500);
                    moveFinger(300,400,1);
                }
                intro14 = true;
            }

            Sleep(1000);
        }

        Sleep(1000);
        //next tab
        moveFinger(250,240,1);
        Sleep(2000);

        //three instructions
        for(int i=0; i<3; i++)
        {
            Sleep(2500);
            moveFinger(260,240,1);
        }

        Sleep(1000);
        //last tab
        moveFinger(350,240,1);

        //last set of instructions
         for(int i=0; i<4; i++)
        {
            Sleep(2500);
            moveFinger(320,240,1);
        }

        Sleep(1500);
        //back button
        moveFinger(50,100,1);
        cout << "All instructions completed" << endl;

        Sleep(3000);
        moveFinger(50,650,1);

        Sleep(2000);
        //close notifications
        moveFinger(200,620,1);

        Sleep(4000);
        moveFinger(50,470,1);
        cout << "Grabbing presents..." << endl;

        Sleep(2000);
        //grab all
        moveFinger(200,210,1);

        Sleep(1500);
        //confirm
        moveFinger(220,400,1);

        //Long load
        Sleep(3000);
        moveFinger(320,670,1);
        cout << "Let's roll" << endl;

        Sleep(2500);
        moveFinger(150,290,1);

        Sleep(1000);
        moveFinger(300,400,1);
        cout << "Roll finished" << endl;
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
                moveFinger(310,145,2);
                Sleep(3000);

                moveFinger(340,30,3);

                Sleep(1000);

                moveFinger(340,270,1);
                Sleep(500);
                moveFinger(300,400,1);

                moveFinger(230,720,1);
                Sleep(1500);
                moveFinger(230,720,1);

                moveFinger(310,145,1);

                break;
            }
        } while (true);

    }

    cout << "Thank you for using BOT@RYO" << endl;




}
