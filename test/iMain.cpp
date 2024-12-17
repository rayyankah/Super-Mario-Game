#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <bits/stdc++.h>

using namespace std;

#define screen_width 800
#define screen_height 285

// Game states
int gamestate = 0; // 0 for homepage

// Mario state and position
int marioX = 100, marioY = 56;
int marioIndex = 0, jumpIndex = 0;
int enemy1index = 0, flyingenemyindex = 0;
int enemy3index = 0;
int isJumping = 0, jumpUp = 1;
int jumpErVelocity = 0;
int moveRight = 0, moveLeft = 0;
int marioDirection = 1;
int movingmario = 0;
int movingbackground = 0;
static int enemy1Direction = 1;
static int enemy3Direction = 1;
int enemy1kototomo = 1;
int enemy2kototomo = 1;
const int marioWidth = 15;
const int marioHeight = 15;
const int enemyWidth = 12;
const int enemyHeight = 05;
int gameshesh = 0;
int gravity = 8;
int score = 0;
int easyhighscore = 0;
int hardhighscore = 0;
// int pipe1X, pipe2X;

// Background and enemies
int backgroundkotoTomo = 0;
int backgroundSpeed = 2;
int backgroundSpeed2 = 4;

int tileWidth = 31;
int backgroundTiles = 9;
int pipe1X = (enemy1kototomo) * 900;
int pipe2X = (enemy1kototomo) * 1110;
int enemy1X = pipe1X + 100;
int enemy1Y = 56;
int enemy3X = 500, enemy3Y = 53;
// int birdX = 200, birdY = 100;

int easy = 0;
int hard = 0;

int coin1khaise = 0, coin1abarashbe = 1;
int coin2khaise = 0, coin2abarashbe = 1;
int coin3khaise = 0, coin3abarashbe = 1;
int coin4khaise = 0, coin4abarashbe = 1;
int coin5khaise = 0, coin5abarashbe = 1;
int coin6khaise = 0, coin6abarashbe = 1;
int coin7khaise = 0, coin7abarashbe = 1;

int mountain1 = 170;
int greengrass1 = 360;
int greengrass2 = 1200;
int bird1X = screen_width + rand() % 800;
int bird1Y = 170 + rand() % 50;
int bird2X = screen_width + rand() % 1300;
int bird2Y = 165 + rand() % 30;

vector<int> easyleaderboardScores; // To store top 10 scores
string leaderboardFile = "easyleaderboard.txt";

vector<int> hardleaderboardScores; // To store top 10 scores
string hardleaderboardFile = "hardleaderboard.txt";

vector<string> marioRightWalk = {
    "pics\\mariowalkingright000.png.bmp", "pics\\mariowalkingright001.png.bmp", "pics\\mariowalkingright002.png.bmp"};

vector<string> marioLeftWalk = {
    "pics\\mariowalkingleft000.png.bmp", "pics\\mariowalkingleft001.png.bmp", "pics\\mariowalkingleft.png.bmp"};

vector<string> marioJumpRight = {
    "pics\\mariojumpupright000.png.bmp", "pics\\mariojumpupright001.png.bmp",
    "pics\\mariojumpupright002.png.bmp", "pics\\mariojumpupright003.png.bmp"};

vector<string> marioJumpLeft = {
    "pics\\mariojumpupleft000.png.bmp", "pics\\mariojumpupleft001.png.bmp",
    "pics\\mariojumpupleft002.png.bmp", "pics\\mariojumpupleft003.png.bmp"};

vector<string> enemy1walk = {
    "pics\\enemy1walk000.png.bmp", "pics\\enemy1walk001.png.bmp"};

char flyingenemy[4][100] = {
    "pics\\flyingenemy000.png.bmp", "pics\\flyingenemy001.png.bmp", "pics\\flyingenemy002.png.bmp", "pics\\flyingenemy001.png.bmp"};
vector<string> enemy3walk = {
    "pics\\enemy3walk000.png.bmp", "pics\\enemy3walk001.png.bmp"};

struct flyingenemy
{
    int birdX, birdY;
    int birdIndex;
};

