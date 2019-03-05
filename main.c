#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>


#define CSV_COMMA_PER_LINE 179

void skip_line (FILE * bpb, int comma_offset, int title_match);
void tab_2_pub (FILE * bpb, int i);
void tell_user_how (void);
void get_track(FILE * bpb);
void ready_to_csv(void);
void completion_msg(void);
int get_month (void);
int get_year (void);
void concat_date(char * text_file_name, char * file_extension);
void create_dir (void);
void press_enter (void);
void skip_to_end_of_line(FILE * bpb)
{
    for (int i = 0; i < 10000; ++i)
    {
        char c = getc(bpb);
        if (c == '\n')
            break;
    }
    getc(bpb);   // get the " from next line
}
int BPB_track_cnt;
int BMI_track_cnt;

char temp[130];

struct name
{
    char name[100];
};

struct record
{
    char period[12];
    char p_w[6];
    char participant[45];
    char participant_num[22];
    char ip_num[20];
    char title_name[45];
    char title_num[25];
    char perf_source[30];
    char cop[40];
    char show_name[40];
    char epi_name[40];
    char show_num[40];
    char use_code[40];
    char timing[40];
    char participant_perc[40];
    char perf_count[40];
    char bonus_level[40];
    char royalty_amt[40];
    char withhold[40];
    char perf_period[40];
    char current_activity_amt[40];
    char hits_song_or_tv_super[40];
    char standards_or_tv_net_theme_bonus[40];
    char foreign_society_adjustment[40];
    char company_code[40];
    char company_name[40];

    char publisher_1[120];
    char publisher_2[120];
    char publisher_3[120];
    char publisher_4[120];
    char publisher_5[120];
    char publisher_6[120];

    int title_match;
    int number_of_matches;
};


void track_to_upper(struct name *ptr,int name_numb);
void name_convention1(struct name *ptr,int name_numb);
void name_convention2(struct name *ptr,int name_numb);
int matching_titles(struct name *ptr,struct record *ptrb);
void list_count_matches(struct record *ptrb,int match_counter);
void publisher(FILE * bpb, struct record *ptrb, int publisher_numb, int m);
void multi_match_text_doc (struct record *t);
void multimatch(int number_tracks_multimatch,struct record *ptrb);

int check_csv_length(FILE * csv, int a);

int bpb_length(FILE * bpb)
{
    int number_of_rows = 0;

    char a [1000000];
    char c;
               // Get one character from the input
    while(fgets(a, sizeof(a), bpb) != NULL){
        number_of_rows++;
    }


    fseek(bpb, 0, SEEK_SET);
    return number_of_rows;
}

void csv (struct record *t);

