




#include <stdlib.h>
#include <string.h>

#include "edit-distance.h"

#define OPTIMIZE_ED

#define COVER_TRANSPOSITION





EditDistance::EditDistance()
{
    currentelements = 2500; 
    d = (int*)malloc(sizeof(int)*currentelements);
}

EditDistance::~EditDistance()
{

    if (d) free(d);
}

#ifdef OPTIMIZE_ED
int EditDistance::CalEditDistance(const gunichar *s,const gunichar *t,const int limit)

{
    int n=0,m=0,iLenDif,k,i,j,cost;
    
    while ( *s && (*s==*t) )
    {
        s++;
		t++;
    }

	while (s[n])
	{
		n++;
	}
	while (t[m])
	{
		m++;
	}
	
    
    while ( n && m && (*(s+n-1)==*(t+m-1)) )
    {
        n--;m--;
    }
    if ( m==0 || n==0 || d==(int*)0 )
        return (m+n);
    if ( m < n )
    {
        const gunichar * temp = s;
        int itemp = n;
        s = t;
        t = temp;
        n = m;
        m = itemp;
    }
    iLenDif = m - n;
    if ( iLenDif >= limit )
        return iLenDif;
    
    n++;m++;

    if ( m*n > currentelements )
    {
        currentelements = m*n*2;    
        d = (int*)realloc(d,sizeof(int)*currentelements);
        if ( (int*)0 == d )
            return (m+n);
    }
    
    for (k=0;k<n;k++)
        d[k] = k;
    for (k=1;k<m;k++)
        d[k*n] = k;
    
    for (i=1;i<n;i++)
    {
        
        for ( j=1;j<iLenDif+i;j++ )
        {
            cost = s[i-1]==t[j-1]?0:1;
            d[j*n+i] = minimum(d[(j-1)*n+i]+1,d[j*n+i-1]+1,d[(j-1)*n+i-1]+cost);
#ifdef COVER_TRANSPOSITION
            if ( i>=2 && j>=2 && (d[j*n+i]-d[(j-2)*n+i-2]==2)
                 && (s[i-2]==t[j-1]) && (s[i-1]==t[j-2]) )
                d[j*n+i]--;
#endif
        }
        
        
        for ( k=1;k<=i;k++ )
        {
            cost = s[k-1]==t[j-1]?0:1;
            d[j*n+k] = minimum(d[(j-1)*n+k]+1,d[j*n+k-1]+1,d[(j-1)*n+k-1]+cost);
#ifdef COVER_TRANSPOSITION
            if ( k>=2 && j>=2 && (d[j*n+k]-d[(j-2)*n+k-2]==2)
                 && (s[k-2]==t[j-1]) && (s[k-1]==t[j-2]) )
                d[j*n+k]--;
#endif
        }
        
        if ( d[j*n+i] >= limit )
        {
            return d[j*n+i];
        }
    }
    
    return d[n*m-1];
}
#else
int EditDistance::CalEditDistance(const char *s,const char *t,const int limit)
{
    
    int k,i,j,n,m,cost;
    n=strlen(s); 
    m=strlen(t);
    if( n!=0 && m!=0 && d!=(int*)0 )
    {
        m++;n++;
        if ( m*n > currentelements )
        {
            currentelements = m*n*2;
            d = (int*)realloc(d,sizeof(int)*currentelements);
            if ( (int*)0 == d )
                return (m+n);
        }
        
        for(k=0;k<n;k++)
            d[k]=k;
        for(k=0;k<m;k++)
            d[k*n]=k;
        
        for(i=1;i<n;i++)
            for(j=1;j<m;j++)
            {
                
                if(s[i-1]==t[j-1])
                    cost=0;
                else
                    cost=1;
                
                d[j*n+i]=minimum(d[(j-1)*n+i]+1,d[j*n+i-1]+1,d[(j-1)*n+i-1]+cost);
#ifdef COVER_TRANSPOSITION
                if ( i>=2 && j>=2 && (d[j*n+i]-d[(j-2)*n+i-2]==2)
                     && (s[i-2]==t[j-1]) && (s[i-1]==t[j-2]) )
                    d[j*n+i]--;
#endif        
            }
        return d[n*m-1];
    }
    else 
        return (n+m);
}
#endif
