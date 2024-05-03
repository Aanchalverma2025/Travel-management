// HEADER FILES
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;

// CONSTANTS AND GLOBAL VARIABLES
const int V = 20;
string str[25];
string mode_of_transport;

// NODE STRUCTURE FOR HUFFMAN ENCODING
struct node
{
       int freq;
       char data;
       const node *child0, *child1;
       node(char d, int f = -1)
       {
              data = d;
              freq = f;
              child0 = NULL;
              child1 = NULL;
       }
       node(const node *c0, const node *c1)
       {
              data = 0;
              freq = c0->freq + c1->freq;
              child0 = c0;
              child1 = c1;
       }
       bool operator<(const node &a) const
       {
              return freq > a.freq;
       }
       void traverse(string code ="") const
       {
              if (child0 != NULL)
              {
                     child0->traverse(code + '0');
                     child1->traverse(code + '1');
              }
              else
              {
                     cout << code;
              }
       }
};
string dest="";

// HUFFMAN ENCODING FUNCTION
void huffmanCoding(string str)
{
       priority_queue<node> qu;
       int frequency[256];
       for (int i = 0; i < 256; i++)
              frequency[i] = 0;
       for (int i = 0; i < str.size(); i++)
       {
              frequency[int(str[i])]++;
       }
       for (int i = 0; i < 256; i++)
       {
              if (frequency[i])
              {
                     qu.push(node(i, frequency[i]));
              }
       }
       while (qu.size() > 1)
       {
              node *c0 = new node(qu.top());
              qu.pop();
              node *c1 = new node(qu.top());
              qu.pop();
              qu.push(node(c0, c1));
       }
       cout <<endl<<"\t\t   TICKET ID : ";
       qu.top().traverse();
}


// FUNCTIONALITIES FOR USER REGISTRATION AND LOGIN
class Register
{
       char password[20], u_name[20];

public:
       bool tag;
       void signup();
       int Login();
};
struct station_code
{
       string station_name;
       int code;
};
struct station_code station[V];
struct node1
{
       vector<float> p;
} P[V];
float graph[V][V];
void Path(float distance, int e, int st, int inter);
int distance_min(float distance[], bool visited[]);
void dijkstra(float graph[V][V], int src, int targ);
void take_input();
void redirect();
void time_effective();
void cost_effective();

int j, satisfy = 0;
int compute[20][2], r = 0;

// SIGNUP FUNCTION
void Register::signup()
{
      // system("clear");
       cout << "\t\t\t\t~~~~~~~";
       cout << "\n\t\t\t\t    SIGN-UP";
       cout << "\n\t\t\t\t~~~~~";
       int p = 0, q = 0, r = 0;
a1:
       cout << "\n\nEnter a valid username (only characters allowed) : ";
       cin >> u_name;
       for (int i = 0; u_name[i] != '\0'; i++)
       {
              if (!(u_name[i] >= 'a' && u_name[i] <= 'z' || u_name[i] >= 'A' && u_name[i] <= 'Z'))
              {
                     cout << "\nInvalid Username!!Enter only characters...";
                     goto a1;
              }
       }
       cout << "\nSet your Password : ";
       cin >> password;
       ofstream myfile;
       myfile.open("LOGIN.txt", ios::app);
       if (myfile.is_open())
       {
              myfile << u_name << "  " << password << "\n";
              myfile.close();
              cout << "\nSIGN-UP SUCCESSFULL...";
              cout << "\nEnter any key to go back to the main page...";
              cin.get();
       }
       else
              cout << "Could not write to file...";
}

// LOGIN FUNCTION
int Register::Login()
{
start:
       string user_name, pass;
       cout << "\t\t\t\t~~~~~";
       cout << "\n\t\t\t\t     LOGIN";
       cout << "\n\t\t\t\t~~~~~";
       cout << "\nUSERNAME : ";
       fflush(stdin);
       getline(cin,user_name);
       fflush(stdin);
       cout << "PASSWORD : ";
       fflush(stdin);
       getline(cin,pass);
       fflush(stdin);
       cin.get();
       ifstream fin;
       //int a = 0;
       fin.open("LOGIN.txt", ios::in);
       if (fin.is_open())
       {
              string line, word;
              while (!fin.eof())
              {
                     getline(fin, line);
                     size_t found = line.find(user_name);
                     size_t f = line.find(pass);
                     if (found != string::npos)
                     {
                            if (f != string::npos)
                            {
                                   cout << "\nLOGIN SUCCESSFULL...";
                                   cin.get();
                                   return 1;
                            }
                            else
                            {
                                   cout << "INVALID PASSWORD!! PLEASE TRY AGAIN...";
                                   cin.get();
                                   goto start;
                            }
                     }
              }
       }
       fin.close();
       return 0;
}

