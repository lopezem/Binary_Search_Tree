#include <stdio.h>
#include <stdlib.h>

struct WORD
{
    int linearr[8];//a word can be in 8 lines maximum
    int linearr_index;//index of line array
    int flag;
    char word[10];//its actual word with max of 10 letters
    struct WORD *LEFT;
    struct WORD *RIGHT;
};

static FILE *input,*output;//input and output file
static int char_index = 0;
static int line_index = 1;
static int itt = 0;
static int itter= 0;
int main()
{

    struct WORD *root,*child,*trash;
    char *str;//the entire string of the function
    char temp_char;//temporary character
    int i = 0;
    int result;

    input = fopen("testcase.txt","r");
    output = fopen("output.txt","w");

    root = (struct WORD*)malloc(sizeof(struct WORD));

    if (root == NULL)
    {
        printf("allocation error!\n");
        exit(0);
    }

   	while(fscanf(input,"%c",&temp_char)!=EOF)
	{
        *(str + i) = temp_char;//assigns character to the string
        i++;
	}//end while
    i=0;

    assign_word(root,str);//first word of root is first word of str
    //root -> LEFT -> linearr[0] = line_index;//first appears a line # ...
    child = root;
    root -> LEFT = NULL;
    root -> RIGHT = NULL;
    root ->linearr[0]=1;
    root->linearr_index = 0;//initalization
    root ->flag = 0;
    create_tree(root,child,str,trash);//creates binary tree
    //result = compare_words(root, str+36);
    //printf("result = %d",result);
    //while(*(root->word + i)!= NULL)
    //{
    //    printf("%c",*(root->word + i));
    //    i++;
    //}

    print_tree(root,root);
    fclose(input);
    fclose(output);
    return 0;
}

void create_tree(struct WORD *root,struct WORD *child,char *str,struct WORD *trash)
{

    int check;
    check = compare_words(child,str+char_index);//compares the strings
    if (*(str + char_index) == '#')
        return;//keep returning until you get back to main

    if (check == 2 )//node word > string word
    {
        if (child -> LEFT == NULL)//means this word hasnt been used yet
        {
            child -> LEFT = (struct WORD*)malloc(sizeof(struct WORD));
            child -> LEFT -> linearr[0] = line_index;//first appears a line # ...
            child->LEFT->linearr_index = 0;//initalization
            child->LEFT->flag = 0;
            assign_word(child->LEFT,str);//create new leaf node on the left
            itt++;

            child = child -> LEFT;//making leaf's left and right node NULL
            child -> LEFT = NULL;
            //child ->LEFT->flag=1;
            child -> RIGHT = NULL;
            //child ->RIGHT->flag=1;

            child = root;//go back to the root node
            create_tree(root,child,str,trash);
        }
        else
        {
            child = child -> LEFT;
            create_tree(root,child,str,trash);
        }

    }

    else if (check == 1)//node word < string word
    {
        if (child -> RIGHT == NULL)//means this word hasnt been used yet
        {
            child -> RIGHT = (struct WORD*)malloc(sizeof(struct WORD));
            child -> RIGHT -> linearr[0] = line_index;//first appears a line # ...
            child->RIGHT->linearr_index = 0;//initalization
            child->RIGHT->flag = 0;
            assign_word(child->RIGHT, str);//create new leaf node on the right
            itt++;

            child = child -> RIGHT;//making leaf's left and right node NULL
            child -> LEFT = NULL;
            //child ->LEFT->flag=1;
            child -> RIGHT = NULL;
            //child ->RIGHT->flag=1;

            child = root;//go back to the root node
            create_tree(root,child,str,trash);
        }
        else
        {
            child = child -> RIGHT;
            create_tree(root,child,str,trash);
        }
    }

    else if (check == 0)//node word == string word
    {
        trash = (struct WORD*)malloc(sizeof(struct WORD));//used to dump unecessary repeated roots
        child->linearr_index++;//next element in the array
        child->linearr[child->linearr_index]=line_index;//outputs that word's  line index to that array

        assign_word(trash, str);//emptys the repeated word into the trash
        itt++;
        child = root;//go back to the root node
        create_tree(root,child,str,trash);
    }

    else
    {
        printf("something went wrong!!!!");
        exit(0);
    }
}

void assign_word(struct WORD *wrd,char *str)//assigns strings word to structure's word value
{
    int i = 0;
    while(*(str + char_index)!= 10 && *(str + char_index)!= '.' && *(str + char_index)!= ',' && *(str + char_index)!= ' ')//check to see if at punctuation mark
        {
          *(wrd->word + i) = *(str + char_index);
          i++;
          char_index++;//traversing through the string
        }//end while

        while(i<10)
        {
            *(wrd->word + i) = NULL;
            i++;
        }

        if(*(str + char_index) != '#')//done to skip over punctuation marks
        {
            if (*(str + char_index) == '.')//right before line character
            {
                line_index++;//static increase
                char_index++;//skip over period punctuation
            }
            char_index++;//skip over punctuation
        }
}