int main(void)
{
    tell_user_how();                                                               /* tell user where to place and name spreadsheets so program will work   */

    press_enter();

    int record_num = 0;
    char bmi_file[130] = "./desktop/a.csv";                                      /*   open BMI statement      */

    FILE *bmi = fopen(bmi_file, "r");
    if (bmi == NULL)
    {
        printf("Unable to open file '%s'\n", bmi_file);
        exit(1);
    }

    BMI_track_cnt = check_csv_length(bmi,
                                     0);                                        /* setting max rows of BMI spreadsheet   */

    struct record new_statement[BMI_track_cnt];
    struct record *ptrb;
    ptrb = new_statement;

    for (int j = 0; j < BMI_track_cnt; ++j)
    {
        printf("\n");
        for (int i = 0; i < 10; ++i)                                         /*  PERIOD  */
        {
            new_statement[record_num].period[i] = (char) getc(bmi);
            if (new_statement[record_num].period[i] == ',')
            {
                new_statement[record_num].period[i] = '\0';
                break;
            }
            if (new_statement[record_num].period[i] == '\n')
                i--;
            if (new_statement[record_num].period[i] == '\r')
                i--;
        }
//    printf("||record %3d period %8s ", (record_num + 1), new_statement[record_num].period);

        for (int i = 0; i < 7; ++i)                                         /*  P     OR     W  */
        {
            new_statement[record_num].p_w[i] = (char) getc(bmi);
            if (new_statement[record_num].p_w[i] == ',')
            {
                new_statement[record_num].p_w[i] = '\0';
                break;
            }
        }
//        printf("||record %3d p_w %10s ", (record_num + 1), new_statement[record_num].p_w);

        for (int i = 0; i < 35; ++i)                                         /*  PARTICIPANT  */
        {
            new_statement[record_num].participant[i] = (char) getc(bmi);
            if (new_statement[record_num].participant[i] == ',')
            {
                new_statement[record_num].participant[i] = '\0';
                break;
            }
        }
//        printf("||record %3d participant %30s ", (record_num + 1), new_statement[record_num].participant);


        for (int i = 0; i < 25; ++i)                                         /*  PARTICIPANT NUM  */
        {
            new_statement[record_num].participant_num[i] = (char) getc(bmi);
            if (new_statement[record_num].participant_num[i] == ',')
            {
                new_statement[record_num].participant_num[i] = '\0';
                break;
            }
        }
//        printf("||record %3d participant_num %20s ", (record_num + 1), new_statement[record_num].participant_num);


        for (int i = 0; i < 25; ++i)                                         /*       IP      #  */
        {
            new_statement[record_num].ip_num[i] = (char) getc(bmi);
            if (new_statement[record_num].ip_num[i] == ',')
            {
                new_statement[record_num].ip_num[i] = '\0';
                break;
            }
        }
//        printf("||record %3d ip_num %20s ", (record_num + 1), new_statement[record_num].ip_num);


        for (int i = 0; i < 60; ++i)                                         /*     TITLE NAME    */
        {
            new_statement[record_num].title_name[i] = (char) getc(bmi);
            if (new_statement[record_num].title_name[i] == ',')
            {
                new_statement[record_num].title_name[i] = '\0';
                break;
            }
        }
//        printf("||record %3d title_name %40s ", (record_num + 1), new_statement[record_num].title_name);

        for (int i = 0; i < 30; ++i)                                         /*      TITLE   #    */
        {
            new_statement[record_num].title_num[i] = (char) getc(bmi);
            if (new_statement[record_num].title_num[i] == ',')
            {
                new_statement[record_num].title_num[i] = '\0';
                break;
            }
        }
//        printf("||record %3d title_num %20s ", (record_num + 1), new_statement[record_num].title_num);

        for (int i = 0; i < 30; ++i)                                         /*  PERFORMANCE SOURCE   */
        {
            new_statement[record_num].perf_source[i] = (char) getc(bmi);
            if (new_statement[record_num].perf_source[i] == ',')
            {
                new_statement[record_num].perf_source[i] = '\0';
                break;
            }
        }
//        printf("||record %3d perf_source %20s ", (record_num + 1), new_statement[record_num].perf_source);


        for (int i = 0; i < 35; ++i)                                         /*  COUNTRY OF PERFORMANCE   */
        {
            new_statement[record_num].cop[i] = (char) getc(bmi);
            if (new_statement[record_num].cop[i] == ',')
            {
                new_statement[record_num].cop[i] = '\0';
                break;
            }
        }
//        printf("||record %3d cop %28s ", (record_num + 1), new_statement[record_num].cop);


        for (int i = 0; i < 60; ++i)                                         /*      SHOW    NAME    */
        {
            new_statement[record_num].show_name[i] = (char) getc(bmi);
            if (new_statement[record_num].show_name[i] == ',')
            {
                new_statement[record_num].show_name[i] = '\0';
                break;
            }
        }
//        printf("||record %3d show_name %50s ", (record_num + 1), new_statement[record_num].show_name);


        for (int i = 0; i < 60; ++i)                                         /*      EPISODE    NAME    */
        {
            new_statement[record_num].epi_name[i] = (char) getc(bmi);
            if (new_statement[record_num].epi_name[i] == ',')
            {
                new_statement[record_num].epi_name[i] = '\0';
                break;
            }
        }
//        printf("||record %3d epi_name %60s ", (record_num + 1), new_statement[record_num].epi_name);


        for (int i = 0; i < 18; ++i)                                         /*      SHOW     #  */
        {
            new_statement[record_num].show_num[i] = (char) getc(bmi);
            if (new_statement[record_num].show_num[i] == ',')
            {
                new_statement[record_num].show_num[i] = '\0';
                break;
            }
        }
//        printf("||record %3d show_num %20s ", (record_num + 1), new_statement[record_num].show_num);


        for (int i = 0; i < 18; ++i)                                         /*      USE   CODE    */
        {
            new_statement[record_num].use_code[i] = (char) getc(bmi);
            if (new_statement[record_num].use_code[i] == ',')
            {
                new_statement[record_num].use_code[i] = '\0';
                break;
            }
        }
//        printf("||record %3d use_code %20s ", (record_num + 1), new_statement[record_num].use_code);

        for (int i = 0; i < 20; ++i)                                         /*       TIMING       */
        {
            new_statement[record_num].timing[i] = (char) getc(bmi);
            if (new_statement[record_num].timing[i] == ',')
            {
                new_statement[record_num].timing[i] = '\0';
                break;
            }
        }
//        printf("||record %3d timing %20s ", (record_num + 1), new_statement[record_num].timing);


        for (int i = 0; i < 20; ++i)                                         /*    PARTICIPANT PERCENTAGE    */
        {
            new_statement[record_num].participant_perc[i] = (char) getc(bmi);
            if (new_statement[record_num].participant_perc[i] == ',')
            {
                new_statement[record_num].participant_perc[i] = '\0';
                break;
            }
        }
//        printf("||record %3d participant_perc %20s ", (record_num + 1), new_statement[record_num].participant_perc);


        for (int i = 0; i < 20; ++i)                                         /*    PERFORMANCE COUNT    */
        {
            new_statement[record_num].perf_count[i] = (char) getc(bmi);
            if (new_statement[record_num].perf_count[i] == ',')
            {
                new_statement[record_num].perf_count[i] = '\0';
                break;
            }
        }
//        printf("||record %3d perf_count %20s ", (record_num + 1), new_statement[record_num].perf_count);


        for (int i = 0; i < 20; ++i)                                         /*     BONUS LEVEL      */
        {
            new_statement[record_num].bonus_level[i] = (char) getc(bmi);
            if (new_statement[record_num].bonus_level[i] == ',')
            {
                new_statement[record_num].bonus_level[i] = '\0';
                break;
            }
        }
//        printf("||record %3d bonus_level %20s ", (record_num + 1), new_statement[record_num].bonus_level);


        for (int i = 0; i < 20; ++i)                                         /*    ROYALTY AMOUNT    */
        {
            new_statement[record_num].royalty_amt[i] = (char) getc(bmi);
            if (new_statement[record_num].royalty_amt[i] == ',')
            {
                new_statement[record_num].royalty_amt[i] = '\0';
                break;
            }
        }
//        printf("||record %3d royalty_amt %20s ", (record_num + 1), new_statement[record_num].royalty_amt);


        for (int i = 0; i < 20; ++i)                                         /*       WITHHOLD      */
        {
            new_statement[record_num].withhold[i] = (char) getc(bmi);
            if (new_statement[record_num].withhold[i] == ',')
            {
                new_statement[record_num].withhold[i] = '\0';
                break;
            }
        }
//        printf("||record %3d withhold %20s ", (record_num + 1), new_statement[record_num].withhold);


        for (int i = 0; i < 25; ++i)                                         /*     PERFORMANCE PERIOD    */
        {
            new_statement[record_num].perf_period[i] = (char) getc(bmi);
            if (new_statement[record_num].perf_period[i] == ',')
            {
                new_statement[record_num].perf_period[i] = '\0';
                break;
            }
        }
//        printf("||record %3d perf_period %20s ", (record_num + 1), new_statement[record_num].perf_period);


        for (int i = 0; i < 25; ++i)                                         /*      CURRENT ACTIVITY AMT    */
        {
            new_statement[record_num].current_activity_amt[i] = (char) getc(bmi);
            if (new_statement[record_num].current_activity_amt[i] == ',')
            {
                new_statement[record_num].current_activity_amt[i] = '\0';
                break;
            }
        }
//        printf("||record %3d current_activity_amt %20s ", (record_num + 1), new_statement[record_num].current_activity_amt);


        for (int i = 0; i < 60; ++i)                                            /*    hits_song_or_tv_super    */
        {
            new_statement[record_num].hits_song_or_tv_super[i] = (char) getc(bmi);
            if (new_statement[record_num].hits_song_or_tv_super[i] == ',')
            {
                new_statement[record_num].hits_song_or_tv_super[i] = '\0';
                break;
            }
        }
//        printf("||record %3d hits_song_or_tv_super %20s ", (record_num + 1),
//               new_statement[record_num].hits_song_or_tv_super);


        for (int i = 0;
             i < 60; ++i)                                                     /*  standards_or_tv_net_theme_bonus  */
        {
            new_statement[record_num].standards_or_tv_net_theme_bonus[i] = (char) getc(bmi);
            if (new_statement[record_num].standards_or_tv_net_theme_bonus[i] == ',')
            {
                new_statement[record_num].standards_or_tv_net_theme_bonus[i] = '\0';
                break;
            }
        }
//        printf("||record %3d standards_or_tv_net_theme_bonus %20s ", (record_num + 1),
//               new_statement[record_num].standards_or_tv_net_theme_bonus);


        for (int i = 0; i < 60; ++i)                                             /*  foreign_society_adjustment  */
        {
            new_statement[record_num].foreign_society_adjustment[i] = (char) getc(bmi);
            if (new_statement[record_num].foreign_society_adjustment[i] == ',')
            {
                new_statement[record_num].foreign_society_adjustment[i] = '\0';
                break;
            }
        }
//        printf("||record %3d foreign_society_adjustment %20s ", (record_num + 1),
//               new_statement[record_num].foreign_society_adjustment);


        for (int i = 0; i < 60; ++i)                                                     /*  company_code  */
        {
            new_statement[record_num].company_code[i] = (char) getc(bmi);
            if (new_statement[record_num].company_code[i] == ',')
            {
                new_statement[record_num].company_code[i] = '\0';
                break;
            }
        }
//        printf("||record %3d company_code %20s ", (record_num + 1), new_statement[record_num].company_code);


        for (int i = 0; i < 20; ++i)                                         /*   company_name   */
        {
            ptrb[record_num].company_name[i] = (char) getc(bmi);
            if (ptrb[record_num].company_name[i] == EOF ||
                ptrb[record_num].company_name[i] == '\n' ||
                ptrb[record_num].company_name[i] == '\0' ||
                ptrb[record_num].company_name[i] == ',' ||
                ptrb[record_num].company_name[i] == '\r')
            {
                ptrb[record_num].company_name[i] = '\0';
                break;
            }
        }
//        printf("||record %3d company_name %14s||", (record_num + 1), new_statement[record_num].company_name);

        new_statement[record_num].title_match = -1;                                  /*  setting initial state of all tracks to no title match flag  */
        ++record_num;
    }

    printf("\nBMI file has %d rows", BMI_track_cnt);
    fclose(bmi);                                                                    /*  close BMI statement   */

    char bpb_file[130] = "./desktop/bpb.csv";                              /*    opening BPB csv    */
    FILE *bpb = fopen(bpb_file, "r");
    if (bpb == NULL)
    {
        printf("\nUnable to open file '%s'\n", bpb_file);
        exit(1);
    }
//    BPB_track_cnt = bpb_length(bpb) - 1;                         /* setting max rows of BPB spreadsheet   */

    printf("\nEnter bpb.csv row count:\n");
    scanf("%d", &BPB_track_cnt);

    struct name track[BPB_track_cnt];                                                /*  holds BPB track titles   */
    struct name *ptr;
    ptr = track;

    fseek(bpb, 0, SEEK_SET);

    printf("\nBPB file has %d rows", BPB_track_cnt + 1);

    press_enter();

    skip_line(bpb, 0,
              1);                                                   /* moved to first track name field in BPB csv          */

    for (int l = 0; l < 30; ++l)
    {
        if ('\r' == getc(bpb))
            break;
    }

    for (int l = 0; l < 30; ++l)
    {
        if (',' == getc(bpb))
            break;
    }
    getc(bpb);


    for (int i = 0; i < BPB_track_cnt -
                        1; i++)                             /*  get all track names from BPB csv except last name  */
    {
        get_track(bpb);
        strcpy(track[i].name, temp);
        printf("%s \n", track[i].name);
        skip_line(bpb, 2, 1);
        for (int l = 0; l < 30; ++l)
        {
            if ('\r' == getc(bpb))
                break;
        }

        for (int l = 0; l < 30; ++l)
        {
            if (',' == getc(bpb))
            {
                getc(bpb);
                break;
            }

        }

    }

//    get_track(bpb);                                                       /*  get last track name from BPB csv   */
    strcpy(track[BPB_track_cnt - 1].name, temp);

    for (int i = 0; i < BPB_track_cnt; ++i)
    {
        track_to_upper(ptr,
                       i);                                            /*   making all letters of bpb titles uppercase like the BMI statement   */
        name_convention1(ptr,
                         i);                                          /*   removing A and THE at the beginning of imported BPB track title     */
        name_convention2(ptr,
                         i);                                          /*   changing ALT MIX to ALT and removing STEM at the end of imported BPB track title   */
//      printf("\n%d        %s", i+1, track[i].name);
    }

    int number_tracks_multimatch = 0;
    for (int k = 1; k < BMI_track_cnt; ++k)
    {
        ptrb[k].number_of_matches = 0;
        for (int i = 0; i < BPB_track_cnt; ++i)
        {
            if (strcmp(ptrb[k].title_name, ptr[i].name) == 0)
            {

                ptrb[k].number_of_matches++;
                if (ptrb[k].number_of_matches > 1)
                    ++number_tracks_multimatch;
            }
        }
//                if(ptrb[k].number_of_matches > 1)
//                    printf("\nBMI track %d       has %d matches!!!!!    ",k,ptrb[k].number_of_matches);
    }


    /* create folder for new files  */

    int match_counter = matching_titles(ptr,
                                        ptrb);                         /*    Matching the BMI statement titles to BPB titles    */



    list_count_matches(ptrb, match_counter);
    create_dir();


    /* creating directory on desktop for new files   */
    multimatch(number_tracks_multimatch,
               ptrb);                   /* counts number of tracks with multiple matches. if theres more than 1 it creates text doc with info */

    ready_to_csv();                                                       /*   wait for user input before making csv     */

    fseek(bpb, 0, SEEK_SET);
//    tab_2_pub(bpb, 0);                                                                  /*    skip to the publisher 1 field    */



//    printf("%s",new_statement[1].title_name);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//
////    skip_line(bpb, -3, 19351);
//
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//    tab_2_pub(bpb, 38);
//
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//
//    skip_to_end_of_line(bpb);
//    tab_2_pub(bpb, 0);
//
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//
////    skip_line(bpb, -3, 19351);
//
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//    tab_2_pub(bpb, 38);
//
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//
//    tab_2_pub(bpb, 38);
//    for (int n = 0; n < 18; ++n)
//    {
//        printf("%c", getc(bpb));
//    }
//    printf("\n");
//    return 0;
//
//
//    skip_line(bpb, 0, new_statement[1].title_match + 1);             /*    skip to the track row in bpb     */
//
//    int publisher_numb = 1;
//    for (int i = 1; i <= 6; ++i)
//    {
//        publisher(bpb, ptrb, publisher_numb, 1);                    /*    assign publisher 1 data          */
//        tab_2_pub(bpb, 0);
//        ++publisher_numb;
//    }
//    tab_2_pub(bpb, -92);
//
//            printf("\n%-4d Title: %s p1 = %s p2 = %s p3 %s p4 %s p5 %s p6 %s %-6d", 1, new_statement[1].title_name,
//               new_statement[1].publisher_1, new_statement[1].publisher_2, new_statement[1].publisher_3,
//               new_statement[1].publisher_4, new_statement[1].publisher_5, new_statement[1].publisher_6,
//               new_statement[1].title_match);
//
//    return 0;
//}
    int first_repeat_flag = 0;
    int look_flag = 1;
    int difference = new_statement[1].title_match;                                      /* amount of entries in between 2 rows */

    for (int m = 1; m < BMI_track_cnt; ++m)                                             /*  find and assign publishers 1-6 to correlating BMI csv tracks   */
    {
        if (new_statement[m].title_match == -1)
        {
            strcpy(new_statement[m].publisher_1, "NO MATCH");                                //if title match -1 assign NO MATCH
            strcpy(new_statement[m].publisher_2, "NO MATCH");
            strcpy(new_statement[m].publisher_3, "NO MATCH");
            strcpy(new_statement[m].publisher_4, "NO MATCH");
            strcpy(new_statement[m].publisher_5, "NO MATCH");
            strcpy(new_statement[m].publisher_6, "NO MATCH");
            if(new_statement[m-1].title_match != -1)
            {
                difference = new_statement[m - 1].title_match;
            }
            look_flag = 0;
            first_repeat_flag = 0;
        }
        if(first_repeat_flag != 0)                                                        /*     skip these if's first time    */
        {
            if(new_statement[m - 1].title_match == -1 && new_statement[m].title_match > difference)
            {
                difference = new_statement[m].title_match - difference -2;
                first_repeat_flag =0;
            }
            if(new_statement[m - 1].title_match == -1 && new_statement[m].title_match < difference)
            {
                fseek(bpb, 0, SEEK_SET);
//                tab_2_pub(bpb, 1);
                difference = new_statement[m].title_match;
                first_repeat_flag =0;
            }
            if (new_statement[m].title_match > new_statement[m - 1].title_match && first_repeat_flag != 0)
            {
                difference = (new_statement[m].title_match - new_statement[m-1].title_match) - 2;
            }
            if (new_statement[m].title_match < new_statement[m - 1].title_match && first_repeat_flag != 0)
            {
                fseek(bpb, 0, SEEK_SET);
//                tab_2_pub(bpb, 40);


                difference = new_statement[m].title_match;
            }
            if (new_statement[m].title_match == new_statement[m - 1].title_match)           // if previous title is the same copy its pub info
            {
                strcpy(new_statement[m].publisher_1, new_statement[m - 1].publisher_1);
                strcpy(new_statement[m].publisher_2, new_statement[m - 1].publisher_2);
                strcpy(new_statement[m].publisher_3, new_statement[m - 1].publisher_3);
                strcpy(new_statement[m].publisher_4, new_statement[m - 1].publisher_4);
                strcpy(new_statement[m].publisher_5, new_statement[m - 1].publisher_5);
                strcpy(new_statement[m].publisher_6, new_statement[m - 1].publisher_6);
                look_flag = 0;
            }
        }

        if(look_flag != 0)                                              // don't look if you matched the title above
        {
            skip_line(bpb, -3, difference + 1);                         /*    skip to the track row in bpb     */
            tab_2_pub(bpb, 0);
            for (int publisher_numb = 1; publisher_numb <= 6; ++publisher_numb)
            {
                publisher(bpb,ptrb,publisher_numb,m);                    /*    assign publisher 1 data          */
                tab_2_pub(bpb, 39);
            }
            skip_to_end_of_line(bpb);
        }
        look_flag = 1;
        first_repeat_flag = 1;


        printf("\n%-4d Title: %s p1 = %s p2 = %s p3 %s p4 %s p5 %s p6 %s %-6d", m, new_statement[m].title_name,
               new_statement[m].publisher_1, new_statement[m].publisher_2, new_statement[m].publisher_3,
               new_statement[m].publisher_4, new_statement[m].publisher_5, new_statement[m].publisher_6,
               new_statement[m].title_match);
    }
    strcpy(new_statement[0].publisher_1 , "pub 1");
    strcpy(new_statement[0].publisher_2 , "pub 2");
    strcpy(new_statement[0].publisher_3 , "pub 3");
    strcpy(new_statement[0].publisher_4 , "pub 4");
    strcpy(new_statement[0].publisher_5 , "pub 5");
    strcpy(new_statement[0].publisher_6 , "pub 6");

    fclose(bpb);
    csv(ptrb);                                            /*      print new csv      */
    completion_msg();                                                    /*      give feedback to user of success */

    return (0);
}


