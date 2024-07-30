#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

//To Do:
//Add Rules for bishop queen king and enpassant
//Add Main Menu
int undoFlag=0;
int ifSameFlag=0;
int moves=0;
int currentMove=0;
//0=White , 1=Black
int oldx,oldy,x,y;
int wrongSide=0;
int board[8][8] =
		{-2,-3,-4,-5,-6,-4,-3,-2,
		 -1,-1,-1,-1,-1,-1,-1,-1,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  1, 1, 1, 1, 1, 1, 1, 1,
		  2, 3, 4, 5, 6, 4, 3, 2};
struct undoStack{
	int undoarr[8][8];
	undoStack* next;
};
void printBoard(){
	std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app);
	if(undoFlag==1){
		moves--;
		outfile << "/////Move:"<<moves<<" Undone/////\n";
		moves--;
	}else{
		outfile << "Move:"<<moves<<"\n";
	}
	moves++;
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++) 
			{
				cout<<board[x][y]<<" ";
				outfile << board[x][y] << " ";
			}
			outfile<<endl;
			cout << endl;
		}
		cout<<endl;
}
//Stack For Undo Move
void push(undoStack* *top){
		undoStack* ptr=(undoStack*)malloc(sizeof(undoStack));
		memcpy (ptr->undoarr, board, 8*8*sizeof(int));
	if(*top==NULL)
	{
		//Clear Log File 
		std::ofstream outfile;
    	outfile.open("log.txt", std::ios_base::out);
		*top=ptr;
		ptr->next=NULL;
		printf("Pushed Starting\n");
		printBoard();
	}else{
		for(int row = 0; row < 8; row++){
    		for(int column = 0; column < 8; column++){
        		if((ptr->undoarr)[row][column] == ((*top)->undoarr)[row][column]){
            	//cout<<"same\n";
					ifSameFlag=0;
        		}
        		else{
            	cout<<"Not same\n";
					ifSameFlag=1;
					break;
        		}
        	}
			if(ifSameFlag==1){
				break;
			}
    	}
		if(ifSameFlag==1){
			ptr->next=*top;
			*top=ptr;
			printf("Pushed\n");
			printBoard();
		}else{
			free(ptr);
		}
	}
}
void pop(undoStack** top){
		cout<<("Pop Called:");
		undoFlag=1;
		if((*top)->next==NULL){
			printf("At Starting Position\n");
			currentMove=0;
			cout<<"Starting move:White\n";
			return;
		}else{
			undoStack* curr=*top;
			*top=(*top)->next;
			free(curr);
			memcpy (board,(*top)->undoarr, 8*8*sizeof(int));
			printBoard();
			switch (currentMove) {
  				case 1:
					currentMove=0;
					cout<<"current move:White\n";
					break;
				case 0:
					currentMove=1;
					cout<<"current move:Black\n";
					break;
				}
		}
	}
void checkCurrentMoveSide(int valueOfPiece){
	if(valueOfPiece==0){
		return ;
	}
	if(currentMove==0){
		if(valueOfPiece>0){
			currentMove=1;
			cout<<"Moving White";
			return ;
		}else{
			cout<<"Pls Move White!!";
			wrongSide=1;
			return ;
		}
	}
	if(currentMove==1){
		if(valueOfPiece<0){
			currentMove=0;
			cout<<"Moving Black";
			return ;
		}else{
			cout<<"Pls Move Black!!";
			wrongSide=1;
			return ;
		}
	}
}
void invalidMove(){
	switch(currentMove){
		case 0:
				currentMove=1;
				break;
		case 1:
				currentMove=0;
				break;
	}
	y=oldy;
	x=oldx;
	cout<<"Invalid Move!";
}
void checkInBetweenSides(){
	//CHECKING SIDES
	if(x == oldx && y != oldy){
		if(oldy > y){
			for (int initialy = y+1;initialy < oldy;initialy++){
				cout<<"Loop Running";
				if(board[initialy][x]==0){
				}else{
					invalidMove();
					return;
				}
			}
		}
		else {
			for (int initialy = oldy+1;initialy < y;initialy++){
				if(board[initialy][x]==0){
				}else{
					invalidMove();
					return;
				}
			}
		}
		
		return;
	}
	if(x != oldx && y == oldy){
		if(oldx > x){
			for (int initialx = x+1 ;initialx < oldx ;initialx++){
				if(board[y][initialx]==0){
				}else{
					invalidMove();
					return;
				}
			}
		}
		else {
			for (int initialx = oldx+1 ;initialx < x ;initialx++){
				if(board[y][initialx]==0){
				}else{
					invalidMove();
					return;
				}
			}
		}
		return;
	}
	//CHECKING DIAGONALS
}



