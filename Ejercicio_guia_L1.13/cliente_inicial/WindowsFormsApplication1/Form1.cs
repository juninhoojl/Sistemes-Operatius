using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

           
        }

   
        private void button2_Click(object sender, EventArgs e)
        {

            // Endereco de onde vamos conectar
            IPAddress direc = IPAddress.Parse("10.211.55.9");
            // Porta
            IPEndPoint ipep = new IPEndPoint(direc, 9050);

            // Criamos o socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try{
                server.Connect(ipep);//Intentamos conectar el socket
                // Se pode conectar bem fica verde
                this.BackColor = Color.Green;
             

                if (Longitud.Checked){
                    // Quiere saber la longitud
                    string mensaje = "1/" + nombre.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);
                    
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    // Passaamos de string para vetor de bytes
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                    MessageBox.Show("La longitud de tu nombre es: " + mensaje);
                }else{
                    // Quiere saber si el nombre es bonito
                    string mensaje = "2/" + nombre.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    // Recebemos a resposta do servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    // Fazemos isso porque depois vem lixo
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                    if (mensaje == "SIM")
                        MessageBox.Show("Tu nombre ES bonito.");
                    else
                        MessageBox.Show("Tu nombre NO bonito. Lo siento.");

                }
             
                // Se terminó el servicio. 
                // Nos desconectamos
                this.BackColor = Color.Gray;
                server.Shutdown(SocketShutdown.Both);
                server.Close();



            }catch (SocketException){
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            } 

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }
    }
}
