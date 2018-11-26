/*****************************************************************************************
                        BioQt - Integrated Bioinformatics Library
Copyright (C) 2013-2014 Usama S Erawab <alrawab@hotmail.com> Libya
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
************************************************************************************************/

#include "LevenshteinDistance.h"

namespace BioQt {


int LevenshteinDistance::GetLevenshteinDistance(const QString& s1,const QString& s2)
{
    const size_t m(s1.size());
    const size_t n(s2.size());

    if( m==0 ) return n;
    if( n==0 ) return m;

    size_t *costs = new size_t[n + 1];

    for( size_t k=0; k<=n; k++ ) costs[k] = k;

    size_t i = 0;

    for ( QString::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
    {
      costs[0] = i+1;
      size_t corner = i;

      size_t j = 0;
      for ( QString::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
      {
        size_t upper = costs[j+1];
        if( *it1 == *it2 )
        {
            costs[j+1] = corner;
        }
        else
        {
          size_t t(upper<corner?upper:corner);
          costs[j+1] = (costs[j]<t?costs[j]:t)+1;
        }

        corner = upper;
      }
    }
    size_t result = costs[n];
    delete [] costs;

    return result;
}
} // namespace BioQt
