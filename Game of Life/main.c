#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int D=47;//defining grid dimension as global variable. Playable grid has dimensions [D-2][D-2] to allow invisible dead border

void randomgrid(char *grid[D][D]);//generates randomly seeded grid

void pentomino(char *grid[D][D]);//draws grid with R-pentomino at its centre

void gun(char *grid[D][D]);//draws grid with glider gun in top left corner, requires D>38 to function properly

void spaceships(char *grid[D][D]);//draws grid that displays moving spaceships

void drawgrid (char *grid[D][D]);//draws current iteration

void drawgridfile (FILE *file, char *grid[D][D]);//writes grid to text file

int countneighbours (char *grid[D][D], int i,int j);//counts the number of live neighbours around a cell

int main()
{
    int i,j,iterations,counter,liveneighbours,inputcheck;
    char *grid[D][D];//Game grid, including invisible dead border
    char *newgrid[D][D];//temporary grid to store changes to cells while evaluating current grid, to avoid incorrect counts
    char choice;
    char *live = 'o';
    char *dead = '.';

    FILE *output_file;
    output_file = fopen("output.txt", "w");//opens text file to print grid iterations in

    if(output_file == NULL)
    {
        printf("Unable to open file to for output");
        return 1;//closes program if file fails to open
    }

    for(i=0;i<D;i++)//create dead grid to start from
        {
            for(j=0;j<D;j++)
            {
                grid[i][j] = dead;
            }
        }

    printf("%c = dead cell\n%c = live cell", dead, live);
    printf("\n\nYou are playing with a %d by %d grid\n", D-2, D-2);
    printf("Each cell has a reference [i,j] where i is the row number and j is the column number\n");
    printf("Top left cell is [1,1], bottom right is [%d,%d]\n\n", D-2, D-2);


    do
    {
        printf("Enter Y to choose live seeds yourself\nEnter N for initial grid wil no live cells\nEnter R for randomly seeded grid\nEnter P for grid seeded with pentomino\nEnter G for grid seeded with glider gun\nEnter S for grid seeded with spaceships\n");
        scanf(" %c", &choice);//space to avoid trailing \n on second go round
        if(choice!='Y' && choice!='y' && choice!='N' && choice!='n' && choice!='R' && choice!='r' && choice!='P' && choice!='p' && choice!='G' && choice!='g' && choice!='S' && choice!='s')
        {
            printf("\nInvalid input, please try again\n\n");
        }
        fflush(stdin);//clears input buffer so later scanf work
    }while (choice!='Y' && choice!='y' && choice!='N' && choice!='n' && choice!='R' && choice!='r' && choice!='P' && choice!='p' && choice!='G' && choice!='g' && choice!='S' && choice!='s');


    if (choice=='N' || choice=='n')
    {
        printf("\nYou have chosen an initial grid with no live cells\n");
    }
    else if(choice=='Y' || choice=='y')
    {

        while (choice=='Y' || choice=='y')
        {

            do
            {
                printf("\nPlease choose a live cell: i=");
                inputcheck = scanf("%d", &i);//scanf should return integer value 1 if it successfully takes in an integer
                if (inputcheck != 1 || (i<1) || (i>D-2))//checks that an integer was entered, and it is within the allowed range
                {
                    printf("\nInvalid input, please try again\n\n");
                }
                fflush(stdin);
            }while(inputcheck != 1 || (i<1) || (i>D-2));

            do
            {
                printf("j=");
                inputcheck = scanf("%d", &j);
                if (inputcheck != 1 || (j<1) || (j>D-2))//checks that an integer was entered, and it is within the allowed range
                {
                    printf("\nInvalid input, please try again\n\n");
                }
                fflush(stdin);
            }while(inputcheck != 1 || (j<1) || (j>D-2));

        printf("Cell [%d,%d] is live\n", i, j);
        grid[i][j]=live;

        printf("Would you like to choose another live cell? (Y/N):");
        scanf(" %c", &choice);//space to consume newline from previous input, otherwise the scanf function doesn't wait for user input of Y/N

        }
    }
    else if(choice=='R' || choice=='r')
    {
        randomgrid(grid);
    }
    else if(choice=='P' || choice=='p')
    {
        pentomino(grid);
    }
    else if(choice=='G' || choice=='g')
    {
        gun(grid);
    }
    else if(choice=='S' || choice=='s')
    {
        spaceships(grid);
    }

    printf("\nHere is your initial grid:\n");
    drawgrid(grid);
    drawgridfile(output_file, grid);//printing to text file to allow easier observation
    fprintf(output_file, "\n");//so the gap between the initial and 1st iteration grids is the same as that between iterations

    do//iteration performer
    {
        printf("\n\nHow many iterations would you like to perform? (Enter 0 to finish):");
        scanf("%d", &iterations);
        if (iterations !=0)
        {
            for (counter=0;counter<iterations;counter++)
            {
                for (i=1;i<(D-1);i++)
                {
                    for(j=1;j<(D-1);j++)
                    {
                        if (grid[i][j] == dead)//apply rules for dead cells
                        {
                            liveneighbours=countneighbours(grid,i,j);
                            if(liveneighbours==3)//condition to create live cell
                            {
                                newgrid[i][j]=live;
                            }
                            else
                            {
                                newgrid[i][j]=dead;
                            }
                        }
                        else if (grid[i][j] == live)//apply rules for live cells
                        {
                            liveneighbours=countneighbours(grid,i,j)-1;//minus 1 to account for the live cell being evaluated

                            if(liveneighbours != 2 && liveneighbours != 3)//conditions for cell to die
                            {
                                newgrid[i][j]=dead;
                            }
                            else
                            {
                                newgrid[i][j]=live;
                            }
                        }
                    }
                }

            for(i=1;i<D-1;i++)
            {
                for(j=1;j<D-1;j++)
                {
                grid[i][j]=newgrid[i][j];//once current grid has finished counting, put new values in
                }
            }

            //printf("\n\n");
            //drawgrid(grid);
            //printf("\n\n");
            fprintf(output_file, "\n");
            drawgridfile(output_file, grid);
            fprintf(output_file, "\n");
            }
        }
        printf("%d iterations performed\n", iterations);
    }while (iterations != 0);

    fclose(output_file);
    return 0;
}

