#define MAZEPATH "../Maze.txt"
#define MazeBackgroundColor WHITE //******************//
#define MazeColor 0 //******************//
#define GoleColor 4 //******************//
#define StepDelay 10
#define NewStepDelay 100
#define OldeStepColor LIGHTMAGENTA
#define CheckingColor LIGHTBLUE
#define bascktrackColor CYAN

#define FrontIndex (((car.X_Current-10)/20*2)+2)\
	 + ((car.Y_Current-10)/20)*Width*2 + ((car.Y_Current-10)/20)-1
#define FrontSituation MatrixMaze[FrontIndex]

#define LowerIndex (((car.X_Current-10)/20*2)+1)\
	 + ((car.Y_Current-10)/20)*Width*2+ ((car.Y_Current-10)/20)-1
#define LowerSituation MatrixMaze[LowerIndex]

#define UpperIndex (((car.X_Current-10)/20*2)+1)\
	 + ((car.Y_Current-10)/20)*Width*2+ ((car.Y_Current-10)/20)-1 -Width*2 -1
#define UpperSituation MatrixMaze[UpperIndex]

#define LeftIndex (((car.X_Current-10)/20*2))\
	 + ((car.Y_Current-10)/20)*Width*2 + ((car.Y_Current-10)/20)-1
#define LeftSituation  MatrixMaze[LeftIndex]

int Counter_Steps =0;

typedef struct{
	unsigned short X_Start,Y_Start;
	unsigned short X_Current,Y_Current;
	unsigned short X_Gole,Y_Gole;
	unsigned short g;
	char Position;
}Car_Contaner_data;

Car_Contaner_data car;

/*
 * Width and Heigt of caracters in the maze that's saved in the matrecs MatrixMaze
 * MAX The maximom caracter in the Maze thats instde the MatrixMaze
 * ****---- MAX = ((Width + 1) * 2 ) * Heigt ----**** 
 * MatrixMaze contane all the Maze  
 */
unsigned short Width,Heigt;
unsigned int MAX;
char *MatrixMaze; // MatrixMaze[MAX]
bool Go();
void DrowCar(){Counter_Steps++;

 	setcolor(BROWN);
	bar(car.X_Current+3, car.Y_Current+3, car.X_Current+17,  car.Y_Current+17);
	setcolor(LIGHTMAGENTA);

	if(car.Position == 'U'){ //move upward

		// Upper Lines
		line(car.X_Current+9,car.Y_Current+6,car.X_Current+10,car.Y_Current+6);
		line(car.X_Current+8,car.Y_Current+8,car.X_Current+11,car.Y_Current+8);

		// Left and right Lines
		line(car.X_Current+5,car.Y_Current+12,car.X_Current+5,car.Y_Current+14);
		line(car.X_Current+7,car.Y_Current+11,car.X_Current+7,car.Y_Current+15);

		line(car.X_Current+15,car.Y_Current+12,car.X_Current+15,car.Y_Current+14);
		line(car.X_Current+13,car.Y_Current+11,car.X_Current+13,car.Y_Current+15);


		// The Box
		setcolor(LIGHTRED);
		bar(car.X_Current+9,car.Y_Current+10,car.X_Current+11,car.Y_Current+16);
	}
	else if(car.Position == 'D'){//move downward

		// Down Lines
		line(car.X_Current+9,car.Y_Current+15,car.X_Current+10,car.Y_Current+15);
		line(car.X_Current+8,car.Y_Current+13,car.X_Current+11,car.Y_Current+13);

		// Left and right Lines
		line(car.X_Current+5,car.Y_Current+8,car.X_Current+5,car.Y_Current+10);
		line(car.X_Current+7,car.Y_Current+7,car.X_Current+7,car.Y_Current+11);

		line(car.X_Current+15,car.Y_Current+8,car.X_Current+15,car.Y_Current+10);
		line(car.X_Current+13,car.Y_Current+7,car.X_Current+13,car.Y_Current+11);

		// The Box
		setcolor(LIGHTRED);
		bar(car.X_Current+9,car.Y_Current+6,car.X_Current+11,car.Y_Current+10);
	}
	else if(car.Position == 'R'){ //move right

		// Up and Down Lines
		line(car.X_Current+8,car.Y_Current+5,car.X_Current+9,car.Y_Current+5);
		line(car.X_Current+7,car.Y_Current+7,car.X_Current+10,car.Y_Current+7);

		line(car.X_Current+8,car.Y_Current+16,car.X_Current+9,car.Y_Current+16);
		line(car.X_Current+7,car.Y_Current+14,car.X_Current+10,car.Y_Current+14);

		// Right Lines
		line(car.X_Current+15,car.Y_Current+10,car.X_Current+15,car.Y_Current+11);
		line(car.X_Current+13,car.Y_Current+9,car.X_Current+13,car.Y_Current+12);

		// The Box
		setcolor(LIGHTRED);
		bar(car.X_Current+5,car.Y_Current+9,car.X_Current+11,car.Y_Current+12);

		// // clearn a picsl

	 // 	setcolor(BLACK);
		// bar(car.X_Current, car.Y_Current+3, car.X_Current+1,  car.Y_Current+17);
	}
	else if(car.Position == 'L'){ //move left

		// Up and Down Lines
		line(car.X_Current+12,car.Y_Current+5,car.X_Current+13,car.Y_Current+5);
		line(car.X_Current+11,car.Y_Current+7,car.X_Current+14,car.Y_Current+7);

		line(car.X_Current+12,car.Y_Current+16,car.X_Current+13,car.Y_Current+16);
		line(car.X_Current+11,car.Y_Current+14,car.X_Current+14,car.Y_Current+14);

		// Right Lines
		line(car.X_Current+5,car.Y_Current+10,car.X_Current+5,car.Y_Current+11);
		line(car.X_Current+7,car.Y_Current+9,car.X_Current+7,car.Y_Current+12);

		// The Box
		setcolor(LIGHTRED);
		bar(car.X_Current+9,car.Y_Current+9,car.X_Current+15,car.Y_Current+12);
	}	
}

