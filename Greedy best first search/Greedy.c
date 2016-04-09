
//  gcc a.c -o a  -lgraph

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Structs.h"
#include "extra.h"


/*
 * 			Check  Situation ( char The destination you wold like to move on)
 *
 * If the car can move in that position
 *  it's return false
 *  and if you cant move in that position
 *  it's return true
 */
void CheckSituation(char check);

/*
 * The Function ScanTheMaze scan The Maze from The path
 * the path saved in the variable MAZEPATH
 */
void IdontKnow(unsigned short Index, short Color);
void ScanTheMaze(); 
void init();
void DrowCar();
void CheckingMovements();
bool Go();



void main(){

	ScanTheMaze();

	int keyboardDelay;
	printf("Enter Number : ");
	scanf("%d",&keyboardDelay);

	int   gd = DETECT, gm=1	;
	initgraph(&gd,&gm,NULL);

	init();
	
	bar(28, 28, Width*20+10 , 32);
	outtextxy ( getmaxx()/2 -123 , getmaxy()-17  ,"Greedy Best First Search Algorithm" );
	
	car.g=20;

	Open = calloc(1, sizeof (graph));
	Close = calloc(1, sizeof (graph));

	edge *e= calloc(1, sizeof (edge));
	e->g = 0;
	e->h =  (abs(car.X_Start - car.X_Gole) + abs(car.Y_Start-20 - car.Y_Gole));
	e->index = LowerIndex;
	add_on_list(e);
	swap_edge_betwen_lests();
	getchar();
		CheckSituation('D');
		CheckSituation('U');
		CheckSituation('L');
		CheckSituation('R');


	while(Open->length){

		if(keyboardDelay > 0){
			--keyboardDelay;
			getchar();
		}

		if(Go()){// it's a new node or not
			swap_edge_betwen_lests();
			DrowCar();
			if(car.X_Current == car.X_Gole && car.Y_Current == car.Y_Gole){
				outtextxy ( 250, 5  ,"Found The Gole" );
				backtrack();
				break;
			}
			CheckingMovements();
			delay(NewStepDelay);
		}

	}
	

	PrintList(Open,"Open.txt");
	PrintList(Close,"Close.txt");
	getch();
	closegraph();
}
void CheckSituation(char check){
	bool posseble = false;
    edge *e = calloc(1, sizeof (edge));
    int i;

	switch(check){
		case 'U':// upward 
			if (UpperSituation == ' '){
				e->previous = LowerIndex;
				e->index  = UpperIndex;
				e->h = (abs(car.X_Current - car.X_Gole) + abs(car.Y_Current-20 - car.Y_Gole));
				posseble = true;
			}
		break;
		case 'L':// left
			if( LeftSituation == ' ' || LeftSituation == '_' ){
				e->previous = LowerIndex;
				e->index  = LeftIndex - 1;
				e->h = (abs(car.X_Current-20 - car.X_Gole) + abs(car.Y_Current - car.Y_Gole));
				posseble = true;
			}
		break;
		case 'D':// downward
			if (LowerSituation == ' '){
				e->previous = LowerIndex;
				e->index  = LowerIndex + Width*2 +1;
				e->h = (abs(car.X_Current - car.X_Gole) + abs(car.Y_Current+20 - car.Y_Gole));
				posseble = true;
			}
		break;
		case 'R':// right
			if( FrontSituation == ' ' || FrontSituation == '_' ){
				e->previous = LowerIndex;
				e->index  = FrontIndex + 1;
				e->h = (abs(car.X_Current+20 - car.X_Gole) + abs(car.Y_Current - car.Y_Gole));
				posseble = true;
			}
		break;
		default:
		return;
		break;
	}
	if(posseble){
		// int x=Open->length+1;
		// while(--x > 0 && Open->edges[x]->index != e->previous);

		// if(x == 0){
			int x=Close->length+1;
			while(--x > 0 && Close->edges[x]->index != e->previous);
			e->g = Close->edges[x]->g + 20 ;
		// }
		// else
			// e->g = Open->edges[x]->g + 20 ;
		add_on_list(e);
	}
}
bool Go(){	
	/* 		What is Go Do !
	 *
	 * go to the plase that we get it from the open lest

		1) now the perant of the node that i'm going to it

		2)X now let us go to acsess it 
			less my ancestor and compar it  with his parent 
			if it's Doun
			if it's not backe another step from my ancestor
			and see agane 
			unliss i found it
			
			ex:
			My parent S -> a -> d -> g -> q -> u -> r -> o
			It's parent d -> m
			i'm in junction with it in the (d) point

		3)X  backtrack the bathe for the node 
				m <- (d) <- g <- q <- u <- r <- o

		(do a move)backe to my parent 
		if i'm in the node done
		else
		search on my children if it's one of them go to that node
	 */
	// char msg[80];
 	// sprintf(msg, " %hu ", Open->edges[Open->length]->index);
 // 	outtextxy(rand()%10*50, 10, msg);
	// delay(1000);
	// outtextxy(rand()%200*2, 10, "!");

	short Index;// move to the index

	if(LowerIndex == Open->edges[Open->length]->previous){
		Index =  Open->edges[Open->length]->index;
		IdontKnow(Index, OldeStepColor);
		return true;
		// add on the close lest
		// remove from the open lest;
	}
	else{// back  steps "my parent"
		if(get_my_ancestry(LowerIndex, Close, Open->edges[Open->length]->previous)){
			Index =  Open->edges[Open->length]->index;
			IdontKnow(Index, OldeStepColor);
		return true;
		}
	}
	return false;
}
void CheckingMovements(){
	setcolor(BLACK);
	if(car.Position == 'R'){
		CheckSituation('U');
		CheckSituation('D');
		CheckSituation('R');
		// car.Position = 'L';
	}
	else if(car.Position == 'U'){

		CheckSituation('L');
		CheckSituation('R');
		CheckSituation('U');
		// car.Position = 'D';
	}
	else if(car.Position == 'L'){

		CheckSituation('D');
		CheckSituation('U');
		CheckSituation('L');
		// car.Position = 'R';
	}
	else if(car.Position == 'D'){

		CheckSituation('L');
		CheckSituation('R');
		CheckSituation('D');
		// car.Position = 'U';
	}
	// else
}





