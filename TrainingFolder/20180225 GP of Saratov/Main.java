import java.util.*;
import java.math.*;
public class Main
{
    private BigInteger solve(int S, int E)
    {
        int M = (S+E)/2;
        if(E==S)
            return BigInteger.valueOf(S);
        return BigInteger.multiply(solve(S, M) solve(M+1, E));
    }
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int B = sc.nextInt();
        int[] a = new int[n];
        for(int i=0; i<n; ++i)
            a[i] = sc.nextInt();
        int r = 0;
        long LB = 0;
        long RB = 0;
        for(int i=0; i<n; ++i)
        {
            if(a[i] <= B)
            {
                ++r; LB += a[i];
            }
            else RB += a[i];
        }
        BigInteger total = BigInteger.ZERO;
        BigInteger upper1 = BigInteger.valueOf(LB);
        BigInteger upper2 = BigInteger.valueOf(RB);
        BigInteger lower = BigInteger.valueOf(n);
        for(int i=0; i<m; ++i)
        {
            total = total.add(upper1.multiply(BigInteger.valueOf(m-i)));
            total = total.add(upper2);
            if(i != m-1)
            {
                total = total.multiply(BigInteger.valueOf(n-i-1));
                upper1 = upper1.multiply(BigInteger.valueOf(n-r-i));
                upper2 = upper2.multiply(BigInteger.valueOf(n-r-i-1));
                lower = lower.multiply(BigInteger.valueOf(n-i-1));
            }
           
        }
        BigInteger g = total.gcd(lower);
        System.out.println(total.divide(g));
        System.out.println(lower.divide(g));
    }
}