void skip_line (FILE * bpb, int comma_offset, int title_match)               /* SKIPPING LINES TO CORRECT ROW  */
{
    int comma_counter;
    for (comma_counter = 0; comma_counter < (CSV_COMMA_PER_LINE - comma_offset) * title_match;)
    {
        if ((char) getc(bpb) == '\"')
            if ((char) getc(bpb) == ',')
                if (((char) getc(bpb) == '\"'))
                    comma_counter++;
    }
}

void publisher(FILE * bpb, struct record *ptrb, int publisher_numb, int m)       /*assigning publishers 1-6  */
{
    char pub[80];
    for (int i = 0; i < 100; ++i)
    {
        pub[i] = (char)getc(bpb);

        if (pub[i] == '\"')
        {
            pub[i + 1] = (char) getc(bpb);
            if (pub[i + 1] == '\"')
            {
                getc(bpb);
                break;
            }
            else if (pub[i + 1] == ',')
            {
                pub[i]='\0';
                getc(bpb);
                break;
            }
        }
    }
    switch(publisher_numb)
    {
        case 1:
            strcpy(ptrb[m].publisher_1, pub);
            break;
        case 2:
            strcpy(ptrb[m].publisher_2, pub);
            break;
        case 3:
            strcpy(ptrb[m].publisher_3, pub);
            break;
        case 4:
            strcpy(ptrb[m].publisher_4, pub);
            break;
        case 5:
            strcpy(ptrb[m].publisher_5, pub);
            break;
        case 6:
            strcpy(ptrb[m].publisher_6, pub);
            break;
        default:
            break;
    }

}

