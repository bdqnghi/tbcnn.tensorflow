package com.pro100svitlo.creditCardNfcReader.parser.apdu.a;

import com.pro100svitlo.creditCardNfcReader.iso7816emv.ITag;
import com.pro100svitlo.creditCardNfcReader.model.EmvTransactionRecord;
import com.pro100svitlo.creditCardNfcReader.parser.apdu.a;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/* compiled from: AnnotationUtils */
public final class b {
    private static final Class<? extends a>[] egS = new Class[]{EmvTransactionRecord.class};
    private static final b egT = new b();
    private final Map<String, Set<a>> egU = new HashMap();
    private final Map<String, Map<ITag, a>> map = new HashMap();

    public static b aSd() {
        return egT;
    }

    private b() {
        aSe();
    }

    private void aSe() {
        for (Class cls : egS) {
            Map hashMap = new HashMap();
            Set treeSet = new TreeSet();
            Field[] declaredFields = cls.getDeclaredFields();
            int length = declaredFields.length;
            int i = 0;
            while (i < length) {
                Field field = declaredFields[i];
                a aVar = new a();
                field.setAccessible(true);
                aVar.a(field);
                c cVar = (c) field.getAnnotation(c.class);
                if (cVar != null) {
                    aVar.a(cVar);
                    hashMap.put(aVar.aRJ(), aVar);
                    try {
                        treeSet.add((a) aVar.clone());
                    } catch (CloneNotSupportedException unused) {
                        i++;
                    }
                }
            }
            this.egU.put(cls.getName(), treeSet);
            this.map.put(cls.getName(), hashMap);
        }
    }

    public Map<String, Set<a>> aSf() {
        return this.egU;
    }

    public Map<String, Map<ITag, a>> aSg() {
        return this.map;
    }
}
