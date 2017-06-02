import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.lang.*;


public class MyTCPServer{
	
public static void main(String[] args) throws IOException {
	System.out.println("MyTCPServer");


int portNumber=8123;

//creation of a server socket
ServerSocket serverSocket = new ServerSocket(portNumber);
System.out.println("MyTCPServer is running at port " + serverSocket.getLocalPort());


//System.out.println("A client is connected from IP: " + clientSocket.getInetAddress().getHostAddress());

while(true){

Socket clientSocket = serverSocket.accept();
new TCPServerThread(clientSocket).start();

}

}

}

class TCPServerThread extends Thread {

	private Socket clientSocket= null;

	TCPServerThread(Socket clientSocket){

	super("TCPServerThread");
	this.clientSocket = clientSocket;
	}
	//new TCPClientThread(Socket).start();
	public void run(){

		try{
		BufferedReader in = new BufferedReader( new InputStreamReader(clientSocket.getInputStream()));


		String inputLine=in.readLine();
		String receivedData = inputLine;


			while(!inputLine.isEmpty()) {
			inputLine=in.readLine();
			receivedData += inputLine + "\n";

		}

		System.out.println("A Client is sconnected");
		System.out.println("Data received from client : " + receivedData);

		String response = "MyTCPServer\n" + (new Date()).toString() + "\n" + "You have sent: " + receivedData ;
		clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
		clientSocket.close();
}
	catch (Exception e){

		System.out.println("Exception occured");

	}


}

}

































