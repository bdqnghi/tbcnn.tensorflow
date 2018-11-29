package aj.algorithm.recursion;

public class EditDistance {

    public static void main(String[] args) {
        EditDistance editDistance = new EditDistance();
        System.out.println("editDistance.getEditDistance(\"Sunday\", \"Saturday\") = " + editDistance.getEditDistance("Sunday", "Saturday"));
        System.out.println("editDistance.getEditDistance(\"Saturday\", \"Sunday\") = " + editDistance.getEditDistance("Saturday", "Sunday"));
        System.out.println("editDistance.getEditDistance(null, null) = " + editDistance.getEditDistance(null, null));
        System.out.println("editDistance.getEditDistance(\"\", \"\") = " + editDistance.getEditDistance("", ""));
        System.out.println("editDistance.getEditDistance(\"\", \"Saturday\") = " + editDistance.getEditDistance("", "Saturday"));
        System.out.println("editDistance.getEditDistance(\"Sunday\", \"\") = " + editDistance.getEditDistance("Sunday", ""));
        System.out.println("editDistance.getEditDistance(\"abd\", \"abcd\") = " + editDistance.getEditDistance("abd", "abcd"));
        System.out.println("editDistance.getEditDistance(\"abcd\", \"abd\") = " + editDistance.getEditDistance("abcd", "abd"));
    }


    public int getEditDistance(String source, String target) {
        if(source == null) source = "";
        if(target == null) target = "";
        return calcEditDistance(source, target);
    }

    private int calcEditDistance(String source, String target) {
        if(source.equals(target))
            return 0;
        if(source.isEmpty()) return target.length();
        if(target.isEmpty()) return source.length();

        String sourceSubString = source.substring(1);
        String targetSubString = target.substring(1);

        if(source.charAt(0) == target.charAt(0))
                return calcEditDistance(sourceSubString, targetSubString);
        else
                return 1 + Math.min(Math.min(calcEditDistance(source, targetSubString),
                        calcEditDistance(sourceSubString, targetSubString)), calcEditDistance(sourceSubString, target));
    }
}
