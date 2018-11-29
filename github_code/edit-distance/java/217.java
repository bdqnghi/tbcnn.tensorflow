/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unidue.ub.api;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import org.jdom2.Element;
import org.jdom2.Namespace;
//import org.jdom2.input.SAXBuilder;
import org.mycore.common.MCRConstants;

/**
 *
 * @author Martin Grunwald
 */
public class ExportComparator {
    private final Namespace modsNS = MCRConstants.MODS_NAMESPACE;
    
    private final String ELSEVIER_URL = "http://www.elsevier.com/xml/svapi/abstract/dtd";
    private final Namespace ELSEVIER_Namespace = Namespace.getNamespace("", ELSEVIER_URL);

    private final String CE_URL = "http://www.elsevier.com/xml/ani/common";
    private final Namespace CE_Namespace = Namespace.getNamespace("ce", CE_URL);

    private final String DC_URL = "http://purl.org/dc/elements/1.1/";
    private final Namespace DC_Namespace = Namespace.getNamespace("dc", DC_URL);

    //private final String PRISM_URL = "http://prismstandard.org/namespaces/basic/2.0/";
    //private final Namespace PRISM_Namespace = Namespace.getNamespace("prism", PRISM_URL);
    
    //private final SAXBuilder saxbuilder = new SAXBuilder();

    /**
     * finds the one result out of multipleResults that matches singleResult
     *
     * @param multipleResults this element contains an export with more than one
     * result
     * @param singleResult this element contains one single result with which
     * every one of multipleResults is compared with
     * @return one of multipleResults, which matches singleResult closely null
     * otherwise
     */
    public Element getFittingElement(Element multipleResults, Element singleResult) {
        // determine export types (Scopus, Crossref...)
        String multipleResultsType = multipleResults.getName();
        String singleResultType = singleResult.getName();

        // create Article classes
        List<Article> candidateArticles = prepareMultipleArticles(multipleResults,
                multipleResultsType);
        Article compArticle = prepareSingleArticle(singleResult, singleResultType);

        // compare Articles
        for (Article art : candidateArticles) {
            art.calcLevDist(compArticle);
        }

        // determine Article with lowest Levenshtein-distance
        Collections.sort(candidateArticles);
        Article fittingArticle = candidateArticles.get(0);
        int indexOfFittingElement = fittingArticle.getPositionInFile();
        System.out.println("Position in Datei: " + indexOfFittingElement);

        // return fitting Element
        List<Element> multipleResultsChildren = multipleResults.getChild("mods", modsNS)
                .getChildren("potential-result");
        return multipleResultsChildren.get(indexOfFittingElement);
    }

    /**
     * determines the export type of multipleResults and calls methods to
     * specifically handle these
     *
     * @param multipleResults the data that was exported
     * @param resultType the export type
     * @return a List with Articles from multipleElements
     */
    private List<Article> prepareMultipleArticles(Element multipleResults,
            String resultType) {
        List<Article> multipleArticles = new LinkedList<Article>();
        // differentiate between export types
        // TODO implement other export types for multipleArticles
        if (resultType.equals("scopus-export")) {
            // collect all candidates from file
            List<Element> candidateElements = multipleResults.getChild("mods", modsNS)
                    .getChildren("potential-result");
            // create Article for every candidate
            for (Element candidateElement : candidateElements) {
                multipleArticles.add(createArticlefromScopusMulti(candidateElement));
            }
            // save their original position in the file
            for (int i = 0; i < multipleArticles.size(); i++) {
                multipleArticles.get(i).setPositionInFile(i);
            }
        }
        return multipleArticles;
    }

    /**
     * this is called if multipleElements consists of scopus-elements
     *
     * @param scopusElement one single potential result from the scopus database
     * @return Article created from scopusElement
     */
    private Article createArticlefromScopusMulti(Element scopusElement) {
        Article art = new Article();
        // extract title
        String title = scopusElement.getChild("extension", modsNS)
                .getChild("abstracts-retrieval-response", ELSEVIER_Namespace)
                .getChild("coredata", ELSEVIER_Namespace)
                .getChild("title", DC_Namespace).getText();
        art.setTitle(title);

        // extract authors
        // format: SURNAME, GIVEN-NAME
        List<Element> authorGroupElements = scopusElement.getChild("extension", modsNS)
                .getChild("abstracts-retrieval-response", ELSEVIER_Namespace)
                .getChild("item")
                .getChild("bibrecord")
                .getChild("head")
                .getChildren("author-group");
        for (Element authorGroupElement : authorGroupElements) {
            List<Element> authorElements = authorGroupElement.getChildren("author");
            for (Element authorElement : authorElements) {
                String surname = authorElement.getChild("surname", CE_Namespace).getText();
                String givenName = authorElement.getChild("given-name", CE_Namespace).getText();
                art.addAuthor(surname + ", " + givenName);
            }
        }
        return art;
    }

    /**
     * determines the export type of multipleResults and calls methods to
     * specifically handle these
     *
     * @param singleResult the data that was exported
     * @param resultType the export type
     * @return an Article from singleElements
     */
    private Article prepareSingleArticle(Element singleResult, String resultType) {
        Article article = new Article();
        // differentiate between export types
        //TODO implement other export types for singleArticles
        if (resultType.equals("crossref-export")) {
            article = createArticleFromCrossRefSingle(singleResult);
        }
        return article;
    }

    /**
     * this is called if singleElement consists of one crossRef element
     *
     * @param crossRefElement the element that every one of multipleResults is
     * compared with
     * @return Article created from crossRefElement
     */
    private Article createArticleFromCrossRefSingle(Element crossRefElement) {
        Article art = new Article();
        // extract title
        String title = crossRefElement.getChild("mods", modsNS)
                .getChild("titleInfo", modsNS)
                .getChild("title", modsNS)
                .getText();
        art.setTitle(title);

        // extract authors
        // format: SURNAME, GIVEN-NAME
        List<Element> authorElements = crossRefElement.getChild("mods", modsNS)
                .getChildren("name", modsNS);
        for (Element authorElement : authorElements) {
            art.addAuthor(authorElement.getChild("displayForm", modsNS).getText());
        }
        return art;
    }
}
