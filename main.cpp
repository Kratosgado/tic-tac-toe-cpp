#include <iostream>
#include <SFML/Graphics.hpp>
#include "TicTacToe.hpp"


int main() {
   TicTacToe game;

   if (!game.loadAssets()) {
      std::cout << "Error loading assets" << std::endl;
      std::system("pause");
      return 1;
   }
   if (!game.loadBoard(1)) {
      std::cout << "Error loading board" << std::endl;
      std::system("pause");
      return 1;
   }

   sf::RenderWindow window(sf::VideoMode(400, 600), "Tic Tac Toe");
   while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
            window.close();
         }
         if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            game.keyPress(pos);
         }
      }
      window.clear();
      window.draw(game.background);
      window.draw(game.board);
      window.draw(game.text);
      window.draw(game.reset);
      for (int i = 0; i < 9; i++) {
         window.draw(game.pieces[i]);
      }
      window.display();
   }

}