package robot;

import java.io.*;
import java.net.Socket;

public class SocketClient {
    String url;
    int port;
    BufferedWriter outputStream;
    BufferedReader inputStream;
    Socket socket;

    public SocketClient(String url, int port) {
        this.url = url;
        this.port = port;
    }
    public SocketClient(String url) {
        this.url = url;
        this.port = 1212;
    }
    public SocketClient() {
        this.url = "pi.akoo.nl";
        this.port = 1212;
    }
    public void setUp() {
        try
        {
            this.socket = new Socket(this.url, this.port);
            OutputStream os = this.socket.getOutputStream();
            InputStream is = this.socket.getInputStream();
            this.outputStream = new BufferedWriter(new OutputStreamWriter(os));
            this.inputStream = new BufferedReader(new InputStreamReader(is));



        }catch(IOException e)
        {

            e.printStackTrace();
        }

    }
    public void stop() throws IOException {
        this.socket.close();
    }

    public void write(String data) throws IOException {
        this.outputStream.write(data);
        this.outputStream.newLine();
        this.outputStream.flush();
    }

    public void write(int data) throws IOException {
        this.outputStream.write(data);
        this.outputStream.flush();
    }

    public String read() throws IOException {
        return this.inputStream.readLine();
    }
}
