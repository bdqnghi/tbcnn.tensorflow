#include <iostream>
#include <fstream>

using namespace std;

ifstream RO("ROMANIA.txt");
ifstream GER("GERMANIA.txt");
ifstream ger_orders("GER_Orders.txt");
ifstream ger_locations("GER_Locations.txt");
ifstream ro_orders("RO_Orders.txt");
ifstream ro_locations("RO_Locations.txt");

#define max_orders 100

int m[50][50]; 
int n; 

void royfloyd(void);
void road(int i, int j);
void amat(void);


int main()
{
    int switch_mode;

    cout<<"Bun venit! Scopul acestui program este cel de a determina drumurile optime\
 pentru o companie de transporturi care are o lista de comenzi si un anumit numar de masini\
 dispuse pe o harta. In continuare, selectati din meniul de mai jos harta pe care doriti sa\
 desfasurati testarea:\n\n\
1. ROMANIA\n\
2. GERMANIA\n\
3. Harta custom\n\n\
Alegerea dumneavoastra: ";

    error_label_1:
    cin>>switch_mode;

    
    switch(switch_mode)
    {
        case 1: 
        {
            cout<<"Legenda ROMANIA:\n\n\
1. Alba Iulia: 14, 29, 35, 41, 23, 2, 5\n\
2. Arad: 5, 1, 23, 38\n\
3. Pitesti: 35, 8, 17, 37, 31, 41\n\
4. Bacau: 30, 40, 42, 16, 22\n\
5. Oradea: 33, 34, 14, 1, 2\n\
6. Bistrita: 29, 27, 14, 36\n\
7. Botosani: 36, 25\n\
8. Brasov: 29, 22, 16, 11, 32, 17, 3, 35\n\
9. Braila: 19, 39, 15, 24, 11, 42\n\
10. Bucuresti: 26\n\
11. Buzau: 16, 42, 9, 24, 32, 8\n\
12. Resita: 38, 23, 21, 28\n\
13. Calarasi: 26, 20, 24, 15\n\
14. Cluj-Napoca: 5, 34, 27, 6, 29, 1\n\
15. Constanta: 13, 24, 9, 39\n\
16. Sfantu Gheorghe: 22, 4, 42, 11, 8\n\
17. Targoviste: 8, 32, 26, 20, 37, 3\n\
18. Craiova: 28, 21, 41, 31\n\
19. Galati: 40, 42, 9, 39\n\
20. Giurgiu: 37, 17, 26, 13\n\
21. Targu Jiu: 12, 23, 41, 18, 28\n\
22. Miercurea Ciuc: 29, 36, 30, 4, 16, 8\n\
23. Deva: 38, 2, 1, 41, 21, 12\n\
24. Slobozia: 32, 11, 9, 15, 13, 26\n\
25. Iasi: 7, 36, 30, 40\n\
26. Buftea: 10, 17, 32, 24, 13, 20\n\
27. Baia Mare: 33, 34, 14, 6, 36\n\
28. Drobeta-Turnu Severin: 12, 21, 18\n\
29. Targu Mures: 14, 6, 36, 22, 8, 35, 1\n\
30. Piatra Neamt: 36, 25, 40, 4, 22\n\
31. Slatina: 18, 41, 3, 37\n\
32. Ploiesti: 17, 8, 11, 24, 26\n\
33. Satu Mare: 5, 34, 27\n\
34. Zalau: 5, 33, 27, 14\n\
35. Sibiu: 1, 29, 8, 3, 41\n\
36. Suceava: 27, 6, 29, 22, 30, 25, 7\n\
37. Alexandria: 31, 3, 17, 20\n\
38. Timisoara: 2, 23, 12\n\
39. Tulcea: 19, 9, 15\n\
40. Vaslui: 25, 4, 30, 42, 19\n\
41. Ramnicu Valcea: 23, 21, 18, 31, 3, 35, 1\n\
42. Focsani: 4, 16, 11, 9, 19, 40\n\n";


            int switch_mode_RO;
            cout<<"Bun venit in modul ROMANIA. Va rugam alegeti cum doriti sa importati\
 lista de comenzi si locatiile camioanelor:\n\n\
1. De la tastatura\n\
2. Din fisier\n\n\
Alegerea dumneavoastra: ";

            error_tag_RO:
            cin>>switch_mode_RO;

            switch(switch_mode_RO)
            {
                case 1: 
                {
                    RO>>n;

                    for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                            if(i == j) m[i][j] = 0;
                            else m[i][j] = 2017;


                    int counter; 
                    int x, y, z; 

                    RO>>counter;
                    for(int i = 1; i <= counter; i++)
                    {
                        RO>>x; 
                        RO>>y; 
                        RO>>z; 

                        m[x][y] = m[y][x] = z; 
                    }

                    int num_o, locations[n+2];
                    
                    


                    int num_trucks = 0; 
                    int num_locs = 0; 

                    
                    cout<<"\n\nIntroduceti numarul de comenzi: ";
                    cin>>num_o;


                    
                    
                    
                    int orders[3][num_o+2];

                    x = y = -1;

                    cout<<"Introduceti cele "<<num_o<<" comenzi dorite:\n\n";
                    for(int i = 1; i <= num_o; i++)
                    {
                        cout<<i<<". ";
                        cin>>x>>y;

                        orders[0][i] = x; 
                        orders[1][i] = y; 
                        orders[2][i] = -1; 
                    }

                    x = y = -1;

                    cout<<"\n\nIntroduceti locatii camioane:\n\n";
                    for(int i = 1; i <= n; i++)
                        locations[i] = 0;
                    while(x)
                    {
                        cin>>x>>y;
                        locations[x] = y;

                        num_trucks += y;
                        num_locs++;
                    }

                    

                    
                    
                    royfloyd();

                    if(num_trucks >= num_o)
                    {
                        int distances[num_o * num_locs+5][4], k = 0;

                        
                        
                        
                        
                        
                        for(int i = 1; i <= num_o; i++)
                            for(int j = 1; j <= n; j++)
                                if(locations[j])
                                {
                                    distances[++k][0] = m[orders[0][i]][j];
                                    distances[k][1] = orders[0][i];
                                    distances[k][2] = i;
                                    distances[k][3] = j;
                                }

                        
                        
                        int found, aux;
                        do
                        {
                            found = 0;
                            for(int i = 1; i < k; i++)
                            {
                                if(distances[i][0] > distances[i+1][0])
                                {
                                    aux = distances[i][0];
                                    distances[i][0] = distances[i+1][0];
                                    distances[i+1][0] = aux;

                                    aux = distances[i][1];
                                    distances[i][1] = distances[i+1][1];
                                    distances[i+1][1] = aux;

                                    aux = distances[i][2];
                                    distances[i][2] = distances[i+1][2];
                                    distances[i+1][2] = aux;

                                    aux = distances[i][3];
                                    distances[i][3] = distances[i+1][3];
                                    distances[i+1][3] = aux;

                                    found = 1;
                                }
                            }
                        }while(found);

                        
                        
                        
                        int check = 0;
                        for(int i = 1; i <= k; i++)
                        {
                            if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                            {
                                orders[2][distances[i][2]] = distances[i][3];
                                locations[distances[i][3]]--;
                                check++;
                            }
                            if(check == num_o)
                                break;
                        }

                        
                        
                        
                        cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";

                        for(int i = 1; i <= num_o; i++)
                        {
                            cout<<i<<": "<<orders[2][i]<<" ";
                            road(orders[2][i], orders[0][i]);
                            road(orders[0][i], orders[1][i]);
                            cout<<"\n";
                        }
                    }
                    else
                    {
                        
                        int times = num_o / num_trucks;
                        times++;

                        int distances[num_o * num_trucks+5][4], k = 0;
                        
                        
                        
                        
                        

                        int list_of_orders[num_trucks+3];
                        
                        

                        for(int current_iteration = 1; current_iteration <= times; current_iteration++)
                        {
                            
                            k = 0;
                            for(int i = 1; i <= num_o; i++)
                            {
                                if(orders[2][i])
                                    for(int j = 1; j <= n; j++)
                                        if(locations[j])
                                        {
                                            distances[++k][0] = m[orders[0][i]][j];
                                            distances[k][1] = orders[0][i];
                                            distances[k][2] = i;
                                            distances[k][3] = j;
                                        }
                            }

                            
                            
                            int found, aux;
                            do
                            {
                                found = 0;
                                for(int i = 1; i < k; i++)
                                {
                                    if(distances[i][0] > distances[i+1][0])
                                    {
                                        aux = distances[i][0];
                                        distances[i][0] = distances[i+1][0];
                                        distances[i+1][0] = aux;

                                        aux = distances[i][1];
                                        distances[i][1] = distances[i+1][1];
                                        distances[i+1][1] = aux;

                                        aux = distances[i][2];
                                        distances[i][2] = distances[i+1][2];
                                        distances[i+1][2] = aux;

                                        aux = distances[i][3];
                                        distances[i][3] = distances[i+1][3];
                                        distances[i+1][3] = aux;

                                        found = 1;
                                    }
                                }
                            }while(found);

                            
                            int assigned_trucks;
                            if(current_iteration < times) assigned_trucks = num_trucks;
                            else assigned_trucks = num_o % num_trucks;

                            
                            
                            
                            int check = 0;
                            for(int i = 1; i <= k; i++)
                            {
                                if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                                {
                                    orders[2][distances[i][2]] = distances[i][3];
                                    locations[distances[i][3]]--;
                                    list_of_orders[++check] = distances[i][2];
                                }
                                if(check == assigned_trucks)
                                    break;
                            }

                            if(current_iteration == 1)
                                cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";


                            for(int i = 1; i <= assigned_trucks; i++)
                            {
                                cout<<(current_iteration - 1)*num_trucks + i<<", "<<list_of_orders[i]<<": "<<orders[2][list_of_orders[i]]<<" ";
                                road(orders[2][list_of_orders[i]], orders[0][list_of_orders[i]]);
                                road(orders[0][list_of_orders[i]], orders[1][list_of_orders[i]]);
                                cout<<"\n";

                                
                                locations[orders[1][list_of_orders[i]]]++;
                                
                                orders[2][list_of_orders[i]] == 0;
                            }
                        }
                    }
                }
                break;
                case 2: 
                {
                    
                    RO>>n;

                    for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                            if(i == j) m[i][j] = 0;
                            else m[i][j] = 2017;


                    int counter; 
                    int x, y, z; 

                    RO>>counter;
                    for(int i = 1; i <= counter; i++)
                    {
                        RO>>x; 
                        RO>>y; 
                        RO>>z; 

                        m[x][y] = m[y][x] = z; 
                    }

                    int num_o, locations[n+2];
                    
                    


                    int num_trucks = 0; 
                    int num_locs = 0; 

                    
                    ro_orders>>num_o;

                    
                    
                    
                    int orders[3][num_o+2];

                    x = y = -1;

                    for(int i = 1; i <= num_o; i++)
                    {
                        ro_orders>>x>>y;

                        orders[0][i] = x; 
                        orders[1][i] = y; 
                        orders[2][i] = -1; 
                    }

                    x = y = -1;

                    for(int i = 1; i <= n; i++)
                        locations[i] = 0;

                    ro_locations>>num_locs;

                    for(int i = 1; i <= num_locs; i++)
                    {
                        ro_locations>>x>>y;

                        locations[x] = y;
                        num_trucks+=y;
                    }

                    

                    
                    
                    royfloyd();

                    if(num_trucks >= num_o)
                    {
                        int distances[num_o * num_locs+5][4], k = 0;

                        
                        
                        
                        
                        
                        for(int i = 1; i <= num_o; i++)
                            for(int j = 1; j <= n; j++)
                                if(locations[j])
                                {
                                    distances[++k][0] = m[orders[0][i]][j];
                                    distances[k][1] = orders[0][i];
                                    distances[k][2] = i;
                                    distances[k][3] = j;
                                }

                        
                        
                        int found, aux;
                        do
                        {
                            found = 0;
                            for(int i = 1; i < k; i++)
                            {
                                if(distances[i][0] > distances[i+1][0])
                                {
                                    aux = distances[i][0];
                                    distances[i][0] = distances[i+1][0];
                                    distances[i+1][0] = aux;

                                    aux = distances[i][1];
                                    distances[i][1] = distances[i+1][1];
                                    distances[i+1][1] = aux;

                                    aux = distances[i][2];
                                    distances[i][2] = distances[i+1][2];
                                    distances[i+1][2] = aux;

                                    aux = distances[i][3];
                                    distances[i][3] = distances[i+1][3];
                                    distances[i+1][3] = aux;

                                    found = 1;
                                }
                            }
                        }while(found);

                        
                        
                        
                        int check = 0;
                        for(int i = 1; i <= k; i++)
                        {
                            if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                            {
                                orders[2][distances[i][2]] = distances[i][3];
                                locations[distances[i][3]]--;
                                check++;
                            }
                            if(check == num_o)
                                break;
                        }

                        
                        
                        
                        cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";

                        for(int i = 1; i <= num_o; i++)
                        {
                            cout<<i<<": "<<orders[2][i]<<" ";
                            road(orders[2][i], orders[0][i]);
                            road(orders[0][i], orders[1][i]);
                            cout<<"\n";
                        }
                    }
                    else
                    {
                        
                        int times = num_o / num_trucks;
                        times++;

                        int distances[num_o * num_trucks+5][4], k = 0;
                        
                        
                        
                        
                        

                        int list_of_orders[num_trucks+3];
                        
                        

                        for(int current_iteration = 1; current_iteration <= times; current_iteration++)
                        {
                            
                            k = 0;
                            for(int i = 1; i <= num_o; i++)
                            {
                                if(orders[2][i])
                                    for(int j = 1; j <= n; j++)
                                        if(locations[j])
                                        {
                                            distances[++k][0] = m[orders[0][i]][j];
                                            distances[k][1] = orders[0][i];
                                            distances[k][2] = i;
                                            distances[k][3] = j;
                                        }
                            }

                            
                            
                            int found, aux;
                            do
                            {
                                found = 0;
                                for(int i = 1; i < k; i++)
                                {
                                    if(distances[i][0] > distances[i+1][0])
                                    {
                                        aux = distances[i][0];
                                        distances[i][0] = distances[i+1][0];
                                        distances[i+1][0] = aux;

                                        aux = distances[i][1];
                                        distances[i][1] = distances[i+1][1];
                                        distances[i+1][1] = aux;

                                        aux = distances[i][2];
                                        distances[i][2] = distances[i+1][2];
                                        distances[i+1][2] = aux;

                                        aux = distances[i][3];
                                        distances[i][3] = distances[i+1][3];
                                        distances[i+1][3] = aux;

                                        found = 1;
                                    }
                                }
                            }while(found);

                            
                            int assigned_trucks;
                            if(current_iteration < times) assigned_trucks = num_trucks;
                            else assigned_trucks = num_o % num_trucks;

                            
                            
                            
                            int check = 0;
                            for(int i = 1; i <= k; i++)
                            {
                                if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                                {
                                    orders[2][distances[i][2]] = distances[i][3];
                                    locations[distances[i][3]]--;
                                    list_of_orders[++check] = distances[i][2];
                                }
                                if(check == assigned_trucks)
                                    break;
                            }

                            if(current_iteration == 1)
                                cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";


                            for(int i = 1; i <= assigned_trucks; i++)
                            {
                                cout<<(current_iteration - 1)*num_trucks + i<<", "<<list_of_orders[i]<<": "<<orders[2][list_of_orders[i]]<<" ";
                                road(orders[2][list_of_orders[i]], orders[0][list_of_orders[i]]);
                                road(orders[0][list_of_orders[i]], orders[1][list_of_orders[i]]);
                                cout<<"\n";

                                
                                locations[orders[1][list_of_orders[i]]]++;
                                
                                orders[2][list_of_orders[i]] == 0;
                            }
                        }
                    }
                }
                break;
                default:
                    cout<<"ERROR. Retastati alegerea: ";
                    goto error_tag_RO;
            }

        }
        break;
        case 2: 
        {
            cout<<"Legenda GERMANIA:\n\n\
1. Berlin: 7, 5, 10, 2\n\
2. Hamburg: 1, 10\n\
3. Munchen: 8\n\
4. Koln: 5, 9, 7\n\
5. Frankfurt: 8, 4, 7, 1\n\
6. Essen: 7, 9\n\
7. Dortmund: 10, 1, 6, 4, 5\n\
8. Stuttgart: 3, 5\n\
9. Dusseldorf: 6, 4\n\
10. Bremen: 7, 2, 1\n\n";

            int switch_mode_GER;
            cout<<"Bun venit in modul GERMANIA. Va rugam alegeti cum doriti sa importati\
 lista de comenzi si locatiile camioanelor:\n\n\
1. De la tastatura\n\
2. Din fisier\n\n\
Alegerea dumneavoastra: ";

            error_tag_GER:
            cin>>switch_mode_GER;

            switch(switch_mode_GER)
            {
                case 1: 
                {
                    
                    GER>>n;

                    for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                            if(i == j) m[i][j] = 0;
                            else m[i][j] = 2017;


                    int counter; 
                    int x, y, z; 

                    GER>>counter;
                    for(int i = 1; i <= counter; i++)
                    {
                        GER>>x; 
                        GER>>y; 
                        GER>>z; 

                        m[x][y] = m[y][x] = z; 
                    }

                    int num_o, locations[n+2];
                    
                    

                    int num_trucks = 0; 
                    int num_locs = 0;

                    
                    cout<<"\n\nIntroduceti numarul de comenzi: ";
                    cin>>num_o;

                    
                    
                    
                    int orders[3][num_o+2];

                    x = y = -1;

                    cout<<"Introduceti cele "<<num_o<<" comenzi dorite:\n\n";
                    for(int i = 1; i <= num_o; i++)
                    {
                        cout<<i<<". ";
                        cin>>x>>y;

                        orders[0][i] = x; 
                        orders[1][i] = y; 
                        orders[2][i] = -1; 
                    }

                    x = y = -1;


                    


                    cout<<"\n\nIntroduceti locatii camioane:\n\n";
                    for(int i = 1; i <= n; i++)
                        locations[i] = 0;
                    while(x)
                    {
                        cin>>x>>y;
                        locations[x] = y;

                        num_trucks += y;
                        num_locs++;
                    }

                    

                    
                    
                    royfloyd();

                    if(num_trucks >= num_o)
                    {
                        int distances[num_o * num_locs+5][4], k = 0;

                        
                        
                        
                        
                        
                        for(int i = 1; i <= num_o; i++)
                            for(int j = 1; j <= n; j++)
                                if(locations[j])
                                {
                                    distances[++k][0] = m[orders[0][i]][j];
                                    distances[k][1] = orders[0][i];
                                    distances[k][2] = i;
                                    distances[k][3] = j;
                                }

                        
                        
                        int found, aux;
                        do
                        {
                            found = 0;
                            for(int i = 1; i < k; i++)
                            {
                                if(distances[i][0] > distances[i+1][0])
                                {
                                    aux = distances[i][0];
                                    distances[i][0] = distances[i+1][0];
                                    distances[i+1][0] = aux;

                                    aux = distances[i][1];
                                    distances[i][1] = distances[i+1][1];
                                    distances[i+1][1] = aux;

                                    aux = distances[i][2];
                                    distances[i][2] = distances[i+1][2];
                                    distances[i+1][2] = aux;

                                    aux = distances[i][3];
                                    distances[i][3] = distances[i+1][3];
                                    distances[i+1][3] = aux;

                                    found = 1;
                                }
                            }
                        }while(found);

                        
                        
                        
                        int check = 0;
                        for(int i = 1; i <= k; i++)
                        {
                            if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                            {
                                orders[2][distances[i][2]] = distances[i][3];
                                locations[distances[i][3]]--;
                                check++;
                            }
                        if(check == num_o)
                            break;
                        }

                        
                        
                        
                        cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";

                        for(int i = 1; i <= num_o; i++)
                        {
                            cout<<i<<": "<<orders[2][i]<<" ";
                            road(orders[2][i], orders[0][i]);
                            road(orders[0][i], orders[1][i]);
                            cout<<"\n";
                        }
                    }
                    else
                    {
                        
                        int times = num_o / num_trucks;
                        times++;

                        int distances[num_o * num_trucks+5][4], k = 0;
                        
                        
                        
                        
                        

                        int list_of_orders[num_trucks+3];
                        
                        

                        for(int current_iteration = 1; current_iteration <= times; current_iteration++)
                        {
                            
                            k = 0;
                            for(int i = 1; i <= num_o; i++)
                            {
                                if(orders[2][i])
                                    for(int j = 1; j <= n; j++)
                                        if(locations[j])
                                        {
                                            distances[++k][0] = m[orders[0][i]][j];
                                            distances[k][1] = orders[0][i];
                                            distances[k][2] = i;
                                            distances[k][3] = j;
                                        }
                            }

                            
                            
                            int found, aux;
                            do
                            {
                                found = 0;
                                for(int i = 1; i < k; i++)
                                {
                                    if(distances[i][0] > distances[i+1][0])
                                    {
                                        aux = distances[i][0];
                                        distances[i][0] = distances[i+1][0];
                                        distances[i+1][0] = aux;

                                        aux = distances[i][1];
                                        distances[i][1] = distances[i+1][1];
                                        distances[i+1][1] = aux;

                                        aux = distances[i][2];
                                        distances[i][2] = distances[i+1][2];
                                        distances[i+1][2] = aux;

                                        aux = distances[i][3];
                                        distances[i][3] = distances[i+1][3];
                                        distances[i+1][3] = aux;

                                        found = 1;
                                    }
                                }
                            }while(found);

                            
                            int assigned_trucks;
                            if(current_iteration < times) assigned_trucks = num_trucks;
                            else assigned_trucks = num_o % num_trucks;

                            
                            
                            
                            int check = 0;
                            for(int i = 1; i <= k; i++)
                            {
                                if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                                {
                                    orders[2][distances[i][2]] = distances[i][3];
                                    locations[distances[i][3]]--;
                                    list_of_orders[++check] = distances[i][2];
                                }
                                if(check == assigned_trucks)
                                    break;
                            }

                            if(current_iteration == 1)
                                cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";


                            for(int i = 1; i <= assigned_trucks; i++)
                            {
                                cout<<(current_iteration - 1)*num_trucks + i<<", "<<list_of_orders[i]<<": "<<orders[2][list_of_orders[i]]<<" ";
                                road(orders[2][list_of_orders[i]], orders[0][list_of_orders[i]]);
                                road(orders[0][list_of_orders[i]], orders[1][list_of_orders[i]]);
                                cout<<"\n";

                                
                                locations[orders[1][list_of_orders[i]]]++;
                                
                                orders[2][list_of_orders[i]] == 0;
                            }
                        }
                    }
                }
                break;
                case 2: 
                {
                    
                    GER>>n;

                    for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                            if(i == j) m[i][j] = 0;
                            else m[i][j] = 2017;


                    int counter; 
                    int x, y, z; 

                    GER>>counter;
                    for(int i = 1; i <= counter; i++)
                    {
                        GER>>x; 
                        GER>>y; 
                        GER>>z; 

                        m[x][y] = m[y][x] = z; 
                    }

                    int num_o, locations[n+2];
                    
                    

                    int num_trucks = 0; 
                    int num_locs = 0;

                    ger_orders>>num_o;

                    
                    
                    
                    int orders[3][num_o+2];

                    x = y = -1;

                    for(int i = 1; i <= num_o; i++)
                    {
                        ger_orders>>x>>y;

                        orders[0][i] = x; 
                        orders[1][i] = y; 
                        orders[2][i] = -1; 
                    }

                    x = y = -1;

                    for(int i = 1; i <= n; i++)
                        locations[i] = 0;

                    ger_locations>>num_locs;

                    for(int i = 1; i <= num_locs; i++)
                    {
                        ger_locations>>x>>y;

                        locations[x] = y;
                        num_trucks+=y;
                    }

                    

                    
                    
                    royfloyd();

                    if(num_trucks >= num_o)
                    {
                        int distances[num_o * num_locs+5][4], k = 0;

                        
                        
                        
                        
                        
                        for(int i = 1; i <= num_o; i++)
                            for(int j = 1; j <= n; j++)
                                if(locations[j])
                                {
                                    distances[++k][0] = m[orders[0][i]][j];
                                    distances[k][1] = orders[0][i];
                                    distances[k][2] = i;
                                    distances[k][3] = j;
                                }

                        
                        
                        int found, aux;
                        do
                        {
                            found = 0;
                            for(int i = 1; i < k; i++)
                            {
                                if(distances[i][0] > distances[i+1][0])
                                {
                                    aux = distances[i][0];
                                    distances[i][0] = distances[i+1][0];
                                    distances[i+1][0] = aux;

                                    aux = distances[i][1];
                                    distances[i][1] = distances[i+1][1];
                                    distances[i+1][1] = aux;

                                    aux = distances[i][2];
                                    distances[i][2] = distances[i+1][2];
                                    distances[i+1][2] = aux;

                                    aux = distances[i][3];
                                    distances[i][3] = distances[i+1][3];
                                    distances[i+1][3] = aux;

                                    found = 1;
                                }
                            }
                        }while(found);

                        
                        
                        
                        int check = 0;
                        for(int i = 1; i <= k; i++)
                        {
                            if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                            {
                                    orders[2][distances[i][2]] = distances[i][3];
                                    locations[distances[i][3]]--;
                                    check++;
                            }
                            if(check == num_o)
                                break;
                        }

                        
                        
                        
                        cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";

                        for(int i = 1; i <= num_o; i++)
                        {
                            cout<<i<<": "<<orders[2][i]<<" ";
                            road(orders[2][i], orders[0][i]);
                            road(orders[0][i], orders[1][i]);
                            cout<<"\n";
                        }
                    }
                    else
                    {
                        
                        int times = num_o / num_trucks;
                        times++;

                        int distances[num_o * num_trucks+5][4], k = 0;
                        
                        
                        
                        
                        

                        int list_of_orders[num_trucks+3];
                        
                        

                        for(int current_iteration = 1; current_iteration <= times; current_iteration++)
                        {
                            
                            k = 0;
                            for(int i = 1; i <= num_o; i++)
                            {
                                if(orders[2][i])
                                    for(int j = 1; j <= n; j++)
                                        if(locations[j])
                                        {
                                            distances[++k][0] = m[orders[0][i]][j];
                                            distances[k][1] = orders[0][i];
                                            distances[k][2] = i;
                                            distances[k][3] = j;
                                        }
                            }

                            
                            
                            int found, aux;
                            do
                            {
                                found = 0;
                                for(int i = 1; i < k; i++)
                                {
                                    if(distances[i][0] > distances[i+1][0])
                                    {
                                        aux = distances[i][0];
                                        distances[i][0] = distances[i+1][0];
                                        distances[i+1][0] = aux;

                                        aux = distances[i][1];
                                        distances[i][1] = distances[i+1][1];
                                        distances[i+1][1] = aux;

                                        aux = distances[i][2];
                                        distances[i][2] = distances[i+1][2];
                                        distances[i+1][2] = aux;

                                        aux = distances[i][3];
                                        distances[i][3] = distances[i+1][3];
                                        distances[i+1][3] = aux;

                                        found = 1;
                                    }
                                }
                            }while(found);

                            
                            int assigned_trucks;
                            if(current_iteration < times) assigned_trucks = num_trucks;
                            else assigned_trucks = num_o % num_trucks;

                            
                            
                            
                            int check = 0;
                            for(int i = 1; i <= k; i++)
                            {
                                if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                                {
                                    orders[2][distances[i][2]] = distances[i][3];
                                    locations[distances[i][3]]--;
                                    list_of_orders[++check] = distances[i][2];
                                }
                                if(check == assigned_trucks)
                                    break;
                            }

                            if(current_iteration == 1)
                                cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";


                            for(int i = 1; i <= assigned_trucks; i++)
                            {
                                cout<<(current_iteration - 1)*num_trucks + i<<", "<<list_of_orders[i]<<": "<<orders[2][list_of_orders[i]]<<" ";
                                road(orders[2][list_of_orders[i]], orders[0][list_of_orders[i]]);
                                road(orders[0][list_of_orders[i]], orders[1][list_of_orders[i]]);
                                cout<<"\n";

                                
                                locations[orders[1][list_of_orders[i]]]++;
                                
                                orders[2][list_of_orders[i]] == 0;
                            }
                        }
                    }
                }
                break;
                default:
                    cout<<"ERROR. Retastati alegerea: ";
                    goto error_tag_GER;
            }

        }
        break;
        case 3: 
        {

            
            cout<<"Numarul de orase: ";
            cin>>n;

            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    if(i == j) m[i][j] = 0;
                    else m[i][j] = 2017;

            cout<<"Introduceti lista muchii cu costuri:\n\n";

            int x = -1, y = -1, z = -1;
            while(x&&y&&z)
            {
                cin>>x>>y>>z;

                m[x][y] = m[y][x] = z;
            }

            int num_o, locations[n+2];
            
            


            
            cout<<"\nIntroduceti numarul de comenzi: ";
            cin>>num_o;

            
            
            
            int orders[3][num_o+2];

            x = y = -1;

            cout<<"Introduceti cele "<<num_o<<" comenzi dorite:\n\n";
            for(int i = 1; i <= num_o; i++)
            {
                cout<<i<<". ";
                cin>>x>>y;

                orders[0][i] = x; 
                orders[1][i] = y; 
                orders[2][i] = -1; 
            }

            x = y = -1;


            
            int num_trucks = 0; 
            int num_locs = 0;

            cout<<"\n\nIntroduceti locatii camioane:\n\n";
            for(int i = 1; i<=n; i++)
                locations[i] = 0;
            while(x)
            {
                cin>>x>>y;
                locations[x] = y;

                num_trucks += y;
                num_locs++;
            }


            

            
            
            royfloyd();

            if(num_trucks >= num_o)
            {
                int distances[num_o * num_locs+5][4], k = 0;

                
                
                
                
                
                for(int i = 1; i <= num_o; i++)
                    for(int j = 1; j <= n; j++)
                        if(locations[j])
                        {
                            distances[++k][0] = m[orders[0][i]][j];
                            distances[k][1] = orders[0][i];
                            distances[k][2] = i;
                            distances[k][3] = j;
                        }

               
               
               int found, aux;
               do
               {
                   found = 0;
                   for(int i = 1; i < k; i++)
                   {
                       if(distances[i][0] > distances[i+1][0])
                       {
                           aux = distances[i][0];
                           distances[i][0] = distances[i+1][0];
                           distances[i+1][0] = aux;

                           aux = distances[i][1];
                           distances[i][1] = distances[i+1][1];
                           distances[i+1][1] = aux;

                           aux = distances[i][2];
                           distances[i][2] = distances[i+1][2];
                           distances[i+1][2] = aux;

                           aux = distances[i][3];
                           distances[i][3] = distances[i+1][3];
                           distances[i+1][3] = aux;

                           found = 1;
                       }
                   }
               }while(found);

               
               
               
               int check = 0;
               for(int i = 1; i <= k; i++)
               {
                   if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                   {
                        orders[2][distances[i][2]] = distances[i][3];
                        locations[distances[i][3]]--;
                        check++;
                   }
                   if(check == num_o)
                       break;
               }

               
               
               
               cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";

               for(int i = 1; i <= num_o; i++)
               {
                   cout<<i<<": "<<orders[2][i]<<" ";
                   road(orders[2][i], orders[0][i]);
                   road(orders[0][i], orders[1][i]);
                   cout<<"\n";
               }
            }
            else
            {
                
                int times = num_o / num_trucks;
                times++;

                int distances[num_o * num_trucks+5][4], k = 0;
                
                
                
                
                

                int list_of_orders[num_trucks+3];
                
                

                for(int current_iteration = 1; current_iteration <= times; current_iteration++)
                {
                    
                    k = 0;
                    for(int i = 1; i <= num_o; i++)
                    {
                        if(orders[2][i])
                            for(int j = 1; j <= n; j++)
                                if(locations[j])
                                {
                                    distances[++k][0] = m[orders[0][i]][j];
                                    distances[k][1] = orders[0][i];
                                    distances[k][2] = i;
                                    distances[k][3] = j;
                                }
                    }

                    
                    
                    int found, aux;
                    do
                    {
                        found = 0;
                        for(int i = 1; i < k; i++)
                        {
                            if(distances[i][0] > distances[i+1][0])
                            {
                                aux = distances[i][0];
                                distances[i][0] = distances[i+1][0];
                                distances[i+1][0] = aux;

                                aux = distances[i][1];
                                distances[i][1] = distances[i+1][1];
                                distances[i+1][1] = aux;

                                aux = distances[i][2];
                                distances[i][2] = distances[i+1][2];
                                distances[i+1][2] = aux;

                                aux = distances[i][3];
                                distances[i][3] = distances[i+1][3];
                                distances[i+1][3] = aux;

                                found = 1;
                            }
                        }
                    }while(found);

                    
                    int assigned_trucks;
                    if(current_iteration < times) assigned_trucks = num_trucks;
                    else assigned_trucks = num_o % num_trucks;

                    
                    
                    
                    int check = 0;
                    for(int i = 1; i <= k; i++)
                    {
                        if((orders[2][distances[i][2]] < 0)&&(locations[distances[i][3]] > 0))
                        {
                            orders[2][distances[i][2]] = distances[i][3];
                            locations[distances[i][3]]--;
                            list_of_orders[++check] = distances[i][2];
                        }
                        if(check == assigned_trucks)
                            break;
                    }

                    if(current_iteration == 1)
                        cout<<"\n\n\nDrumurile de parcurs pentru rezolvarea fiecarei comenzi:\n\n";


                    for(int i = 1; i <= assigned_trucks; i++)
                    {
                        cout<<(current_iteration - 1)*num_trucks + i<<", "<<list_of_orders[i]<<": "<<orders[2][list_of_orders[i]]<<" ";
                        road(orders[2][list_of_orders[i]], orders[0][list_of_orders[i]]);
                        road(orders[0][list_of_orders[i]], orders[1][list_of_orders[i]]);
                        cout<<"\n";

                        
                        locations[orders[1][list_of_orders[i]]]++;
                        
                        orders[2][list_of_orders[i]] == 0;
                    }
                }
            }
        }
        break;
        default:
            cout<<"ERROR. Retastati alegerea: ";
            goto error_label_1;

    }
}

void royfloyd(void)
{
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
            for(int j = i+1; j <= n; j++)
                if((i!=k)&&(j!=k))
                    if(m[i][j] > m[i][k] + m[k][j])
                    {
                        m[i][j] = m[i][k] + m[k][j];
                        m[j][i] = m[i][j];
                    }
    }
}

void road(int i, int j)
{
    int k = 1, found = 0;
    while((k<=n) && (!found))
    {
        if((i!=k)&&(j!=k)&&(m[i][j] == m[i][k] + m[k][j]))
        {
            road(i,k);
            road(k,j);
            found = 1;
        }
        k++;
    }
    if(!found) cout<<j<<" ";
}

void amat(void)
{
    cout<<"\n\n";
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            cout<<"\t"<<m[i][j];
        cout<<"\n";
    }
    cout<<"\n\n";
}


