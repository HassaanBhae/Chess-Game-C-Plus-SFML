#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
int flag=1;
int board[8][8] =
		{ 2, 3, 4, 5, 6, 4, 3, 2,
		  1, 1, 1, 1, 1, 1, 1, 1,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		 -1,-1,-1,-1,-1,-1,-1,-1,
		 -2,-3,-4,-5,-6,-4,-3,-2,};
struct undoStack{
	int undoarr[8][8];
	undoStack* next;
};
void printBoard(){
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				cout<<board[x][y]<<" ";
			}
			cout << endl;
		} 
}
//Stack For Undo Move
void push(undoStack* *top){
		undoStack* ptr=(undoStack*)malloc(sizeof(undoStack));
		memcpy (ptr->undoarr, board, 8*8*sizeof(int));
		flag=1;
	if(*top==NULL)
	{
		*top=ptr;
		ptr->next=NULL;
		printf("Pushed Starting\n");
		printBoard();
	}else{
		ptr->next=*top;
		*top=ptr;
		printf("Pushed\n");
		printBoard();
	}
}
void pop(undoStack** top){
		cout<<("Pop Called:")<<flag;
		if (flag==1)
		{
		undoStack* curr=*top;
		*top=(*top)->next;
		free(curr);
		cout<<"Pop Called At Same Postition\n";
		flag=2;
		}
		undoStack* curra=(*top);
		memcpy (board,(*top)->undoarr, 8*8*sizeof(int));
		printBoard();
		if((*top)->next==NULL)
		{
			printf("Pop Called Top In Else Statement\n");
		}else
		{
		*top=(*top)->next;
		free(curra);
		}
	}
