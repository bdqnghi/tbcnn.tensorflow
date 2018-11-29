// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: braces fieldsfirst space lnc 

package com.google.android.play.search;

import android.content.Context;
import android.text.SpannableString;

// Referenced classes of package com.google.android.play.search:
//            SuggestionFormatter, LevenshteinDistance

public final class LevenshteinSuggestionFormatter extends SuggestionFormatter
{

    public LevenshteinSuggestionFormatter(Context context)
    {
        super(context);
    }

    private static LevenshteinDistance.Token[] tokenize(String s)
    {
        int j = 0;
        int i1 = s.length();
        Object aobj[] = s.toCharArray();
        s = new LevenshteinDistance.Token[i1];
        int i = 0;
        int k;
        for (; j < i1; j = k)
        {
            for (; j < i1 && (aobj[j] == ' ' || aobj[j] == '\t' || aobj[j] == '"'); j++) { }
            for (k = j; k < i1 && aobj[k] != ' ' && aobj[k] != '\t' && aobj[k] != '"'; k++) { }
            if (j != k)
            {
                int l = i + 1;
                s[i] = new LevenshteinDistance.Token(((char []) (aobj)), j, k);
                i = l;
            }
        }

        aobj = new LevenshteinDistance.Token[i];
        System.arraycopy(s, 0, ((Object) (aobj)), 0, i);
        return ((LevenshteinDistance.Token []) (aobj));
    }

    protected final volatile CharSequence formatSuggestion(String s, String s1, int i, int j)
    {
        LevenshteinDistance.Token atoken[];
        LevenshteinDistance levenshteindistance;
        LevenshteinDistance.Token atoken1[];
        LevenshteinDistance.Token atoken2[];
        int ai2[][];
        int ai3[][];
        int k;
        int j2;
        int k2;
        s = tokenize(s.toLowerCase());
        atoken = tokenize(s1);
        levenshteindistance = new LevenshteinDistance(s, atoken);
        atoken1 = levenshteindistance.mSource;
        atoken2 = levenshteindistance.mTarget;
        j2 = atoken1.length;
        k2 = atoken2.length;
        ai2 = levenshteindistance.mDistanceTable;
        ai3 = levenshteindistance.mEditTypeTable;
        k = 1;
_L7:
        LevenshteinDistance.Token token1;
        int i1;
        if (k > j2)
        {
            break; /* Loop/switch isn't completed */
        }
        token1 = atoken1[k - 1];
        i1 = 1;
_L3:
        LevenshteinDistance.Token token2;
        if (i1 > k2)
        {
            break MISSING_BLOCK_LABEL_330;
        }
        token2 = atoken2[i1 - 1];
        j = token1.length();
        if (j <= token2.length()) goto _L2; else goto _L1
_L1:
        i = 0;
_L4:
        int l1;
        int i2;
        int l2;
        if (i != 0)
        {
            l1 = 0;
        } else
        {
            l1 = 1;
        }
        i2 = ai2[k - 1][i1] + 1;
        j = 0;
        l2 = ai2[k][i1 - 1];
        i = i2;
        if (l2 + 1 < i2)
        {
            i = l2 + 1;
            j = 1;
        }
        i2 = ai2[k - 1][i1 - 1];
        if (i2 + l1 < i)
        {
            i = i2 + l1;
            char ac[];
            char ac1[];
            if (l1 == 0)
            {
                j = 3;
            } else
            {
                j = 2;
            }
        }
        ai2[k][i1] = i;
        ai3[k][i1] = j;
        i1++;
        if (true) goto _L3; else goto _L2
_L2:
        l1 = token1.mStart;
        i2 = token2.mStart;
        ac = token1.mContainer;
        ac1 = token2.mContainer;
        i = 0;
_L5:
label0:
        {
            if (i >= j)
            {
                break MISSING_BLOCK_LABEL_313;
            }
            if (Character.toLowerCase(ac[l1 + i]) == Character.toLowerCase(ac1[i2 + i]))
            {
                break label0;
            }
            i = 0;
        }
          goto _L4
        i++;
          goto _L5
        i = 1;
          goto _L4
        k++;
        if (true) goto _L7; else goto _L6
_L6:
        int l = atoken.length;
        int ai1[] = new int[l];
        j = levenshteindistance.mTarget.length;
        LevenshteinDistance.EditOperation aeditoperation[] = new LevenshteinDistance.EditOperation[j];
        i = levenshteindistance.mSource.length;
        int ai[][] = levenshteindistance.mEditTypeTable;
        do
        {
            if (j > 0)
            {
                int j1 = ai[i][j];
                switch (j1)
                {
                case 0: // '\0'
                    i--;
                    break;

                case 1: // '\001'
                    j--;
                    aeditoperation[j] = new LevenshteinDistance.EditOperation(j1, i);
                    break;

                case 2: // '\002'
                case 3: // '\003'
                    j--;
                    i--;
                    aeditoperation[j] = new LevenshteinDistance.EditOperation(j1, i);
                    break;
                }
            } else
            {
                i = 0;
                while (i < l) 
                {
                    if (aeditoperation[i].mType == 3)
                    {
                        ai1[i] = aeditoperation[i].mPosition;
                    } else
                    {
                        ai1[i] = -1;
                    }
                    i++;
                }
                s1 = new SpannableString(s1);
                l = ai1.length;
                for (i = 0; i < l; i++)
                {
                    LevenshteinDistance.Token token = atoken[i];
                    j = 0;
                    int k1 = ai1[i];
                    if (k1 >= 0)
                    {
                        j = s[k1].length();
                    }
                    applyTextStyle(0x7f11015e, s1, token.mStart + j, token.mEnd);
                    applyTextStyle(0x7f11015d, s1, token.mStart, j + token.mStart);
                }

                return s1;
            }
        } while (true);
    }
}
