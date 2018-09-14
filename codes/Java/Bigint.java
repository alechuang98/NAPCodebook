import java.math.*;
import java.util.*;

public class Bigint{
	public static void main(String arg[]){
		Scanner reader = new Scanner(System.in);
		int n;
		n = reader.nextInt();
		BigInteger D[] = new BigInteger[105];
    BigInteger v1 = BigInteger.valueOf(4839032);
    BigInteger v2 = BigInteger.valueOf(3);
    BigInteger v3 = BigInteger.valueOf(5);
    v1.add(v3);
    v1 = v1.multiply(BigInteger.valueOf(43298432));
    v1.divide(v2);
    BigInteger gd = v1.gcd(v2);
    if(v1.equals(v2)){
      System.out.println("0");
    }
    else System.out.println(v1 + "/" + v2);
	}
}
