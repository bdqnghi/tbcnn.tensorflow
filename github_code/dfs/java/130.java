import org.omg.CORBA.StringSeqHelper;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Created by cjames on 3/24/2014.
 */
public class Solution {
    private List<Deque<String>> _depthChunks = new ArrayList<Deque<String>>();

    private String _element = null;

    public Solution(String p_ToSolve) {
        _element = p_ToSolve;
    }

    private void searchForNestedChunks(String p_Search, int p_Depth) {
        // Trim any leading / trailing spaces for sanity
        p_Search = p_Search.trim();

        // Finding the first index of a bracket
        int pIndex = p_Search.indexOf("(");
        int bIndex = p_Search.indexOf("{");
        int qIndex = p_Search.indexOf("[");

        int firstIndex = pIndex;
        if (firstIndex == -1) {
            firstIndex = bIndex;
        }
        else if (bIndex != -1) { firstIndex = Math.min(firstIndex, bIndex); }

        if (firstIndex == -1) {
            firstIndex = qIndex;
        }
        else if (qIndex != -1) { firstIndex = Math.min(firstIndex, qIndex); }

        // If we didnt find an opener, then bomb out
        //  We are probably done searching this string
        if (firstIndex == -1) {
            getStackForDepth(p_Depth).push(p_Search);
            return;
        }

        // Get the actual bracket char, and then find its corresponding closer
        char c = p_Search.charAt(firstIndex);
        int lastIndex = p_Search.lastIndexOf(getClosingBracketCharacterFor(c));

        if (lastIndex < firstIndex) {
            throw new IllegalStateException("Mismatched closing brackets!");
        }

        // Extract that group, and recursively search for more groups
        String before = p_Search.substring(0, firstIndex).trim();
        String after = p_Search.substring(lastIndex+1).trim();
        String nested = p_Search.substring(firstIndex+1, lastIndex).trim();

        searchForNestedChunks(nested, p_Depth+1);

        p_Search = before + ' ' + after;

        searchForNestedChunks(p_Search, p_Depth);
    }

    private char getClosingBracketCharacterFor(char p_OpenBracket) {
        switch (p_OpenBracket) {
            case '(':
                return ')';

            case '{':
                return '}';

            case '[':
                return ']';

            default:
                throw new IllegalArgumentException();
        }
    }

    private Deque<String> getStackForDepth(int p_Depth) {
        while (_depthChunks.size() <= p_Depth) {
            _depthChunks.add(new ArrayDeque<String>());
        }

        return _depthChunks.get(p_Depth);
    }

    public String solve() {
        searchForNestedChunks(_element, 0);

        StringBuilder b = new StringBuilder();

        for(int depth = _depthChunks.size()-1; depth >= 0; depth--) {
            Deque<String> chunks = getStackForDepth(depth);

            while (!chunks.isEmpty()) {
                b.append(chunks.pop());
                b.append(' ');
            }

        }

        return b.toString().trim();
    }
}
