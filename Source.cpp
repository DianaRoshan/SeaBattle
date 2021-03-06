#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <Windows.h>

#define SFML_NO_DEPRECATED_WARNINGS

using namespace sf;
using namespace std;

int board_Opponent[N][N];
RenderWindow window(VideoMode(1000, 600), "Sea Battle");//����������� ����
Vector2f centerWindow = Vector2f(window.getSize().x / 2, window.getSize().y / 2);

int cellBoardX, cellBoardY;

void draw(Game& player1, Game& player2) {
	unsigned int width = 84;
	unsigned int height = 108;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (player1.board[i][j] == 0) player1.sprite.setTextureRect(IntRect(0, 0, 32, 32));
			if (player1.board[i][j] == 1) player1.sprite.setTextureRect(IntRect(32, 0, 32, 32));
			if (player1.board[i][j] == 2) player1.sprite.setTextureRect(IntRect(64, 0, 32, 32));
			if (player1.board[i][j] == 3) player1.sprite.setTextureRect(IntRect(96, 0, 32, 32));
			if (player1.board[i][j] == 4) player1.sprite.setTextureRect(IntRect(128, 0, 32, 32));

			player1.sprite.setPosition(width + (i * 32), height + (j * 32));//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. 
			//���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
			window.draw(player1.sprite);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board_Opponent[i][j] == 0) player2.sprite.setTextureRect(IntRect(0, 0, 32, 32));
			if (board_Opponent[i][j] == 1) player2.sprite.setTextureRect(IntRect(32, 0, 32, 32));
			if (board_Opponent[i][j] == 2) player2.sprite.setTextureRect(IntRect(64, 0, 32, 32));
			if (board_Opponent[i][j] == 3) player2.sprite.setTextureRect(IntRect(96, 0, 32, 32));
			if (board_Opponent[i][j] == 4) player2.sprite.setTextureRect(IntRect(128, 0, 32, 32));

			player2.sprite.setPosition((i * 32) + 448 + width, height + (j * 32));//
			window.draw(player2.sprite);
		}
	}
}
void shootPlayer(Game& player2) {
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (IntRect((564 + 32 * i), (140 + 32 * j), 32, 32).contains(Mouse::getPosition(window))) {//
				cellBoardX = j + 1;
				cellBoardY = i + 1;
				if (player2.board[cellBoardY][cellBoardX] == 0) { board_Opponent[cellBoardY][cellBoardX] = 2; player2.board[cellBoardY][cellBoardX] = 2; break; }
				if (player2.board[cellBoardY][cellBoardX] == 1) { board_Opponent[cellBoardY][cellBoardX] = 3; player2.board[cellBoardY][cellBoardX] = 3; break; }
			}
		}
	}
}
void shootComputer(Game& player1) {
	bool EXIT = false;
	int cellX, cellY;
	while (!EXIT) {
		cellY = rand() % 10 + 1;
		cellX = rand() % 10 + 1;
		if (player1.board[cellY][cellX] == 0) { player1.board[cellY][cellX] = 2; EXIT = true; }
		if (player1.board[cellY][cellX] == 1) { player1.board[cellY][cellX] = 3; EXIT = true; }
	}
}
int win(Game& player1, Game& player2) { //���� �� �����-�� ���� ��� �������� - true, ����� - false.
	int win1 = 0, win2 = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (player1.board[i][j] == 1) {
				win2++;
				break;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (player2.board[i][j] == 1) {
				win1++;
				break;
			}
		}
	}
	if (win1 == 0) { player1.win = true; return true; }
	if (win2 == 0) { player2.win = true; return true; }
	return false;
}

int main() {

	window.setFramerateLimit(60);

	Font font;//�����
	font.loadFromFile("C:\\Users\\diana\\OneDrive\\�����������\\����\\������ ��\\Project1\\comic.ttf");

	Text Titletxt("", font, 20);//������� ������ ������. ���������� � ������ ������, �����, ������ ������(� ��������)
	Titletxt.setFillColor(Color::Black);
	Titletxt.setString("Push Esc to exit or push Enter to play new game");
	Titletxt.setPosition(centerWindow.x - Titletxt.getGlobalBounds().width / 2, 50);

	Text Wintxt("", font, 40);	
	Wintxt.setFillColor(Color::Red);

	Game player1;
	Sleep(1000);
	Game player2;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board_Opponent[i][j] = 4;
		}
	}

	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			board_Opponent[i][j] = 0;
		}
	}

	while (window.isOpen()) {
		//����������� ����������� �������
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				player1.setShips();
				Sleep(1000);
				player2.setShips();
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						board_Opponent[i][j] = 4;
					}
				}

				for (int i = 1; i < N - 1; i++) {
					for (int j = 1; j < N - 1; j++) {
						board_Opponent[i][j] = 0;
					}
				}
			}
			if (e.type == Event::MouseButtonPressed) {
				shootPlayer(player2);
				shootComputer(player1);
			}
		}

		if (win(player1, player2)) {
			window.clear(Color::White);
			if (player1.win) Wintxt.setString("You won!"); else if (player2.win) Wintxt.setString("You lost!");
			Wintxt.setPosition(centerWindow.x - Wintxt.getGlobalBounds().width / 2, centerWindow.y - Wintxt.getGlobalBounds().height / 2);
			//getGlobalBounds() - ��� ������� ���������� ������� ������� � ���������� ������� ��������� 2D-����
			window.draw(Wintxt);
			window.display();
			Sleep(3000);
			window.close();
		}

		window.clear(Color::White);
		draw(player1, player2);
		window.draw(Titletxt);
		window.display();
	}

	return 0;
}