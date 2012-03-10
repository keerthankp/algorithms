/*
  Name of program: Sudoku Solver, Password Protected. :P. Just a little fancy thing. :P
  Programmer: Keerthan.
  Description: My C++ project for 11th.
*/

#include <iostream>
#include <conio.h>
#include <time.h>
#include <cstdlib>
#include <process.h>
#include <fstream>

#define inputfile "sudoku.dat" //Change filename of the Text file here.
#define passwd "lollol" //Change Password here.

using namespace std;

time_t now, later;//For Time delay function
int inputgrid[9][9];//Array for the input of the puzzle
int introc = 1;//To make sure Intro doesn't repeat
int flag;//Flag for Password

void sleep(int delay)//For Time Delay.
{
 now=time(NULL);
 later=now+delay;
 while(now<=later)
 now=time(NULL);
}

void intro()//Function For the Popup Messages at the beginning.
{
 	 cout<<"\t\t\tWelcome To Sudoku Solver!!"<<endl<<endl<<"\t\t\t   Program by Keerthan."<<endl<<endl;
 	 cout<<"Please enter your Unsolved Sudoku Puzzle and my program will solve it for you! :D"<<endl<<"Note: Enter 0 for a blank space."<<endl<<endl;
}


void textinput()//Function to Read from a File.
{
	int i,j;
	ifstream infromfile;
	infromfile.open(inputfile);

	if(!infromfile)
	{
	cout << "Cannot open file.\n";
	}

	for (i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
            infromfile >> inputgrid[i][j];
		}
	}

	infromfile.close();

}

void maninput()//Function for Manually entering Values.
{
        int i, j;
        char tmp;
        system("cls");
        cout<<"Enter Details manually.. Press x if you want to delete previous box!\n\n";
		for(i=0; i<9;i++)
		{
		 		 for(j=0; j<9; j++)
				  {
				   		  cout<<"Please Enter the value for Row "<<i+1<<" Column "<<j+1<<": ";

				   		  tmp = getch();
				   		  if (tmp == 'x'|| tmp == 'X')
				   		  {
				   		        if (j==0 && i>=0)
                                        {
                                            j = 7;
                                            i--;
                                            if(i>=0)
                                            cout<<"\n\nValue deleted.";
                                        }
                                else
                                        {
                                            j-=2;
                                            if(i>=0)
                                            {
                                                cout<<"\n\nValue Deleted.";
                                            }
                                        }
                                if(i<0)
                                        {
                                            cout<<"\n\nNo More values to delete!";
                                            i = 0;
                                            j = -1;
                                        }
				   		  }
                          else
                          {
                             {
                                 inputgrid[i][j] = tmp - 48;
                                 cout<<inputgrid[i][j];
                             }
                          }
                          cout<<endl;
				  }
        }
}

void output()//Prints the grid.
{
        for (int i = 0; i < 9; i++)
        {
            if (i == 3 || i == 6)
                {
                    cout << endl;
                    cout << "--------------------";
                }
            cout << " " << endl;
            for (int j = 0; j < 9; j++)
                {
                    if (j == 3 || j == 6)
                        {
                        cout << "|";
                        }
                    cout << " ";
                    cout << inputgrid[i][j];
                }
        }
}


int checkrow(int row, int col)//Checks for all sudoku conditions in a row.
{
        for (int i = 0; i < 9; i++)
		{
                if (i != col)
				{
                        if (inputgrid[row][i] == inputgrid[row][col] )
						{
                                return 0;
                        }
                }
        }

        return 1;
}


int checkcol(int row, int col)//Checks for all Sudoku conditions in a col.
{
        for (int i = 0; i < 9; i++)
		{
                if (i != row)
				{
                        if (inputgrid[i][col] == inputgrid[row][col] )
						{
                                return 0;
                        }
                }
        }
        return 1;
}


int checksquare(int row, int col)//Checks for all sudoku conditions in a box. (3x3)
{
        int vsquare = row/3;
        int hsquare = col/3;
        for (int i = vsquare * 3; i < (vsquare*3 + 3); i++)
		{
                for (int j = hsquare * 3; j < (hsquare*3 + 3); j++)
				{
                        if (i != row || j != col)
						{
                                if (inputgrid[ row ][ col ] == inputgrid[i][j])
								{
                                        return 0;
                                }
                        }
                }
        }
        return 1;
}


