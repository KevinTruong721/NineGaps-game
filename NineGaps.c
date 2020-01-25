#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int result(int a, char x, int b, char y, int c);        // function prototype

int result(int a, char op1, int b, char op2, int c)     // function to calculate row and column results
{
        int results;

        // If the first operator of the equation is "+" then addition is prioritize first
        if (op1 == '+' && op2 == '+') {
                results = (a + b) + c;
        }

        else if (op1 == '+' && op2 == '-') {
                results = (a + b) - c;
        }

        else if (op1 == '+' && op2 == '*') {
                results = (a + b) * c;
        }


        // If the first operator of the equation is "-" then subtraction is prioritize first
        if (op1 == '-' && op2 == '+') {
                results = (a - b) + c;
        }

        else if (op1 == '-' && op2 == '-') {
                results = (a - b) - c;
        }

        else if (op1 == '-' && op2 == '*') {
                results = (a - b) * c;
        }

        // If the first operator of the equation is "*" then multiplication is prioritize first
        if (op1 == '*' && op2 == '+') {
                results = (a * b) + c;
        }

        else if (op1 == '*' && op2 == '-') {
                results = (a * b) - c;
        }

        else if (op1 == '*' && op2 == '*') {
                results = (a * b) * c;
        }    

        return results;   
}


