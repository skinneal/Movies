/**********************************************************
 * Program: Assignment 1 - Movies
 * Author: Skinneal (Allison Skinner)
 * Date: 10/10/2020
 * Description:
 * (1) Reads a CSV file with movie data that is provided
 * to the program as an argument.
 * (2) Process the data in the file to create structs
 * to hold data for each movie.
 * (3) Creates a linked list of all structs.
 * (4) Gives user choices to ask questions about the 
 * movies in the data.
 * (5) Prints out the data about the movies per
 * user choice.
 * Input: csv file and user input (integers)
 * Output: file data (string and integers)
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//movie structure
struct movie{
	char title [1000];
	float rating;
	int year;
	char lang [1000];
};


/***********************************************************
 * Function: comparator
 * Description: comparing for qsort function; sorts first 
 * on basis of year, then descending order of rating
 * Parameters: const void, const void
 * Pre-Conditions: user selects choice 2
 * Post-Conditions: sorts the movies by year and descending
 * rating 
 **********************************************************/
int comparator (const void *a, const void *b){
	if(((struct movie*)a)->year==((struct movie*)b)->year)
		return ((struct movie*)a)->rating < ((struct movie*)b)->rating;
	else
		return ((struct movie*)a)->year < ((struct movie*)b)->year;
}


/***********************************************************
 * Function: show_movies_byyear
 * Description: shows movies of specified year
 * Parameters: movie struct, int, and int
 * Pre-Conditions: user selects choice 1
 * Post-Conditions: prints all movies of specified year
 **********************************************************/
//Show movies by year
void show_movies_byyear(struct movie m[], int n, int year){
	int flag = 0;
	for (int i = 0; i<n; i++){
		if (m[i].year == year){
			printf("%s\n", m[i].title);
			flag = 1;
		}
	}

	//if no movie is found that year
	if(flag == 0) printf("No data about movies released in year %d\n", year);
	printf("\n");
}


/***********************************************************
 * Function: show_movies_bylang
 * Description: shows movies of specified language
 * Parameters: movie struct, int, char 
 * Pre-Conditions: user selects choice 3
 * Post-Conditions: prints all movies of specified language
 **********************************************************/
//Show movies by language
void show_movies_bylang(struct movie m[], int n, char l[]){
	int flag = 0;
	int flag_2 = 0;
	char lang_new[34][20] = {{"English"}, {"Russian"}, {"Hindi"}, {"Korean"}, {"Spanish"}, {"Norewegian"}, {"French"}, {"German"}, {"Romanian"}, {"Swedish"}, {"Portuguese"}, {"Urdu"}, {"Arabic"}, {"Hungarian"}, {"Persian"}, {"Chinese"}, {"Bengali"}, {"Japanese"}, {"Panjabi"}, {"Vietnamese"}, {"Javanese"}, {"Telugu"}, {"Marathi"}, {"Tamil"}, {"Italian"}, {"Turkish"}, {"Gujarati"}, {"Polish"}, {"Ukranian"}, {"Malayalam"}, {"Kannada"}, {"Oriya"}, {"Burmese"}, {"Thai"}};

	//parse through each language in lang_new
	for (int i = 0; i<34; i++){
		if (strcmp(lang_new[i],l)==0){
			flag_2 = 1;		
		}
	}
	
	//if language matches, print the year and title of movie
	for (int i = 0; i<n; i++){
		if (strstr(m[i].lang, l) != NULL && flag_2) {
			printf("%d %s\n", m[i].year, m[i].title);
			flag = 1;
		}
	}
	//if no movies is found in that language
	if (flag == 0) printf("No data about movies released in language %s\n", l);
}


/***********************************************************
 * Function: show_highest_rated
 * Description: shows highest rated movie of each year
 * Parameters: movie struct and int
 * Pre-Conditions: user selects choice 2 
 * Post-Conditions: prints the highest rated movie of each
 * year
 **********************************************************/
//Show highest rated movie of every year
void show_highest_rated(struct movie m[], int n){
	//sort the object array by year first, then sort by descending rating
	qsort(m, n + 1, sizeof(m[0]), comparator);

	int curr_year = -1;
	for (int i = 0; i < n-1; i++){
		if (m[i].year != curr_year){
			printf("%d %.2f %s\n", m[i].year, m[i].rating, m[i].title);
		}	
		curr_year = m[i].year;
	}
}


/***********************************************************
 * Function: main
 * Description: takes user's command line args, opens file,
 * process file, takes in user input
 * Parameters: commandline args
 * Pre-Conditions: user inputs command line args
 * Post-Conditions: file opens (read)
 **********************************************************/
int main(int argc, char** argv){

//if filename is not given from command line
	if (argc == 1){
		printf("Movie file not specified!\n");
	}
	else {
		//create movie object array
		struct movie m[1000];

		//extracting command line arg
		char* filename = argv[1];

		//opening file in read mode
		FILE* file = fopen(filename, "r");

		//if there is a problem opening
		if(file == NULL){
			printf("Error opening file %s", filename);
			return 0;
		}

	char line [4096];

	int count = 0;

	//reading file line by line
	while (fgets(line, sizeof(line), file)){
		if (count >= 1){
			char* tp = strdup(line);
			char* tok = strtok(tp, ",\n");
			int k = 1;
			while (tok != NULL){
				//extracting various fields of movie from the line
				if (k == 1) strcpy(m[count - 1].title, tok);
				if (k == 4) m[count - 1].rating = atof(tok);
				if (k == 2) m[count - 1].year = atoi(tok);
				if (k == 3) strcpy (m[count - 1].lang, tok);
				tok = strtok (NULL, ",\n");
				k++;
			}
			free(tp);
		}
		count++;
	}

	//file is processed
	printf("Processed file %s and parsed data for %d movies\n", filename, count);

	int op; //user's choice
	int year;
	char lang [1000];

	//loop to take user input continuously
	while (1) {
		printf("1. Show movies released in the specified year\n");
		printf("2. Show highest rated movie for each year\n");
		printf("3. Show the title and year of release of all movies in a specific language\n");
		printf("4. Exit the program\n");
		printf("\n Enter a choice from 1 to 4:\n");

		//read user's input
		scanf("%d", &op);

		//decide what to do based on user's choice
		switch(op){

			//user wants to see movies from specific year
			case 1:
				printf("Enter the year for which you want to see movies: ");
				scanf("%d", &year);
				show_movies_byyear(m, count, year);
				break;

			//user wants to see highest rated movies from all years
			case 2:
				show_highest_rated(m, count);
				break;

			//user wants to see movies from specific language
			case 3:
				printf("Enter the language for which you want to see movies: ");
				scanf("%s", lang);
				show_movies_bylang(m, count, lang);
				break;

			//user wants to stop the program
			case 4:
				exit(0);

		}
	}
}
	return 0;
}












