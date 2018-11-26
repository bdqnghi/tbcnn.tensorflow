#ifndef MERGE_SORT_CPP_CPP_INCLUDED
#define MERGE_SORT_CPP_CPP_INCLUDED

template<typename T>
void algcpp_merge(T &obj, int a, int m, int b)
{
    int i,j,k;
    i=0, j=0;
    T L, R;

    while(i != m+1)
    {
        L.push_back(obj.at(i));
        i++;
    }

    while(i != b+1)
    {
        R.push_back(obj.at(i));
        i++;
    }

    for(i=0, k=a; ( i!=L.size()-1 ) && ( j!=R.size()-1 ) ; k++)
    {
        if(L.at(i) < R.at(j))
            obj.at(k)=L.at(i),
            i++;

        else
            obj.at(k)=R.at(j),
            j++;
    }

    while( i!=L.size()-1 && k != b+1 )
      {
         obj.at(k)=L.at(i);
         i++;
         k++;
      }

    while( j!=R.size()-1 && k != b+1)
     {
         obj.at(k)=R.at(j);
         j++;
         k++;
     }

}

template<typename T>
void algcpp_mg_sort(T &obj, int a, int b)
{
     if( b>a )
     {
         int m=(a+b)/2;
         algcpp_mg_sort(obj, a, m);
         algcpp_mg_sort(obj, m+1, b);

         algcpp_merge(obj, a, m, b);

     }
}


#endif // MERGE_SORT_CPP_CPP_INCLUDED
