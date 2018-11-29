/*
 * Decompiled with CFR 0_110.
 * 
 * Could not load the following classes:
 *  android.content.Context
 *  java.io.File
 *  java.io.IOException
 *  java.lang.Exception
 *  java.lang.Long
 *  java.lang.NumberFormatException
 *  java.lang.Object
 *  java.lang.String
 *  java.lang.Throwable
 *  java.util.ArrayList
 *  java.util.Comparator
 *  java.util.Iterator
 *  java.util.List
 *  java.util.Locale
 *  java.util.TreeSet
 *  java.util.concurrent.CopyOnWriteArrayList
 */
package b.a.a.a.a.d;

import android.content.Context;
import b.a.a.a.a.b.i;
import b.a.a.a.a.b.k;
import b.a.a.a.a.d.c;
import b.a.a.a.a.d.d;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.TreeSet;
import java.util.concurrent.CopyOnWriteArrayList;

public abstract class b<T> {
    protected final Context a;
    protected final b.a.a.a.a.d.a<T> b;
    protected final k c;
    protected final c d;
    protected volatile long e;
    protected final List<d> f = new CopyOnWriteArrayList();
    private final int g;

    public b(Context context, b.a.a.a.a.d.a<T> a2, k k2, c c2, int n2) throws IOException {
        this.a = context.getApplicationContext();
        this.b = a2;
        this.d = c2;
        this.c = k2;
        this.e = this.c.a();
        this.g = n2;
    }

    private void a(int n2) throws IOException {
        if (!this.d.a(n2, this.c())) {
            Locale locale = Locale.US;
            Object[] arrobject = new Object[]{this.d.a(), n2, this.c()};
            String string = String.format((Locale)locale, (String)"session analytics events file is %d bytes, new event is %d bytes, this is over flush limit of %d, rolling it over", (Object[])arrobject);
            i.a(this.a, 4, "Fabric", string);
            this.d();
        }
    }

    private void b(String string) {
        for (d d2 : this.f) {
            try {
                d2.a(string);
            }
            catch (Exception var4_4) {
                i.a(this.a, "One of the roll over listeners threw an exception", (Throwable)var4_4);
            }
        }
    }

    public long a(String string) {
        String[] arrstring = string.split("_");
        if (arrstring.length != 3) {
            return 0;
        }
        try {
            long l2 = Long.valueOf((String)arrstring[2]);
            return l2;
        }
        catch (NumberFormatException var3_4) {
            return 0;
        }
    }

    protected abstract String a();

    public void a(d d2) {
        if (d2 != null) {
            this.f.add((Object)d2);
        }
    }

    public void a(T t2) throws IOException {
        byte[] arrby = this.b.a(t2);
        this.a(arrby.length);
        this.d.a(arrby);
    }

    public void a(List<File> list) {
        this.d.a(list);
    }

    protected int b() {
        return this.g;
    }

    protected int c() {
        return 8000;
    }

    /*
     * Enabled aggressive block sorting
     */
    public boolean d() throws IOException {
        String string;
        int n2 = 1;
        if (!this.d.b()) {
            string = this.a();
            this.d.a(string);
            Context context = this.a;
            Locale locale = Locale.US;
            Object[] arrobject = new Object[n2];
            arrobject[0] = string;
            i.a(context, 4, "Fabric", String.format((Locale)locale, (String)"generated new file %s", (Object[])arrobject));
            this.e = this.c.a();
        } else {
            string = null;
            n2 = 0;
        }
        this.b(string);
        return (boolean)n2;
    }

    public List<File> e() {
        return this.d.a(1);
    }

    public void f() {
        this.d.a(this.d.c());
        this.d.d();
    }

    public void g() {
        List<File> list = this.d.c();
        int n2 = this.b();
        if (list.size() <= n2) {
            return;
        }
        int n3 = list.size() - n2;
        Context context = this.a;
        Locale locale = Locale.US;
        Object[] arrobject = new Object[]{list.size(), n2, n3};
        i.a(context, String.format((Locale)locale, (String)"Found %d files in  roll over directory, this is greater than %d, deleting %d oldest files", (Object[])arrobject));
        TreeSet treeSet = new TreeSet((Comparator)new Comparator<a>(){

            public int a(a a2, a a3) {
                return (int)(a2.b - a3.b);
            }

            public /* synthetic */ int compare(Object object, Object object2) {
                return this.a((a)object, (a)object2);
            }
        });
        for (File file : list) {
            treeSet.add((Object)new a(file, this.a(file.getName())));
        }
        ArrayList arrayList = new ArrayList();
        Iterator iterator = treeSet.iterator();
        while (iterator.hasNext()) {
            arrayList.add((Object)((a)iterator.next()).a);
            if (arrayList.size() != n3) continue;
        }
        this.d.a((List<File>)arrayList);
    }

    static class a {
        final File a;
        final long b;

        public a(File file, long l2) {
            this.a = file;
            this.b = l2;
        }
    }

}