// READING DESTINATION NAMES FROM CITIES.TXT FILE
void destination()
{
       system("clear");
       cout << "\t\t     ~~~~~~~~~~~~";
       cout << "\n\t\t\t   WELCOME TO TRAVELCRAFTERS";
       cout << "\n\t\t   ~~~~~~~~~~~~";
       ifstream fin;
       int n, i = 0;
       fin.open("CITIES.txt", ios::in);
       if (fin.is_open())
       {
              string line;
              cout << endl;
              cout << "\n--------------------";
              cout << "\nDESTINATIONS CATALOG";
              cout << "\n--------------------";
              cout << "\nINDEX   CITY NAME\n";
              while (getline(fin, line))
              {
                     cout << i << "      " << line;
                     str[i] = line;
                     cout << endl;
                     i++;
              }
       }
       fin.close();
}

// FUNCTION TO CAPITALIZE USER INPUT OF START AND END STATION
string capitalize(string str)
{
       for (int i = 0; i < str.length(); ++i)
       {
              if (str[i] > 96 && str[i] < 123)
                     str[i] = str[i] - 32;
       }
       return str;
}

// FUNCTION TO GENERATE PATH
void Path(float dis, int dest, int st, int inter)
{
       int t = dest, s;
       static float distance = 0;
       distance += dis;
       cout << "THE SHORTEST PATH IS : ";
       static int pos_x = 12;
       static int pos_y = 15;
       vector<int> path;
       path.push_back(t);
       while (t != st)
       {
              s = P[t].p.size();
              t = P[t].p[s - 1];
              path.push_back(t);
       }
       vector<int>::iterator i = path.end();
       string str;
       if (!inter)
       {
              cout << "* ROUTE FOUND *";
              satisfy = 1;
       }
       vector<int>::iterator i2 = path.end();
       i2--;
       int n_of_stations = 0;
       while (i != path.begin())
       {
              i--;
              str = station[*i].station_name;
              if (pos_x + 5 + str.size() < 106)
              {
                     cout << " ->> " << str;
                     satisfy = 1;
              }
              else
              {
                     cout << " ->> " << str;
                     satisfy = 1;
              }
       }
       if (inter)
       {
              cout << "\nDO YOU WANT TO SEARCH AGAIN ? (Yes/No) ";
              string choice;
              cin >> choice;
              choice = capitalize(choice);
              if (choice == "Y" || choice == "YES")
              {
                     take_input();
              }
              else
              {
                     redirect();
              }
       }
}

