package com.twitter.sdk.android.core.internal.oauth;

import com.twitter.sdk.android.core.TwitterAuthConfig;
import com.twitter.sdk.android.core.TwitterAuthToken;
import io.fabric.sdk.android.r;
import io.fabric.sdk.android.services.network.q;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

final class b
{
  static final SecureRandom a = new SecureRandom();
  final TwitterAuthConfig b;
  final TwitterAuthToken c;
  final String d;
  final String e;
  final String f;
  final Map<String, String> g;

  public b(TwitterAuthConfig paramTwitterAuthConfig, TwitterAuthToken paramTwitterAuthToken, String paramString1, String paramString2, String paramString3, Map<String, String> paramMap)
  {
    this.b = paramTwitterAuthConfig;
    this.c = paramTwitterAuthToken;
    this.d = paramString1;
    this.e = paramString2;
    this.f = paramString3;
    this.g = paramMap;
  }

  static String a(TreeMap<String, String> paramTreeMap)
  {
    StringBuilder localStringBuilder = new StringBuilder();
    int j = paramTreeMap.size();
    paramTreeMap = paramTreeMap.entrySet().iterator();
    int i = 0;
    while (paramTreeMap.hasNext())
    {
      Map.Entry localEntry = (Map.Entry)paramTreeMap.next();
      localStringBuilder.append(q.b(q.b((String)localEntry.getKey()))).append("%3D").append(q.b(q.b((String)localEntry.getValue())));
      i += 1;
      if (i < j)
        localStringBuilder.append("%26");
    }
    return localStringBuilder.toString();
  }

  static void a(StringBuilder paramStringBuilder, String paramString1, String paramString2)
  {
    if (paramString2 != null)
      paramStringBuilder.append(' ').append(q.b(paramString1)).append("=\"").append(q.b(paramString2)).append("\",");
  }

  final String a(String paramString)
  {
    try
    {
      if (this.c != null);
      for (Object localObject = this.c.c; ; localObject = null)
      {
        localObject = q.a(this.b.b) + '&' + q.a((String)localObject);
        paramString = paramString.getBytes("UTF8");
        localObject = new SecretKeySpec(((String)localObject).getBytes("UTF8"), "HmacSHA1");
        Mac localMac = Mac.getInstance("HmacSHA1");
        localMac.init((Key)localObject);
        paramString = localMac.doFinal(paramString);
        paramString = new String(io.fabric.sdk.android.services.network.f.a(paramString, paramString.length), "UTF8");
        return paramString;
      }
    }
    catch (InvalidKeyException paramString)
    {
      io.fabric.sdk.android.f.b().c("Twitter", "Failed to calculate signature", paramString);
      return "";
    }
    catch (NoSuchAlgorithmException paramString)
    {
      io.fabric.sdk.android.f.b().c("Twitter", "Failed to calculate signature", paramString);
      return "";
    }
    catch (UnsupportedEncodingException paramString)
    {
      io.fabric.sdk.android.f.b().c("Twitter", "Failed to calculate signature", paramString);
    }
    return "";
  }
}

/* Location:           C:\crazyd\work\ustone\odm2016031702\baidu\android\nut-dex2jar.jar
 * Qualified Name:     com.twitter.sdk.android.core.internal.oauth.b
 * JD-Core Version:    0.6.2
 */