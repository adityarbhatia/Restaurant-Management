/**************************
 * Name: Adi Bhatia
 * Project: Lab with Linked Lists
 * Date: May 30, 2016
 * 
**************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	char name[20];
	int partySize;
	struct Node* next;
};

struct listNode
{
	struct Node* head;
	struct Node* tail;
};

//FUNCTION PROTOTYPES
void reserve();
void assign();
void show();
void quit();
int findCategory(int tableSize);
int findMatch(int category,int tableSize);
void pop(struct Node* temp, int category);
struct Node* getNewNode(char name[],int partySize);
void addNode(struct Node* temp);



//GLOBAL VARIABLES
struct listNode reservations[4];



int main(void)
{
	while(1)
	{
		char entry;
		if(entry != '\n')
		{
			printf("Welcome! \n\t To reserve, select R  \n\t\t To Assign, select A \n\t To show, select S \n\n To Quit, Select Q\n ");
		}
		scanf("%c",&entry);

		switch(entry)
		{
			case 'R':
			case 'r': reserve();
					  break;
			case 'A':
			case 'a': assign();
					  break;
			case 'S':
			case 's': show();
					  break;
			case 'Q':
			case 'q': quit();
					  return 0;
					  break;
			default:
					  break;
		}
	}

	return 0;
}


/*************************
*
*	RESERVATION FUNCTIONS
*
**************************/
void addNode(struct Node* temp)
{
	int ps = temp->partySize;
	if(ps >= 1 && ps <= 2)
	{
		if(reservations[0].tail == NULL)
		{
			reservations[0].tail = temp;
			reservations[0].head = temp;
		}
		else
		{
			reservations[0].tail->next = temp;
			reservations[0].tail = temp;
		}
	}
	else if(ps >=3 && ps <=4)
	{
		if(reservations[1].tail == NULL)
		{
			reservations[1].tail = temp;
			reservations[1].head = temp;
		}
		else
		{
			reservations[1].tail->next = temp;
			reservations[1].tail = temp;
		}
	}
	else if(ps >=5 && ps <=6)
	{
		if(reservations[2].tail == NULL)
		{
			reservations[2].tail = temp;
			reservations[2].head = temp;
		}
		else
		{
			reservations[2].tail->next = temp;
			reservations[2].tail = temp;
		}
	}
	else if(ps > 6)
	{
		if(reservations[3].tail == NULL)
		{
			reservations[3].tail = temp;
			reservations[3].head = temp;
		}
		else
		{
			reservations[3].tail->next = temp;
			reservations[3].tail = temp;
		}
	}
	return;
}
struct Node* getNewNode(char name[],int partySize)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->next = NULL;
	strcpy(temp->name,name);
	temp->partySize = partySize;

	return temp;
}
int checkName(char name[])
{
	int i;
	for(i=0;i<4;i++)
	{
		struct Node* temp = reservations[i].head;
		while(temp)
		{
			if(strcmp(temp->name,name) == 0)
			{
				return 1;
			}
			temp = temp->next;
		}
	}
	return 0;
}

void reserve()
{
	char name[20];
	int partySize;
	printf("Enter Name: ");
	scanf("%s",name);
	int a = checkName(name);
	if(a == 1)
	{
		printf("Reservation already Present\n");
		return;
	}
	printf("Enter Party Size: ");
	scanf("%d",&partySize);

	if(partySize < 1)
	{
		printf("Invalid Party Size!\n");
		return;
	}

	struct Node* temp = getNewNode(name,partySize);
	addNode(temp);
	printf("Reservation Accepted!\n");

	return;
}

/*************************
*
*	RESERVATION FUNCTIONS - END
*
**************************/

/*************************
*
*	SHOW FUNCTIONS
*
**************************/
void show()
{
	int i;
	for(i=0;i<4;i++)
	{
		struct Node* temp = reservations[i].head;
		printf("**************************\n");
		printf("Category %d:\n",i+1);
		printf("**************************\n");
		int count = 0;
		while(temp != NULL)
		{
			printf("===============\n");
			printf("Reservation %d\n:",count+1);
			printf("Name: %s\n",temp->name);
			printf("Party Size: %d\n",temp->partySize);
			printf("===============\n");
			temp = temp->next;
			count++;
		}
	}
	return;
}
/*************************
*
*	SHOW FUNCTIONS - END
*
**************************/

/*************************
*
*	QUIT FUNCTIONS
*
**************************/
void quit()
{
	int i;
	for(i=0;i<4;i++)
	{
		struct Node* temp = reservations[i].head;
		while(temp)
		{
			struct Node* prev = temp;
			temp = temp->next;
			free(prev);
		}
	}
	printf("All Memory Freed! Exiting Program...\n");
	return;
}
/*************************
*
*	QUIT FUNCTIONS - END
*
**************************/
/*************************
*
*	ASSIGN FUNCTIONS
*
**************************/
void pop(struct Node* temp, int category)
{
	struct Node* tmp = reservations[category].head;
	if(tmp == NULL)
	{
		return;
	}
	if(tmp == temp)
	{
		reservations[category].head = tmp->next;
		free(tmp);
		if(reservations[category].head == NULL)
		{
			reservations[category].tail = reservations[category].head;
		}
		return;
	}

	while(tmp->next != temp)
	{
		tmp = tmp->next;
	}
	tmp->next = tmp->next->next;
	free(temp);
	tmp = reservations[category].head;
	while(tmp->next)
	{
		tmp = tmp->next;
	}
	reservations[category].tail = tmp;

	return;

}
int findCategory(int tableSize)
{
	if(tableSize>=1 && tableSize<=2)
	{
		return 0;
	}
	else if(tableSize >=3 && tableSize <=4)
	{
		return 1;
	}
	else if(tableSize >=5 && tableSize <=6)
	{
		return 2;
	}
	else 
	{
		return 3;
	}

	return -1;
}
int findMatch(int category,int tableSize)
{
	struct Node* temp = reservations[category].head;
	if(temp == NULL)
	{
		reservations[category].tail = reservations[category].head;
		return -1;
	}
	while(temp)
	{
		if(tableSize == temp->partySize)
		{
			pop(temp,category);
			return 0;
		}
		temp = temp->next;
	}
	temp = reservations[category].head;

	int min_diff = 65536;
	struct Node* temp2 = NULL;
	while(temp)
	{
		if(tableSize - temp->partySize < min_diff && tableSize > temp->partySize)
		{
			min_diff = tableSize - temp->partySize;
			temp2 = temp;
		}
		
		temp = temp->next;
	}
	if(temp2 == NULL)
	{
		return -1;
	}
	else
	{
		pop(temp2,category);
		return 0;
	}
	
	return 2;
}
void assign()
{
	int tableSize;
	printf("Enter Table Size to Be Assigned: ");
	scanf("%d",&tableSize);
	if(tableSize < 1)
	{
		printf("Invalid Table Size, please reenter\n");
		return;
	}

	int category = findCategory(tableSize);

	int a = findMatch(category,tableSize);
	while(a == -1)
	{

		a = findMatch(category--,tableSize);
		if(category<0)
		{
			printf("No Possible Matching Reservations\n");
			return;
		}
	}

	return;
}
/*************************
*
*	ASSIGN FUNCTIONS - END
*
**************************/
