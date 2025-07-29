#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum: enChoice
// Represents the available choices in the game
enum enChoice { chStone = 1, chPaper = 2, chScissors = 3 };

// Enum: enRoundResult
// Represents the result of a round
enum enRoundResult { rsPlayer1 = 1, rsPlayer2 = 2, rsDraw = 3 };

// Struct: stMatchRound
// Holds the data of a single round
struct stMatchRound {
    short RoundID = 0;
    enChoice Player1Move;
    enChoice Player2Move;
    enRoundResult RoundOutcome;
    string RoundWinner;
};

// Struct: stMatchSummary
// Summarizes the entire game
struct stMatchSummary {
    short TotalRounds = 0;
    short Player1Wins = 0;
    short Player2Wins = 0;
    short Draws = 0;
    enRoundResult OverallResult;
    string MatchWinner = "";
};

string fnChoiceToStr(enChoice choice) {
    string options[] = { "Stone", "Paper", "Scissors" };
    return options[choice - 1];
}

string fnWinnerToStr(enRoundResult result, bool vsComputer = false) {
    if (vsComputer) {
        if (result == rsPlayer1) return "Player1";
        else if (result == rsPlayer2) return "Computer";
        else return "Draw";
    }
    string winners[] = { "Player1", "Player2", "Draw" };
    return winners[result - 1];
}

enChoice fnReadPlayerChoice(short playerNum) {
    short input;
    do {
        cout << "\nPlayer " << playerNum << " - Choose [1] Stone, [2] Paper, [3] Scissors: ";
        cin >> input;
    } while (input < 1 || input > 3);
    return (enChoice)input;
}

// New function to support multiplayer or vs computer
enChoice fnGetPlayerChoice(short playerNum, bool isComputer) {
    if (isComputer) {
        return (enChoice)(rand() % 3 + 1);
    }
    else {
        return fnReadPlayerChoice(playerNum);
    }
}

enRoundResult fnEvaluateRoundWinner(const stMatchRound& round) {
    if (round.Player1Move == round.Player2Move)
        return rsDraw;

    switch (round.Player1Move) {
    case chStone:
        return (round.Player2Move == chPaper) ? rsPlayer2 : rsPlayer1;
    case chPaper:
        return (round.Player2Move == chScissors) ? rsPlayer2 : rsPlayer1;
    case chScissors:
        return (round.Player2Move == chStone) ? rsPlayer2 : rsPlayer1;
    }
    return rsDraw;
}

enRoundResult fnEvaluateMatchWinner(short p1Wins, short p2Wins) {
    if (p1Wins > p2Wins)
        return rsPlayer1;
    else if (p2Wins > p1Wins)
        return rsPlayer2;
    else
        return rsDraw;
}

void fnDisplayRound(const stMatchRound& round, bool vsComputer) {
    cout << "\n--- Round " << round.RoundID << " ---\n";
    cout << "Player 1: " << fnChoiceToStr(round.Player1Move) << endl;
    cout << (vsComputer ? "Computer" : "Player 2") << ": " << fnChoiceToStr(round.Player2Move) << endl;
    cout << "Winner: " << round.RoundWinner << "\n";
}

stMatchSummary fnPlayMatch(short rounds, bool vsComputer) {
    stMatchRound round;
    short p1Wins = 0, p2Wins = 0, draws = 0;

    for (short i = 1; i <= rounds; ++i) {
        round.RoundID = i;
        round.Player1Move = fnGetPlayerChoice(1, false);
        round.Player2Move = fnGetPlayerChoice(2, vsComputer);
        round.RoundOutcome = fnEvaluateRoundWinner(round);
        round.RoundWinner = fnWinnerToStr(round.RoundOutcome, vsComputer);

        switch (round.RoundOutcome) {
        case rsPlayer1: ++p1Wins; break;
        case rsPlayer2: ++p2Wins; break;
        case rsDraw: ++draws; break;
        }

        fnDisplayRound(round, vsComputer);
    }

    enRoundResult matchResult = fnEvaluateMatchWinner(p1Wins, p2Wins);
    return { rounds, p1Wins, p2Wins, draws, matchResult, fnWinnerToStr(matchResult, vsComputer) };
}

void fnGameLoop() {
    char again = 'Y';
    do {
        system("cls");
        char mode;
        cout << "Welcome to Rock-Paper-Scissor Game :) \n" << endl;
        cout << "Choose mode: [1] Player vs Player, [2] Player vs Computer: ";
        cin >> mode;

        bool vsComputer = false;
        if (mode == '2') vsComputer = true;

        stMatchSummary summary = fnPlayMatch(3, vsComputer);
        cout << "\nMatch Over. Final Winner: " << summary.MatchWinner << endl;
        cout << "\nPlay again? (Y/N): ";
        cin >> again;
    } while (again == 'Y' || again == 'y');
}

int main() {
    srand((unsigned)time(nullptr));
    fnGameLoop();
    return 0;
}