void init(void){
	setbkcolor (0);
	// setcolor (DARKGRAY);
	// bar(0,0,getmaxx()-6,getmaxy()-6);

	unsigned short x,y,i;
	setcolor (MazeBackgroundColor);
	bar(23, 23, 617, 457);


	x=y=10;
	setcolor (MazeColor);

	for(x=30;x<620;x+=20)// circle in the center of evere + 
		for(y=30;y<460;y+=20){
			circle(x,y,2);
			floodfill(x,y,RED);
		}

	x=10;y=30;
	i=0;

	while(MatrixMaze[i++] != 10);// clearn the ferst line from the maze
	MatrixMaze[i] = ' ';
	bool count = false; // to Know if it's a ferst or secand step
	for(; i<MAX ;i++){

		if(MatrixMaze[i] == '_'){
			//mark the Down
			bar(x, y+18, x+20, y+22);
			x+=(count)?20:0;
			count=!count;
		}
		else if(MatrixMaze[i] == '!'){
			//mark the Front
			bar(x+18, y, x+22, y+20);
			x+=(count)?20:0;
			count=!count;
		}
		else if(MatrixMaze[i] == 10){
			MatrixMaze[i+1] = ' ';
			//New Line
			// i+=2;
			x=10;
			y+=20;
			count= false;
		}
		else if(MatrixMaze[i] == ' '){
			//clear the mark if it's not the ferst time
			x+=(count)?20:0;
			count=!count;
		}
		else if(MatrixMaze[i] == 'G'){
			MatrixMaze[i]=' ';
			count=true;
			// to know ware the car is posted in ! 
			car.Y_Gole =  y;
			car.X_Gole =  x;
			
			setcolor (GoleColor);
			bar(x+3, y+3, x+17,  y+17);
			setcolor (MazeColor);
		}
		else if(MatrixMaze[i] == 'S'){
			MatrixMaze[i]=' ';
			count=true;
			setcolor (GoleColor);
			bar(x+3, y+3, x+17,  y+17);
			// to know ware the car is posted in ! 
			car.Y_Current = car.Y_Start = y;
			car.X_Current = car.X_Start= x;
			car.Position = 'R';
			DrowCar();

			setcolor (MazeColor);
		}
		else{
			// done
		}
	}    
}
void ScanTheMaze(void){

	FILE *fp;
	char new = NULL;
	int i=0;

	fp = fopen(MAZEPATH, "r");
	fscanf(fp,"%hu 	%hu ", &Width, &Heigt);
	MAX  = (Width+1)*2*Heigt;
	MatrixMaze = calloc(MAX, sizeof(char));
	while(fscanf(fp,"%c",&new) != EOF)
			MatrixMaze[i++]=new;
	
	fclose(fp);

	/*		//			Print The Maze
    printf("The Width = %d, Heigt =  %d and The Matrix size = %d",Width,Heigt,MAX);
	printf("%s\n", MatrixMaze );
	*/
}


