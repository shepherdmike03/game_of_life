#include <stdio.h>
#include <stdlib.h>



                                       /***********************************************************************/
                                       /*                          Code Description                           */
                                       /*                                                                     */
                                       /*    This Program is a "Game Of Life" code which does the following:  */
                                       /*          Takes the starting coordinates from 'input.txt'.           */
                                       /*              Takes the parameters from the terminal.                */
                                       /*                  Rows - Columns - Iterations.                       */
                                       /*                      Prints the game by it's rules in 'output.txt'  */
                                       /*                                                                     */
                                       /*   Code created by: Pasztor Miklos || pmkm0005 || LAB_6 || Ansi C    */
                                       /***********************************************************************/








struct koordinata_rendszer
        {

    int sor;
    int oszlop;

        };


int compareCoordinates(const void *a, const void *b) {
    const struct koordinata_rendszer *coordA = (const struct koordinata_rendszer*)a;
    const struct koordinata_rendszer *coordB = (const struct koordinata_rendszer*)b;

                        /*Compare Rows*/
    if (coordA->sor != coordB->sor)
    {
        return coordA->sor - coordB->sor;
    }

                    /*Compare Columns*/
    return coordA->oszlop - coordB->oszlop;
}










int neighbour_counter(int j,int y,int rows,int columns,int matrix[rows][columns]){
    int count =0;
    if(matrix[j][y+1] == 1)  /*jobb szomszed*/
    {
        count++;
    }
    if(matrix[j][y-1] == 1)  /*bal szomszed*/
    {
        count++;
    }

    if(matrix[j-1][y] == 1) /*felso szomszed*/
    {
        count++;
    }
    if(matrix[j-1][y-1] == 1) /*felso bal sarok*/
    {                                                                                   /***********/
        count++;                                                                        /*  0 0 0  */
    }                                                                                   /*  0 x 0  */
    if(matrix[j-1][y+1] == 1) /*felso jobb sarok*/                                      /*  0 0 0  */
    {                                                                                   /***********/
        count++;
    }
    if(matrix[j+1][y] == 1) /*also szomszed*/
    {
        count++;
    }
    if(matrix[j+1][y-1] == 1) /*also bal sarok*/
    {
        count++;
    }
    if(matrix[j+1][y+1] == 1) /*also jobb sarok*/
    {
        count++;
    }

    return count;
}





int should_live(int j, int y,int rows,int columns,int matrix[rows][columns]){
    int is_alive =0;

    int neighbour_count = neighbour_counter(j,y,rows,columns,matrix);
    if((int) matrix[j][y] == 1)
    {
        is_alive=1;
    }
    else
    {
        is_alive=0;
    }

    if(is_alive==1 && neighbour_count < 2)                  /*elszigetelodes */
    {
        return 0;
    }
    else if(is_alive==1 && (neighbour_count == 2 || neighbour_count == 3))              /*live*/
    {
        return 1;
    }
    else if(is_alive==1 && neighbour_count > 3)                               /*Tulnepesedes*/
    {
        return 0;
    }
    else if(is_alive==0 && neighbour_count ==3)                                 /*Szuletes*/
    {
        return 1;
    }
    else if(neighbour_count==0 || neighbour_count < 0)
    {
        return 0;
    }
}










