/******************************************************************************

Author: Harry Wang
Date: Feb-11-23
Lab: lab03
Last modified: Feb-15-23
Purpose: The programming lab assignment requires reading an NFL game score for a team and to determine the scoring possibilities. A score is expected to be 2 or higher. Thus if a score less than 2 is entered, the program should stop.

*******************************************************************************/

#include <stdio.h>
#include <math.h>
#define touchdown 6
#define field_goal 3
#define safety 2
#define touchdown_2pt 8
#define touchdown_field_goal 7

//check if the goals equals the score we want, if so return 1 (true) else return 0 (false)
int is_valid_value(int check_value, int td_2pt, int td_fg, int td, int fg, int sft)
{
    if (((td * touchdown)+(fg * field_goal)+(sft * safety)+(td_2pt * touchdown_2pt)+(td_fg * touchdown_field_goal)) == check_value)
    {
        return 1;
    }
    return 0;
}

int main()
{
    int score = 1, td_2pt, td_fg, td, fg, sft;
    // get the score from the user
    printf("Enter 0 or 1 to STOP\nEnter the NFL score: ");
    scanf("%d", &score);
    // if the score is greater than 1 start the nested loops.
    // the score must be greater than 1 because a negative sore, zero or one is impossiable
    if (score > 1)
    {
        //run for every touchdown + 2 points even for the case when the touch down makes up the majority of the score
        // repeat this for every other way that the place can score
        for (td_2pt = 0; td_2pt <= ceil(score/touchdown_2pt); td_2pt++)
        {
            for (td_fg = 0; td_fg <= ceil(score/touchdown_field_goal); td_fg++)
            {
                for (td = 0; td <= ceil(score/touchdown); td++)
                {
                    for (fg = 0; fg <= ceil(score/field_goal); fg++)
                    {
                        for (sft = 0; sft <= ceil(score/safety); sft++)
                        {
                            //test if the scores are possiable then print the possiable combination.
                            if (is_valid_value(score, td_2pt, td_fg, td, fg, sft) == 1)
                            {
                                printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td_2pt, td_fg, td, fg, sft);
                            }
                        }
                    }
                }
            }
        }
    }


    return 0;
}
