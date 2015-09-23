package robot;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main  {
    public static void main(String[] args) {
        SocketClient sc = new SocketClient();
        sc.setUp();
        try {
			boolean running = true;
			while(running) {
				BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
				String input = inFromUser.readLine();
				if(input != "q") {
					int inputParsed = Integer.parseInt(input);
					sc.write(inputParsed);
				} else {
					running = false;
				}
			}

            sc.stop();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
