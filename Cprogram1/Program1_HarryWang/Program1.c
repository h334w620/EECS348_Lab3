/******************************************************************************

Author: Harry Wang
Date: Feb-11-23
Lab: lab03
Last modified: Feb-15-23
Purpose:The programming lab assignment requires that 12 monthly sales to be read and a sales report to be generated. The report should include the (1) a title for the report, (2) a tabular report of the month and sales in two columns, one for the month (January, February, ..) and one for the corresponding sales, (2) the sales summary, e.g., month with the lowest sales, month with the highest sales, and the average sales, (3) a six-month moving average also in a tabular format, and finally (4) a tabular listing of months and sales with the sales from the highest to the lowest.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define months 12


//read in a file containing only floats and return those floats in an array
double* read_file(char* filename)
{
  //create a file pointer
  FILE *fp;
  fp = fopen(filename, "r");
  //make sure the file exist if not raise an error
  if (fp == NULL)
    {
      printf("cannot read '%s': No such file was found\n", filename);
      exit(1);
    }
  int i = 0;
  //each line we read must be within 255 charaters long
  char lines[255];
  //orginal string pointer
  char *og_string;
  static double sales[13];
  //read each line of the file less than 12 lines long and that it's not a null value
  while((i < 12) && (fgets(lines, sizeof(lines), fp) != NULL))
    {
      //we convert each line which is a string to a double value
      sales[i] = strtod(lines, &og_string);
      //increment the line index
      i++;
    }
  //once we read the file to an array we can close the file
  fclose(fp);
  return sales;
}

//is_sorted test of the array is sorted, if it is sorted return true (1) else false (0)
int is_sorted(double* input_value)
{
    // define the index
    int i;
    // loop though the month
    for (i = 0; i < months -1; i++)
    {
        // for every month's sales figures compare the next month's sales figure, if the next month is greater than exit with 0
        if (!(input_value[i] <= input_value[i + 1]))
        {
            return 0;
        }
    }
    // if the loop ran without exiting than we can assume the array is sorted
    return 1;
}

//sorter takes in a float array and a follower month array which acts like a hash map
void sorter(double input_value[], char** months_index)
{
    char* months_hold;
    double hold, *value = input_value;
    int i = 0;
    // runs forever until the loop is broken
    while (1)
    {
      //if the current value and the next value is less than or equal to perform the sort
        if (!(value[i] <= value[i + 1]))
        {
	  // first hold the current value
            hold = value[i];
	    // second override the current value with the next value
            value[i] = value[i + 1];
	    // third override the next value with the hold value 
            value[i + 1] = hold;
	    //as a result the current value and the next value swapped places

	    //repeat for the months so the months can track with the sales figure.
            months_hold = months_index[i];
            months_index[i] = months_index[i + 1];
            months_index[i + 1] = months_hold;
        }

	//increcemnt the index and reset the index
        if (i < months -1)
        {
            i++;
        }else
        {
            i = 0;
        }

	//exit the loop when the values are all sorted
        if (is_sorted(value))
        {
            break;
        }
    }
}

//print the current sales report with the months.
void print_sales_report(char** month_name, double* sales_fig)
{
    int i;
    printf("Monthly sales report for 2022:\n\n Months \t Sales\n\n");
    for (i = 0; i <= months - 1; i++)
    {
        printf("%s\t$%0.2f\n", month_name[i], sales_fig[i]);
    }
    printf("\n\n");
}

//print the min and max and average of the sales figures
void print_min_max_avg(char** month_name, double* sales_fig)
{
    int i;
    double average = 0;
    printf("Sales summary: \n\n");
    // we know at index 1 resides the min when sorted
    printf("Minimum sales:\t$%0.2f\t(%s)\n", sales_fig[1], month_name[1]);
    // we know at index 12 resides the max when sorted
    printf("Minimum sales:\t$%0.2f\t(%s)\n", sales_fig[months], month_name[months]);
    // we add up every average and divide by 12 to get the average sales over the 12 months.
    for (i = 0; i <= months; i++)
    {
        average = average + sales_fig[i];
    }
    printf("Average sales:\t$%0.2f\n\n", average/months);
    printf("\n\n");
}

//calculate the 6 month running average 
double* calc_running_avg(double sales[])
{
    int i, j;
    // replacing the values in result from null values to 0 solves a problem with adding to null values
    static double result[7];
    for (i = 0; i < months/2; i++)
    {
        result[i] = 0;
    }
    // iterate thought the 6 months
    for (i = 0; i <= months/2; i++)
    {
      // for every 6 month add the 6 month together
        for (j = 0; j < months/2; j++)
        {
            result[i] = result[i] + sales[i+j];
        }
	// 0.001 solve some of the rounding error
        result[i] = ((result[i]/6) + 0.001);
    }
    return result;
}

//print out the 6 month rolling average.
void print_6_mon_avg(double* avg)
{
    int i;
    char* month_inorder[] = {"January  ","February ","March    ","April    ","May      ","June     ","July     ","August   ","September","October  ","November ","December "};
    printf("Six-Month Moving Average Report:\n\n");
    for (i = 0; i <= months/2; i++)
    {
        printf("%s\t-   %s\t$%0.2f\n", month_inorder[i], month_inorder[5+i], avg[i]);
    }
    printf("\n\n");
}

// print out the sorted sales and the month relative to the sales.
void print_sorted_sales(char** month_name, double* sales_fig)
{
    int i;
    printf("Sales Report (Highest to Lowest):\n\n Months \t Sales\n\n");
    for (i = 0; i <= months - 1; i++)
    {
        printf("%s\t$%0.2f\n", month_name[months - i], sales_fig[months - i]);
    }
}

int main()
{
  //an array of months
  char* months_index[13] = {"January  ","February ","March    ","April    ","May      ","June     ","July     ","August   ","September","October  ","November ","December "};

  // we need to pass in a filename pointer to get the entire string else if we pass in filename we will only be passing in singlr char.
  char filename[255], *filename_pointer = filename;
  // ask the user for a filename
  printf("Enter your filename (example: sales_numbers.txt)(must be in the same directory): ");
  scanf("%s", filename);
  //points the sales variable to the float array of sales figures
  double* sales = read_file(filename_pointer);
  
  // calculates and store the running_avg
  double* running_avg = calc_running_avg(sales);
    
  //Sales report (month and sales in two columns)
  print_sales_report(months_index, sales);

  //call the sorter function sorts the sales and the months relative to sales
  sorter(sales, months_index);
  //minimum, maximum, and average of the monthly sales. 
  print_min_max_avg(months_index, sales);

  //six-month moving averages. 
  print_6_mon_avg(running_avg);

  //monthly sales report from highest to lowest. 
  print_sorted_sales(months_index, sales);

  return 0;
}
