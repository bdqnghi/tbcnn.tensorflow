package sorting.ui;

import sorting.SimpleBucketSlot;
import sorting.SimpleSlot;
import sorting.Slot;
import sorting.alg.BucketSort;
import sorting.config.SlotConst;
import sorting.control.SlotGenerater;

import javax.swing.*;
import java.awt.*;


public class BucketSortPanel extends SortPanel {

    private Slot[] bucket;

    public BucketSortPanel(Slot[] slots) {
        super(slots);
        this.bucket = createBucket(10);
    }

    private Slot[] createBucket(int count){
        Slot[] b = new Slot[count];
        for (int i = 0; i < count; i++) {
            b[i] = new SimpleBucketSlot(i, 0);
        }
        return b;
    }

    @Override
    public void paint(Graphics g) {

        for (int i = 0; i < slots.length; i++) {
            g.setColor(slots[i].getColor());
            g.fillRect(slots[i].x(SlotConst.UI_START_X), slots[i].y(SlotConst.UI_START_Y), slots[i].width(), slots[i].height());
        }

        for (Slot slot : bucket) {
            drawBucket(slot, g);
        }
    }

    
    private int x;
    private int y;
    private int w;
    private int h;

    private void drawBucket(Slot slot, Graphics g){

        x = slot.x(SlotConst.UI_START_X);
        y = slot.y(SlotConst.UI_START_Y + 50);
        w = slot.width();
        h = slot.height();

        
        g.drawRect(x, y, w, h);
        g.drawString(String.valueOf(slot.getPosition()),x + SimpleBucketSlot.WIDTH_HALF-3, y);

        
        if(null != BucketSort.buckets){
            drawBucketLinked(BucketSort.buckets[slot.getPosition()], g);
        }
    }

    int offset = 0;
    private void drawBucketLinked(BucketSort.Node head, Graphics g){
        offset = y + 10;
        while (head.next!=null){
            g.drawRect(x, offset, w, h * 3);
            g.drawString(String.valueOf(head.next.data.getValue()),x + SimpleBucketSlot.WIDTH_HALF-3, offset + 10);
            head = head.next;
            offset += h * 3 + 10;
        }
    }

    public static void main(String[] args) {

        SlotGenerater g = new SlotGenerater();
        Slot[] slots = g.generate(SlotConst.SLOT_NUM);
        BucketSort bucketSort = new BucketSort();

        BucketSort.buckets = new BucketSort.Node[10];
        for (int i = 0; i < BucketSort.buckets.length; i++) {
            BucketSort.buckets[i] = new BucketSort.Node();
        }
        BucketSort.Node n1 = new BucketSort.Node();
        n1.next = null;
        n1.data = slots[10];

        BucketSort.buckets[1].next = n1;


        BucketSortPanel bucketSortPanel = new BucketSortPanel(slots);
        JFrame jFrame = new JFrame();
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jFrame.setLayout(new BorderLayout());
        jFrame.setSize(600,400);
        jFrame.add(bucketSortPanel, BorderLayout.CENTER);
        jFrame.setVisible(true);
    }

}