void tab_2_pub (FILE * bpb, int i)
{

    for (int comma_counter = 0; comma_counter < 45 - i;)
    {
        if ((char) getc(bpb) == '\"')
            if ((char) getc(bpb) == ',')
                if (((char) getc(bpb) == '\"'))
                    comma_counter++;
    }
}


void csv (struct record *t)
{
    char csv_file_name[130] = "./desktop/bmi_conversion";
    concat_date(csv_file_name,"/new_bmi");
    concat_date(csv_file_name,".csv");

    FILE *f = fopen(csv_file_name, "w");
    if (f == NULL)
    {
        printf("ERROR CREATING FILE!!!!!!!!");
        exit(-1);
    }
    int errnum;
    int i = 0;
    if(fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s","Number Of Matches",
               t[i].period, t[i].p_w, t[i].participant, t[i].participant_num, t[i].ip_num, t[i].title_name,t[i].title_num,
               t[i].perf_source,t[i].cop,t[i].show_name,t[i].epi_name,t[i].show_num,t[i].use_code,t[i].timing,t[i].participant_perc,
               t[i].perf_count,t[i].bonus_level,t[i].royalty_amt,t[i].withhold,t[i].perf_period,t[i].current_activity_amt,t[i].hits_song_or_tv_super,
               t[i].standards_or_tv_net_theme_bonus,t[i].foreign_society_adjustment,t[i].company_code,t[i].company_name,t[i].publisher_1,
               t[i].publisher_2,t[i].publisher_3,t[i].publisher_4,t[i].publisher_5,t[i].publisher_6) < 0)

    {
        errnum = errno;
        printf("\n!!!!!!        ERROR # %d      !!!!!!", errnum);
        exit(EXIT_FAILURE);
    }
    fprintf(f,"\n");
    i++;
    while (i < BMI_track_cnt)
    {
        // you might want to check for out-of-disk-space here, too
        if(fprintf(f, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",t[i].number_of_matches,
                   t[i].period, t[i].p_w, t[i].participant, t[i].participant_num, t[i].ip_num, t[i].title_name,t[i].title_num,
                   t[i].perf_source,t[i].cop,t[i].show_name,t[i].epi_name,t[i].show_num,t[i].use_code,t[i].timing,t[i].participant_perc,
                   t[i].perf_count,t[i].bonus_level,t[i].royalty_amt,t[i].withhold,t[i].perf_period,t[i].current_activity_amt,t[i].hits_song_or_tv_super,
                   t[i].standards_or_tv_net_theme_bonus,t[i].foreign_society_adjustment,t[i].company_code,t[i].company_name,t[i].publisher_1,
                   t[i].publisher_2,t[i].publisher_3,t[i].publisher_4,t[i].publisher_5,t[i].publisher_6) < 0)
        {
            errnum = errno;
            printf("\n!!!!!!        ERROR # %d      !!!!!!", errnum);
            exit(EXIT_FAILURE);
        }
        fprintf(f,"\n");
        ++i;
    }
    fclose(f);
}