void MoveCheck(int valueOfPiece){
	//Friendly Fire
	if(valueOfPiece < 0 && board[y][x] < 0){
		invalidMove();
		return;
	}
	else if(valueOfPiece > 0 && board[y][x] > 0){
		invalidMove();
		return;
	}
	switch(valueOfPiece){
		//Black Pawn
		case (-1):
				cout<<"Moving Black Pawn";
				//TAKING PIECE
				if (board[y][x]!=0 && y == oldy+1){
					if(x == oldx+1 || x == oldx-1){
						cout<<"Taking Piece";
						return;
					}else{
						invalidMove();
						return;
					}
				}   
				//MOVING 1 BOX IN SAME X AND NOTHING IN FRONT
				if (y == oldy+1 && x == oldx && board[y][x] == 0){
						cout<<"Moving 1 Block";
						return;
					}
				//MOVING 2 BOX IN SAME X AND NOTHING IN FRONT AND NOTHING IN BETWEEN
				else if (y == oldy+2 && x == oldx && board[y-1][x] == 0 && board[y][x] == 0 && oldy==1){
						cout<<"Moving 2 Block";
						return;
				}else{
					invalidMove();
					return;
				}
		break;
		//White Pawn
		case (1):
				cout<<"Moving White Pawn";
				//TAKING PIECE
				if (board[y][x]!=0 && y == oldy-1){
					if(x == oldx+1 || x == oldx-1){
						cout<<"Taking Piece";
						return;
					}else{
						invalidMove();
						return;
					}
				}   
				//MOVING 1 BOX IN SAME X AND NOTHING IN FRONT
				if (y == oldy-1 && x == oldx && board[y][x] == 0){
						cout<<"Moving 1 Block";
						return;
					}
				//MOVING 2 BOX IN SAME X AND NOTHING IN FRONT AND NOTHING IN BETWEEN
				else if (y == oldy-2 && x == oldx && board[y+1][x] == 0 && board[y][x] == 0 && oldy==6){
						cout<<"Moving 2 Block";
						return;
				}else{
					invalidMove();
					return;
				}
		break;
		//Black Rook
		case (-2):
			//If not same X and Not Same Y
			if((y != oldy && x != oldx) || (y == oldy && x == oldx)){
				invalidMove();
				return;
			}
			//If same Y then Diff X
			if((y == oldy && x != oldx)  || (y != oldy && x == oldx)){
				checkInBetweenSides();
				return;
			}
    	break;
		//White Rook
  		case (2):
			//If not same X and Not Same Y
			if((y != oldy && x != oldx) || (y == oldy && x == oldx)){
				invalidMove();
				return;
			}
			//If same Y then Diff X
			if((y == oldy && x != oldx) || (y != oldy && x == oldx)){
				checkInBetweenSides();
				return;
			}
    	break;
		//Black Knight
		case (-3):
    	break;
		//White Knight
  		case (3):
    	break;
		//Black Bishop
		case (-4):
    	break;
		//White Bishop
  		case (4):
    	break;
		//Black Queen
		case (-5):
    	break;
		//White Queen
  		case (5):
    	break;
		//Black King
		case (-6):
    	break;
		//White King
  		case (6):
    	break;

	}
}
int main(){
	undoStack* top=NULL;
	int LENGTH 		=  8 ,size = 100 ,moving = 0;
	  								//0=false, 1=true
	int BlackPawn   = -1;
	int BlackRook   = -2;
	int BlackKnight = -3;
	int BLackBishop = -4;
	int BlackQueen  = -5;
	int BlackKing   = -6;
	int WhitePawn   =  1;
	int WhiteRook   =  2;
	int WhiteKnight =  3;
	int WhiteBishop =  4;
	int WhiteQueen  =  5;
	int WhiteKing   =  6;
//top should always be chess starting position
	push(&top);
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14;
    // Load icon image
    sf::Image icon;
    icon.loadFromFile("images/ticon.png");
    // Create SFML window with icon
    //sf::RenderWindow window(sf::VideoMode(850, 850), "Chess Board");
	RenderWindow window(VideoMode(850, 850), "Chess Board");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
							//board[y][x] = 0;
						}
						if (board[y][x] == WhitePawn)
						{
							valueOfPiece = WhitePawn;
							currentTexture = tWhitePawn;
							//board[y][x] = 0;
						}
						if (board[y][x] == BlackRook)
						{
							valueOfPiece = BlackRook;
							currentTexture = tBlackRook;
							//board[y][x] = 0;

						}
						if (board[y][x] == WhiteRook)
						{
							valueOfPiece = WhiteRook;
							currentTexture = tWhiteRook;
							//board[y][x] = 0;

						}
						if (board[y][x] == WhiteKnight)
						{
							valueOfPiece = WhiteKnight;
							currentTexture = tWhiteKnight;
							//board[y][x] = 0;
						}
						if (board[y][x] == BlackKnight)
						{
							valueOfPiece = BlackKnight;
							currentTexture = tBlackKnight;
							//board[y][x] = 0;
						}
						if (board[y][x] == BLackBishop)
						{
							valueOfPiece = BLackBishop;
							currentTexture = tBLackBishop;
							//board[y][x] = 0;
						}
						if (board[y][x] == WhiteBishop)
						{
							valueOfPiece = WhiteBishop;
							currentTexture = tWhiteBishop;
							//board[y][x] = 0;
						}
						if (board[y][x] == WhiteQueen)
						{
							valueOfPiece = WhiteQueen;
							currentTexture = tWhiteQueen;
							//board[y][x] = 0;
						}
						if (board[y][x] == BlackQueen)
						{
							valueOfPiece = BlackQueen;
							currentTexture = tBlackQueen;
							//board[y][x] = 0;
						}
						if (board[y][x] == BlackKing)
						{
							valueOfPiece = BlackKing;
							currentTexture = tBlackKing;
							//board[y][x] = 0;
						}
						if (board[y][x] == WhiteKing)
						{
							valueOfPiece = WhiteKing;
							currentTexture = tWhiteKing;
							//board[y][x] = 0;
						}
							//set OLD X AND Y
							oldx=x;
							oldy=y;
							checkCurrentMoveSide(valueOfPiece);
							if(wrongSide!=1){
								board[y][x] = 0;
								moving = 1;
							}else{
								moving=0;
								board[y][x] = valueOfPiece;
								valueOfPiece = 0;
								wrongSide=0;
							}
				}
			}
		//Mouse Released
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					MoveCheck(valueOfPiece);
					if(valueOfPiece!=0){
						board[y][x] = valueOfPiece;
					}
					push(&top);
                    moving = 0;
					valueOfPiece=0;
				}
			}
		//Undo button
			if (e.type == sf::Event::KeyPressed)
			{
                if (e.key.code == sf::Keyboard::Space)
				{  
				pop(&top);
				undoFlag=0;
				//push(&top);
                }
            }
		}
	//Draw Board 
		window.clear();
		window.draw(tBoard);
		tundo.setPosition(800,800);
		window.draw(tundo);
	//while moving cursor draws current Texture at current mouse pos
		if (moving == 1 && valueOfPiece!=0)
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