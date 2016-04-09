/*
void add_on_list( edge *NewEdge);
edge *get_closelist();

edge *get_openlist();*/

#define F(n)  n->g


typedef struct {
	unsigned short previous; // edge, that's Parent to me; I came from it
	unsigned short g; // the g(n)  the cost of the path from the start node to n 
	unsigned short h; // the h(n)  heuristic that estimates the cost of the cheapest path from n to the goal
	unsigned short index; // it's name
} edge;


typedef struct {
	edge **edges;
	unsigned short length;
	unsigned short size;
} graph;


graph *Open;
graph *Close;


void PrintList(graph *list,char *name){

	FILE *fp;
	char new = NULL;
	int i=1,j=0;

	fp = fopen(name, "w");

	fprintf(fp,"Size %hu, length %hu \n", list->size, list->length);
	while(i <= list->length){
		fprintf(fp,"\n%d- previous %4hu, index %4hu, h %hu ,f(n) %hu\n ",
			i,
			list->edges[i]->previous, 
			list->edges[i]->index, 
			list->edges[i]->g, 
			list->edges[i]->g);
		i++;
		fprintf(fp,"\n-----------------------------------------------------");
	}

	fclose(fp);
}
void swap_edge_betwen_lests(){
	if( Close->length +1 >= Close->size ){
		Close->size = Close->size ? Close->size * 2 :32;
		Close->edges = realloc(Close->edges, Close->size * sizeof(edge));
	}
	Close->edges[++Close->length] = Open->edges[Open->length];
	--Open->length;
}

void add_on_list( edge *NewEdge){



	// outtextxy ( rand()%200*2, 10  ,"?" );
	// delay(1000);
	int x,y;
	/* No I'm Not Going To Doit X_X I have Myn way V_V
	 * if the noew nod is beter then the exesting node  thin i will 
	 * delet it from the open list and pot it in the close lest 
	 * and i will delet all the node that is connected with it from the open lest 
	*/
	// chek if the New Edge exest or not
	x=Open->length;
	while(--x > 0 && Open->edges[x]->index != NewEdge->index);
	if( x > 0 ){// the New Edge is olrade exest in the Open list

		// if the new edge better then the olde one
		if(NewEdge->g < Open->edges[x]->g){
			// outtextxy ( 20, 10  ,"Open!!" );
			//for(y=Open->length; y > 0 && Open->edges[y]->index != Open->edges[x]->previous; y--);


			Open->edges[x]->previous = NewEdge->previous;
			Open->edges[x]->g = NewEdge->g;

			// change the ather g(n)
			// MeshArsfShosnmo(list,Open->edges[x]);
			// sort

		}
		else// the new edge isn't better 
			return;
	
	}

	else{

	x=Close->length;
	while(--x > 0 && Close->edges[x]->index != NewEdge->index);
	if(x > 0 ){// Chek if The New Edge Better Then The one That is exest in The Close Lest
		return;// Error
		// if the new edge better then the olde one
		if(NewEdge->g < Open->edges[x]->g){

			outtextxy ( 50, 10  ,"Close !!" );
			return;
		}
		else// the new edge isn't better 
			return;
	}

	else // it's a new edge
		if( Open->length + 1 >=  Open->size ){
			Open->size = Open->size ? Open->size * 2 : 32 ;
			Open->edges = realloc(Open->edges, Open->size * sizeof(edge));
		}

		Open->edges[++Open->length] = NewEdge;

	DrawCheckedNode(NewEdge->index);



	}
}


bool get_my_ancestry(unsigned short start, graph *list, unsigned short gole){


	unsigned short s,g;
	s = g = list->length;
	for(;s>0 && start != list->edges[s]->index; s--);// get the current start pointer
	for(;g>0 && gole  != list->edges[g]->index; g--);// get the gole pointer
	if(s<0 || g<0)
		return false;
	short size_s = 5,size_g = 5;
	unsigned short *track_s = calloc( size_s, sizeof(unsigned short));
	unsigned short *track_g = calloc( size_g, sizeof(unsigned short));

	track_s[0] = start;
	track_g[0] = gole;
	int count_s=0,count_g=0,i;
	while(true){
		if(count_s +1 >= size_s){
			size_s *=2;
			track_s = realloc(track_s, size_s * sizeof(unsigned short));
		}
		if(count_g +1 >= size_g){
			size_g *=2;
			track_g = realloc(track_g, size_g * sizeof(unsigned short));;
		}

		if(track_s[count_s] !=0 )
			track_s[++count_s] = list->edges[s]->previous;

		if(track_g[count_g] != 0 )
			track_g[++count_g] = list->edges[g]->previous;


		s = g = list->length;/// list->edges[s]->previus != 0 "it's the root :3 " Error maype Solvde :3 
		for(;s>0 && track_s[count_s] != list->edges[s]->index; s--);// track ancestry of start pointer
		for(;g>0 && track_g[count_g] != list->edges[g]->index; g--);// track ancestry of gole pointer
		if(s<0 || g<0)
			return false;
		for(i=count_s;i >=0 && track_g[count_g] != track_s[i];i--);
		if(i>=0)
			break;
		for(i=count_g;i >=0 && track_s[count_s] != track_g[i];i--);
		if(i>=0)
			break;
	}

	if(s<0 || g<0){
		outtextxy ( 50, 10  ,"what !!  it's not in the list ?? how!!" );
		return false;
	}
	else{
		int i,j=-1;
		for(i=count_s;i >=0 && track_g[count_g] != track_s[i];i--);
		if(i>=0){
		// outtextxy ( rand()%10*50, 10  ,"!" );
			short Counter = 0;
			while(Counter <= i){
				IdontKnow(track_s[Counter++], OldeStepColor);
				// DrowCar();
				delay(StepDelay);
			}
			Counter = count_g;
			while(Counter >= 0){
				IdontKnow(track_g[Counter--], OldeStepColor);
				// DrowCar();
				delay(StepDelay);
			}
			return true;
		}
		for(i=count_g;i >=0 && track_s[count_s] != track_g[i];i--);
		if(i>=0){
		// outtextxy ( rand()%10*50, 10  ,"?" );
			short Counter = 1;
			while(Counter <= count_s){
				IdontKnow(track_s[Counter++], OldeStepColor);
				// DrowCar();
				delay(StepDelay);
			}
			Counter = i;
			while(Counter >= 0){
				IdontKnow(track_g[Counter--], OldeStepColor);
				// DrowCar();
				delay(StepDelay);
			}

		return true;
		}
	return false;
 	}
}
void backtrack(){


	char msg[80];
 	sprintf(msg, "Counter Steps = %hu ", Counter_Steps);
	outtextxy ( 420, 10  ,msg );

	short x,LingthPath=0;
	short index = Close->edges[Close->length]->previous;
	while(Close->edges[Close->length]->previous != 0){LingthPath++;
		x = Close->length;
		for(; x > 0 && index != Close->edges[x]->index ; x--);
			if(!x)
				break;
		index = Close->edges[x]->previous;

		IdontKnow(Close->edges[x]->index, bascktrackColor);

		DrowCar();
		delay(StepDelay);
	}

	setcolor(GoleColor);
	bar(car.X_Gole+3, car.Y_Gole+3, car.X_Gole+17, car.Y_Gole+17);
	
	char msg2[80];
 	sprintf(msg2, "shortest path = %hu ",LingthPath);
 	outtextxy(20, 10, msg2);
	
}
