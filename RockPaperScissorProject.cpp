#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
// Rock-Paper-Scissor Project
enum enWhoWin
{
    Player = 1,
    Computer = 2,
    Draw = 3
};


enum enRockPaperScissor
{
    Rock = 1,
    Paper = 2,
    Scissor = 3
};



struct stGameResult
{
    int GameRound;
    int PlayerWonTimes;
    int ComputerWonTimes;
    int DrawTimes;
};


int RandomNumber(int from, int to)
{
    int randomNumber = 0;

    randomNumber = rand() % (to - from + 1) + from;
    return randomNumber;
}

int ReadHowManyRounds()
{
    int rounds = 0;

    do
    {
        cout << "How Many Rounds ?" << endl;
        cin >> rounds;

    } while (rounds <= 0);

    return rounds;
}


enWhoWin CheckWhoWin(enRockPaperScissor PlayerChoice, enRockPaperScissor ComputerChoice)
{
    if (PlayerChoice == ComputerChoice)
        return enWhoWin::Draw;

    if ((PlayerChoice == enRockPaperScissor::Rock     && ComputerChoice == enRockPaperScissor::Scissor) ||
        (PlayerChoice == enRockPaperScissor::Paper    && ComputerChoice == enRockPaperScissor::Rock)    ||
        (PlayerChoice == enRockPaperScissor::Scissor  && ComputerChoice == enRockPaperScissor::Paper))
    {
        return enWhoWin::Player;
    }

    return enWhoWin::Computer;
}

void ShowGameOverScreen()
{
    cout << "\n\t\t--------------------------------------------------------------------------\n";
    cout << "\t\t\t\t+++ G a m e O v e r +++\n";
    cout << "\n\t\t--------------------------------------------------------------------------\n";
}


void ShowFinalGameResult(stGameResult gameResult)
{
    cout << "\n\t\t----------------------------------[Game Result]----------------------------\n";
    cout << "\t\tGame Rounds\t\t: " << gameResult.GameRound << endl;
    cout << "\t\tPlayer1 won times\t: " << gameResult.PlayerWonTimes << endl;
    cout << "\t\tComputer won times\t: " << gameResult.ComputerWonTimes << endl;
    cout << "\t\tDraw times\t\t: " << gameResult.DrawTimes << endl;
    
    if(gameResult.ComputerWonTimes > gameResult.PlayerWonTimes)
    {
        cout << "\t\tFinal Winner\t\t: " << "Computer" << endl;
    }
    else if(gameResult.PlayerWonTimes > gameResult.ComputerWonTimes)
    {
        cout << "\t\tFinal Winner\t\t: " << "Player" << endl;
    }
    else
    cout << "\t\tFinal Winner\t\t: " << "No Winner" << endl;
    
    cout << "\n\t\t--------------------------------------------------------------------------\n";

}

enRockPaperScissor GetPlayerOption()
{
    int choice = 0;
    do
    {
        cin >> choice;
    } while (choice < 1 || choice > 3);
    
    enRockPaperScissor PlayerOption = (enRockPaperScissor)choice;
    return PlayerOption;
}

enRockPaperScissor GetComputerOption()
{
    int choice = 0;
    choice = RandomNumber(1, 3);
    enRockPaperScissor ComputerOption = (enRockPaperScissor)choice;
    return ComputerOption;
}

void ResetGame(stGameResult &GameResult)
{
    GameResult.ComputerWonTimes = 0;
    GameResult.DrawTimes = 0;
    GameResult.GameRound = 0;
    GameResult.PlayerWonTimes = 0;
   
}

void ThanksMessage()
{
    cout << "\nI Hope you enjoy the game(:\n";
}

void ResetColor()
{
    system("color 07");
}

void StartGame()
{
    stGameResult GameResult;

    GameResult.PlayerWonTimes = 0;
    GameResult.ComputerWonTimes = 0;
    GameResult.DrawTimes = 0;   
    char playAgain;
    do
    {
        GameResult.GameRound = ReadHowManyRounds();

        for (int i = 1; i <= GameResult.GameRound; i++)
        {
            cout << "Round[" << i << "] begins:" << endl << endl;
            cout << "Your Choice: [1]:Rock, [2]:Paper, [3]:Scissor ? ";
    
        
            enRockPaperScissor PlayerOption = GetPlayerOption();
            enRockPaperScissor ComputerOption = GetComputerOption();
            
            
            cout << "------------------Round[" << i << "]" << "------------------" << endl << endl;
            cout << "Player1 choice: ";
            if (PlayerOption == enRockPaperScissor::Rock)
            {
                cout << "Rock" << endl;
            }
            else if (PlayerOption == enRockPaperScissor::Paper)
            {
                cout << "Paper" << endl;
            }
            else
                cout << "Scissor" << endl;
    
            cout << "Computer Choice: ";
            if (ComputerOption == enRockPaperScissor::Rock)
            {
                cout << "Rock" << endl;
            }
            else if (ComputerOption == enRockPaperScissor::Paper)
            {
                cout << "Paper" << endl;
            }
            else
                cout << "Scissor" << endl;
    
            cout << "Round Winner : ";
            if (CheckWhoWin(PlayerOption, ComputerOption) == enWhoWin::Computer)
            {
                cout << "[ Computer ]\n";
                system("color 4F");
                GameResult.ComputerWonTimes++;
            }
            else if (CheckWhoWin(PlayerOption, ComputerOption) == enWhoWin::Player)
            {
                cout << "[ Player ]\n";
                system("color 2F");
                GameResult.PlayerWonTimes++;
            }
            else
            {
                cout << "[ No Winner ]\n";
                system("color 6F");
                GameResult.DrawTimes++;
            }
    
            cout << "-------------------------------------------\n";
            if(i == GameResult.GameRound)
            {
                ShowGameOverScreen();
                ShowFinalGameResult(GameResult);
                cout << "Do you want to play again y/n ?";
                cin >> playAgain;
                if(tolower(playAgain) == 'y')
                {
                    ResetGame(GameResult);
                    ResetColor();
                }
            }
        }
    }while(playAgain == 'y');
   
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    ResetColor();
    ThanksMessage();

    return 0;
}