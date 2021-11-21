#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct equa//This structure saves the numbers in the equation, result and the numbers that represent operaters.
{
	int number1, number2, result, operater;
};
struct answer//This structure saves the imput answers of the user.
{
	int num;
};
char userid(char *);//This function tests user's ID validation. 
void MathP(char [],FILE *f);//This function is used to produce questions. 
int note3(equa []);//This function makes sure the random numbers are valid.
int compare(equa [], answer[]);//This function gives user his/her score.
void save(char [],int,int,FILE *);//This function is for saving data.
void load(FILE *, char *);//This function is for loading previous data. 

int main()
{
	char *ID;
	FILE *f;
	int choose;
	 
	printf("Please input your ID no:");
	gets(ID);//Get the input ID.

	while (userid(ID) == 1)
	{
		printf("Error\nPlease enter your ID in the correct form.\nExample:AB1234\n");
		printf("Please input your ID no:");
		gets(ID);//If the imput ID is in the wrong from, let the user try again.
	} 

    printf("(1) Start a test\n(2) Check scores\n(3) Exit\nExample: If you want to start a test, please enter 1.\n");//User can now choose what they want to do.
    scanf("%d", &choose);
    while(choose == 1|| choose ==2|| choose ==3)
    {
    	if (choose == 2)
        {
		    load(f,ID);
            printf("(1) Start a test\n(2) Check scores\n(3) Exit\nExample: If you want to start a test, please enter 1.\n");//User can now choose what they want to do.
            scanf("%d", &choose);
		}
    	 if (choose == 3)
        {
    	exit(0);

        }
        if (choose == 1)//Using "while" in order to let the program end only when choose equals to 3.
        {
  	    	MathP(ID,f);
  	        printf("(1) Start a test\n(2) Check scores\n(3) Exit\nExample: If you want to start a test, please enter 1.\n");//User can now choose what they want to do.
            scanf("%d", &choose);
        }
   }
    
    if(choose >3 && choose <1)
        printf("Error, please enter a valid number between 1 to 3.\n");
	return 0;
}

char userid(char *ID)//The function that determines is the input ID in the correct form. 
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 6; i++)//ID has 6 characters in total.
    {
        if(i == 0 || i == 1)//Testing is the first two letters of ID capital letters.
        {
            if(*(ID+i) >= 'A' && *(ID+i) <= 'Z')
                continue;
            else
            {
                j = 1;
                break;
            }
        }
        else
        {
            if(*(ID+i) >= '0' && *(ID+i)<= '9')//Testing is the rest four letters of ID numbers.
                continue;
            else
            {
                j = 1;
                break;
            }
        }

    }
    if(j == 1)//If the ID isn't the form we required, return 1
    {
        return 1;
    }
    else//If the ID is correct, return 0 
    {
        return 0;;
    }
}

