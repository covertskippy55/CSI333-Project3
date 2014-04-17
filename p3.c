/*
   Ryan Wood RW422598 Lab: Friday 11:30
   The functions I wrote were adc, prp, pvp, psc, end. Me and Dilan 
   emailed the p3.c file after back and forth doing some of our 
   assigned functions each time, as well as the writing of the main and 
   debugging. I ran the test cmd's supplied by Proffessor Ravi and got 
   positive outputs and manually tested my functions that have specific  
   cases in order to work completely.
*/
/*
  Dilan Samarasinghe DS697678 Lab: Friday 11_30
  I wrote the dex,der,plc,prd and prc. We each wrote the test cases for
  our own functions. Writing the main and debugging it was shared by doing one part of the
  main at a time as we finished each function. Testing of various values including zero, numbers
  not included in the polynomial as well as ofcorse numbers included in the polynormial were tested
  Testing on null was also done and it works fine.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# define MAX 3

char cmd[MAX];
struct node *head;
void adc(int, int);                       // prototypes
void dex(struct node **head, int value);
void der(int start, int end);
void prp();
int pvp(int val);
void prd(struct node *head);
void prc(struct node *head, int value);
void plc(struct node *head);
int psc();

struct node
{
 int coef;
 int exp;
 struct node *next;
};

int main(void)
{
  int firstCommand;
  int secondCommand;
  printf("Command?\n ");
  fflush(stdout);
  scanf("%s", cmd);
/*
while loop that runs as long as "end" isnt inputed and then checks to see 
if the cmd is and of the functions by using strcmp and if they are it runs 
the designated function making sure to take in the vaiables as well if 
they are needed with that specific function.
*/ 
  while(strcmp(cmd, "end") != 0)
    {
      if(strcmp(cmd,"adc") == 0)
	{
          scanf("%d %d", &firstCommand, &secondCommand);
	  adc(firstCommand,secondCommand);
	}
      else if(strcmp(cmd,"dex") == 0)
	{
          scanf("%d", &firstCommand);
	  dex(&head,firstCommand);
	}
      else if(strcmp(cmd,"der") == 0)
	{
	  scanf("%d %d",&firstCommand,&secondCommand);
	  der(firstCommand,secondCommand);
	}
      else if(strcmp(cmd, "prp") == 0)
        {
          prp();
          printf("\n");
          fflush(stdout);
        }
      else if(strcmp(cmd, "pvp") == 0)
        {
          scanf("%d", &firstCommand);
          pvp(firstCommand);
          printf("\n");
        }
      else if(strcmp(cmd, "psc") == 0)
        {
         psc();
         printf("\n");
         fflush(stdout);
        }
      else if(strcmp(cmd, "prd") == 0)
        {
	  prd(head);
        }
      else if(strcmp(cmd, "prc") == 0)
        {
          scanf("%d",&firstCommand);
	  prc(head, firstCommand);
        }
      else if(strcmp(cmd, "plc") == 0)
        {
          plc(head);
        }

      printf("Next Command? \n ");
      fflush(stdout);
      scanf("%s", cmd);

    }  
  return 0;
}


/* This function adds a node to the polynomial list keeping the exponents 
in decreasing order and deletes a node if the coefficient adds to 0 when the 
exponents are the same.
*/
void adc(int iCoef, int iExp)
{
/* Creates a temp node pointing to the start of the linked list as well 
 as the new node that will be added 
*/
 struct node *temp = head;
 struct node *newNode;
 
 if((newNode = (struct node *)malloc(sizeof(struct node))) == NULL)
 {
  exit(1);
 }

/*
Puts the data within the node equal to the user's input of the exponent 
and coefficient.
*/
 newNode->exp = iExp;
 newNode->coef = iCoef;
 newNode->next = NULL;

/*
  If statement that checks if the list is empty or if the exponent is 
  greater then the first node and appends the list.
*/
 if(head == NULL || iExp > head->exp)
 {
  newNode->next = head;
  head = newNode;
  return;
 }
 
/*
While statement that checks if the node is not the last one and if the 
node infront of temp is greater than or equal to the inputed exponent. If 
so it increments to the next node 
*/
 while(temp->next != NULL && temp->next->exp >= iExp)
 {
  temp = temp->next;
 }

/* If statement that checks if the temp exponent is equal to the exponent 
inputed and if so adds the coefficients together rather then adding a 
whole new node. Also checks to see if after the coefficient is added, if 
it equals zero, it then deletes the node.
*/ 
 if(temp->exp == iExp)
 {
  temp->coef += iCoef;
  if(temp->coef == 0)
  {
   dex(&head,temp->exp);
  }
  return;
 }
 
/*
  Sets the next pointer of the new node to temps next and then sets temps 
  next equal to the new node thus adding the new node to the list. 
*/
 newNode->next = temp->next;
 temp->next = newNode;
 
}

