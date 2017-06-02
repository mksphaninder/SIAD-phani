import java.io.*;
import java.net.*;
public class MyTCPClient{

public static void main(String[] args) throws IOException {

public static void main(String[] args) throws IOException {


if(args.length !=2){
	System.err.println("Usage : java MyTCPClient <host name> <port number>");
	System.exit(1);
}

String hostName = args[0];
int portNumber = Integer.parseInt(args[1]);


try{

Socket socket=new Socket(hostName, portNumber);
System.out.println("Connecetd to the server\""+hostName+"\'at port"+portNumber); 
//Print formatted representations of objects to a text-output stream
PrintWriter out= new PrintWriter(socket.getOutputStream(),true);

new TCPClientThread(socket).start();
//buffered reader to read from user input'
BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

String userInput;

while((userInput = stdIn.readLine()) !=null)
  {
   out.println(userInput);
   System.out.println("Received from server:"+ stdIn.readLine());
   String message= stdIn.readLine();
   if(message.equals("exit")){
   socket.close();
   System.exit(0);
}
  } 

}
catch(UnknownHostException e){
	System.err.println("Dont know about the host"+hostName);
	System.exit(1);
     }catch(IOException e){
	System.err.println("Couldn't get the I/O connection to "+hostName);                            
	System.exit(1);
    }

  }
}

class TCPClientThread extends Thread{

    private Socket clientSocket = null;
 
    TCPClientThread(Socket clientSocket) {
    	super("TCPClientThread");
    	this.clientSocket = clientSocket;
    }
    public void run() {
	 try {
        	BufferedReader in = new BufferedReader(
            	new InputStreamReader(clientSocket.getInputStream()));
  	
		while(true){
                	String inputLine=in.readLine();
  		while ((inputLine!=null) && !inputLine.isEmpty() && !inputLine.equals("exit")) {
      			System.out.println("received from client: " + inputLine);
      			inputLine=in.readLine();
  		}	 
  	     }	
        } catch (IOException e) {
          e.printStackTrace();
       }
   }}


