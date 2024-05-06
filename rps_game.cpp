#include <iostream>
#include <cstdlib>
using namespace std;

struct stGamestatics
{
    short GameRounds = 0;
    short Player1WonTimes = 0;
    short CpWonTimes = 0;
    short DrawTimes = 0;
};

enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };

int RandomNumber(int From, int To)
{
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadPostiveNumber(string Message)
{
    int Num;
    do {
        cout << Message << endl;
        cin >> Num;
    } while (Num <= 0);
    return Num;
}

int ReadUserChoice()
{
    int num;
    cin >> num;
    while (num <= 0 || num > 3)
    {
        cout << "\n Please enter a valid choice between 1 and 3: ";
        cin >> num;
    }
    return num;
}

short ReadNumberOfRounds()
{
    short numOfRounds = 0;
    numOfRounds = ReadPostiveNumber("How many rounds 1 to 10 ?");
    while (numOfRounds > 10) {
        cout << "Please enter a number in the range between 1 and 10" << endl;
        numOfRounds = ReadPostiveNumber("How many rounds 1 to 10 ?");
    }

    return numOfRounds;
}

void PrintChoices()
{
    cout << "[1]: Stone, [2]: Paper, [3]: Scissors" << endl;
    cout << "Choose your choice: ";
}

enChoice convChoice(int convChoice)
{
    return enChoice(convChoice);
}

string Choice(enChoice Choice)
{
    if (Choice == enChoice::Paper)
    {
        return "Paper";
    }
    else if (Choice == enChoice::Stone)
    {
        return "Stone";
    }
    else
    {
        return "Scissors";
    }
}

string ReturnResult(enChoice UserCh, enChoice ComputerCh)
{
    if (UserCh == ComputerCh)
    {
        return "[No Winner]";
    }
    else
    {
        switch (UserCh)
        {
        case Stone:
            if (ComputerCh == enChoice::Scissors)
            {
                return "[Player 1]";
            }
            else if (ComputerCh == enChoice::Paper)
            {
                return "[Computer]";
            }
            break;
        case Paper:
            if (ComputerCh == enChoice::Scissors)
            {
                return "[Computer]";
            }
            else if (ComputerCh == enChoice::Stone)
            {
                return "[Player 1]";
            }
            break;
        case Scissors:
            if (ComputerCh == enChoice::Stone)
            {
                return "[Computer]";
            }
            else if (ComputerCh == enChoice::Paper)
            {
                return "[Player 1]";
            }
            break;
        }
    }
    return "";
}

void PrintStructreRound(int roundNumber, string userChoice, string ComputerChoice)
{
    cout << "\n_______________Round[" << roundNumber << "]______________\n" << endl;
    cout << "Player 1 choice: " << userChoice << endl;
    cout << "Computer choice: " << ComputerChoice << endl;
    cout << "Round Winner: ";
}

void FindFinalReuslt(enChoice userChoice, enChoice ComputerChoice, stGamestatics& read)
{
    string result = ReturnResult(userChoice, ComputerChoice);
    if (result == "[No Winner]")
    {
        read.DrawTimes++;
        system("Color 6f");
        cout << "[No Winner]" << endl;
    }
    else if (result == "[Player 1]")
    {
        read.Player1WonTimes++;
        system("Color 2f");
        cout << "[Player 1]" << endl;
    }
    else if (result == "[Computer]")
    {
        read.CpWonTimes++;
        system("Color 4f");
        cout << "[Computer]\a" << endl;
    }
}

void PrintResult(string Result, enChoice userChoice, enChoice ComputerChoice, int roundNumber, stGamestatics& read)
{
    PrintStructreRound(roundNumber, Choice(userChoice), Choice(ComputerChoice));
    FindFinalReuslt(userChoice, ComputerChoice, read);
    cout << "\n_____________________________________\n" << endl;
}

void StartRounds(int NumberOfRounds, stGamestatics& read)
{
    int userChoice = 0;
    int ComputerChoice = 0;
    for (int i = 0; i < NumberOfRounds; i++)
    {
        cout << "\nRound [" << i + 1 << "] begins:\n" << endl;
        PrintChoices();
        userChoice = ReadUserChoice();
        ComputerChoice = RandomNumber(1, 3);
        PrintResult(ReturnResult(convChoice(userChoice), convChoice(ComputerChoice)), convChoice(userChoice), convChoice(ComputerChoice), i + 1, read);
    }
    read.GameRounds = NumberOfRounds;
}

string FinalWinner(stGamestatics read)
{
    if (read.Player1WonTimes > read.CpWonTimes)
    {
        return "Player 1";
    }
    else if (read.Player1WonTimes < read.CpWonTimes)
    {
        return "Computer";
    }
    else
    {
        return "No Winner";
    }
}

void PrintGameOverScreen(stGamestatics read)
{
    cout << "\t\t\t\t______________________________________________________\t\t\t\t\n" << endl;
    cout << "\t\t\t\t\t\t+++G A M E   O V E R+++\t\t\t\t\t\t\t\t\n" << endl;
    cout << "\t\t\t\t______________________________________________________\t\t\t\t\n" << endl;
    cout << "\t\t\t\t__________________[ GAME RESULTS ]____________________\t\t\t\t\n" << endl;
    cout << "\t\t\t\tGame Rounds: " << read.GameRounds << "\t\t\t\t\n" << endl;
    cout << "\t\t\t\tPlayer 1 Wins: " << read.Player1WonTimes << "\t\t\t\t\n" << endl;
    cout << "\t\t\t\tComputer Wins: " << read.CpWonTimes << "\t\t\t\t\n" << endl;
    cout << "\t\t\t\tDraw times: " << read.DrawTimes << "\t\t\t\t\n" << endl;
    cout << "\t\t\t\tFinal Winner: " << FinalWinner(read) << "\t\t\t\t\n" << endl;
    cout << "\t\t\t\t______________________________________________________\t\t\t\t\n" << endl;
}

void RestScreen()
{
    system("cls");
    system("Color 0F");
}

void Start()
{
    char PlayAgain = '+';
    do
    {
        RestScreen();
        stGamestatics read;
        StartRounds(ReadNumberOfRounds(), read);
        PrintGameOverScreen(read);

        cout << "Do you want to play again? Y/N  ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));

    Start();

    return 0;
}