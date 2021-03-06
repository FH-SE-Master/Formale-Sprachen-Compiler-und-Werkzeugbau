// MiniCPPSem.cs                                              HDO, 2006-08-28
// -------------
// Semantic evaluator for table-driven top-down parsing.
// Generated by Coco-2 (PGT).
//=====================================|========================================

using System;
using System.Text;

using Lex = MiniCPPLex;
using Syn = MiniCPPSyn;

public class MiniCPPSem {


  public const String MODULENAME = "MiniCPPSem";

  public static void MiniCPPSemMethod(Utils.ModuleAction action, out String moduleName) {
  //-----------------------------------|----------------------------------------
    moduleName = MODULENAME;
    switch (action) {
      case Utils.ModuleAction.getModuleName:
        return;
      case Utils.ModuleAction.initModule:
        break;
      case Utils.ModuleAction.resetModule:
        break;
      case Utils.ModuleAction.cleanupModule:
        return;
    } // switch
  } // MiniCPPSemMethod


  // *** start of global SYN and SEM declarations from ATG ***
  
  private static int stc = 0;
  	private static int mc  = 0;
  
  	public static void printResults() {
  				// it seems a line is count too much !?!
  				Console.WriteLine($"Lines of code: {MiniCPPLex.tokenLine - 1}");
  				Console.WriteLine($"Lines of statements: {stc}");
  				Console.WriteLine($"Complexity by McCabe: {1 + mc}");
  	}

  // *** end of global SYN and SEM declarations from ATG ***

  

  private static void NT_MiniCPP() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_ConstDecl();
          break;
        case 2:
          NT_VarDefOrFuncDeclOrDef();
          break;
        case 3: // SEM
          Console.WriteLine($"Lines of code:        {MiniCPPLex.tokenLine - 1}");
          																  Console.WriteLine($"Lines of statements:  {stc}");
          																  Console.WriteLine($"Complexity by McCabe: {mc}");
          														