void tell_user_how(void)
{
    printf("+----------------------------------------------------------------------------+\n");
    printf("|                                                                            |\n");
    printf("|  1.) Make sure the BMI statement and BPB csv are on the desktop.           |\n");
    printf("|                                                                            |\n");
    printf("|  2.) Title the BMI statement file with the name:        a                  |\n");
    printf("|                                                                            |\n");
    printf("|  3.) Title the BPB csv file with the name:              bpb                |\n");
    printf("|                                                                            |\n");
    if(get_month() < 10)
        printf("|  The program will create new_bmi_%d_%4d.csv and if necessary               |\n", get_month(), get_year());
    else
        printf("|  The program will create new_bmi_%d_%4d.csv and if necessary              |\n", get_month(), get_year());

    if(get_month() < 10)
        printf("|  multiple_matches_%d_%4d.text                                              |\n", get_month(), get_year());
    else
        printf("|  multiple_matches_%d_%4d.text                                             |\n", get_month(), get_year());
    printf("|                                                                            |\n");
    printf("+----------------------------------------------------------------------------+\n");

}
void get_track (FILE * bpb)
{
    temp[0]='\0';
    char temp_track_name[130];

    for (int k = 0; k < 130; ++k)
    {
        temp_track_name[k] = (char) getc(bpb);
        if (temp_track_name[k] == '\'')
            temp_track_name[k] = ' ';
        if (temp_track_name[k] == '(')
        {
            temp_track_name[k] = ' ';
            k--;
        }
        if (temp_track_name[k] == ')')
            temp_track_name[k] = '\0';
        else if (temp_track_name[k] == '\"')
            if ((char) getc(bpb) == ',')
            {
                temp_track_name[k] = '\0';
                break;
            }
    }
    strcpy(temp,temp_track_name);
}

