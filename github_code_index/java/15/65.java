package Dynamic_Programming;

public class RodCutting {

    private int[][] dpTable;
    private int lengthOfRod;
    private int[] prices;

    public RodCutting(int lengthOfRod,int[]prices){
        this.lengthOfRod=lengthOfRod;
        this.prices=prices;
        this.dpTable=new int[prices.length+1][lengthOfRod+1];

    }

    public void solve(){
        //initialize first row and cloumn to be 0
        //hence do nothing

        for(int i=1;i<prices.length;i++){
            for(int j=1;j<=lengthOfRod;j++){

                if(i<=j){
                    //we are able to make cut
                    dpTable[i][j]=Math.max(dpTable[i-1][j],prices[i-1]+dpTable[i][j-i]);
                }else{
                    dpTable[i][j]=dpTable[i-1][j];
                }


            }
        }
    }

    public void showResult(){
        System.out.println("Optimal profit:"+dpTable[prices.length-1][lengthOfRod]);
        for(int n=prices.length-1,w=lengthOfRod;n>0;--n){
            if(dpTable[n][w]!=0 && dpTable[n][w]!=dpTable[n-1][w]){
                System.out.println("we make cut:"+n+"m");
                w=w-n;
            }
        }
    }

    public static void main(String[] args){
        int lengthOfRod=5;
        int[] prices={0,2,5,7,3};

        RodCutting rodCutting=new RodCutting(lengthOfRod,prices);
        rodCutting.solve();
        rodCutting.showResult();
    }
}
