/**
* Main class for first lab
* @author Alex Trigolos
* @version 1.0
* @since 2021-10-22
**/
public class Main {
	/**
	* Main function
	* @param args Params main function
	**/
    public static void main(String[] args) {
        System.out.println("Starting project");
		byte v_byte = 120;
		short v_short = 129;
		char v_char = 'a';
		int v_int = 65999;
		long v_long = 4294967296L;
		float v_float = 0.33333334f;
		double v_double = 0.3333333333333333;
		boolean v_boolean = true;
		System.out.println("This is a byte: " + v_byte);
		System.out.println("This is a short: " + v_short);
		System.out.println("This is a char: " + v_char);
		System.out.println("This is a int: " + v_int);
		System.out.println("This is a long: " + v_long);
		System.out.println("This is a float: " + v_float);
		System.out.println("This is a double: " + v_double);
		System.out.println("This is a boolean: " + v_boolean);
		for (int i = 97; i < 123; i++) {
			System.out.print((char)i + " ");
		}
		System.out.println();
		long begin = new java.util.Date().getTime();
		for (int i = 0; i < 100000000; i++){}
		long end = new java.util.Date().getTime();
		System.out.println("For int time is: " + (end - begin));
		begin = new java.util.Date().getTime();
		for (long i = 0; i < 10000000; i++){}
		end = new java.util.Date().getTime();
		System.out.println("For long time is: " + (end - begin));
		System.out.println("For long, the execution time increases");
		int[] mas = {12,43,12,-65,778,123,32,76};
		int max = Integer.MIN_VALUE;
		for (int i : mas){
			if (i > max) max = i;
		}
		System.out.println("Max in mas: " + max);
		int[][] matrix = new int[3][3];
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				matrix[i][j]=(int)Math.round(Math.random()*10);
			}
		}
		System.out.println("Normal matrix");
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println();
		}
		
		System.out.println("Transposed matrix");
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				System.out.print(matrix[j][i] + " ");
			}
			System.out.println();
		}
    }
}