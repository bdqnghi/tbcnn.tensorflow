package algorithms_introduction.graph;

import java.util.ArrayList;

/*
    使用Ford-Fulkerson算法求取最大流
        TMD恶心
        最大流：链路中虽然是单项路径，但是要设计该路径的反向路径，设置其CF=0，F=0.
        在实际应用中，只会应用到单项路径的CF,F和其不存在的路径--反向路径的CF.
        反向路径存在的意义在于--有时候需要缩减路径上的流量以实现整体流的最大化。
        每次更新节点是，要更新单项路径和反向路径的CF、F值。。
 */
class FordFulkersonPoint{

    private Character fromC;
    private Character toC;
    private Integer f;
    private Integer cf;
    private Boolean belong;

    public Character getFromC() {
        return fromC;
    }

    public void setFromC(Character fromC) {
        this.fromC = fromC;
    }

    public Character getToC() {
        return toC;
    }

    public void setToC(Character toC) {
        this.toC = toC;
    }

    public Integer getCf() {
        return cf;
    }

    public void setCf(Integer cf) {
        this.cf = cf;
    }

    public Integer getF() {
        return f;
    }

    public void setF(Integer f) {
        this.f = f;
    }

    public Boolean getBelong() {
        return belong;
    }

    public void setBelong(Boolean belong) {
        this.belong = belong;
    }


    public FordFulkersonPoint(Character fromC, Character toC, Integer cf, Integer f, Boolean belong){
        this.fromC = fromC;
        this.toC = toC;
        this.cf = cf;
        this.f = f;
        this.belong = belong;
    }

}
public class FordFulkerson {

    public static  int max_value = 1 << 30;

    public static void main(String[] args){

        ArrayList<FordFulkersonPoint> points = new ArrayList<FordFulkersonPoint>();
        init(points);
        fordfulkerson(points);
    }

    public static void fordfulkerson(ArrayList<FordFulkersonPoint> list){

        ArrayList<Character> p;
        p = findAugmentingPath(list);
        while(p != null){
            Integer minf = max_value;
            for(int index = 0; index < p.size() - 1; index++){
                FordFulkersonPoint point = getPoint(list, p.get(index), p.get(index + 1));
                if(point.getCf() < minf)
                    minf = point.getCf();
            }
            for(int index = 0; index < p.size() - 1; index++) {
                FordFulkersonPoint point = getPoint(list, p.get(index), p.get(index + 1));
                if(point.getBelong()){

                    point.setF(point.getF() + minf);
                    point.setCf(point.getCf() - minf);
                    FordFulkersonPoint inversePoint = getPoint(list, p.get(index+1), p.get(index));
                    inversePoint.setCf(inversePoint.getCf() + minf);
                }else{
                    point.setCf(point.getCf() - minf);
                    FordFulkersonPoint inversePoint = getPoint(list, p.get(index+1), p.get(index));
                    inversePoint.setF(inversePoint.getF() - minf);
                    inversePoint.setCf(inversePoint.getCf() + minf);
                }

            }
            p = findAugmentingPath(list);
        }
        for(FordFulkersonPoint point : list){
            System.out.println(point.getFromC() + "-->" + point.getToC() + " : " + point.getCf() +", " + point.getF()
            );
        }
    }

    public static ArrayList<Character> findAugmentingPath(ArrayList<FordFulkersonPoint> list){
        ArrayList<Character> augmentingpath = new ArrayList<Character>();
        augmentingpath.add('s');
        getNext(list, augmentingpath);
        if(augmentingpath.contains('t')){
            return augmentingpath;
        }else{
            return null;
        }
    }

    public static FordFulkersonPoint getPoint(ArrayList<FordFulkersonPoint> list, Character fromC, Character toC){

        for(FordFulkersonPoint item : list){
            if(item.getFromC() == fromC && item.getToC() == toC){
                return item;
            }
        }
        return null;
    }

    public static void getNext(ArrayList<FordFulkersonPoint> list, ArrayList<Character> augmentingpath){

        Boolean flag = false;
        if(augmentingpath.contains('t')){
            return;
        }else{
            Character fromC = augmentingpath.get(augmentingpath.size() - 1);
            for(FordFulkersonPoint point : list){
                if(point.getFromC() == fromC && point.getCf() > 0){
                    flag = true;
                    if(augmentingpath.contains(point.getToC()))
                        continue;
                    augmentingpath.add(point.getToC());
                    getNext(list, augmentingpath);
                    if(augmentingpath.contains('t'))
                        return;
                    else
                        augmentingpath.remove(augmentingpath.size() -1 );
                }
            }
            if(flag == false)
                return;
        }
    }
    public static void init(ArrayList<FordFulkersonPoint> list){
        FordFulkersonPoint point;
        point = new FordFulkersonPoint('s', '1',16,0, true);
        list.add(point);
        point = new FordFulkersonPoint('1', 's',0, 0,false);
        list.add(point);
        point = new FordFulkersonPoint('s', '2',13,0, true);
        list.add(point);
        point = new FordFulkersonPoint('2', 's',0,0, false);
        list.add(point);
        point = new FordFulkersonPoint('1', '2',0,0, false);
        list.add(point);
        point = new FordFulkersonPoint('2', '1',4,0, true);
        list.add(point);
        point = new FordFulkersonPoint('1', '3',12,0, true);
        list.add(point);
        point = new FordFulkersonPoint('3', '1',0, 0,false);
        list.add(point);
        point = new FordFulkersonPoint('2', '3',0, 0,false);
        list.add(point);
        point = new FordFulkersonPoint('3', '2',9,0, true);
        list.add(point);
        point = new FordFulkersonPoint('2', '4',14,0, true);
        list.add(point);
        point = new FordFulkersonPoint('4', '2',0,0, false);
        list.add(point);
        point = new FordFulkersonPoint('3', '4',0, 0,false);
        list.add(point);
        point = new FordFulkersonPoint('4', '3',7,0, true);
        list.add(point);
        point = new FordFulkersonPoint('3', 't',20, 0,true);
        list.add(point);
        point = new FordFulkersonPoint('t', '3',0, 0,false);
        list.add(point);
        point = new FordFulkersonPoint('4', 't',4,0, true);
        list.add(point);
        point = new FordFulkersonPoint('t', '4',0, 0,false);
        list.add(point);
    }
}