int main(int arguments, char *arg[]) {

    if(arguments != 4)
    {
        printf("Usage: \nrows \ncolumns \niteration\n\nRESTART THE PROGRAM!");
        exit(0);
    }
    else
    {
        int rows = atoi(arg[1]);
        int columns = atoi(arg[2]);
        int iterations = atoi(arg[3]);
        printf("\n*********************************************************************************************\n");
        printf("The simulation will start with the following"
               " stats:\nRows:        | %d\nColumns:     | %d\nIterations:  | %d", rows, columns, iterations);
    }

    printf("\n*********************************************************************************************\n");

    FILE *inputfile;
    inputfile=fopen("input.txt","r");
    if(inputfile==NULL)
    {
        printf("ERROR: There is no 'input.txt' on the directory");
        FILE *outputfile;
        outputfile= fopen("output.txt","w");
        fprintf(outputfile,"hiba");
        exit(0);
    }

    /************ checking if file is empty ******************/

    fseek(inputfile,0,SEEK_END);
    long file_size = ftell(inputfile);
    if(file_size==0)
    {
        printf("ERROR: The 'input.txt' file is empty, please put some coordinates in it, save it, and restart the program!");
        FILE *outputfile;
        outputfile= fopen("output.txt","w");
        fprintf(outputfile,"hiba");
        exit(0);
    }
    fclose(inputfile);


                                                                    /*   Reopening the file because it aint working without it   */
    inputfile=fopen("input.txt","r");

    /**************************************/
    /*      Vector from our struct        */
    /**************************************/

    int max_hossz =100000;
    int num =0;
    int rows = atoi(arg[1]);
    int columns = atoi(arg[2]);
    int iteration = atoi(arg[3]);
    struct koordinata_rendszer koordinata[max_hossz];
    while (fscanf(inputfile, "%d %d", &koordinata[num].sor, &koordinata[num].oszlop) ==2)
    {
        num++;
    }

                                                        /*   Sorting the coordinates by rows than columns  */
                    qsort(koordinata, num, sizeof(struct koordinata_rendszer), compareCoordinates);

    printf("\n\ncoordinates from input.txt:\n*******\n");
    for(int i=0;i<num;i++)
    {
        printf("* %d %d *\n",koordinata[i].sor,koordinata[i].oszlop);
    }
    printf("*******");


    /*   Printing the first iteration in the terminal!   */
    char teli =219;
    char ures =' ';
    int core=0;

    FILE *outputfile;
    outputfile= fopen("output.txt","w");

    if(iteration!=0)
    {
           /*   Create a matrix which stores "1" for live cells and stores 0 for dead ones     */
           int matrix[rows][columns];



         printf("\n\n");
         printf("1 Iteracio:");
         printf("\n\n");

         fprintf(outputfile,"\n\n");
         fprintf(outputfile,"1 Iteracio:");
         fprintf(outputfile,"\n\n");


        for(int i = 0 ; i < rows ; i++ )
        {
            for(int j = 0 ; j < columns ; j++)
            {
              if(i == koordinata[core].sor && j == koordinata[core].oszlop)
                 {
                   core++;
                   printf("%c",teli);
                   fprintf(outputfile,"%c",teli);
                   matrix[i][j]=1;
                 }
              else
              {
                  printf("%c",ures);
                  fprintf(outputfile,"%c",ures);
                  matrix[i][j]=0;
              }
            }
         printf("\n");
         fprintf(outputfile,"\n");
        }


      /*Printing every single iteration*/

      int upgrade_matrix[rows][columns];

        for(int i=1;i<iteration;i++)
        {
            int checker=0;
            printf("\n\n %d Iteration: \n\n",i+1);
            fprintf(outputfile,"\n\n %d Iteration: \n\n",i+1);
            for(int j=0;j<rows;j++)
            {
                for(int y=0;y<columns;y++)
                {
                   int print = should_live(j,y,rows,columns,matrix);
                   if(print==1)
                   {
                       printf("%c",teli);
                       fprintf(outputfile,"%c",teli);
                       upgrade_matrix[j][y]=1;
                       checker++;
                   }
                   else if(print==0)
                   {
                       printf("%c",ures);
                       fprintf(outputfile,"%c",ures);
                       upgrade_matrix[j][y]=0;
                   }
                }
                printf("\n");
                fprintf(outputfile,"\n");
            }


                                /*upgrading our matrix*/
            if(checker!=0)
            {
                int ismetles=0;
                for(int q=0;q<rows;q++)
                {
                    for(int w=0;w<columns;w++)
                    {
                        if(matrix[q][w] != upgrade_matrix[q][w])
                        {
                            matrix[q][w] = upgrade_matrix[q][w];
                            ismetles++;
                        }
                        else
                        {
                            matrix[q][w] = upgrade_matrix[q][w];
                        }    
                    }
                }
                        if(ismetles==0)
                        {
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\nERROR: THE PROGRAM REACHED IT'S LIMIT!\nGAME OVER!");
                            exit(0);
                        }
            }
            else if(checker==0)
            {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\nERROR: ALL LIFE IS DEAD\nGAME OVER!");
                exit(0);
            }
        }


    }
    else
    {
        printf("\n\n\n\nIteration can't be 0!\n\n\nRESTART THE PROGRAM!\n\n\n\n");
        exit(0);
    }
    return 0;
}
