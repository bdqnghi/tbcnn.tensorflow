package scorer.termproject;

import java.io.IOException;
import java.util.*;

import org.galagosearch.core.parse.Document;
import org.galagosearch.core.parse.TagTokenizer;
import org.galagosearch.exercises.TermAssociationManager;

public class QueryModifier {
    final static String CLOSER = " )";
    final static String INTAPP_SCORER = "#feature:class=scorer.termproject.IntappScorer( ";

    public static String modifyQuery(String query) {
        TagTokenizer tokenizer = new TagTokenizer();
        String modQuery = query;
        StringBuffer sbuff = new StringBuffer();

        if (query.contains("#")) {
            return query;
        }

        try {
            Document tokenizeResult = tokenizer.tokenize(query);
            List<String> tokens = tokenizeResult.terms;

            TermAssociationManager termAssociationManager = TermAssociationManager.get();
            termAssociationManager.init();
            HashMap<String, Float> expandTokens = null;
            expandTokens = termAssociationManager.MakeAssoTermList(tokens.get(0));

            // If query contains one start character with hyphen, make a acronym.
            if (tokens.size() == 2 && tokens.get(0).length() == 1)
                tokens.add(tokens.get(0) + tokens.get(1).charAt(0));

            // If query contains 3 or more words, make a acronym.
            if (tokens.size() > 2 && !tokens.contains("of") && !tokens.contains("and")) {
                String initialAcronym = "";
                for (String x : tokens) {
                    initialAcronym += x.charAt(0);
                }
                tokens.add(initialAcronym);
            }

            // If query contains hyphen(-), just remove hyphen add ato token list.
            if (query.contains("-")) {
                tokens.add(query.trim().replace("-", ""));
            }

            for (String token : tokens) {
                sbuff.append("#scale:weight=");
                sbuff.append("1");
                sbuff.append("( ");
                sbuff.append(INTAPP_SCORER);
                sbuff.append(token);
                sbuff.append(CLOSER);
                sbuff.append(CLOSER);
                sbuff.append(" ");

            }
            if (expandTokens != null) {
                // Calculate whole frequency
                float freqDenominator = 0;
                for (String expandTokenKey : expandTokens.keySet()) {
                    freqDenominator += expandTokens.get(expandTokenKey);
                }

                // Expand tokens to querystring with weight by assoValue
                for (String expandTokenKey : expandTokens.keySet()) {
                    float expandTokenAssoValue = expandTokens.get(expandTokenKey);
                    float incentive = (expandTokenAssoValue / freqDenominator) * 0.15f;

                    // Check Levenshtein-Distance and add incentives.
                    if (calculateLevenshteinDistance(tokens.get(0), expandTokenKey) == 0) {
                        continue;
                    } else if (calculateLevenshteinDistance(tokens.get(0), expandTokenKey) < 2) {
                        incentive = incentive * 2;
                    }

                    sbuff.append("#scale:weight=");
                    sbuff.append(incentive);
                    sbuff.append("( ");
                    sbuff.append(INTAPP_SCORER);
                    sbuff.append(expandTokenKey);
                    sbuff.append(CLOSER);
                    sbuff.append(CLOSER);
                    sbuff.append(" ");
                }
            }
            if (sbuff.length() > 0) modQuery = sbuff.toString();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return modQuery;
    }

    /**
     * 두 문자열 사이에 Levenshtein 거리를 측정하는 함수 구현체
     *
     * @param s0 문자열 1
     * @param s1 문자열 2
     * @return Levenshtein 거리
     */
    public static int calculateLevenshteinDistance(String s0, String s1) {
        int len0 = s0.length() + 1;
        int len1 = s1.length() + 1;

        int[] cost = new int[len0];
        int[] newcost = new int[len0];

        for (int i = 0; i < len0; i++) cost[i] = i;

        for (int j = 1; j < len1; j++) {

            newcost[0] = j - 1;

            for (int i = 1; i < len0; i++) {

                int match = (s0.charAt(i - 1) == s1.charAt(j - 1)) ? 0 : 1;

                int cost_replace = cost[i - 1] + match;
                int cost_insert = cost[i] + 1;
                int cost_delete = newcost[i - 1] + 1;

                // keep minimum cost
                newcost[i] = Math.min(Math.min(cost_insert, cost_delete), cost_replace);
            }
            int[] swap = cost;
            cost = newcost;
            newcost = swap;
        }
        // the distance is the cost for transforming all letters in both strings
        return cost[len0 - 1];
    }
}