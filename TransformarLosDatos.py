#Organizar los archivos para Matlab 
import sys
import serial
import time 
#creandoUnaFuncion para crear archivos 
def creararchivo():
	archivo=open('DatosTransformados10.txt','w')
	archivo.close()

def escribir(viene):
	archivo=open('DatosTransformados10.txt','a')
	archivo.write(viene)

#crear el puerto serial donde lo voy a conectar el bluetooth
archivo=open('DatosSinTransformar.txt','r')
print(archivo)
s=archivo.readlines()
print(s)
print(len(s))#Sacar el tamaño
print(s[len(s)-1])
cuenta=0
creararchivo()

for i in range(1,len(s)):
	
	if(s[i]!='\n'):
		print('Numero')
		s[i]=s[i][:-1]
		escribir(s[i])
		if(i%3==0):
			escribir('\n')
		
		else:
			escribir(',')
	else:
		print('Espacio')
print(s)