void ready_to_csv()
{
    printf("\nAre you ready to print your new BMI csv with publisher data? y/n\n");
    if(getc(stdin) != 'y')
    {
        printf("\nWhen you are ready, run the program again.\n");
        exit (0);
    }
}

void track_to_upper(struct name *ptr,int name_numb)
{
    for (int j = 0; j < strlen(ptr[name_numb].name); ++j)
    {
        if (ptr[name_numb].name[j] == '\0')
            break;
        ptr[name_numb].name[j] = (char)toupper((ptr[name_numb].name[j]));
    }
}

void name_convention1(struct name *ptr,int name_numb)
{
    int a = 0;
    if (ptr[name_numb].name[a] == 'A')
    {
        ++a;
        if (ptr[name_numb].name[a] == ' ')
            for (int q = 0; q < (strlen(ptr[name_numb].name)); q++)
            {
                ptr[name_numb].name[q] = ptr[name_numb].name[q + 2];
            }
    }
    else if (ptr[name_numb].name[a] == 'T')                        /*   removing THE at the beginning of BPB track title */
    {
        ++a;
        if (ptr[name_numb].name[a] == 'H')
        {
            ++a;
            if (ptr[name_numb].name[a] == 'E')
            {
                ++a;
                if (ptr[name_numb].name[a] == ' ')
                {
                    for (int i = 0; i < (strlen(ptr[name_numb].name) - 2); ++i)
                    {
                        ptr[name_numb].name[i] = ptr[name_numb].name[i + 4];
                    }
                }

            }
        }

    }
}

