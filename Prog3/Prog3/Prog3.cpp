// Prog3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int WIDTH_PLAYER_LETTER = 3;
const int WIDTH_MATCHES_WON = 9;
const int WIDTH_GAMES_WON = 12;
const int WIDTH_GAMES_LOST = 10;
const int MAX_SCORE = 11;
const int WINNING_MARGIN = 2;
const int GAMES_TO_WIN_MATCH = 3;
void ProcessOneMatch(int& player1Matches, int& player1GamesWon,
   int& player1GamesLoss, int& player2Matches,
   int& player2GamesWon, int& player2GamesLoss);
bool NoClearWinner(int Aswins, int Asmatches,
   int Bswins, int Bsmatches, int Cswins,
   int Csmatches);
void PrintPlayerResults(char playerLetter, int matchesWon,
   int gamesWon, int gamesLost);

int main()
{
   int playerAMatchesWon = 0, playerAGamesWon = 0, playerAGamesLost = 0;
   int playerBMatchesWon = 0, playerBGamesWon = 0, playerBGamesLost = 0;
   int playerCMatchesWon = 0, playerCGamesWon = 0, playerCGamesLost = 0;
   ProcessOneMatch(playerAMatchesWon, playerAGamesWon,
      playerAGamesLost, playerBMatchesWon,
      playerBGamesWon, playerBGamesLost);
   ProcessOneMatch(playerBMatchesWon, playerBGamesWon,
      playerBGamesLost, playerCMatchesWon,
      playerCGamesWon, playerCGamesLost);
   ProcessOneMatch(playerCMatchesWon, playerCGamesWon,
      playerCGamesLost, playerAMatchesWon,
      playerAGamesWon, playerAGamesLost);
   cout << endl << "Round Robin Results" << endl;
   cout << "Player    Matches     Games     Games" << endl;
   cout << "          Won         Won       Lost" << endl;
   cout << "------    -------     -----     -----" << endl;
   PrintPlayerResults('A', playerAMatchesWon,
      playerAGamesWon, playerAGamesLost);
   PrintPlayerResults('B', playerBMatchesWon,
      playerBGamesWon, playerBGamesLost);
   PrintPlayerResults('C', playerCMatchesWon,
      playerCGamesWon, playerCGamesLost);
   cout << endl;

   if (NoClearWinner(playerAGamesWon, playerAMatchesWon,
      playerBGamesWon, playerBMatchesWon,
      playerCGamesWon, playerCMatchesWon))
   {
      cout << "There is no clear winner." << endl;
   }
   else
   {
      if (playerAMatchesWon > playerBMatchesWon
         && playerAMatchesWon > playerCMatchesWon
         && playerAGamesWon > playerBGamesWon
         && playerAGamesWon > playerCGamesWon
         || playerAMatchesWon == playerBMatchesWon
         && playerAMatchesWon == playerCMatchesWon
         && playerAGamesWon > playerBGamesWon
         && playerAGamesWon > playerCGamesWon)
      {
         cout << "Winner is player A." << endl;
      }
      else if (playerBMatchesWon > playerAMatchesWon
         && playerBMatchesWon > playerCMatchesWon
         && playerBGamesWon > playerAGamesWon
         && playerBGamesWon > playerCGamesWon
         || playerBMatchesWon == playerAMatchesWon
         && playerBMatchesWon == playerCMatchesWon
         && playerBGamesWon > playerAGamesWon
         && playerBGamesWon > playerCGamesWon)
      {
         cout << "Winner is player B." << endl;
      }
      else if (playerCMatchesWon > playerAMatchesWon
         && playerCMatchesWon > playerBMatchesWon
         && playerCGamesWon > playerAGamesWon
         && playerCGamesWon > playerBGamesWon
         || playerCMatchesWon == playerAMatchesWon
         && playerCMatchesWon == playerBMatchesWon
         && playerCGamesWon > playerAGamesWon
         && playerCGamesWon > playerBGamesWon)
      {
         cout << "Winner is player C." << endl;
      }
   }
}

