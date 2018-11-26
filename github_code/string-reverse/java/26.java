package com.ir.cs101.core.impl;

import com.ir.cs101.core.StringReverse;

public class StringReverseFactory {
  
  private static StringReverse _simpleStringReverse;
  public static final StringReverse GetSimpleStringReverse() {
    
    if(_simpleStringReverse == null) {
      _simpleStringReverse = new SimpleStringReverseImpl();
    }
    
    return _simpleStringReverse;
  }
  
  private static StringReverse _recursiveStringReverse;
  public static final StringReverse GetRecursiveStringReverse() {
    
    if(_recursiveStringReverse == null) {
      _recursiveStringReverse = new RecursiveStringReverseImpl();
    }
    
    return _recursiveStringReverse;
  }
  
  private static StringReverse _loopAndTempStringReverse;
  public static final StringReverse GetLoopAndTempStringReverse() {
    
    if(_loopAndTempStringReverse == null) {
      _loopAndTempStringReverse = new LoopAndTempStringReverseImpl();
    }
    
    return _loopAndTempStringReverse;
  }
  
}