void MathP(char ID[],FILE *f)
{
	clock_t start, end;
    struct equa problems[10];
    struct answer inputA[10];
	int i;
	int timeused;
	int opr[4];
	int finalscore = 0;
	
	for(i=0;i++;i<4)
        opr[i] = 1;

    srand((unsigned int)time(NULL));
    

    problems[0].operater = rand()%4; 
    opr[problems[0].operater] = 0;
    for (i=1;i<8;i++)//Make sure that the adjacent questions have different operations. 
    {
    	problems[i].operater = rand()%4;
    	while (problems[i].operater == problems[i-1].operater)
    	    problems[i].operater = rand()%4;
    	opr[problems[i].operater] = 0;//When opr[i] = 0, we have the ith operater in the random math problems.
    }
    if (opr[0]||opr[1] == 1)//The following program makes sure that all four kinds of operaters exist. 
        problems[8].operater = rand()%2;
    else if (opr[2]||opr[3] == 1)
       	problems[8].operater = (rand()%2+2);
   	else if (opr[0]||opr[2] == 1)
    	problems[8].operater = (rand()%2)*2;
   	else if (opr[1]||opr[3] == 1)
   		problems[8].operater = ((rand()%2)*2)+1;
   	else if (opr[0]||opr[3] == 1)
   		problems[8].operater = (rand()%2)*3;
   	else if (opr[1]||opr[2] == 1)
   		problems[8].operater = (rand()%2)+1;
    else
    {
        problems[8].operater = rand()%4;
	    while(problems[7].operater == problems[8].operater)
    	     problems[8].operater = rand()%4;
     }
    if (opr[0] == 1)
        problems[9].operater = 0;
    else if (opr[1] == 1)
        problems[9].operater = 1;
    else if (opr[2] == 1)
        problems[9].operater = 2;
    else if (opr[3] == 1)
        problems[9].operater = 3;
    else 
    {
	    problems[9].operater = rand()%4;
    	while(problems[9].operater == problems[8].operater)
    	     problems[9].operater = rand()%4;
    }
               
    for(i=0;i<10;i++)
    {
    	problems[i].number1 = (rand()%99+1);
		problems[i].number2 = (rand()%99+1);//In this way can number one and number two be random numbers that are less than 100 and greater than 0.
		while(note3(&problems[i])==1)//If the numbers doesn't meet the standard of note 3, choose another number randomly.
		{
		    problems[i].number1 = (rand()%99+1);
		    problems[i].number2 = (rand()%99+1);
		} 
    }

    start = clock();//Record the time used.
    for (i=0;i<10;i++)
    {
    	printf("%d", problems[i].number1);
    	
    	if (problems[i].operater == 0)
    	    printf("+");
	    else if (problems[i].operater == 1)
	        printf("-");
        else if (problems[i].operater == 2)
            printf("*");
        else 
            printf("/");
        printf("%d = ", problems[i].number2);
        scanf("%d", &inputA[i].num);
        
    }
    end = clock();
    timeused = (int)(end-start)/CLOCKS_PER_SEC;        
	printf("Your score is:%d\n", compare(problems,inputA));
	printf("Time used:%d\n", timeused);
    printf("Ques. | Correct Answ. | Ur Answ\n");
        for (i=0;i<10;i++)
    {
    	printf("%d", problems[i].number1);
    	
    	if (problems[i].operater == 0)
    	    printf("+");
	    else if (problems[i].operater == 1)
	        printf("-");
       else if (problems[i].operater == 2)
            printf("*");
        else 
            printf("/");
        printf("%d = ", problems[i].number2);
        printf(".| %d .| %d\n", problems[i].result,inputA[i].num);
    }
    save(ID, compare(problems,inputA), timeused,f);//Save the data we need in file.
    
}

int note3(equa problems[])//By using this function, we can get the result of each equation and also make sure that the result is below 100.
{
	int i;
	for (i=0;i<10;i++)//First, calculate the result and then make sure the result the smaller than 100.
	{
		if(problems[i].operater == 0)
		{
			problems[i].result = problems[i].number1 + problems[i].number2;
			if(problems[i].result<100)
			{
	            return 0; 
				break; 
			}           
			else 
            {
            	return 1;
                break;
            }  
		}
		
		else if(problems[i].operater == 1)
		{
			problems[i].result = problems[i].number1 - problems[i].number2;
			if(problems[i].result<100 && problems[i].result>=0)
			{  
			    return 0;            
			    break;
				
			}  
			else 
            {
            	return 1;
                break;
            }  
		} 
		
		else if(problems[i].operater == 2)
		{
			problems[i].result = problems[i].number1 * problems[i].number2;
			if(problems[i].result<100 && problems[i].result>0)
			{
			    return 0;
			    break;	
			}  
            else 
            {
          	    return 1;
                break;
            }   
		}
		
		else
		{
			problems[i].result = problems[i].number1 / problems[i].number2;
			if(problems[i].result<100 && problems[i].result>0 && problems[i].number1%problems[i].number2 == 0)
			{
				return 0;
			    break;
			}  
            else 
            {
          	    return 1;
                break;
            }   
		}
	}
}

int compare(equa problems[], answer result[])//Compare the correct answer and the answer user input.
{
	int i;
	int score = 0;
	for (i=0;i<10;i++)
	{
		if (problems[i].result == result[i].num)
		    score = score + 10;
        else
            score = score;
	}
	return score;
}

void save(char ID[],int score,int timeused,FILE *f)//Add the new data to the file.
{
    if((f=fopen("record.txt","a"))==NULL)
    {
        if((f=fopen("record.txt","w"))==NULL)
        {
            printf("Error, failed to open the file.\n");
            exit(0);
        }
    }
        fprintf(f,"%s %d %d",ID,score,timeused);
        fclose(f);
}

void load(FILE *f, char *id)
{    
    char ID[7];
    int score,i,j;
    int timeused;
    j = 0;
    if((f=fopen("record.txt","r"))==NULL)
    {
        printf("Error, failed to open the file.\n");
        exit(0);
    }

    printf("Your previous records are:\n");
    while(fscanf(f,"%s %d %d",ID,&score,&timeused) != EOF)
    {
    	j = 0;
        for(i=0;i<6;i++)//This is for judging whether user's ID can match with previous saved data.
		    if(*(id+i) != ID[i])
			    j = 1;
		if (j == 0) 
            printf("%s %d %dseconds\n",ID,score,timeused);//Print the saved data.
    }
    
    fclose(f);
}
