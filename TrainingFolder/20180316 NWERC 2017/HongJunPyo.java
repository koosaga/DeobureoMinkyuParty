import java.lang.*;
import java.util.*;
import java.math.*;
public class HongJunPyo
{
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int g = sc.nextInt();
		int t = sc.nextInt();
		int a[] = new int[n + t + 1];
		int sum[] = new int[n + t + 1];
		a[0] = 0;
		for(int i=1; i<=n; i++){
			a[i] = sc.nextInt();
		}
		for(int i=n+1; i<=n+t; i++) a[i] = g;
		Arrays.sort(a);
		for(int i=1; i<=n; i++) sum[i] = sum[i-1] + a[i];
		for(int i=n+1; i<=n+t; i++) sum[i] = sum[i-1];
		BigInteger bino[][] = new BigInteger[n+t+1][n+t+1];
		BigInteger fuck[][] = new BigInteger[n+t+1][n+t+1];
		BigInteger dp[][] = new BigInteger[n+t+1][n+t+1];
		BigInteger d2[][] = new BigInteger[n+t+1][n+t+1];
		for(int i=0; i<=n+t; i++){
			for(int j=0; j<=n+t; j++){
				bino[i][j] = dp[i][j] = d2[i][j] = fuck[i][j] = 
				BigInteger.ZERO;
			}
		}
		for(int i=0; i<=n+t; i++){
			for(int j=i; j<=n+t; j++){
				fuck[i][j] = BigInteger.ONE;
				for(int k=0; k<j-i; k++){
					fuck[i][j].multiply(BigInteger.valueOf(a[j] - a[i]));
				}
			}
		}
		for(int i=0; i<=n+t; i++){
			bino[i][0] = BigInteger.ONE;
			for(int j=1; j<=i; j++){
				bino[i][j] = bino[i-1][j-1].add(bino[i-1][j]);
			}
		}
		for(int i=0; i<=n+t; i++){
			for(int j=1; j+i<=n+t; j++){
				int s = j;
				int e = j+i;
				dp[s][e] = BigInteger.ZERO;
				for(int m=s; m<=e; m++){
					BigInteger l = (s == m ? BigInteger.ONE : dp[s][m-1]);
					BigInteger r = (e == m ? BigInteger.ONE : dp[m+1][e]);
					dp[s][e] = dp[s][e].add(
						l.multiply(r).multiply(bino[e-s][m-s]).
						multiply(BigInteger.valueOf(a[m] - a[s-1])));
				}
				System.out.println(s + " " + e + " " + dp[s][e].toString());
			}
		}
		d2[0][0] = BigInteger.ONE;
		for(int i=1; i<=n+t; i++){
			d2[i][i] = dp[1][i].multiply(BigInteger.valueOf(sum[i]));
			for(int j=0; j<=t; j++){
				for(int k=1; k<=j && k<=i; k++){
					BigInteger JackBlack = BigInteger.ZERO;
					for(int l=0; l<=i-k-1; l++){
						JackBlack = JackBlack.add(d2[l][j-k]);
					}
					d2[i][j] = d2[i][j].add(
						JackBlack.multiply(dp[i-k+1][i]).
						multiply(BigInteger.valueOf(sum[i] - sum[i-k])));
				}
			}
		}
		BigInteger hongjunpyo = BigInteger.ZERO;
		for(int i=1; i<=n; i++) hongjunpyo = hongjunpyo.add(d2[i][t]);
		BigInteger gg = BigInteger.ONE;
		for(int i=1; i<=t; i++) gg = gg.multiply(BigInteger.valueOf(g));
		BigDecimal ad = new BigDecimal(hongjunpyo);
		BigDecimal bd = new BigDecimal(gg);	
		System.out.println(ad.divide(bd, 100, RoundingMode.HALF_UP).toPlainString());
	}
}