          break;
      } // switch
    } // for
  } // NT_MiniCPP

  private static void NT_VarDefOrFuncDeclOrDef() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Type();
          break;
        case 2:
          Lex.GETidentAttr();
          break;
        case 3:
          NT_VarDef();
          break;
        case 4:
          NT_FuncHead();
          break;
        case 5:
          NT_Block();
          break;
      } // switch
    } // for
  } // NT_VarDefOrFuncDeclOrDef

  private static void NT_ConstDecl() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Type();
          break;
        case 2:
          Lex.GETidentAttr();
          break;
        case 3:
          NT_Init();
          break;
      } // switch
    } // for
  } // NT_ConstDecl

  private static void NT_Init() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETnumberAttr();
          break;
      } // switch
    } // for
  } // NT_Init

  private static void NT_VarDef() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Init();
          break;
        case 2:
          Lex.GETidentAttr();
          break;
        case 3:
          NT_Init();
          break;
      } // switch
    } // for
  } // NT_VarDef

  private static void NT_FuncHead() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_FormParList();
          break;
      } // switch
    } // for
  } // NT_FuncHead

  private static void NT_FormParList() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_FormParListRest();
          break;
        case 2:
          NT_NonVoidType();
          break;
        case 3:
          NT_FormParListRest();
          break;
      } // switch
    } // for
  } // NT_FormParList

  private static void NT_FormParListRest() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETidentAttr();
          break;
        case 2:
          NT_Type();
          break;
        case 3:
          Lex.GETidentAttr();
          break;
      } // switch
    } // for
  } // NT_FormParListRest

  private static void NT_Type() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_NonVoidType();
          break;
      } // switch
    } // for
  } // NT_Type

  private static void NT_NonVoidType() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
      } // switch
    } // for
  } // NT_NonVoidType

  private static void NT_Block() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_ConstDecl();
          break;
        case 2:
          NT_Type();
          break;
        case 3:
          Lex.GETidentAttr();
          break;
        case 4:
          NT_VarDef();
          break;
        case 5:
          NT_Stat();
          break;
      } // switch
    } // for
  } // NT_Block

  private static void NT_Stat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1: // SEM
          stc++;
          break;
        case 2:
          NT_IdentStat();
          break;
        case 3:
          NT_IfStat();
          break;
        case 4:
          NT_WhileStat();
          break;
        case 5:
          NT_BreakStat();
          break;
        case 6:
          NT_InputStat();
          break;
        case 7:
          NT_OutputStat();
          break;
        case 8:
          NT_DeleteStat();
          break;
        case 9:
          NT_ReturnStat();
          break;
        case 10:
          NT_Block();
          break;
      } // switch
    } // for
  } // NT_Stat

  private static void NT_IdentStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETidentAttr();
          break;
        case 2:
          NT_Expr();
          break;
        case 3:
          NT_Expr();
          break;
        case 4:
          NT_ActParList();
          break;
      } // switch
    } // for
  } // NT_IdentStat

  private static void NT_ActParList() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Expr();
          break;
        case 2:
          NT_Expr();
          break;
      } // switch
    } // for
  } // NT_ActParList

  private static void NT_IfStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1: // SEM
          mc++;
          break;
        case 2:
          NT_Expr();
          break;
        case 3:
          NT_Stat();
          break;
        case 4: // SEM
          mc++;
          break;
        case 5:
          NT_Stat();
          break;
      } // switch
    } // for
  } // NT_IfStat

  private static void NT_WhileStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1: // SEM
          mc++;
          break;
        case 2:
          NT_Expr();
          break;
        case 3:
          NT_Stat();
          break;
      } // switch
    } // for
  } // NT_WhileStat

  private static void NT_BreakStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
      } // switch
    } // for
  } // NT_BreakStat

  private static void NT_InputStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETidentAttr();
          break;
      } // switch
    } // for
  } // NT_InputStat

  private static void NT_OutputStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Expr();
          break;
        case 2:
          Lex.GETstringAttr();
          break;
        case 3:
          NT_Expr();
          break;
        case 4:
          Lex.GETstringAttr();
          break;
      } // switch
    } // for
  } // NT_OutputStat

  private static void NT_DeleteStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETidentAttr();
          break;
      } // switch
    } // for
  } // NT_DeleteStat

  private static void NT_ReturnStat() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Expr();
          break;
      } // switch
    } // for
  } // NT_ReturnStat

  private static void NT_Expr() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_OrExpr();
          break;
      } // switch
    } // for
  } // NT_Expr

  private static void NT_OrExpr() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_AndExpr();
          break;
        case 2:
          NT_AndExpr();
          break;
      } // switch
    } // for
  } // NT_OrExpr

  private static void NT_AndExpr() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_RelExpr();
          break;
        case 2:
          NT_RelExpr();
          break;
      } // switch
    } // for
  } // NT_AndExpr

  private static void NT_RelExpr() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_SimpleExpr();
          break;
        case 2:
          NT_SimpleExpr();
          break;
      } // switch
    } // for
  } // NT_RelExpr

  private static void NT_SimpleExpr() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Term();
          break;
        case 2:
          NT_Term();
          break;
      } // switch
    } // for
  } // NT_SimpleExpr

  private static void NT_Term() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_NotFact();
          break;
        case 2:
          NT_NotFact();
          break;
      } // switch
    } // for
  } // NT_Term

  private static void NT_NotFact() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_Fact();
          break;
      } // switch
    } // for
  } // NT_NotFact

  private static void NT_Fact() {
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          Lex.GETnumberAttr();
          break;
        case 2:
          Lex.GETidentAttr();
          break;
        case 3:
          NT_Expr();
          break;
        case 4:
          NT_ActParList();
          break;
        case 5:
          NT_Type();
          break;
        case 6:
          NT_Expr();
          break;
        case 7:
          NT_Expr();
          break;
      } // switch
    } // for
  } // NT_Fact


  public delegate void PragmaMethod();
  public static PragmaMethod[] pragmaMethods = {
      // none
    };


  public static void StartSem() {
  //-----------------------------------|----------------------------------------
    for (;;) {
      switch (Syn.Interpret()) {
        case 0:
          return;
        case 1:
          NT_MiniCPP();
          break;
      } // switch
    } // for
  } // StartSem

    
} // MiniCPPSem

// End of MiniCPPSem.cs
//=====================================|========================================