void IdontKnow(unsigned short Index, short Color){
	char check;
	if(FrontIndex+1 == Index)// im in the shosmo
		check = 'R';
	
	else if(LeftIndex-1 == Index)
		check = 'L';
	
	else if(UpperIndex == Index)
		check = 'U';
	
	else if(LowerIndex + Width*2 +1 == Index)
		check = 'D';	
	
	setcolor(MazeBackgroundColor);
	bar(car.X_Current+3, car.Y_Current+3, car.X_Current+17, car.Y_Current+17);
	setcolor(Color);
	switch(check){
		case 'U':// upward 
			if (UpperSituation == ' '){
				bar(car.X_Current+5, car.Y_Current+5, car.X_Current+15,  car.Y_Current+15);
				car.Y_Current -= 20;
				car.Position = 'U';
			}
		break;
		case 'L':// left
			if( LeftSituation == ' ' || LeftSituation == '_' ){
				bar(car.X_Current+5, car.Y_Current+5, car.X_Current+15,  car.Y_Current+15);
				car.X_Current -= 20;
				car.Position = 'L';
				
			}
		break;
		case 'D':// downward
			if (LowerSituation == ' '){
				bar(car.X_Current+5, car.Y_Current+5, car.X_Current+15,  car.Y_Current+15);
				car.Y_Current += 20;
				car.Position = 'D';
			}
		break;
		case 'R':// right
			if( FrontSituation == ' ' || FrontSituation == '_' ){
				bar(car.X_Current+5, car.Y_Current+5, car.X_Current+15,  car.Y_Current+15);
				car.X_Current += 20;
				car.Position = 'R';
			}
		break;
	}
}
void DrawCheckedNode(unsigned short Index){
	char check;
	if(FrontIndex+1 == Index)// im in the shosmo
		check = 'R';
	
	else if(LeftIndex-1 == Index)
		check = 'L';
	
	else if(UpperIndex == Index)
		check = 'U';
	
	else if(LowerIndex + Width*2 +1 == Index)
		check = 'D';	
		delay(10);	
	
 	setcolor(CheckingColor);
	switch(check){
		case 'U':// upward 
			if (UpperSituation == ' '){
				bar(car.X_Current+5, car.Y_Current+5 -20, car.X_Current+15,  car.Y_Current+15 -20);
				setcolor(MazeBackgroundColor);
				bar(car.X_Current+7, car.Y_Current+7 -20, car.X_Current+13,  car.Y_Current+13 -20);
			}
		break;
		case 'L':// left
			if( LeftSituation == ' ' || LeftSituation == '_' ){
				bar(car.X_Current+5 -20, car.Y_Current+5, car.X_Current+15 -20,  car.Y_Current+15);
				setcolor(MazeBackgroundColor);
				bar(car.X_Current+7 -20, car.Y_Current+7, car.X_Current+13  -20,  car.Y_Current+13);
			}
		break;
		case 'D':// downward
			if (LowerSituation == ' '){
				bar(car.X_Current+5, car.Y_Current+5 +20, car.X_Current+15,  car.Y_Current+15 +20);
				setcolor(MazeBackgroundColor);
				bar(car.X_Current+7, car.Y_Current+7 +20, car.X_Current+13,  car.Y_Current+13 +20);

			}
		break;
		case 'R':// right
			if( FrontSituation == ' ' || FrontSituation == '_' ){
				bar(car.X_Current+5 +20, car.Y_Current+5, car.X_Current+15 +20,  car.Y_Current+15);
				setcolor(MazeBackgroundColor);
				bar(car.X_Current+7 +20, car.Y_Current+7, car.X_Current+13  +20,  car.Y_Current+13);
			}
		break;
	}
		delay(10);	

}
