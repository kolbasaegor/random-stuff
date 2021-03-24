#include <stdio.h>
#include <string.h>


int equal_string(char str1[100], char str2[100]){              //This function checks whether strings match
	int flag = 1;
	for(int i = 0; str1[i] != NULL | str2[i] != NULL; i++){
		if(str1[i] != str2[i]){
			flag = 0;
			break;
		}
	}
	return flag;
}

typedef struct Book{   //Structure for books. changed to just book using typedef
	int nonEmpty;      //This variable checks whether the book was deleted(1 - no; 0 -Yes)
	char title[60];
	char author[50];
	int year;
	float book_rate;
} book;

struct customer{       //Structure for customer
	int nonEmpty;      //This variable checks whether the customer was deleted(1 - no; 0 -Yes)
	char name[50];
	int age;
	float customer_rate;
};



int tmp = 0;        //The degree of occupancy of the array of books
book myBook[100];   //Creating a global variable for storing books
int tmp_c = 0;      //The degree of occupancy of the array of customers
struct customer myCustomer[100]; //Creating a global variable for storing customers

void show_books(){  // Function for displaying all books on the screen
	int j = 1;
	printf("Here are all our books:\n");
	for(int i = 0; i<tmp;i++)
		if(myBook[i].nonEmpty){ //checks if the cell is not empty
			printf("%d)'%s' by %s (%d %f)\n", j,myBook[i].title, myBook[i].author, myBook[i].year, myBook[i].book_rate);
			j++;
		}
	printf("\n");
}

void show_customers(){ // Function for displaying all customers on the screen
	int j = 1;
	printf("Here are all our customers:\n");
	for(int i = 0; i<tmp_c;i++) //checks if the cell is not empty
		if(myCustomer[i].nonEmpty){
			printf("%d)%s %d %f\n", j,myCustomer[i].name, myCustomer[i].age, myCustomer[i].customer_rate);
			j++;	
		}
	printf("\n");
}

void add_book(){ //Function for adding a book
	myBook[tmp].nonEmpty = 1; //Marks the cell as filled in
	printf("Enter the book's title: ");
	gets(myBook[tmp].title); 
	gets(myBook[tmp].title);
	printf("Enter the book's author: ");
	gets(myBook[tmp].author);
	printf("Enter the book's year: ");
	scanf("%d", &(myBook[tmp].year));
	printf("Enter the book's rate: ");
	scanf("%f", &(myBook[tmp].book_rate));
	printf("The Book is added!\n\n");
	tmp++; //increasing the level of occupancy
}

void add_customer(){ //Function for adding a customer
	myCustomer[tmp_c].nonEmpty = 1; //Marks the cell as filled in
	printf("Enter the customer's name: ");
	gets(myCustomer[tmp_c].name); 
	gets(myCustomer[tmp_c].name);
	printf("Enter the customer's age: ");
	scanf("%d", &(myCustomer[tmp_c].age));
	printf("Enter the customer's rate: ");
	scanf("%f", &(myCustomer[tmp_c].customer_rate));
	printf("The Customer is added!\n\n");
	tmp_c++; //increasing the level of occupancy
}

void update_customer(){ //Function for updating a customer
	int flag = 0; //Checking the existence of such customer
	auto char name[50];
	printf("Enter the name of the customer you want to update: ");
	gets(name);
	gets(name);
	for(int i = 0; i<tmp_c;i++){
		if(myCustomer[i].nonEmpty){
			if(equal_string(myCustomer[i].name,name)){
				printf("We find %s\n", myCustomer[i].name);
				printf("Enter new customer's name: ");
				gets(myCustomer[i].name);
				printf("Enter new customer's age: ");
				scanf("%d", &(myCustomer[i].age));
				printf("Enter new customer's rate: ");
				scanf("%f", &(myCustomer[i].customer_rate));
				printf("The Customer is updated!\n\n");
				flag = 1; break; 
			}
		}
	}
	if(flag == 0) printf("We cant find this person\n\n");
}

void update_book(){ //Function for updating a book
	int flag = 0; //Checking the existence of such a book
	auto char title[60];
	printf("Enter the name of the book you want to update: ");
	gets(title);
	gets(title);
	for(int i = 0; i<tmp;i++){
		if(myBook[i].nonEmpty){
			if(equal_string(myBook[i].title,title)){
				printf("We find '%s' by %s (%d %f)\n", myBook[i].title, myBook[i].author, myBook[i].year, myBook[i].book_rate);
				printf("Enter new book's title: ");
				gets(myBook[i].title);
				printf("Enter new book's author: ");
				gets(myBook[i].author);
				printf("Enter new book's year: ");
				scanf("%d", &(myBook[i].year));
				printf("Enter new book's rate: ");
				scanf("%f", &(myBook[i].book_rate));
				printf("The Book is updated!\n\n");
				flag = 1; break; 
			}
		}
	}
	if(flag == 0) printf("We cant find this book\n\n");
}

void remove_book(){ //Function for deleting a book
	int flag = 0; //Checking the existence of such a book
	auto char title[60];
	printf("Enter the name of the book you want to remove: ");
	gets(title);
	gets(title);
	for(int i = 0; i<tmp;i++){
		if(myBook[i].nonEmpty){
			if(equal_string(myBook[i].title,title)){
				myBook[i].nonEmpty = 0; //remove book
				printf("The Book is removed!\n\n");
				flag = 1;
				break; 
			}
		}
	}
	if(flag == 0) printf("We cant find this book\n\n");
	
}

void remove_customer(){ //Function for deleting a customer
	int flag = 0; //Checking the existence of such a customer
	auto char name[50];
	printf("Enter the name of the customer you want to remove: ");
	gets(name);
	gets(name);
	for(int i = 0; i<tmp_c;i++){
		if(myCustomer[i].nonEmpty){
			if(equal_string(myCustomer[i].name,name)){
				myCustomer[i].nonEmpty = 0; //remove customer
				printf("The Customer is removed!\n\n");
				flag = 1;
				break; 
			}
		}
	}
	if(flag == 0) printf("We cant find this person\n\n");
	
}

void library(){ //core function
	system("color F0"); //change background color (just for fun)
	
	auto int choice = -1; 
	while(choice != 9){
		system("cls");
		printf("#########################################################################################\n#                                                                                       #\n#                                Welcome to the library!                                #\n#                                                                                       #\n#########################################################################################\n\n");
		printf("Here is our functionality:\n1 - Show Books\n2 - Add Book\n3 - Update Books\n4 - Remove Book\n5 - Show Customers\n6 - Add Customer\n7 - Update Customer\n8 - Remove Customer\n9 - Exit\n");
		printf("Please make your choice: ");
		scanf("%d", &choice);
		if(choice == 1) show_books();
		else if(choice == 2) add_book();
		else if(choice == 3) update_book();
		else if(choice == 4) remove_book();
		else if(choice == 5) show_customers();
		else if(choice == 6) add_customer();
		else if(choice == 7) update_customer();
		else if(choice == 8) remove_customer();
		else if(choice == 9) break;
		else printf("We don't have this function\n\n");
		printf("Press any button...\n");
		getch();
	}
	printf("#########################################################################################\n#                                                                                       #\n#                                Goodbye!                                               #\n#                                                                                       #\n#########################################################################################");
}

int main(){
	
	library();
	
	return 0;
}







