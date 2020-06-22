package elimination.cramer;

import java.util.Scanner;

public class Program {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.printf("* Cramer's Rule Algorithm\n");
        System.out.printf("* Translate: <X>x + <Y>y + <Z>z = <C>\n");
        System.out.printf("* Ctrl+C to forcefully quit\n");

        while (true) {
            Equation eq1 = new Equation(1, input);
            Equation eq2 = new Equation(2, input);
            Equation eq3 = new Equation(3, input);

            Matrix M = new Matrix(new float[][] {
                {eq1.x, eq1.y, eq1.z},
                {eq2.x, eq2.y, eq2.z},
                {eq3.x, eq3.y, eq3.z}
            });

            Matrix Mx = new Matrix(new float[][] {
                {eq1.c, eq1.y, eq1.z},
                {eq2.c, eq2.y, eq2.z},
                {eq3.c, eq3.y, eq3.z}
            });

            Matrix My = new Matrix(new float[][] {
                {eq1.x, eq1.c, eq1.z},
                {eq2.x, eq2.c, eq2.z},
                {eq3.x, eq3.c, eq3.z}
            });

            Matrix Mz = new Matrix(new float[][] {
                {eq1.x, eq1.y, eq1.c},
                {eq2.x, eq2.y, eq2.c},
                {eq3.x, eq3.y, eq3.c}
            });

            float D = M.det();
            float Dx = Mx.det();
            float Dy = My.det();
            float Dz = Mz.det();

            float x = Dx / D;
            float y = Dy / D;
            float z = Dz / D;

            System.out.printf(" --> SOLUTION (");
            System.out.printf(" x: %.2f, ", x);
            System.out.printf("y: %.2f, ", y);
            System.out.printf("z: %.2f", z);
            System.out.printf(" )\n");

            System.out.printf("Again? (y/n) ");
            char confirm = input.next().charAt(0);
            if (!(confirm == 'Y' || confirm == 'y')) {
                System.out.println("Bye ;)");
                break;
            }
        }
    }

}

public class Matrix {

    public float M11, M12, M13;
    public float M21, M22, M23;
    public float M31, M32, M33;

    public Matrix(float[][] M) {
        M11 = M[0][0]; M12 = M[0][1]; M13 = M[0][2];
        M21 = M[1][0]; M22 = M[1][1]; M23 = M[1][2];
        M31 = M[2][0]; M32 = M[2][1]; M33 = M[2][2];
    }

    public float det() {
        float M14 = M11, M15 = M12;
        float M24 = M21, M25 = M22;
        float M34 = M31, M35 = M32;

        float add = (M11 * M22 * M33) + (M12 * M23 * M34) + (M13 * M24 * M35);
        float sub = (M31 * M22 * M13) + (M32 * M23 * M14) + (M33 * M24 * M15);

        return add - sub;
    }

}

public class Equation {

    public float x, y, z, c;

    public Equation(int id, Scanner input) {
        System.out.printf(" > EQUATION #%d (X Y Z C): ", id);
        x = input.nextFloat();
        y = input.nextFloat();
        z = input.nextFloat();
        c = input.nextFloat();
    }

}
