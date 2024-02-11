#include "TicTacToe.hpp"
#include <string.h>

bool TicTacToe::loadAssets() {
   if (!this->background_i.loadFromFile("assets/background.png")) {
      return false;
   }
   if (!this->background_t.loadFromImage(this->background_i)) {
      return false;
   }
   this->background.setTexture(this->background_t);

   if (!this->board_i.loadFromFile("assets/board.png")) {
      return false;
   }
   if (!this->board_t.loadFromImage(this->board_i)) {
      return false;
   }
   this->board.setTexture(this->board_t);
   this->board.setPosition(sf::Vector2f(0.0f, 100.0f));

   if (!this->reset_i.loadFromFile("assets/reset.png")) {
      return false;
   }
   if (!this->reset_t.loadFromImage(this->reset_i)) {
      return false;
   }
   this->reset.setTexture(this->reset_t);
   this->reset.setPosition(sf::Vector2f(25.0f, 525.0f));

   if (!this->cross_i.loadFromFile("assets/cross.png")) {
      return false;
   }
   if (!this->cross.loadFromImage(this->cross_i)) {
      return false;
   }
   if (!this->circle_i.loadFromFile("assets/circle.png")) {
      return false;
   }
   if (!this->circle.loadFromImage(this->circle_i)) {
      return false;
   }
   if (!this->blank_i.loadFromFile("assets/blank.png")) {
      return false;
   }
   if (!this->blank.loadFromImage(this->blank_i)) {
      return false;
   }

   if (!this->font.loadFromFile("assets/font.ttf")) {
      return false;
   }
   this->text.setFont(this->font);
   this->text.setCharacterSize(40);
   this->text.setFillColor(sf::Color::Black);
   this->text.setPosition(sf::Vector2f(25.0f, 25.0f));

   return true;
}
bool TicTacToe::loadBoard(int startPlayer) {
   memset(this->set, 0, 9);

   this->waitForReset = false;

   this->pieces[0].setPosition(sf::Vector2f(10.0f, 110.0f));
   this->pieces[1].setPosition(sf::Vector2f(150.0f, 110.0f));
   this->pieces[2].setPosition(sf::Vector2f(290.0f, 110.0f));
   this->pieces[3].setPosition(sf::Vector2f(10.0f, 250.0f));
   this->pieces[4].setPosition(sf::Vector2f(150.0f, 250.0f));
   this->pieces[5].setPosition(sf::Vector2f(290.0f, 250.0f));
   this->pieces[6].setPosition(sf::Vector2f(10.0f, 390.0f));
   this->pieces[7].setPosition(sf::Vector2f(150.0f, 390.0f));
   this->pieces[8].setPosition(sf::Vector2f(290.0f, 390.0f));
   for (int i = 0; i < 9; i++)
      this->pieces[i].setTexture(this->blank);

   this->cur = startPlayer;
   this->msg = std::string(startPlayer == 1 ? "It is player 1's turn" : "It is player 2's turn");
   this->text.setString(this->msg);

   return true;
}
bool TicTacToe::checkWin(int placement) {
   int row = (placement / 3) * 3;
   int column = placement % 3;

   if (this->set[row] == this->cur && this->set[row + 1] == this->cur && this->set[row + 2] == this->cur) return true;

   if (this->set[column] == this->cur && this->set[column + 3] == this->cur && this->set[column + 6] == this->cur) return true;

   if (this->set[0] == this->cur && this->set[4] == this->cur && this->set[8] == this->cur) return true;

   if (this->set[2] == this->cur && this->set[4] == this->cur && this->set[6] == this->cur) return true;

   return false;
}

bool TicTacToe::checkDraw() {
   for (int i = 0; i < 9; i++) {
      if (this->set[i] == 0) return false;
   }
   return true;
}

void TicTacToe::keyPress(sf::Vector2f pos) {
   if (!this->waitForReset) {
      for (int i = 0; i < 9; i++) {
         if (this->pieces[i].getGlobalBounds().contains(pos)) {
            if (this->set[i] == 0) {
               this->pieces[i].setTexture(this->cur == 1 ? this->cross : this->circle);

               this->set[i] = this->cur;

               if (this->checkWin(i)) {
                  this->waitForReset = true;
                  this->msg = this->cur == 1 ? "Player 1 wins!" : "Player 2 wins!";
                  this->text.setString(this->msg);
               }
               else {
                  if (this->checkDraw()) {
                     this->waitForReset = true;
                     this->msg = "Draw. Nobody wins.";
                     this->text.setString(this->msg);
                  }
                  else {
                     this->cur = this->cur == 1 ? 2 : 1;
                     this->msg = this->cur == 1 ? "It is player 1's turn" : "It is player 2's turn";
                     this->text.setString(this->msg);
                  }
               }
            }
            break;
         }
      }
   }

   if (this->reset.getGlobalBounds().contains(pos))
      this->loadBoard(this->cur == 1 ? 2 : 1);
}
