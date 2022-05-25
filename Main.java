import java.util.Random;
import java.util.Scanner;

class Ball {
    int x;
    int y;
}

class SomeThreads extends Thread {
    private int ballIndex;

    SomeThreads(int ballIndex) {
        this.ballIndex = ballIndex;
    }

    @Override
    public void run() {
        System.out.println(this.currentThread().getName());
        Main.setRandom(ballIndex);
    }
}

public class Main {
    private static Ball[] balls;
    private static Random random = new Random();

    public static int setRandom(int ballIndex) {
        System.out.printf("CHILDREN %s: BEGIN!\n", ballIndex);
        synchronized (balls) {
            System.out.printf("CHILDREN %s: begin change memory\n", ballIndex);
            int prevX = balls[ballIndex].x;
            int prevY = balls[ballIndex].y;

            balls[ballIndex].x += random.nextInt(100) - 50;
            balls[ballIndex].y += random.nextInt(100) - 50;

            if (balls[ballIndex].y < 0) {
                System.out.printf("CHILDREN %s: moved FROM (%d, %d) TO (%d, %d) and DESTROYED\n",
                        ballIndex, prevX, prevY,
                        balls[ballIndex].x, balls[ballIndex].y);
                balls[ballIndex] = null;
                System.out.printf("CHILDREN %s: end memory changing \n", ballIndex);
                return 1;
            }

            System.out.printf("CHILDREN %s: moved FROM (%d, %d) TO (%d, %d)\n",
                    ballIndex, prevX, prevY,
                    balls[ballIndex].x, balls[ballIndex].y);
            System.out.printf("CHILDREN %s: end memory changing  \n", ballIndex);

            return 0;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int ballCount = 0;
        while (true) {
            System.out.print("PARENT: Enter count (1 - 10):\n");
            Scanner input = new Scanner(System.in);
            ballCount = input.nextInt();
            if (ballCount <= 10 && ballCount > 0)
                break;
            System.out.print("PARENT: Input Error!\n");
        }

        balls = new Ball[ballCount];

        for (int i = 0; i < ballCount; ++i) {
            balls[i] = new Ball();
            balls[i].y = random.nextInt(10);
            balls[i].x = random.nextInt(10);
        }

        SomeThreads[] threads = new SomeThreads[ballCount];

        for (int i = 0; i < ballCount; i++) {
            threads[i] = new SomeThreads(i);
        }

        for (SomeThreads i : threads) {
            i.start();
        }

        for (SomeThreads i : threads) {
            i.join();
        }

        System.out.print("PARENT: FINAL!\n");
    }
}

