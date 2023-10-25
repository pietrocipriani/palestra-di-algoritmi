import java.io.FileInputStream;
import java.io.PrintStream;
import java.io.IOException;
import java.util.*;

class Template {

  public static void main(final String[] args) throws IOException {
    System.setIn(new FileInputStream("input.txt"));
    System.setOut(new PrintStream("output.txt"));
    final Scanner in = new Scanner(System.in);
    
    // TODO: algoritmo

    out.close(); in.close();
  }

}
