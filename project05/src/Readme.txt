Hello,

Link to demo video: https://youtu.be/XsIqX0LvcUA

This client-server program is a very simple implementation of Tic-Tac-toe.

You will simply need to create three (3) terminals.

And follow this process:

1. In the first terminal enter "make". This command will build both the "server" and "client" executable.
2. In the first terminal enter "./server 4320". You can use another port number but this worked for me in Jupyter hub.
3. In the second terminal enter "./client localhost 4320". This will start the client and it will connect to the server. It will aks for your name.
4. In the third terminal enter "./client localhost 4320". This will again ask for your name.
5. Once both clients have conncted and been given a name the server will prompt the first client for a move. Enter "1..9" to set the square.
6. The server will show the entry and ask the other client for their move.
7. This will go on until somebody wins or there is a draw.
8. Once complete the server will send command to the client to disconnect.

Notes:
- Ensure all terminals are in the same directory where the "server" and "client" executables are located.
- You can choose a different port number if "4320" is unavailable.

Have fun playing Tic-Tac-Toe!

Thanks,
Richard