// USING HUFFMAN ENCODING TO GENERATE CODE FOR TICKET
void gen_code()
{

       string str;
       int luggage, people;
       string date;
       int freq[100];
       cout << "Enter Name: ";
       fflush(stdin);
       getline(cin,str);
       fflush(stdin);
       cout << "Enter the weight of the luggage: ";
       cin >> luggage;
       cout << "Enter the number of people travelling: ";
       cin >> people;
       cout << "Enter the date of travel: ";
       cin >> date;
       int n = sizeof(str);
       cout << "\n\t||~~~~~~~~~~~~~||";
       cout << "\n\t\t        TICKET          ";
       cout << "\n\t||~~~~~~~~~~~~~||\n";
       huffmanCoding(str);
       cout << "\n                   NAME      :     ";
       cout << str;
       cout << "\n                   LUGGAGE   :     ";
       cout << luggage;
       cout << "\n                   PEOPLE    :     ";
       cout << people;
       cout << "\n                   DATE      :     ";
       cout << date;
       cout<<"\n           MODE OF TRANSPORT :  "<<mode_of_transport;
       cout << "\n\n\t||~~~~~~~~~~~~~||\n";

}
int distance_min(float distance[], bool visited[])
{
       float min = INT_MAX;
       int min_index;
       for (int v = 0; v < V; v++)
       {
              if (visited[v] == false && distance[v] <= min)
              {
                     min = distance[v];
                     min_index = v;
              }
       }
       return min_index;
}
void dijkstra(float graph[V][V], int src, int targ, int inter)
{
       float distance[V];
       bool visited[V];
       for (int i = 0; i < V; i++)
       {
              distance[i] = INT_MAX;
              visited[i] = false;
       }
       distance[src] = 0;
       for (int count = 0; count < V - 1; count++)
       {
              int u = distance_min(distance, visited);
              visited[u] = true;
              for (int v = 0; v < V; v++)
              {
                     if (!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                     {
                            distance[v] = distance[u] + graph[u][v];
                            compute[r][0] = v;
                            compute[r][1] = u;
                            r++;
                            P[v].p.push_back(u);
                     }
              }
       }
       Path(distance[targ], targ, src, inter);
}

// FUNCTION TO TAKE INPUT FOR STARTING POINT AND DESTINATION POINT FROM USER
void take_input()
{
       string startStation, endStation, line, col;
       int startcode, endcode;
       cout << "\n\t\t||~~~DETERMINATION OF PATH~~~||";
       cout << "\n\nENTER THE STARTING POINT:";
       cin>>startStation;
       cout << "ENTER THE DESTINATION POINT:";
       cin>>endStation;
       startStation = capitalize(startStation);
       endStation = capitalize(endStation);
       // Convert user input to uppercase for case-insensitive comparison
  	   //transform(startStation.begin(), startStation.end(), startStation.begin(), ::toupper);
       //transform(endStation.begin(), endStation.end(), endStation.begin(), ::toupper);
       int flag_start = 0, flag_end = 0;
       for (int i = 0; i < 20; i++)
       {
              if (station[i].station_name == startStation)
              {
                     startcode = station[i].code;
                     flag_start = 1;
              }
              if (station[i].station_name == endStation)
              {
                     endcode = station[i].code;
                     flag_end = 1;
              }
       }
       int fault = 0;
       if (flag_start == 0)
       {
              cout << "WRONG STARTING STATION NAME ENTERED\n";
              fault = 1;
       }
       if (flag_end == 0)
       {
              cout << "WRONG DESTINATION STATION NAME ENTERED";
              fault = 1;
       }
       if (fault)
       {
              take_input();
              return;
       }
       dijkstra(graph, startcode, endcode, 1);
}
void time_effective()
{
       int flight_time[20][20], train_time[20][20], cab_time[20][20];
       for (int i = 0; i < V; i++)
       {
              for (int j = 0; j < V; j++)
              {
                     flight_time[i][j] = rand() % 10;
                     train_time[i][j] = rand() % 10;
                     cab_time[i][j] = rand() % 10;
                     if (flight_time[i][j] == 0)
                            flight_time[i][j] = j + 1;
                     if (train_time[i][j] == 0)
                            train_time[i][j] = (j + 1) * 2;
                     if (cab_time[i][j] == 0)
                            cab_time[i][j] = (j + 1) * 4;
              }
       }
       int t1 = 0, t2 = 0, t3 = 0;
       for (int i = 0; i < r; i++)
       {
              t1 += flight_time[compute[i][0]][compute[i][1]];
              t2 += train_time[compute[i][0]][compute[i][1]];
              t3 += cab_time[compute[i][0]][compute[i][1]];
       }
       if (t1 <= t2 && t1 <= t3)
       {
              cout << "Preferred Mode of transport is flight";
              cout<<"\nThe minimum time of your journey will be "<<t1<<" min";
              mode_of_transport="Flight";
       }
       else if (t2 <= t1 && t2 <= t3)
       {
              cout << "Preferred Mode of transport is train";
              cout<<"\nThe minimum time of your journey will be "<<t2<<" min";
              mode_of_transport="Train";
       }
       else
       {
              cout << "Preferred Mode of transport is cab";
              cout<<"\nThe minimum time of your journey will be "<<t3<<" min";
              mode_of_transport="Cab";
       }
}
void cost_effective()
{
       int flight_cost[20][20], train_cost[20][20], cab_cost[20][20];
       for (int i = 0; i < V; i++)
       {
              for (int j = 0; j < V; j++)
              {
                     flight_cost[i][j] = rand() % 100;
                     train_cost[i][j] = rand() % 100;
                     cab_cost[i][j] = rand() % 100;
                     if (flight_cost[i][j] == 0)
                            flight_cost[i][j] = j + 1;
                     if (train_cost[i][j] == 0)
                            train_cost[i][j] = (j + 1) * 2;
                     if (cab_cost[i][j] == 0)
                            cab_cost[i][j] = (j + 1) * 4;
              }
       }
       int c1 = 0, c2 = 0, c3 = 0;
       for (int i = 0; i < r; i++)
       {
              c1 += flight_cost[compute[i][0]][compute[i][1]];
              c2 += train_cost[compute[i][0]][compute[i][1]];
              c3 += cab_cost[compute[i][0]][compute[i][1]];
       }
       if (c1 <= c2 && c1 <= c3)
       {
            cout << "Preferred Mode of transport is flight";
            cout<<"\nThe minimum cost of your journey will be "<<c1<<" Rupees";
            mode_of_transport="Flight";
       }
       else if (c2 <= c1 && c2 <= c3)
       {
              cout << "Preferred Mode of transport is train";
              cout<<"\nThe minimum cost of your journey will be "<<c2<<" Rupees";
              mode_of_transport="Train";
       }
       else
       {
              cout << "Preferred Mode of transport is cab";
              cout<<"\nThe minimum cost of your journey will be "<<c3<<" Rupees";
              mode_of_transport="Cab";
       }
}


void exit_program()
{
       cout << "\n~~~~~~~~~~~~~~~";
       cout << "\n              THANK YOU :))";
       cout << "\n~~~~~~~~~~~~~~~";
       exit(0);
}
void redirect()
{
       int x, num;
       cout << "\t\t      ~~~~~~~~~~~~";
       cout << "\n\t\t\t      TRAVELCRAFTERS";
       cout << "\n\t\t    ~~~~~~~~~~~~";
       cout << "\nUSE:\n1.Shortest Path\n2.Plan Journey\n3.Generate Ticket\n4.Exit\n";
       cout << "\nEnter your choice:";
       cin >> x;
       switch (x)
       {
       case 1:
       {
              destination();
              int temp, n1, n2;
              float dis;
              ifstream fin;
              ifstream code;
              code.open("CITIES.txt");
              fin.open("DIST_VALUES.txt");
              for (int i = 0; i < 20; ++i)
              {
                     for (int j = 0; j < 20; ++j)
                            graph[i][j] = 0;
              }
              for (int i = 1; i <= V; ++i)
              {
                     fin >> temp;
                     fin >> n1;
                     for (int j = 0; j < temp; ++j)
                     {
                            fin >> n2;
                            fin >> dis;
                            graph[n1 - 1][n2 - 1] = dis;
                     }
              }
              string line, col;
              dest=line;
              for (int i = 0; i < V; ++i)
              {
                     getline(code, line);
                     station[i].code = i;
                     station[i].station_name = line;
              }
              take_input();
              code.close();
              fin.close();
       }
       break;
       case 2:
              while (1)
              {
                     //system("cls");
                     cout << "\nChoose your preference\nUSE:\n1.Time-Effective\n2.Cost-Effective\n3.Exit";
                     cout << "\nEnter your choice:";
                     cin >> num;
                     switch (num)
                     {
                     case 1:
                            if (satisfy == 0)
                                   cout << "First determine the shortest path!!";
                            else
                                   time_effective();
                            break;
                     case 2:
                            if (satisfy == 0)
                                   cout << "First determine the shortest path!!";
                            else
                                   cost_effective();
                            break;
                     case 3:
                            redirect();
                            break;
                     default:
                            cout << "Please enter a valid number!!";
                     }
                   //  getch();
              }
              break;
       case 3:
              gen_code();
              break;
       case 4:

              exit_program();
              break;
       default:
              cout << "Please enter a valid number!!";
       }
      // getch();
}
int main()
{

       int c, choice, d = 0;
       Register r;
start:
       //system("cls");
       cout << "\t\t   ~~~~~~~~~~~~~~~";
       cout << "\n\t\t\tWELCOME TO TRAVELCRAFTERS";
       cout << "\n\t\t ~~~~~~~~~~~~~~~";
       cout << "\nUSE:\n1.Login\n2.Sign-Up ";
       cout << "\nEnter your choice : ";
       cin >> choice;
       switch (choice)
       {
       case 1:
       {
              d = r.Login();
              if (d == 1)
              {
                     redirect();
              }
              else
              {
                     cout << "\nINVALID USER !!";
                     cout << "\nYou need to sign-up firstly...\nPress any key to go back to the main window...";
                     cin.get();
                     goto start;
              }
       }
       break;
       case 2:
       {
              r.signup();
              cout << "Press any key to go back to the main window...";
              cin.get();
              goto start;
       }
       default:
              cout << "\nINVALID INPUT...";
       }
       return 0;
}
