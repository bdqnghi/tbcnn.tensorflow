package simulator.algorithms;

import simulator.algorithms.AlgorithmBase.AlgorithmContent;
import simulator.algorithms.AlgorithmBase.AlgorithmElement;

/**
 * Trida predstavujici zapis pseudokodu algoritmu topologickeho usporadani. 
 * @author Jakub Varadinek <jvaradinek at gmail.com>
 */
public class AlgorithmTopologicalSort extends AbstractAlgorithm{

  protected AlgorithmElement[] content = new AlgorithmElement[] {
    new AlgorithmElement(AlgorithmBase.algorithmHeadingName, new AlgorithmContent[] {      
      new AlgorithmContent(AlgorithmBase.algorithmName, "Topological-Sort"), 
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, "("),
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "G"),
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, ")"),
    }),
    new AlgorithmElement(AlgorithmBase.algorithmLineName0, new AlgorithmContent[] {      
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, "zavolej "), 
      new AlgorithmContent(AlgorithmBase.algorithmMethodsName, "DFS"), 
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, "("),
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "G"),
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, ")"),
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, " pro výpočet hodnot "), 
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "f"),
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, " ["),
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "v"),
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, "]"),
    }),
    new AlgorithmElement(AlgorithmBase.algorithmLineName0, new AlgorithmContent[] {      
      new AlgorithmContent(AlgorithmBase.algorithmOthersName, "každý dokončený uzel zařaď na začátek seznamu uzlů "), 
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "L"),
    }),
    new AlgorithmElement(AlgorithmBase.algorithmLineName0, new AlgorithmContent[] {      
      new AlgorithmContent(AlgorithmBase.algorithmKeywordsName, "return "), 
      new AlgorithmContent(AlgorithmBase.algorithmVariableName, "L"),
    }),
  };
  
  public AlgorithmTopologicalSort() {
    this.algorithmParts.add(content);
    this.algorithmParts.add(AlgorithmDfs.content1);
    this.algorithmParts.add(AlgorithmDfs.content2);
    this.addAlgorithm();
  }
  
}