int main() {

    int main_board[9]={1,2,3,4,5,6,7,8,9}; // It defines the main board to store all the values from 1-9
    int missing_array[9]; // This line generates an array of size 9 to keep track of missing values
    int game_board[9]; // It defines an array to form the actual game board with random numbers and hidden values
    int temp_board[9]; // It defines an array which is a copy of the game_board and will be displayed to the user and will be updated in each iteration
    int row_results[3]; // this is an array that stores the results of calculation of each row
    int column_results[3]; // this is an array that stores the results of calculation of each column
    char operators_array[12]; // this is an array that stores random operations
    int i,j; // these variables will be used for loop indexes
    int rand_num,temp1; // rand_num will be used to store the result of random number generations, temp1 will be used as a temporary variable
    int level; // this variable stores the level of difficulty
    char check_game; // this is a flag variable to determine if the user solves the game correctly
    int play_again; // this is a flag variable to determine if the user wants to play again or not
    int missing_count; // this is a variable that keep track of the number of missing values in the game board.
    int counter = 0;

    srand(time(NULL));  // It generates a seed, using current time, for the random generator

    do{
        check_game=1;
        level=0;
        printf("Welcome to Nine-Gaps game!...\n");
	    printf("*****************************\n");
	    printf("      *****************      \n");
	    printf("            *****            \n");
	    printf("              *              \n");
	
        // get the level of difficulty from the user
        do{
		    puts("Choose the level of difficulty (1-Beginner, 2-Intermediate, 3-Advanced, 4-Expert):");
		    scanf("%d",&level);
		    if ((level < 1) || (level > 4))
			    puts("The entered value is not valid");
		    else{
		        switch (level){
		            case 1:
		                puts("You have chosen the Beginner level");
		                break;
		            case 2:
		                puts("You have chosen the Intermediate level");
		                break;
		            case 3:
		                puts("You have chosen the Advanced level");
		                break;
		            case 4:
		                puts("You have chosen the Expert level");
		                break;
		        }
		        break;
		    }
	    } while (1);



	
	for (i = 0; i < 9; i++) {
		rand_num = rand() % 9;  // Generates postion from 0 to 8 to shuffle the board later
		
		temp1 = main_board[i];
		main_board[i] = main_board[rand_num];
		main_board[rand_num] = temp1;

	}

        // Generate random operators (+, -, x)
        for (i = 0; i < 12; i++) {
                operators_array[i] = rand() % 3;

                if (operators_array[i] == 0) {          // 0 will convert the operator array of that specific postion to '+'
                        operators_array[i] = '+'; 
                }

                else if (operators_array[i] == 1) {     // 1 will convert the operator array of that specific postion to '-'
                        operators_array[i] = '-';
                }

                else if (operators_array[i] == 2) {     // 2 will convert the operator array of that specific postion to '*'
                        operators_array[i] = '*';
                }

        }

        // Calculates the results for row
        for (i = 0; i < 3; i++) {
                if (i == 0) {   // calculates results for row 1
                        row_results[i] = result(main_board[0], operators_array[0], main_board[1], operators_array[1], main_board[2]);
                }

                else if (i == 1) {   // calculates results for row 2
                        row_results[i] = result(main_board[3], operators_array[2], main_board[4], operators_array[3], main_board[5]);
                }

                else if (i == 2) {   // calculates results for row 3
                        row_results[i] = result(main_board[6], operators_array[4], main_board[7], operators_array[5], main_board[8]);
                }
        }

        // Calculates the results for column
        for (i = 0; i < 3; i++) {
                if (i == 0) {   // calculates results for column 1
                        column_results[i] = result(main_board[0], operators_array[6], main_board[3], operators_array[9], main_board[6]);
                }

                else if (i == 1) {   // calculates results for column 2
                        column_results[i] = result(main_board[1], operators_array[7], main_board[4], operators_array[10], main_board[7]);
                }

                else if (i == 2) {   // calculates results for column 3
                        column_results[i] = result(main_board[2], operators_array[8], main_board[5], operators_array[11], main_board[8]);
                }
        }

        


	// initializing missing array to 0
	
	for (i = 0; i < 9; i++) {
		missing_array[i] = 0;
	}	
	


	// copy the main_board into game_board
		
	for (i = 0; i < 9; i++) {
		game_board[i] = main_board[i];
	}



	// Based on the selected level, 3 or 5 7 board values will be hidden.

	i = 0; // initializing i to 0

	while (i < level*2+1) {
		int r = rand() % 3;
		int c = rand() % 3;
		if (game_board[3*r+c]!='?') {
			missing_array[game_board[3*r+c]-1] = game_board[3*r+c]; // the hidden values will be added to the set of missing values
			game_board[3*r+c] = '?';
			i++; 
		} // end of if
	} // end of while	


	// Copy the game board into a temporary board

	for (i = 0; i < 9; i++) {
		temp_board[i] = game_board[i];
	}	


	// the inner loop to get values from the user
        do{
        
            // Display the game board after each update
            
            printf("Game Board:\n");
	        printf("---------------------------------------------------\n");
            for (i=0;i<3;i++){
                if (i>0){                   // show the column operators
                    for (j=0;j<3;j++){
                        printf(" %c\t\t", operators_array[3*(i+1)+ j]);
                    }
                    printf("\n");
                }
               
		 for (j=0;j<3;j++){          // show the rows

		    if (game_board[(i*3)+j]!='?')
                        printf(" %d\t ", temp_board[(i*3)+j]);
                    else if (game_board[(i*3)+j]!=temp_board[(i*3)+j]){
                        printf(" %d?\t ", temp_board[(i*3)+j]);
                    }
                    else
                        printf(" ?\t ");
                
                    if (j<2)
                        printf(" %c\t", operators_array[(i*2) + j]);
                    else
                        printf("= %d", row_results[i]);       // show the rows results
                }
                printf("\n");
                if (i==2)
                    printf (" =\t\t =\t\t =\n");    
            }
            for (i=0;i<3;i++)               // show the columnar results
                printf(" %d\t\t", column_results[i]);
            printf("\n---------------------------------------------------\n");





	// Display the missing values and update the missing_count variable

	printf("List of Missing Values=\n");

	missing_count = 0;

	for (i = 0; i < 9; i++) {		
		if (missing_array[i] > 0) {
			missing_count = missing_count + 1;	
			printf("%d\t", missing_array[i]);
		}			

	}	
		// break if the missing values are empty

		if (missing_count == 0) {
			break;
		}	

		
        printf("\n---------------------------------------------------\n");


	// Get user's guess (location and value) and check input's validity
	

	        printf("Enter a row number (1-3), column(1-3), value(One of the missing values):\n");
	        int r, c, v; 
	        scanf("%d %d %d", &r, &c, &v);
	        if (r==0 || c==0 || v==0)
	            break;
	        
	        if (r < 1 || r > 3 || c < 1 || c > 3){
	            puts("Invalid row and/or column numbers. Try again.");
	            continue;
	        }
	        
	        if (v < 1 || v > 9) {
	            puts("Invalid cell value. Try again.");
	            continue;
	        }
	        
	        if (missing_array[v-1]<1) {
	            puts("This value is already there. Try again.");
	            continue;
	        }
         

   
		// 9- if the selected cell is changeable, add the value into the cell and remove it from the missing values, in other case show an error and repeat the inner loop.
		if ((game_board[(r-1)*3 + (c-1)] == '?') && (game_board[(r-1)*3 + (c-1)] == temp_board[(r-1)*3 + (c-1)])) {
			temp_board[(r-1)*3 + (c-1)] = v;
			missing_array[temp_board[(r-1)*3 + (c-1)]-1] = 0;	
		}
		else if ((game_board[(r-1)*3 + (c-1)] == '?') && (game_board[(r-1)*3 + (c-1)] != temp_board[(r-1)*3 + (c-1)])) {
			missing_array[temp_board[(r-1)*3 + (c-1)]-1] = temp_board[(r-1)*3 + (c-1)];
			temp_board[(r-1)*3 + (c-1)] = v;
			missing_array[temp_board[(r-1)*3 + (c-1)]-1] = 0;
		} 
		else {
			printf("ERROR\n");
		}
	} while (1); // end of the inner loop
 
	printf("\n---------------------------------------------------\n");

 
	// Check the results


        for (i = 0; i < 9; i++) {
                if (temp_board[i] == main_board[i]) {
                counter += 1;
                }
        }

        if (counter == 9) {
                check_game = 1;
        }

        else {
                check_game = 0;
        }


        if (check_game)             // display Wining/Losing Message
            printf ("**** Congratulations!!!****\n ***You Won!!!!*** \n");
        else
            printf (":( Sorry it is not correct :( \n");
        
        printf("#######################################\n");
        printf ("   Do you want to play again? (Yes:1, No:0)\n"); // ask the user to play again
        printf("#######################################\n");
        scanf ("%d", &play_again);
        
        if (!play_again){
            printf("Bye!");
            break;
        }

        counter = 0;

   } while(1); // end of the outer loop
}

