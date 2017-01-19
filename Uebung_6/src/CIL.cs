using System;

class BasicIO {

  public static void ReadFromCin(out bool b) {
    Console.Write("bool > ");
    String s = Console.ReadLine();
//  try {
      b = Convert.ToBoolean(s);
//  } catch (Exception e) {
//    b = false;
//  } // catch
  } // ReadFromCin

  public static void ReadFromCin(out int i) {
    Console.Write("int > ");
    String s = Console.ReadLine();
//  try {
      i = Convert.ToInt32(s);
//  } catch (Exception e) {
//    i = 0;
//  } // catch
  } // ReadFromCin

  public static void WriteToCout(bool b) {
    Console.Write(b);
  } // WriteToCout

  public static void WriteToCout(int i) {
    Console.Write(i);
  } // WriteToCout

  public static void WriteToCout(String s) {
    Console.Write(s);
  } // WriteToCout
  
  public static void WriteEndlToCout() {
    Console.WriteLine();
  } // WriteEndlToCout
  
} // BasicIO


public class CIL {

  public static void Main() {
  } // Main
  
} // CIL