int compare_words(struct WORD *wrd,char *str)//compares node's word with the word in the string
{
    int i = 0;
    int keep_going = 1;
    int counter = 0;//counts to see how many characters are the same
    do
    {
        if (*(wrd->word + i) == *(str + i))
        {
            if (*(wrd->word + i + 1) == NULL && ( *(str + i + 1) == ','|| *(str + i + 1) == '.'|| *(str + i + 1) == ' '))//truly the same
                return 0;//truly the same
            else if(*(wrd->word + i + 1) == NULL && (*(str + i + 1) != ',' && *(str + i + 1) != '.' && *(str + i + 1) != ' '))
                return 1;//1 means the node's word in higher than the string in a aplhabetical manner
            else if(*(wrd->word + i + 1) != NULL && (*(str + i + 1) == ',' || *(str + i + 1) == '.' || *(str + i + 1) == ' '))
                return 2;//2 means the string in higher than the node's word in a aplhabetical manner
            //else
                //the next characters are the same
        }
        else if(*(wrd->word + i) > *(str + i))
            return 1;//1 means the node's word in higher than the string in a aplhabetical manner
        else if(*(wrd->word + i) < *(str + i))
            return 2;//2 means the string in higher than the node's word in a aplhabetical manner

            i++;

    } while(keep_going);

    return 3;//means they are the same
}

void print_tree(struct WORD *child, struct WORD *root)
{
    int i = 0, j = 0;

    itter++;
    struct WORD *temp, *trash_ptr;
//    trash = (struct WORD*)malloc(sizeof(struct WORD));//used to dump unecessary repeated roots

    if ((child == root && child ->RIGHT->flag==1 && child ->flag != 1))//leaf node and print
    {
            while(*(child->word + i) != NULL)
        {
            fprintf(output,"%c",*(child->word + i));
            i++;
        }


        if (*(child->word) != NULL)
        {

            for (j=0;j <= child->linearr_index;j++)
                fprintf(output,"\t %d",child->linearr[j]);

            fprintf(output,"\n\n");
        }

        child ->flag = 1;
        temp = root;

        print_tree(temp,root);

    }
    if ((child ->RIGHT==NULL && child ->LEFT==NULL))//leaf node and print
    {
            while(*(child->word + i) != NULL)
        {
           fprintf(output,"%c",*(child->word + i));
            i++;
        }

        if (*(child->word) != NULL)
              {
                for (j=0;j <= child->linearr_index;j++)
                    fprintf(output,"\t %d",child->linearr[j]);

                fprintf(output,"\n\n");
              }

        child ->flag = 1;
        temp = root;

        print_tree(temp,root);

    }

    else if (child ->RIGHT!=NULL && child ->LEFT!=NULL)
    {
        if(child ->RIGHT->flag==1 && child ->LEFT->flag==1)
        {
            if(child->flag == 1)
                return;

                while(*(child->word + i) != NULL)
            {
                fprintf(output,"%c",*(child->word + i));
                i++;
            }//end while


            if (*(child->word) != NULL)
              {
                  for (j=0;j <= child->linearr_index;j++)
                    fprintf(output,"\t %d",child->linearr[j]);

                fprintf(output,"\n\n");
              }

            child ->flag = 1;
            temp = root;

            print_tree(temp,root);
        }//end if

    }//end else if


    if (child->RIGHT!= NULL)
    {
        if (child ->RIGHT->flag == 1 && child ->LEFT==NULL)
        {
                while(*(child->word + i) != NULL)
                {
                    fprintf(output,"%c",*(child->word + i));
                    i++;
                }//end while


                if (*(child->word) != NULL)
                  {
                    for (j=0;j <= child->linearr_index;j++)
                        fprintf(output,"\t %d",child->linearr[j]);

                    fprintf(output,"\n\n");
                  }

                child ->flag = 1;
                temp = root;

                print_tree(temp,root);

        }//end else if

        if (child ->RIGHT->flag != 1)
        {
            child = child -> RIGHT;
            print_tree(child,root);
        }

    }


    if (child->LEFT != NULL)
    {
        if (child ->RIGHT==NULL && child ->LEFT-> flag==1)
        {

                while(*(child->word + i) != NULL)
                {
                    fprintf(output,"%c",*(child->word + i));
                    i++;
                }//end while


                if (*(child->word) != NULL)
                  {
                    for (j=0;j <= child->linearr_index;j++)
                        fprintf(output,"\t %d",child->linearr[j]);

                    fprintf(output,"\n\n");
                  }

                child ->flag = 1;
                temp = root;
                print_tree(temp,root);


        }//end if

        if (child ->LEFT->flag != 1)
        {
            child = child -> LEFT;
            print_tree(child,root);
        }
    }



    return;
    fprintf(output,"\n\n");
}