int main(){
	undoStack* top=NULL;
	int LENGTH =8;
	int BlackPawn =1;
	int WhitePawn =-1;
	int BlackRook =2;
	int WhiteRook =-2;
	int WhiteKnight =-3;
	int BlackKnight =3;
	int BLackBishop =4;
	int WhiteBishop =-4;
	int WhiteQueen =-5;
	int BlackQueen= 5;
	int BlackKing =6;
	int WhiteKing =-6;
	int  size = 100, move = 0, x, y;
//top should always be chess starting position
	push(&top);
	RenderWindow window(VideoMode(850, 850), "Chess Board");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14;

	t1.loadFromFile("images/tBoard.jpg");
	t2.loadFromFile("images/tBlackPawn.png");
	t3.loadFromFile("images/tWhitePawn.png");
	t4.loadFromFile("images/tBlackRook.png");
	t5.loadFromFile("images/tWhiteRook.png");
	t6.loadFromFile("images/tWhiteKnight.png");
	t7.loadFromFile("images/tBlackKnight.png");
	t8.loadFromFile("images/tBLackBishop.png");
	t9.loadFromFile("images/tWhiteBishop.png");
	t10.loadFromFile("images/tWhiteQueen.png");
	t11.loadFromFile("images/tBlackQueen.png");
	t12.loadFromFile("images/tBlackKing.png");
	t13.loadFromFile("images/tWhiteKing.png");
	t14.loadFromFile("images/tUndo.png");

	Sprite tBoard(t1);
	Sprite tBlackPawn(t2);
	Sprite tWhitePawn(t3);
	Sprite tBlackRook(t4);
	Sprite tWhiteRook(t5);
	Sprite tWhiteKnight(t6);
	Sprite tBlackKnight(t7);
	Sprite tBLackBishop(t8);
	Sprite tWhiteBishop(t9);
	Sprite tWhiteQueen(t10);
	Sprite tBlackQueen(t11);
	Sprite tBlackKing(t12);
	Sprite tWhiteKing(t13);
	Sprite tundo(t14);
	Sprite currentTexture;
	float dx = 0, dy = 0;
	int valueOfPiece = 0;
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		 x = pos.x / size;
		 y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
		//Mouse Pressed
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;
						if (board[y][x] == BlackPawn)
						{
							valueOfPiece = BlackPawn;
							currentTexture = tBlackPawn;
							board[y][x] = 0;
						}
						if (board[y][x] == WhitePawn)
						{
							valueOfPiece = WhitePawn;
							currentTexture = tWhitePawn;
							board[y][x] = 0;
						}
						if (board[y][x] == BlackRook)
						{
							valueOfPiece = BlackRook;
							currentTexture = tBlackRook;
							board[y][x] = 0;

						}
						if (board[y][x] == WhiteRook)
						{
							valueOfPiece = WhiteRook;
							currentTexture = tWhiteRook;
							board[y][x] = 0;

						}
						if (board[y][x] == WhiteKnight)
						{
							valueOfPiece = WhiteKnight;
							currentTexture = tWhiteKnight;
							board[y][x] = 0;
						}
						if (board[y][x] == BlackKnight)
						{
							valueOfPiece = BlackKnight;
							currentTexture = tBlackKnight;
							board[y][x] = 0;
						}
						if (board[y][x] == BLackBishop)
						{
							valueOfPiece = BLackBishop;
							currentTexture = tBLackBishop;
							board[y][x] = 0;
						}
						if (board[y][x] == WhiteBishop)
						{
							valueOfPiece = WhiteBishop;
							currentTexture = tWhiteBishop;
							board[y][x] = 0;
						}
						if (board[y][x] == WhiteQueen)
						{
							valueOfPiece = WhiteQueen;
							currentTexture = tWhiteQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BlackQueen)
						{
							valueOfPiece = BlackQueen;
							currentTexture = tBlackQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BlackKing)
						{
							valueOfPiece = BlackKing;
							currentTexture = tBlackKing;
							board[y][x] = 0;
						}
						if (board[y][x] == WhiteKing)
						{
							valueOfPiece = WhiteKing;
							currentTexture = tWhiteKing;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
						}
				}
			}
		//Mouse Released
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					board[y][x] = valueOfPiece;
					push(&top);
                    move = 0;
				}
			}
		//Undo button
			if (e.type == sf::Event::KeyPressed)
			{
                if (e.key.code == sf::Keyboard::Space)
				{  
				pop(&top);
				push(&top);
                }
            }
		}
	//Draw Board 
		window.clear();
		window.draw(tBoard);
		tundo.setPosition(800,800);
		window.draw(tundo);
	//while moving cursor draws current Texture at current mouse pos
		if (move == 1)
		{
			currentTexture.setPosition(pos.x-dx, pos.y-dy);
			window.draw(currentTexture);
		}
	//Fills Chess Board after every move
		for (int i = 0; i < LENGTH; i++)
		{
			for (int j = 0; j < LENGTH; j++)
			{
				if (board[i][j] != 0)
				{
					int x;
					if (board[i][j] == BlackPawn)
					{
						tBlackPawn.setPosition(j * size, i * size);
						window.draw(tBlackPawn);
					}
					if (board[i][j] == WhitePawn)
					{
						tWhitePawn.setPosition(j * size, i * size);
						window.draw(tWhitePawn);
					}
					if (board[i][j] == BlackRook)
					{
						tBlackRook.setPosition(j * size, i * size);
						window.draw(tBlackRook);

					}
					if (board[i][j] == WhiteRook)
					{
						tWhiteRook.setPosition(j * size, i * size);
						window.draw(tWhiteRook);

					}
					if (board[i][j] == WhiteKnight)
					{
						tWhiteKnight.setPosition(j * size, i * size);
						window.draw(tWhiteKnight);
					}
					if (board[i][j] == BlackKnight)
					{
						tBlackKnight.setPosition(j * size, i * size);
						window.draw(tBlackKnight);
					}
					if (board[i][j] == BLackBishop)
					{
						tBLackBishop.setPosition(j * size, i * size);
						window.draw(tBLackBishop);
					}
					if (board[i][j] == WhiteBishop)
					{
						tWhiteBishop.setPosition(j * size, i * size);
						window.draw(tWhiteBishop);
					}
					if (board[i][j] == WhiteQueen)
					{
						tWhiteQueen.setPosition(j * size, i * size);
						window.draw(tWhiteQueen);
					}
					if (board[i][j] == BlackQueen)
					{
						tBlackQueen.setPosition(j * size, i * size);
						window.draw(tBlackQueen);
					}
					if (board[i][j] == BlackKing)
					{
						tBlackKing.setPosition(j * size, i * size);
						window.draw(tBlackKing);
					}
					if (board[i][j] == WhiteKing)
					{
						tWhiteKing.setPosition(j * size, i * size);
						window.draw(tWhiteKing);
					}
				}
			}
		}
		window.display();
	}
		return 0;
}