/*
  This function takes in a int value thats the exponent and a pointer to the head of the linked list and if the value sepecified is foun in a node, removes that node.
*/
void dex(struct node **headp, int value){
  struct node *currentp, *prevp; // temporary node pointers
  prevp = NULL; // we set the previous to be null because theres no node before the head node
  // we start from the head node and work all the way until the end node is met, we also move the
  // previous pointer along with the current one
  for(currentp = *headp;currentp != NULL; prevp = currentp, currentp = currentp->next){
    if(currentp->exp == value){  // we check if the exponent of the current node match the one given
      if(prevp == NULL){ // we must also check to see if previous is null because that means this is the first node, if it is we set head to be next node
	*headp = currentp->next;
      }
      // otherwise we use the previous node  and set the next value to be the next of the current node
      else{
	prevp->next = currentp->next;
      }
      free(currentp);
      
    }
  }
}
/* This function takes in two int values and deletes any nodes that is between the two values given.
 */

void der(int start, int end){
  int i;
  // we use the i variable to store the start value and we use a for loop to work through the exponents till we reach the last exponenet, each time we call the dex function with the exponenet value.
  
  for(i = start; i <= end; i++)
    {
      dex(&head,i);
    }
}

/* 
   This function prints out the polynomial. If the polynomial is empty it 
   prints out 0x^0.
*/
void prp()
{
 /* Creates temp node */
 struct node *temp;

/* If list is empty prints 0x^0 */
 if(head == NULL)
 {
  printf("0x^0 \n");
  fflush(stdout);
 }

/*
  If the list is not empty, the for loop loops through the linked list and 
  checks the following cases to make sure it prints each polynomial with 
  the correct + and - signs before and after each node.
*/
 else if(head != NULL)
 {
  for(temp = head; temp != NULL; temp = temp->next)
  {
/* 
If the next node is empty print the ndoe with a + or - sign following 
it
*/
   if(temp->next == NULL)
   {
    printf("%d x^%d", temp->coef, temp->exp);
    fflush(stdout);
   }
/* Checking if the nodes next coefficients is positive and if so puts a + 
sign after it.
*/
   else if(temp->next->coef > 0)
   {
    printf("%d x^%d +", temp->coef, temp->exp);
    fflush(stdout);
   }
/* 
Checks to see if the nodes next coefficients is negative and if so 
doesn't print any sign because the minus sign is aleady there
*/
   else if(temp->next->coef < 0)
   {
    printf("%d x^%d ", temp->coef, temp->exp);
    fflush(stdout);
   }
  }
 }
}

/* 
This function prints out the value of the polynomial when setting the x 
to whatever the user wants
*/
int pvp(int val)
{
/* 
Creates a temp pointer to loop through linked list and initiates ints 
to help calulate the power with using power function from math.lib
*/
 struct node *temp;
 int i;
 int eVal = 1;
 int wVal = 0;
 int pVal = 0;
 for(temp = head;temp != NULL; temp = temp->next)
 {
/* 
For loop that runs as many times as the exponent and multiplys whatever 
the user inputed by itself that many times.
*/
  for(i=0; i < temp->exp; i++)
  {
   eVal *= val;
  }
/*
  Then multiplies the exponent value with the coefficient to get the total 
value of the node and adds it to pVal to keep track of the whole value of 
the polynomial. Resets eVal to 1 and prints out total value.
*/
  wVal = temp->coef * eVal; 
  pVal += wVal;
  eVal = 1;
 }

 printf("%d", pVal);
 return 0;
}

/* This function prints out the node with the smallest coefficient
*/

int psc()
{
/* Prints 0 if list is empty */
 if(head == NULL)
   {
     printf("%i \n", 0);
     return 0;
   }
 else{
/*
Creates a temp node to loop through list and sets sCoef = to the first 
nodes coeff
*/
 struct node *temp;
 int sCoef = head->coef;

 for(temp = head; temp != NULL; temp = temp->next)
 {
/* 
Checks to see if temps coeff is less than sCoeff, if so it sets sCoeff 
to that thus getting the smallest coefficient as it loops through the list
*/
  if(temp->coef < sCoef)
  {
   sCoef = temp->coef;
  }
 } 
 printf("%d", sCoef);
 return 0;
 }
}

/* This function takes in a pointer to a list and prints 0 if the list is empty or prints the value of the highest exponenet
 */
void prd(struct node *head){
  if(head == NULL) printf("%i \n", 0); // if list is empty print 0
  else printf("%i \n", head->exp); // otherwise print the exponent of the first node
}
/* This function takes in a pointer to a list and a exponent value, then prints the coefficient of the exponenet given, if the exponenet doesnt exist it prints 0.
 */
void prc(struct node *head, int value){
 struct node *temp;
 // work throgh the list until you hit a null node
    for(temp = head; temp != NULL; temp = temp->next)
      { // if we find the given exponent print the coefficient
	if(temp->exp == value )
	  {
	    printf("%i \n", temp->coef);
	    return;
	  }
	 
      }
    printf("%i \n", 0);
}

/* This function takes in a pointer to list and prints the largest coeeficent, if the list is empty prints 0
 */
void plc(struct node *head){
  struct node *temp;
  int lCoef; // keeps track of the largest coefficient
  if(head == NULL){ // if list is empty print 0 and return
    printf("%i \n", 0);
    return;
  }
  else{
    // set lCoef to the coefficint of the head
    lCoef = head->coef;
    // standard loop till null
    for(temp = head; temp != NULL; temp = temp->next){
      if(temp->coef > lCoef){ // if the current coefficinet is bigger set lCoef to be that value 
	lCoef = temp->coef;
      }
  
    }
    printf("%i \n", lCoef);

  }


}
