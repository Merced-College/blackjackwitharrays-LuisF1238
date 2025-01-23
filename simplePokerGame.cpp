// Simple Poker Game
// Luis Flores
// Caydin Klups
// Hemant Kulkarni
// 10/10/2021
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define the suits and ranks of the cards
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

// Array to represent the deck of cards
int DECK[52];

// Index to keep track of the current card to be dealt
int currentCardIndex = 0;

// Function to initialize the deck with values from 0 to 51
void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
}
// Function to shuffle the deck using the Fisher-Yates algorithm
void shuffleDeck() {
    srand(time(0));// Random number generator
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52; // Gets a random index
        int temp = DECK[i]; // Swap the current card with the card at the random index
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}
// Function that deals a card from the deck
int dealCard() {
    return DECK[currentCardIndex++] % 13; // Returns rank of the card and increment the index
}

// Function to get the value of a card
int cardValue(int card) {
    return card < 9 ? card + 2 : 10;  // Cards 2-10 have their face values, while Jack, Queen, King = 10
}

int dealInitialPlayerCards() {
    int card1 = dealCard(); // Deals first card
    int card2 = dealCard(); // Deals second card
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);
}// Print the dealt cards

// Function that deals the dealer's initial card
int dealInitialDealerCards() {
    int card1 = dealCard();   // Deals first card
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1); // Returns card value
}

// Function to handle player's turn
int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);  // Get player's action
        if (action == "hit") {
            int newCard = dealCard(); // Deal a new card
            playerTotal += cardValue(newCard); // Add card value to the player's total
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[newCard / 13] << endl;
            if (playerTotal > 21) {  // Checks if  player busted
                break;
            }
        } else if (action == "stand") {
            break; // End player turn
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal; // Return player total
}

// Function to handle dealer's turn
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) { // Dealer always hits until their total is 17 or higher
        int newCard = dealCard(); // Deal new card
        dealerTotal += cardValue(newCard); // Add card value to dealer's total
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal; // Return dealer's final total
}
// Function to determine winner
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) { // Player wins if dealer busts or player has a higher total
        cout << "You win!" << endl;
    } else if (dealerTotal == playerTotal) {  // Tie if both totals are equal
        cout << "It's a tie!" << endl;
    } else {  // Otherwise, dealer wins
        cout << "Dealer wins!" << endl;
    }
}
// Function Added to initialize user input money
int initializeMoney() {   
    int money;
    cout << "How much money do you have? "; 
    cin >> money;
    cout << "You have this much money: " << money << endl;
    return money;
}

// Function Added to initialize user input bet
int initializeBet(int &money) { 
    int bet;
    cout << "How much money do you want to bet? "; 
    cin >> bet;

    if (bet > money) {
        cout << "You cannot bet more than you have!" << endl;
        return 0;
    }
    money -= bet;
    cout << "You have this much money left: " << money << endl;
    return bet;
}

// Function Added to display users final money after
int finalMoney(int money) {
    cout << "You have this much money left: " << money << endl;
    return money;
}



int main() {
    int money = initializeMoney();
    int bet = initializeBet(money);
    if (bet == 0) {
        return 0; // Exit if the bet is invalid
    }

    initializeDeck(); // Initialize deck
    shuffleDeck(); // Shuffle deck
  
    int playerTotal = dealInitialPlayerCards(); // Deal player's initial cards
    int dealerTotal = dealInitialDealerCards(); // Deal dealer's initial card
  
    playerTotal = playerTurn(playerTotal); // Player's turn
    if (playerTotal > 21) { // Check if player busted
        cout << "You busted! Dealer wins." << endl;
        finalMoney(money);
        return 0;
    }
    dealerTotal = dealerTurn(dealerTotal); // Dealer's turn
    determineWinner(playerTotal, dealerTotal); // Determine winner
    finalMoney(money);
    return 0;
}