vector<int> mountainpositions = {};
string playButton = "pics\\playbutton.png.bmp";
string infoButton = "pics\\info.png.bmp";
string instructionButton = "pics\\instructionbutton.png.bmp";
string gameOverScreen = "pics\\gameover.png.bmp";
string retryScreen = "pics\\retry.png.bmp";
string homeScreenImage = "pics\\picforhomescreen.png.bmp";

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if (x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void updatePipes()
{
    if (pipe1X < -50)
    {
        pipe1X = 1200;
    }
    if (pipe2X < -150)
    {
        pipe2X = pipe1X + 200;
    }
    if (mountain1 < -150)
    {
        mountain1 = screen_width + 170;
    }
    if (greengrass1 < -200)
    {
        greengrass1 = screen_width + 800;
    }
    if (greengrass2 < -200)
    {
        greengrass2 = screen_width + 1600;
    }
    if (bird1X < -50)
    {
        bird1X = screen_width + rand() % 500;
        bird1Y = 170 + rand() % 50;
    }
    if (bird2X < -50)
    {
        bird2X = screen_width + rand() % 1200;
        bird2Y = 165 + rand() % 30;
    }
}

void loadEasyLeaderboard()
{
    easyleaderboardScores.clear();
    FILE *file = fopen("easyleaderboard.txt", "r");
    if (file)
    {
        int score;
        while (fscanf(file, "%d", &score) == 1)
        {
            easyleaderboardScores.push_back(score);
        }
        fclose(file);
    }
    else
    {
        printf("Leaderboard file not found. Initializing an empty leaderboard.\n");
    }

    sort(easyleaderboardScores.rbegin(), easyleaderboardScores.rend());
    if (!easyleaderboardScores.empty())
    {
        easyhighscore = easyleaderboardScores[0];
    }

    if (easyleaderboardScores.size() > 10)
    {
        easyleaderboardScores.resize(10);
    }
}

void loadHardLeaderboard()
{
    hardleaderboardScores.clear();
    FILE *file = fopen("hardleaderboard.txt", "r");
    if (file)
    {
        int score;
        while (fscanf(file, "%d", &score) != EOF)
        {
            hardleaderboardScores.push_back(score);
        }
        fclose(file);
    }
    else
    {
        printf("Leaderboard file not found. Initializing an empty leaderboard.\n");
    }
    sort(hardleaderboardScores.rbegin(), hardleaderboardScores.rend());
    if (!hardleaderboardScores.empty())
    {
        hardhighscore = hardleaderboardScores[0];
    }

    if (hardleaderboardScores.size() > 10)
    {
        hardleaderboardScores.resize(10);
    }
}
void saveEasyLeaderboard(int newScore)
{
    cout << "savingscore: " << newScore << endl;
    FILE *file = fopen("easyleaderboard.txt", "a"); // Open in append mode
    if (file)
    {
        fprintf(file, "%d\n", newScore); // Append the new score on a new line
        fclose(file);
    }
}

void saveHardLeaderboard(int newScore)
{
    FILE *file = fopen("hardleaderboard.txt", "a");
    if (file)
    {
        fprintf(file, "%d\n", newScore);
        fclose(file);
    }
}

void prothomThekeShuru()
{
    marioX = 50, marioY = 56;
    marioIndex = 0, jumpIndex = 0;
    enemy1index = 0, flyingenemyindex = 0;
    enemy3index = 0;
    isJumping = 0, jumpUp = 1;
    jumpErVelocity = 0;
    moveRight = 0, moveLeft = 0;
    marioDirection = 1;
    movingmario = 0;
    movingbackground = 0;
    enemy1Direction = 1;
    enemy3Direction = 1;
    enemy1kototomo = 1;
    enemy2kototomo = 1;

    gameshesh = 0;
    easyhighscore = 0;
    hardhighscore = 0;
    backgroundkotoTomo = 0;
    backgroundSpeed = 2;
    backgroundSpeed2 = 4;
    tileWidth = 31;
    backgroundTiles = 9;
    pipe1X = (enemy1kototomo) * 900;
    pipe2X = (enemy1kototomo) * 1110;
    enemy1X = pipe1X + 100;
    enemy1Y = 56;
    enemy3X = 500, enemy3Y = 53;

    coin1khaise = 0, coin1abarashbe = 1;
    coin2khaise = 0, coin2abarashbe = 1;
    coin3khaise = 0, coin3abarashbe = 1;
    coin4khaise = 0, coin4abarashbe = 1;
    coin5khaise = 0, coin5abarashbe = 1;
    coin6khaise = 0, coin6abarashbe = 1;
    coin7khaise = 0, coin7abarashbe = 1;

    mountain1 = 170;
    greengrass1 = 360;
    greengrass2 = 1200;

    bird1X = screen_width + rand() % 800;
    bird1Y = 170 + rand() % 50;
    bird2X = screen_width + rand() % 1300;
    bird2Y = 165 + rand() % 30;
    if (easy)
    {
        easyleaderboardScores.push_back(score);
        sort(easyleaderboardScores.rbegin(), easyleaderboardScores.rend());
        if (easyleaderboardScores.size() > 10)
        {
            easyleaderboardScores.resize(10);
        }
        saveEasyLeaderboard(score);
    }
    else if (hard)
    {
        hardleaderboardScores.push_back(score);
        sort(hardleaderboardScores.rbegin(), hardleaderboardScores.rend());
        if (hardleaderboardScores.size() > 10)
        {
            hardleaderboardScores.resize(10);
        }
        saveHardLeaderboard(score);
    }
    score = 0;
}

int brick1;
void drawbricksandcoins()
{
    iShowBMP2(greengrass1, 59, "pics//greengrass.bmp", 0);
    iShowBMP2(greengrass2, 59, "pics//greengrass.bmp", 0);
    iShowBMP2(mountain1, 59, "pics//mountain.bmp", 0);
    iShowBMP2(mountain1 + 30, 240, "pics//cloud1.bmp", 0);
    iShowBMP2(greengrass1 + 10, 240, "pics//cloud2.bmp", 0);
    iShowBMP2(greengrass1 + 90, 245, "pics//cloud1.bmp", 0);
    iShowBMP2(greengrass2 + 30, 240, "pics//cloud2.bmp", 0);
    brick1 = pipe1X - 200;

    iShowBMP2(brick1, 150, "pics\\brownbrick.png.bmp", 0);
    // if (coin1abarashbe && (marioX < brick1 + 5 || marioX > brick1 + 35) && (marioY<167 || marioY>186) )
    //     iShowBMP2(brick1 + 5, 167, "pics\\coin.png.bmp", 0);
    if (coin1abarashbe)
    {
        iShowBMP2(brick1 + 5, 167, "pics\\coin.png.bmp", 0);
    }
    iShowBMP2(brick1 + 30, 150, "pics\\brownbrick.png.bmp", 0);
    // if (coin2abarashbe && (marioX < brick1 + 35 || marioX > brick1 + 56) && (marioY<167 || marioY>186) )
    if (coin2abarashbe)
    {
        iShowBMP2(brick1 + 35, 167, "pics\\coin.png.bmp", 0);
    }

    iShowBMP2(brick1 + 60, 150, "pics\\brownbrick.png.bmp", 0);
    // if (coin3abarashbe && (marioX < brick1 + 65 || marioX > brick1 + 86) && (marioY<167 || marioY>186) )
    if (coin3abarashbe)
    {
        iShowBMP2(brick1 + 65, 167, "pics\\coin.png.bmp", 0);
    }
    if (brick1 + 6 <= marioX && marioX <= brick1 + 35 && marioY >= 167 && marioY <= 185 && !coin1khaise)
    {
        coin1khaise = 1;
        coin1abarashbe = 0;
    }
    if (brick1 + 36 <= marioX && marioX <= brick1 + 56 && marioY >= 167 && marioY <= 185 && !coin2khaise)
    {
        coin2khaise = 1;
        coin2abarashbe = 0;
    }
    if (brick1 + 66 <= marioX && marioX <= brick1 + 86 && marioY >= 167 && marioY <= 185 && !coin3khaise)
    {
        coin3khaise = 1;
        coin3abarashbe = 0;
    }

    // if (coin4abarashbe && (marioX < pipe1X + 10 || marioX > pipe1X + 32) && (marioY<118 || marioY>141) )
    if (coin4abarashbe && !coin4khaise)
        iShowBMP2(pipe1X + 12, 120, "pics\\coin.png.bmp", 0);
    // if (coin5abarashbe && (marioX < pipe2X + 10 || marioX > pipe2X + 32) && (marioY<98 || marioY>118) )
    if (coin5abarashbe && !coin5khaise)
        iShowBMP2(pipe2X + 10, 100, "pics\\coin.png.bmp", 0);

    if (pipe1X + 10 <= marioX && marioX <= pipe1X + 32 && marioY >= 118 && marioY <= 140 && !coin4khaise)
    {
        coin4khaise = 1;
        coin4abarashbe = 0;
    }
    if (pipe2X + 8 <= marioX && marioX <= pipe2X + 30 && marioY >= 98 && marioY <= 118 && !coin5khaise)
    {
        coin5khaise = 1;
        coin4abarashbe = 0;
    }

    if (coin6abarashbe && (marioX < pipe1X + 104 || marioX > pipe1X + 122) && (marioY < 59 || marioY > 77))
        iShowBMP2(pipe1X + 110, 59, "pics\\coin.png.bmp", 0);
    if (pipe1X + 105 <= marioX && marioY >= 59 && marioY <= 77 && !coin6khaise)
    {

        coin6khaise = 1;
        coin6abarashbe = 0;
    }
}

void checkCoinCollision()
{
    if (coin1khaise)
    {

        coin1khaise = 0;
        coin1abarashbe = 0;
    }
    if (coin2khaise)
    {
        // score += 5;
        coin2khaise = 0;
        coin2abarashbe = 0;
    }
    if (coin3khaise)
    {
        // score += 5;
        coin3khaise = 0;
        coin3abarashbe = 0;
    }
    if (coin4khaise)
    {
        // score += 5;
        coin4khaise = 0;
        coin4abarashbe = 0;
    }
    if (coin5khaise)
    {
        // score += 5;
        coin5khaise = 0;
        coin5abarashbe = 0;
    }
    if (coin6khaise)
    {
        // score += 5;
        coin6khaise = 0;
        coin6abarashbe = 0;
    }
    if (marioX >= brick1 + 470)
    {
        coin1abarashbe = 1;
        coin2abarashbe = 1;
        coin3abarashbe = 1;
    }
    if (marioX >= pipe1X + 400)
    {
        coin4abarashbe = 1;
    }
    if (marioX >= pipe2X + 400)
    {
        coin5abarashbe = 1;
    }
    if (marioX >= enemy1X + 400)
    {
        coin6abarashbe = 1;
    }
    // if (marioX >= pipe2X + 400)
    // {
    //     coin7abarashbe=1;
    // }
}

void scoreUpdateWithCoinCollison()
{
    if (coin1khaise)
    {
        score += 5;
    }
    if (coin2khaise)
    {
        score += 5;
    }
    if (coin3khaise)
    {
        score += 5;
    }
    if (coin4khaise)
    {
        score += 5;
    }
    if (coin5khaise)
    {
        score += 5;
    }
    if (coin6khaise)
    {
        score += 5;
    }
}

// Draw functions
void drawHomeScreen()
{

    iShowBMP(0, 0, "pics\\bgpic.bmp");
}

void drawEasyLeaderboard()
{
    iShowBMP(0, 0, "pics\\background.bmp");
    iSetColor(0, 0, 0);
    iText(300, 260, "Top 10 Scores", GLUT_BITMAP_HELVETICA_18);
    int y = 240;
    for (int i = 0; i < easyleaderboardScores.size(); i++)
    {
        char scoreStr[20];
        sprintf(scoreStr, "%d. %d", i + 1, easyleaderboardScores[i]);
        iText(300, y, scoreStr, GLUT_BITMAP_HELVETICA_18);
        y -= 20;
    }
    iText(300, 40, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
}

void mario_and_pipe()
{
    if (marioX >= pipe1X - 20 && marioX <= pipe1X + 15 && marioY < 105)
    {
        // movingmario = 0;
        // if(marioX>=pipe1X-15 && marioX<=pipe1X+15 && marioY<=107)
        marioX = pipe1X - 20;
    }

    else if (marioX >= pipe1X - 20 && marioX <= pipe1X + 15 && marioY >= 105)
    {
        // movingmario = 1;
        if (marioY <= 109)
        {
            marioY = 109;
            marioX = pipe1X + 5;
        }
    }
    if (marioX >= pipe2X - 20 && marioX <= pipe2X + 15 && marioY < 100)
    {
        // movingmario = 0;
        // if(marioX>=pipe1X-15 && marioX<=pipe1X+15 && marioY<=107)
        marioX = pipe2X - 20;
    }
    else if (marioX >= pipe2X - 20 && marioX <= pipe2X + 15 && marioY >= 102)
    {
        // movingmario = 1;
        if (marioY <= 103)
            marioY = 103;
        marioX = pipe2X + 5;
    }
    // if(marioX >= brick1 && marioX<=brick1+90 && marioY >= 100){

    //     if(marioY<=150){
    //     marioY = 150;
    //     }
    // }
}

void drawHardLeaderboard()
{
    iShowBMP(0, 0, "pics\\background.bmp");
    iSetColor(0, 0, 0);
    iText(300, 260, "Top 10 Scores", GLUT_BITMAP_HELVETICA_18);
    int y = 240;
    for (int i = 0; i < hardleaderboardScores.size(); i++)
    {
        char scoreStr[20];
        sprintf(scoreStr, "%d. %d", i + 1, hardleaderboardScores[i]);
        iText(300, y, scoreStr, GLUT_BITMAP_HELVETICA_18);
        y -= 20;
    }
    iText(300, 40, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
}

void drawEasyScreen()

{
    for (int i = 0; i < 27; i++) // 9
    {
        int xPosition = backgroundkotoTomo + i * tileWidth;
        iShowBMP2(xPosition, 0, "pics\\onlysmallbackground.bmp", 0);
    }
    drawbricksandcoins();
    iSetColor(255, 0, 0);
    // iText(680, 260, "Score:");
    char scoreStr[3];
    sprintf(scoreStr, "Score: %d", score);
    iText(650, 260, scoreStr, GLUT_BITMAP_HELVETICA_18);
    loadEasyLeaderboard();
    char highscoreStr[10];
    sprintf(highscoreStr, "Highscore: %d", easyhighscore);
    iText(650, 240, highscoreStr, GLUT_BITMAP_HELVETICA_18);

    // mario_and_pipe();
    if (!movingmario)
    {
        iShowBMP2(marioX, marioY, "pics\\standingmario.png.bmp", 0);
    }
    else
    {
        if (marioDirection == 1)
        {
            iShowBMP2(marioX, marioY, (char *)marioRightWalk[marioIndex].c_str(), 0);
        }
        else
        {
            iShowBMP2(marioX, marioY, (char *)marioLeftWalk[marioIndex].c_str(), 0);
        }
    }

    iShowBMP2(enemy1X, enemy1Y, (char *)enemy1walk[enemy1index].c_str(), 0);

    if (abs(enemy1X - enemy3X) > 20)
    {

        iShowBMP2(enemy3X, enemy3Y, (char *)enemy3walk[enemy3index].c_str(), 0);
    }

    iShowBMP2(pipe1X, 51, "pics\\pipe001.png.bmp", 0);
    iShowBMP2(pipe2X, 51, "pics\\pipe002.png.bmp", 0);
}

void drawHardScreen()
{
    for (int i = 0; i < 27; i++) // 9
    {
        int xPosition = backgroundkotoTomo + i * tileWidth;
        iShowBMP2(xPosition, 0, "pics\\hardbackground.bmp", 0);
    }

    drawbricksandcoins();
    iShowBMP2(bird1X, bird1Y, flyingenemy[rand() % 2], 0);
    iShowBMP2(bird2X, bird2Y, flyingenemy[rand() % 2], 0);
    iSetColor(255, 255, 100);
    // iText(680, 260, "Score:");
    char scoreStr[3];
    sprintf(scoreStr, "Score: %d", score);
    iText(650, 260, scoreStr, GLUT_BITMAP_HELVETICA_18);
    char highscoreStr[10];
    // sprintf(highscoreStr, "Highscore: %d", hardleaderboardScores[0]);
    sprintf(highscoreStr, "Highscore: %d", hardhighscore);
    iText(650, 240, highscoreStr, GLUT_BITMAP_HELVETICA_18);
    // // mario_and_pipe();

    if (!movingmario)
    {
        iShowBMP2(marioX, marioY, "pics\\standingmario.png.bmp", 0);
    }
    else
    {
        if (marioDirection == 1)
        {
            iShowBMP2(marioX, marioY, (char *)marioRightWalk[marioIndex].c_str(), 0);
        }
        else
        {
            iShowBMP2(marioX, marioY, (char *)marioLeftWalk[marioIndex].c_str(), 0);
        }
    }
    iShowBMP2(enemy1X, enemy1Y, (char *)enemy1walk[enemy1index].c_str(), 0);
    if (abs(enemy1X - enemy3X) > 20)
    {

        iShowBMP2(enemy3X, enemy3Y, (char *)enemy3walk[enemy3index].c_str(), 0);
        // Drawing pipes at fixed positions
    }
    iShowBMP2(pipe1X, 51, "pics\\pipe001.png.bmp", 0);
    iShowBMP2(pipe2X, 51, "pics\\pipe002.png.bmp", 0);
}

void drawGameOverScreen()
{
    iShowBMP(270, 50, "pics//gameover.png.bmp");
    iSetColor(255, 255, 255);
    iText(320, 110, "Press Space to go next");
}

drawTryAgainScreen()
{
    iShowBMP(270, 50, "pics//retry.png.bmp");
}
drawInstructionScreen()
{
    iShowBMP(0, 0, "pics\\instruction.bmp");
}
drawInfoPage()
{
    iShowBMP(0, 0, "pics\\about.bmp");
}
drawEasyHardScreen()
{
    iShowBMP(0, 0, "pics\\easyhard.bmp");
}

// iGraphics functions
void iDraw()
{
    iClear();
    // mario_and_pipe();
    if (gamestate == 0)
    {

        drawHomeScreen();
        // PlaySound(0,0,0);
        // PlaySound("audio\\intro.wav", NULL, SND_ASYNC);
    }

    else if (gamestate == 1)
    {
        easy = 1;
        hard = 0;

        drawEasyScreen();
        iShowBMP(0, 0, "pics\\onlysmallbackground.bmp");
        if (collision(marioX, marioY, marioWidth, marioHeight, enemy1X, enemy1Y, enemyWidth, enemyHeight) ||
            collision(marioX, marioY, marioWidth, marioHeight, enemy3X, enemy3Y, enemyWidth, enemyHeight))
        {
            gamestate = 2;
            PlaySound(0, 0, 0);
            PlaySound(("audio\\gameover.wav"), NULL, SND_ASYNC);
            prothomThekeShuru();
        }
    }
    else if (gamestate == 9)
    {
        easy = 0;
        hard = 1;

        drawHardScreen();
        hard = 1;
        loadHardLeaderboard();
        drawHardScreen();
        iShowBMP(0, 0, "pics\\hardbackground.bmp");
        if (collision(marioX, marioY, marioWidth, marioHeight, enemy1X, enemy1Y, enemyWidth, enemyHeight) ||
            collision(marioX, marioY, marioWidth, marioHeight, enemy3X, enemy3Y, enemyWidth, enemyHeight) ||
            collision(marioX, marioY, marioWidth, marioHeight + 5, bird1X, bird1Y, enemyWidth, enemyHeight + 5) ||
            collision(marioX, marioY, marioWidth, marioHeight + 5, bird2X, bird2Y, enemyWidth, enemyHeight + 5))
        {
            gamestate = 2; // Switch to Game Over state
            PlaySound(0, 0, 0);
            PlaySound(("audio\\gameover.wav"), NULL, SND_ASYNC);
            prothomThekeShuru();
        }
    }
    else if (gamestate == 2)
    {
        drawGameOverScreen();
    }
    else if (gamestate == 3)
    {
        drawTryAgainScreen();
    }
    else if (gamestate == 4)
    {
        drawInstructionScreen();
    }
    else if (gamestate == 5)
    {
        drawInfoPage();
    }
    else if (gamestate == 6 && gamestate != 7)
    {
        drawEasyLeaderboard();
    }
    else if (gamestate == 8 && gamestate != 7)
    {
        drawHardLeaderboard();
    }
    else if (gamestate == 7 || gamestate == 10)
    {
        drawEasyHardScreen();
    }

    // drawGameScreen();
}

void iKeyboard(unsigned char key)
{
    if (gamestate == 1 || gamestate == 9)
    {

        if (key == 'd' || key == 'D')

        {
            // score++;
            // PlaySound(("pics\\begin.wav"), NULL, SND_LOOP);
            if (marioX < screen_width)
            {
                movingmario = 1;
                moveRight = 1;
                marioDirection = 1;
            }
        }

        if (key == 'a')
        {
            if (movingmario)
                movingmario = 0;
        }
        // int gravity = 2;
        if (key == ' ')
        {
            isJumping = 1;
            jumpErVelocity = 20;
        }
    }
    if (key == 's')
    {
        // if(mariomoving){
        //     mariomoving =0;
        // }
    }

    if (gamestate == 2)
    {
        if (key == ' ')
        {
            gamestate = 3;
            prothomThekeShuru();
        }
    }
    if (gamestate == 4 || gamestate == 5)
    {
        if (key == 'b' || key == 'B')
        {
            gamestate = 0;
        }
    }

    if ((gamestate == 6 || gamestate == 8) && key == 'b')
    {
        gamestate = 0;
    }
}

void iKeyboardUp(unsigned char key)
{
    if (key == 'd')
    {
        movingmario = 0;
        moveRight = 0;
    }
    if (key == 'a')
    {
        moveLeft = 0;
        movingmario = 0;
    }
    if (key == ' ')
    {
        jumpUp = 0;
    }
}

void iSpecialKeyboard(unsigned char key)
{
}

void iSpecialKeyboardUp(unsigned char key)
{
}

void iMouseMove(int mx, int my)
{
    // Handle mouse movement if necessary
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << mx << " " << my << endl;
        if (gamestate == 0)
        {
            if (mx > 297 && mx < 505 && my > 143 && my < 171)

            {
                // PlaySound(("pics\\begin.wav"), NULL, SND_LOOP);

                gamestate = 10;
            }
            if (mx > 297 && mx < 505 && my > 75 && my < 103)
            {
                gamestate = 4;
            }
            if (mx > 297 && mx < 503 && my > 107 && my < 136)
            {
                gamestate = 7;
            }
            if (mx > 297 && mx < 503 && my > 40 && my < 69)
            {
                gamestate = 5;
            }
        }
        if (gamestate == 10)
        {
            if (mx >= 221 && mx <= 373 && my >= 93 && my <= 145)
            {
                gamestate = 1;
                easy = 1;
                hard = 0;
                PlaySound(0, 0, 0);
                PlaySound(("audio\\normal.wav"), NULL, SND_ASYNC);
            }
            if (mx >= 427 && mx <= 581 && my >= 94 && my <= 143)
            {
                gamestate = 9;
                easy = 0;
                hard = 1;
                PlaySound(0, 0, 0);
                PlaySound(("audio\\normal.wav"), NULL, SND_ASYNC);
            }
        }
        if (gamestate == 3)
        {
            cout << "mx: " << mx << "my: " << my << endl;
            if (mx >= 363 && mx <= 423 && my >= 180 && my <= 190)
            {
                if (easy)
                {
                    easy = 0;
                }
                else if (hard)
                {
                    hard = 0;
                }
                gamestate = 0;
                PlaySound(0, 0, 0);
                PlaySound(("audio\\intro.wav"), NULL, SND_ASYNC);
            }
            if (mx >= 361 && mx <= 400 && my >= 166 && my <= 173)
            {
                cout << "easy: " << easy << endl;
                cout << "hard: " << hard << endl;
                if (easy)
                {
                    gamestate = 1;
                }
                else if (hard)
                {
                    gamestate = 9;
                }
                PlaySound(0, 0, 0);
                PlaySound(("audio\\normal.wav"), NULL, SND_ASYNC);
            }
        }

        if (gamestate == 7)
        {
            if (mx >= 221 && mx <= 373 && my >= 93 && my <= 145)
            {
                if (gamestate != 0)
                {
                    loadEasyLeaderboard();
                    gamestate = 6;
                }
            }
            if (mx >= 427 && mx <= 581 && my >= 94 && my <= 143)
            {
                if (gamestate != 0)
                {
                    loadHardLeaderboard();
                    gamestate = 8;
                }
            }
        }
    }
}

void updateBackground()
{
    if (movingmario && marioX >= 400)
    {
        movingbackground = 1;
    }
    if (!movingmario)
    {
        movingbackground = 0;
    }
    if (hard)
    {
        if (!movingmario)
        {
            bird1X -= 5;
            bird2X -= 5;
        }
        if (movingmario)
        {
            bird1X -= backgroundSpeed + 5;
            bird2X -= backgroundSpeed + 5;
        }
    }

    if (movingbackground)
    {
        if (easy)
        {
            backgroundSpeed = 2;
        }
        else if (hard)
        {
            backgroundSpeed = 4;
        }
        backgroundkotoTomo -= backgroundSpeed;

        if (enemy1Direction == 1)
        {
            enemy1X -= backgroundSpeed + 1;
        }
        else
        {
            enemy1X -= 1;
        }
        if (enemy3Direction == 1)
        {
            enemy3X -= backgroundSpeed + 1;
        }

        pipe1X -= backgroundSpeed;
        pipe2X -= backgroundSpeed;

        mountain1 -= backgroundSpeed;
        greengrass1 -= backgroundSpeed;
        greengrass2 -= backgroundSpeed;

        updatePipes();
        if (backgroundkotoTomo <= -tileWidth)
        {
            backgroundkotoTomo += tileWidth;
        }

        if (enemy1X < -50)
        {
            enemy1kototomo++;
            enemy1X = pipe1X + 100;
        }
        if (enemy3X < -50)
        {
            enemy2kototomo++;
            enemy3X += screen_width + rand() % 300;
        }
    }
}

void change()
{

    if (movingmario && moveRight)
    {
        if (marioX < screen_width / 2)
        {
            marioX += 10;
        }
        marioIndex++;
        if (marioIndex >= marioRightWalk.size())
        {
            marioIndex = 0;
        }
    }
    else if (movingmario && moveLeft)
    {
        if (marioX > 0)
        {
            marioX -= 10;
            backgroundkotoTomo += backgroundSpeed;
            marioIndex++;
            if (marioIndex >= marioLeftWalk.size())
            {
                marioIndex = 0;
            }
        }
    }
}

void jump()
{

    if (isJumping)
    {
        marioY += jumpErVelocity;
        jumpErVelocity -= gravity;

        if (jumpErVelocity < 0 && marioY <= 56)
        {
            marioY = 56;
            isJumping = 0;
            jumpErVelocity = 20;
        }
        if (marioY > 197)
        {
            marioY = 195;
            jumpErVelocity = 0;
            gravity = 10;
        }
    }
}
void marioStill()
{
    if (!movingmario)
    {
        if (enemy1Direction == 1)
        {
            enemy1X -= 5;
        }
        else
        {
            enemy1X += 5;
        }
        if (enemy3Direction == 1)
        {
            enemy3X -= backgroundSpeed + 1;
        }
    }
}

void enemychange()
{

    if (enemy1X >= pipe2X - 40 || enemy1X <= pipe1X + 70)
    {
        enemy1Direction *= -1;
        enemy1X += enemy1Direction * 2;
        enemy1index++;
        if (enemy1index >= enemy1walk.size())
        {
            enemy1index = 0;
        }
    }

    if (enemy3X >= (enemy2kototomo + 1) * 1000 || enemy3X <= enemy2kototomo * 1000)
    {
        enemy3Direction *= -1;
        enemy3X += enemy3Direction * 2;
        enemy3index++;
        if (enemy3index >= enemy3walk.size())
        {
            enemy3index = 0;
        }
    }

    flyingenemyindex++;
    if (flyingenemyindex >= 2)
    {
        flyingenemyindex = 0;
    }
}

int main()
{

    iSetTimer(50, change);
    iSetTimer(90, jump);
    iSetTimer(1000, enemychange);

    iSetTimer(16, updateBackground);
    iSetTimer(150, marioStill);
    iSetTimer(1, checkCoinCollision);
    iSetTimer(70, scoreUpdateWithCoinCollison);
    PlaySound("audio\\intro.wav", NULL, SND_ASYNC);
    iInitialize(screen_width, screen_height, "Super Mario Reincarnated");

    return 0;
}
