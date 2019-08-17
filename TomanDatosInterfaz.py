#Se importan todas las librerías que se utilizarán para la recepción de datos.
import sys
import serial
import time 
from tkinter import *
from tkinter import messagebox
import os
#Se crea la interfaz gráfica nombrada root
root= Tk()
root.title("Toma de Datos serial")
#Se definen las funciones para crear archivos
def creararchivo1(nombre):
	archivo=open(nombre,'w')
	archivo.close()

def escribir1(viene,nombre):
	archivo=open(nombre,'a')
	archivo.write(viene)

def creararchivo():
	archivo=open('DatosSinTransformar.txt','w')
	archivo.close()

def escribir(viene):
	archivo=open('DatosSinTransformar.txt','a')
	archivo.write(viene)

#Luego de presionar el boton esto es lo que se realiza
def SayBye():
	#Recibe el nombre del archivo
	nombreDelArchivo=nombreArchivo.get()
	#Crea el archivo de texto con el nombre escogido
	creararchivo1(nombreDelArchivo)
	#Guarda el tiempo en el que se inicio la receptcion de datos
	empezar=time.time()
# Bucle de almacenar datos
	while 1:

		time.sleep(0)
		#guarda en info los datos seriales 
		info=ser.readline()
		#Muestra cuanto tiempo va desde que empezó la recepción
		diferencia= time.time()-empezar
		#Compara si sa se llego a la trasmisión de datos de 2 minutos 
		if diferencia > 120:
			break
		#Decodifica para poder guardar los bits como texto
		valor=info.decode('utf-8', "ignore")
		#Muestra el valor de la variable
		print(info)
		#Muestra el valor decodificado para debugging
		print(valor)
		#Si hay espacios en la comunicacion serial no se guardan 
		if(info==b''):
			print("Esta en vacio")

		else:
			print(valor)
			#Escribe en el archivo de texto 
			escribir1(valor,nombreDelArchivo)
#Indica que ya se realizó la toma de datos
	myvar.configure(text=" Ya fueron tomados y guardados ",font=("BatmanForeverAlternate",20))

#crear el puerto serial donde lo voy a conectar el bluetooth
import serial.tools.list_ports
#Muestra la lista de puertos conectados
ports = list(serial.tools.list_ports.comports())
for p in ports:
    print (p)
if ports==[]:
	#si no hay puerto detectado no se inicia la interfaz gráfica
	mensaje=messagebox.showerror("Puerto Serial","No hay puerto conectado")
	print("El puerto Serial no esta conectado")
	#Termina el programa
	sys.exit(0)

else:
	print("si hay puerto")
	#Define el la variable ser el puerto serial
	ser = serial.Serial(p[0],9600,timeout=0)
#Caracteristicas de la interfaz gráfica
root.resizable(0,0)
root.geometry("700x400")
root.configure(background='white')
#Crea el botón de recepción 
sayHelloButton1=Button(root,text="Iniciar Toma de datos",command=SayBye,height=10,width=70,font=("BatmanForeverAlternate",10),bg="white",fg="grey")#medium spring green
sayHelloButton1.pack()
myvar=Label(root,fg="grey",font=("BatmanForeverAlternate",70),bg="white")
myvar.pack()
myvar0=Label(root, text = "Ingresa la frecuencia de toma de datos",fg="grey",font=("BatmanForeverAlternate",10),bg="white")
myvar0.pack()
w=Scale(root,from_=10, to=120,orient=HORIZONTAL,fg="grey",font=("BatmanForeverAlternate",10),bg="white")
w.pack()
myvar1=Label(root, text = "Ingresa el nombre del archivo con .txt",fg="grey",font=("BatmanForeverAlternate",10),bg="white")
myvar1.pack()
#Nombre del archivo donde se guardarán los datos.
nombreArchivo=Entry(root,width=30,font=("BatmanForeverAlternate",10),bg="white",fg="grey")
nombreArchivo.pack()

root.mainloop()