void name_convention2(struct name *ptr,int name_numb)
{
    char alt_mix[8] = "ALT MIX";                      /* remove MIX  */
    char alt[4] = "ALT";

    int len = (int) strlen(ptr[name_numb].name);
    int x = 1;
    for (int i = 6; i >= 0; i--)
    {

        if (ptr[name_numb].name[len - x] == alt_mix[i])
        {
            x++;
        }
        if (i == 0 && x == 8)
        {
            ptr[name_numb].name[len - 7] = '\0';
            strcat(ptr[name_numb].name, alt);
        }
    }
    char stem[5] = "STEM";                            /*    remove STEM    */

    int len2 = (int) strlen(ptr[name_numb].name);
    int y = 1;
    for (int i = 3; i >= 0; i--)
    {

        if (ptr[name_numb].name[len2 - y] == stem[i])
        {
            y++;
        }
        if (i == 0 && y == 5)
        {
            ptr[name_numb].name[len2 - 5] = '\0';
        }
    }
}

int matching_titles(struct name *ptr,struct record *ptrb)
{
    int counter = 0;
    for (int n = 1; n < BMI_track_cnt; ++n)
    {
        for (int i = 0; i < BPB_track_cnt; ++i)
        {
            if (strcmp(ptrb[n].title_name, ptr[i].name) == 0)
            {
                ptrb[n].title_match = i;
                counter++;
                break;
            }
        }
    }
    return counter;
}