int solve(int row, int col)
{

         while (inputgrid[row][col] != 0)
         {
                col++;
                if(col > 8)
                {
                col = 0;
                row++;
                }
                if(row > 8)
                {
                    return 1;
                }
        }
        for (int n = 1; n < 10; n++)
        {
                int tryrow, trycol;
                inputgrid[row][col] = n;
                if ( checkcol(row, col)
                  && checkrow(row, col)
                  && checksquare(row, col))
                  {
                        trycol = col+ 1;
                        tryrow = row;
                        if(trycol > 8)
                        {
                            trycol = 0;
                            tryrow++;
                        }


                        if(tryrow > 8)
                        {
                                return 1;
                        }
                        if(solve(tryrow, trycol))
                        {
                            return 1;
                        }
                 }
        }
        inputgrid[row][col] = 0;
        return 0;
}

//End of Solving.

void password()
{
     string pass;
		char ch;
		char y;
		int pcount = 3;
		char ex;
        passwordr:
        pass="";
        pcount--;
        system("cls");
        cout << "Enter password: ";
        ch = getch();
        while(ch != 13)
        {
            pass.push_back(ch);
            cout << '*';
            ch = getch();
        }
        if(pass == passwd)
        {
            cout << "\nAccess granted :P\n";
            sleep(1);
            cout<<"Press any key to Continue.";
            getch();
            system("cls");
            flag = 1;
        }
        else
        {
            cout << "\t\t\nWrong Password :O\n";
            sleep(1);
            if(pcount!=0)
                {
                    cout<<"Please Try again.\n";
                    if(pcount==1)
                    cout<<"\n"<<pcount<<" attempt left.\n";
            else
                    cout<<"\n"<<pcount<<" attempts left.\n";
                    cout<<"Press any key to try again or x to exit.\n";
                    ex=_getch();
                    if(ex=='x'||ex=='X')
                    {
                        flag = 0;
                    }
                    system("cls");
                }
            if(pcount==0)
                {
                    system("cls");
                    flag = 0;
                }
            else
            {
                system("cls");
                goto passwordr;
            }
        }
}




int main()
{
        int x;
        password();
        if(flag == 0)
        goto endp;
        start:
        while(introc)
        {
            introc--;
            intro();
        }
        cout<<"\n\nDo you want to read from a Text file or Manually input the values? (t) or (m): ";
        char ch;
        ch = getch();
        cout<<ch;
        if(ch=='t'||ch=='T')
        {
            system("cls");
            textinput();
            output();
            char ay;
            cout<<"\n\nIs this the Puzzle? (y)es or (n)o. ";
            ay = getch();
            cout<<ay;
            if(ay=='n'||ay=='N')
            goto start;
        }
        else if(ch=='m'||ch=='M')
        {
            system("cls");
            maninput();
            output();
            char al;
            cout<<"\n\nIs this the Puzzle? (y)es or (n)o. ";
            al = getch();
            cout<<al;
            if(al=='n'||al=='N')
            goto start;
            else
            goto proc;

        }
        proc:
        char ax;
        cout<<endl<<endl;
        if(solve(0,0))
            {

                cout<<"Processing";
                for(int x=0; x<3; x++)
                {
                    cout<<".";
                    sleep(1);
                }
				cout<<endl<<endl<<"The Puzzle has been solved! Here is your solution! :D\n"<<endl;
                output();
                cout<<"\n\nPress s to enter another puzzle or any other key to Exit!\n\n";
                char y;
                y= getch();
                if(y =='s'||y=='S')
                    {
                        system("cls");
                        goto start;
                    }
                else
                    {
                        system("cls");
                        goto endp;
                    }
            }
		else
		{
                cout<<"Processing";
                for(int x=0; x<3; x++)
                {
                    cout<<".";
                    sleep(1);
                }
				cout<<"\n\nIt is not Possible :/";
                cout<<"\nPress s to enter another puzzle or any other key to Exit!\n";
                char y;
                y=_getch();
                if(y=='s'||y=='S')
                    {
                        system("cls");
                        goto start;
                    }
                else
                    {
                        system("cls");
                        goto endp;
                    }
        }
        cout << endl;
		getch();
		endp:
		for(int s=5; s>=1; s--)
		{
		 		system("cls");
		 		cout<<"Thank you for using Sudoku Solver.\nThis window will self destruct in: "<<s;
		 		sleep(0.5);
		}
        return 0;
}

/*************************************************************-PEACE-*****************************************************************/