//--------------------------------------------------------------
// This function reads in a table tennis score and returns the 
// value read if it is a legitimate score. A legitimate score
// is any nonnegative value. The function continues to read
// until a valid score is read issuing an error message if not 
// valid.
// params: out
//--------------------------------------------------------------
int ReadScore(string prompt)
{
   int score;
   cout << prompt;
   cin >> score;
   while (score < 0)
   {
      cout << endl << "Incorrect score : " << score << " entered." << endl
         << "Make sure score is nonnegative." << endl;
      cout << prompt;
      cin >> score;
   }
   return score;
}

//--------------------------------------------------------------
// This function returns true if the two table tennis scores
// entered are legitimate according to the present USATT rules 
// that stipulate the first player to 11 wins and must win by 2 
// points.
// It returns false otherwise.
// params: out
//--------------------------------------------------------------
bool LegitScores(int score1, int score2)
{
   return (score1 == MAX_SCORE && score1 > score2 && score2 + WINNING_MARGIN <= score1)
      || (score2 == MAX_SCORE && score2 > score1 && score1 + WINNING_MARGIN <= score2);
}

//--------------------------------------------------------------
// This function reads in table tennis scores for one table
// tennis game until legitimate scores are entered and returns 
// the points scored via the parameters, score1 and score2.
// params: in
//--------------------------------------------------------------
void ProcessOneGame(int& score1, int& score2)
{
   score1 = ReadScore("Enter first score: ");
   cout << endl;
   score2 = ReadScore("Enter second score: ");
   cout << endl;
   while (!LegitScores(score1, score2))
   {
      cout << "Scores given are not legitimate." << endl;
      score1 = ReadScore("Enter first score: ");
      cout << endl;
      score2 = ReadScore("Enter second score: ");
      cout << endl;
   }
}

//--------------------------------------------------------------
// This function processes a table tennis match of best 3 of 5
// games to win a match.  Games are processed until the match is 
// won; the match is won when a player has won 3 games. Each
// players, wins and losses [player1GamesWon, player1GamesLoss, 
// player2GamesWon, player2GamesLoss] are updated appropriately.  
// Finally, once the winner of the match is determined, the
// appropriate player's match total is updated [player1Matches, 
// player2Matches].
// params: inout
//--------------------------------------------------------------
void ProcessOneMatch(int& player1Matches, int& player1GamesWon,
   int& player1GamesLoss, int& player2Matches,
   int& player2GamesWon, int& player2GamesLoss)
{
   int player1GamesWonThisMatch = 0, player2GamesWonThisMatch = 0;
   while (player1GamesWonThisMatch < GAMES_TO_WIN_MATCH && player2GamesWonThisMatch < GAMES_TO_WIN_MATCH)
   {
      int score1, score2;
      ProcessOneGame(score1, score2);
      if (score1 > score2)
      {
         player1GamesWonThisMatch++;
         player1GamesWon++;
         player2GamesLoss++;
      }
      else
      {
         player2GamesWonThisMatch++;
         player2GamesWon++;
         player1GamesLoss++;
      }
   }
   if (player1GamesWonThisMatch > player2GamesWonThisMatch)
   {
      player1Matches++;
   }
   else
   {
      player2Matches++;
   }
   return;
}

//--------------------------------------------------------------
// This function returns true if there is a tie (no clear 
// winner) based on the games won and matches won.  It returns 
// false otherwise.
// params: out
//--------------------------------------------------------------
bool NoClearWinner(int Aswins, int Asmatches,
   int Bswins, int Bsmatches, int Cswins,
   int Csmatches)
{
   return (Asmatches == Bsmatches && Bsmatches == Csmatches)
      && (Csmatches == Asmatches && Aswins == Bswins)
      && (Bswins == Cswins && Cswins == Aswins)
      || (Asmatches == Bsmatches && Aswins == Bswins && Cswins < Aswins)
      || (Bsmatches == Csmatches && Bswins == Cswins && Aswins < Bswins)
      || (Csmatches == Asmatches && Cswins == Aswins && Bswins < Cswins);
}

//--------------------------------------------------------------
// This function displays a players individual results
// params: in
//--------------------------------------------------------------
void PrintPlayerResults(char playerLetter, int matchesWon,
   int gamesWon, int gamesLost)
{
   cout << setw(WIDTH_PLAYER_LETTER) << playerLetter
      << setw(WIDTH_MATCHES_WON) << matchesWon
      << setw(WIDTH_GAMES_WON) << gamesWon
      << setw(WIDTH_GAMES_LOST) << gamesLost << endl;
}