void list_count_matches(struct record *ptrb,int match_counter)
{
    for (int l = 1; l < BMI_track_cnt; ++l)
    {
        printf("\n Entry = %4d   %-30s title match %d", l, ptrb[l].title_name, ptrb[l].title_match);
    }
    printf("\n\n%d exact matches!\n", match_counter);
}

void completion_msg(void)
{
    printf("\n+-----------------------------------------------------------------+\n");
    printf("|                                                                 |\n");
    printf("|           Publishers 1-6 assigned successfully                  |\n");
    if(get_month()<10)
        printf("|           new_bmi_%d_%d.csv created and placed in              |\n",get_month(),get_year());
    else
        printf("|           new_bmi_%d_%d.csv created and placed in             |\n",get_month(),get_year());
    if(get_month()<10)
        printf("|           folder bmi_conversion_%d_%d on your desktop          |\n",get_month(),get_year());
    else
        printf("|           folder bmi_conversion_%d_%d on your desktop         |\n",get_month(),get_year());
    printf("+-----------------------------------------------------------------+\n");

}

void multi_match_text_doc (struct record *t)                               /*creates text file list track names with multiple matches  */
{

    char text_file_name [90] = "./desktop/bmi_conversion";

    concat_date(text_file_name,"/multiple_matches");
    concat_date(text_file_name,".text");

    FILE *c = fopen(text_file_name, "w");
    if (c == NULL)
    {
        printf("\nERROR CREATING FILE!!!!!!!!\n");
        strerror(errno);
        exit(-1);
    }
    int errnum;
    int i = 1;

    while (i < BMI_track_cnt)
    {
        if(t[i].number_of_matches > 1)
        {
            // you might want to check for out-of-disk-space here, too
            if (fprintf(c, "Bmi statement entry # %4d titled: %-35s has   %d matches\n", i + 1, t[i].title_name,
                        t[i].number_of_matches) < 0)
            {
                errnum = errno;
                printf("\n!!!!!!        ERROR # %d      !!!!!!", errnum);
                exit(EXIT_FAILURE);
            }
        }
        ++i;
    }
    fclose(c);
}

void multimatch(int number_tracks_multimatch,struct record *ptrb)
{
    if(number_tracks_multimatch > 0)
    {
        char entry[6] = "entry";
        char entries[8] = "entries";
        if(number_tracks_multimatch > 1)
            printf("\n%d BMI %s with multiple matches!\n", number_tracks_multimatch,entries);
        if(number_tracks_multimatch == 1)
            printf("\n%d BMI %s with multiple matches!\n", number_tracks_multimatch,entry);
        multi_match_text_doc(ptrb);
    }
}

int get_month (void)
{
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    int month = tm.tm_mon + 1;

    return month;
}

int get_year (void)
{
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    int year = tm.tm_year + 1900;

    return year;
}

void concat_date(char * text_file_name, char * file_extension)
{
    char year[6]="\0";
    char month[3]="\0";
    sprintf(year,"_%d", get_year ());
    sprintf(month,"_%d", get_month ());
    strcat(text_file_name,month);
    strcat(text_file_name,year);
    strcat(text_file_name,file_extension);
}

void create_dir (void)
{
    char directory [120] = "./desktop/bmi_conversion";
    concat_date(directory,"\0");
    int i = mkdir(directory ,S_IRWXU |S_IRWXG );
    if(i != 0)
    {
        printf("\nCreating new directory skipped. Location already exists!\n");
    }
}

int check_csv_length(FILE * csv, int a)
{
    int count=0;
    if(a == 0)
    {
        for (char c = getc(csv); c != EOF; c = getc(csv))
            if (c == '\n')                                   // Increment count if this character is newline
                ++count;
    }
    if(a == 1)
    {
        for (char c = getc(csv); c != EOF; c = getc(csv))
            if (c == '\r')                                   // Increment count if this character is newline
                ++count;
    }
    fseek(csv, 0, SEEK_SET);
    return count;
}

void press_enter (void)
{
    printf("\nPress ENTER to continue:");
    getchar();
}