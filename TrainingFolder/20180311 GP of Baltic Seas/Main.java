import java.util.*;
import java.lang.*;
import java.math.*;
public class Main
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        BigInteger A = BigInteger(sc.nextLine());
        BigInteger B = BigInteger(sc.nextLine());
        System.out.println(A.minus(B));
        return;
    }
}
