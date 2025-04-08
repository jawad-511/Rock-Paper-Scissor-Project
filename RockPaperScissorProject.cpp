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

struct stRoundInfo
{
    short RoundNumber = 0;
    enRockPaperScissor PlayerChoice;
    enRockPaperScissor ComputerChoice;
    enWhoWin Winner;
    string WinnerName;
};

struct stGameResult
{
    int GameRounds;
    int PlayerWinTimes;
    int ComputerWinTimes;
    int DrawTimes;
    enWhoWin GameWinner;
    string WinnerName = "";
};

string Tabs(int NumberOfTabs)
{
    string t = "";

    for (int i = 1; i <= NumberOfTabs; i++)
    {
        t += "\t";
    }

    return t;
}

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

enWhoWin CheckWhoWin(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWhoWin::Draw;
    }
    // Determine the winner based on game rules.
    switch (RoundInfo.PlayerChoice)
    {
    case enRockPaperScissor::Rock:
        return (RoundInfo.ComputerChoice == enRockPaperScissor::Paper) ? enWhoWin::Computer : enWhoWin::Player;

    case enRockPaperScissor::Paper:
        return (RoundInfo.ComputerChoice == enRockPaperScissor::Scissor) ? enWhoWin::Computer : enWhoWin::Player;

    case enRockPaperScissor::Scissor:
        return (RoundInfo.ComputerChoice == enRockPaperScissor::Rock) ? enWhoWin::Computer : enWhoWin::Player;
    }
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "--------------------------------------------------------------------------\n";
    cout << Tabs(2) << "                               +++ G a m e O v e r +++\n";
    cout << Tabs(2) << "---------------------------------------------------------------------------\n";
}

void SetWinnerScreenColor(enWhoWin GameWinner)
{
    switch (GameWinner)
    {
    case enWhoWin::Player:
        system("color 2F"); // Turn screen to green
        break;

    case enWhoWin::Computer:
        system("color 4F"); // Turn screen to red
        break;

    case enWhoWin::Draw:
        system("color 6F"); // Turn screen to yellow
        break;
    }
}

void ShowFinalGameResult(stGameResult gameResult)
{
    cout << Tabs(2) << "----------------------------------[Game Result]----------------------------\n";
    cout << Tabs(2) << "Game Rounds        : " << gameResult.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << gameResult.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << gameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << gameResult.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner         : " << gameResult.WinnerName << endl;

    SetWinnerScreenColor(gameResult.GameWinner);
}

enRockPaperScissor ReadPlayerChoice()
{
    int choice = 0;
    do
    {
        cout << "\n Your Choice: [1]:Rock, [2]:Paper, [3]:Scissor ? ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return (enRockPaperScissor)choice;
}

enRockPaperScissor ReadComputerChoice()
{
    return (enRockPaperScissor)RandomNumber(1, 3);
}

string WinnerName(enWhoWin winner)
{
    string arrWinnerNames[3] = {"Player", "Computer", "Draw"};
    return arrWinnerNames[winner - 1];
}

// Function: ChoiceName
// Purpose: Converts an enGameChoice enum to a string representation.
string ChoiceName(enRockPaperScissor Choice)
{
    string arrGameChoices[3] = {"Rock", "Paper", "Scissor"};
    return arrGameChoices[Choice - 1];
}

// Function: PrintRoundResults
// Purpose: Displays the results of a single round.
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n"
         << endl;
}

stGameResult PlayGame(int HowManyRounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = ReadComputerChoice();
        RoundInfo.Winner = CheckWhoWin(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // Increase/Decrease Player & computer & draw counters

        if (RoundInfo.Winner == enWhoWin::Player)
        {
            PlayerWinTimes++;
        }
        else if (RoundInfo.Winner == enWhoWin::Computer)
        {
            ComputerWinTimes++;
        }
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
        SetWinnerScreenColor(RoundInfo.Winner);
    }

    return {HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes, CheckWhoWin(RoundInfo), WinnerName(CheckWhoWin(RoundInfo))};
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResult GameResult = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResult);

        cout << endl
             << Tabs(3) << "Do you want to play again Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    ResetScreen();

    return 0;
}