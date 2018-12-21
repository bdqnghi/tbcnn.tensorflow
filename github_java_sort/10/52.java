package nl.hva.dmci.ict.se.datastructures.sortstudents.util;

import nl.hva.dmci.ict.se.datastructures.sortstudents.KlasGenerator;
import nl.hva.dmci.ict.se.datastructures.sortstudents.models.SortedLinkedList;
import nl.hva.dmci.ict.se.datastructures.sortstudents.models.Student;

import java.util.Comparator;
import java.util.List;


public class Bucketsort {

    public static <T> SortedLinkedList<SortedLinkedList<Student>> sort(List<T> lijst, Comparator<SortedLinkedList<T>> bucketsComparator, Comparator<T> bucketComparator){
        
        String[] klasNamen = KlasGenerator.maakKlassen(lijst.size());
        int klassenIndex = 0;

        
        for (T object : lijst) {
            if (klassenIndex == klasNamen.length) {
                klassenIndex = 0;
            }
            if (object instanceof Student){
                Student student = (Student) object;
                student.setKlas(klasNamen[klassenIndex]);
            }
            klassenIndex++;
        }

        
        SortedLinkedList<SortedLinkedList<Student>> buckets = new SortedLinkedList(bucketsComparator);

        
        for (int i = 0; i < klasNamen.length; i++) {
            SortedLinkedList<Student> bucket = new SortedLinkedList(bucketComparator);
            for (T object : lijst) {
                if (object instanceof Student){
                    Student student = (Student) object;
                    if (student.getKlas().equals(klasNamen[i])){
                        bucket.add(student);
                    }
                }

            }
            buckets.add(bucket);
        }

        return buckets;
    }
    
}