void randomgrid(char *grid[D][D])
{
    int i,j,randnum;
    char live = 'o';
    char dead = '.';
    int randnumgrid[D][D];
    srand(time(NULL));//seed random number generator with computer time to give different random grid each time

    for(i=1;i<D-1;i++)//populate a grid of random binary numbers
    {
        for(j=1;j<D-1;j++)
        {
            randnum=(rand() % 2);//generates a 'random' binary number
            randnumgrid[i][j]=randnum;
        }
    }

    for(i=1;i<D-1;i++)//create randomly seeded initial grid
    {
        for(j=1;j<D-1;j++)
        {
            if (randnumgrid[i][j] == 0)
            {
                grid[i][j] = dead;
            }
            else if (randnumgrid[i][j] == 1)
            {
                grid[i][j] = live;
            }
        }
    }

}

void pentomino(char *grid[D][D])
{
    int C=D/2;//halves dimension to find middle of grid, keeping only integer part of the calculation
    char live = 'o';
    grid[C][C]=live;
    grid[C][C-1]=live;
    grid[C+1][C]=live;
    grid[C-1][C]=live;
    grid[C-1][C+1]=live;
}

void gun(char *grid[D][D])
{
    char live = 'o';

    grid[6][2]=live;//populating the shapes that make the glider gun
    grid[6][3]=live;
    grid[7][2]=live;
    grid[7][3]=live;

    grid[4][14]=live;
    grid[4][15]=live;
    grid[5][13]=live;
    grid[5][17]=live;
    grid[6][12]=live;
    grid[6][18]=live;
    grid[7][12]=live;
    grid[7][16]=live;
    grid[7][18]=live;
    grid[7][19]=live;
    grid[8][12]=live;
    grid[8][18]=live;
    grid[9][13]=live;
    grid[9][17]=live;
    grid[10][14]=live;
    grid[10][15]=live;

    grid[2][26]=live;
    grid[3][24]=live;
    grid[3][26]=live;
    grid[4][22]=live;
    grid[4][23]=live;
    grid[5][22]=live;
    grid[5][23]=live;
    grid[6][22]=live;
    grid[6][23]=live;
    grid[7][24]=live;
    grid[7][26]=live;
    grid[8][26]=live;

    grid[4][36]=live;
    grid[4][37]=live;
    grid[5][36]=live;
    grid[5][37]=live;
}

void spaceships(char *grid[D][D])
{
    char live = 'o';

    grid[3][4]=live;//lightweight spaceship
    grid[3][5]=live;
    grid[4][2]=live;
    grid[4][3]=live;
    grid[4][5]=live;
    grid[4][6]=live;
    grid[5][2]=live;
    grid[5][3]=live;
    grid[5][4]=live;
    grid[5][5]=live;
    grid[6][3]=live;
    grid[6][4]=live;

    grid[12][5]=live;//middleweight spaceship
    grid[12][6]=live;
    grid[13][2]=live;
    grid[13][3]=live;
    grid[13][4]=live;
    grid[13][6]=live;
    grid[13][7]=live;
    grid[14][2]=live;
    grid[14][3]=live;
    grid[14][4]=live;
    grid[14][5]=live;
    grid[14][6]=live;
    grid[15][3]=live;
    grid[15][4]=live;
    grid[15][5]=live;

    grid[20][6]=live;
    grid[20][7]=live;
    grid[21][2]=live;
    grid[21][3]=live;
    grid[21][4]=live;
    grid[21][5]=live;
    grid[21][7]=live;
    grid[21][8]=live;
    grid[22][2]=live;
    grid[22][3]=live;
    grid[22][4]=live;
    grid[22][5]=live;
    grid[22][6]=live;
    grid[22][7]=live;
    grid[23][3]=live;
    grid[23][4]=live;
    grid[23][5]=live;
    grid[23][6]=live;
}

void drawgrid(char *grid[D][D])//only prints playable cells, leave invisible dead border out
{
    int i,j;
    for(i=1;i<(D-1);i++)
        {
            for(j=1;j<(D-1);j++)
            {
                printf("%c ", grid[i][j]);
            }
            printf("\n");
        }
}

void drawgridfile (FILE *file, char *grid[D][D])
{
    int i,j;
    for(i=1;i<(D-1);i++)
        {
            for(j=1;j<(D-1);j++)
            {
                fprintf(file, "%c ", grid[i][j]);
            }
            fprintf(file, "\n");
        }
}

int countneighbours (char *grid[D][D], int i, int j)
{
    int livecount=0;
    int a,b;
    char live = 'o';

    for(a=(i-1);a<(i+2);a++)
    {
        for(b=(j-1);b<(j+2);b++)
        {
            if(grid[a][b]==live)
            {
                livecount+=1;
            }
        }
    }
    return livecount;
}
